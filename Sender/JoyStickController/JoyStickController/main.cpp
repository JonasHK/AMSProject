#include <avr/io.h>
#define F_CPU 16e6
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

//
#include "uart.h"
#include "ADC.h"

//Data to send to arm controller
#include "DataToSendClasses/BaseDataClass.h"
#include "DataToSendClasses/DoubleClickDataToSend.h"
#include "DataToSendClasses/SingleClickDataToSend.h"
#include "DataToSendClasses/PositionDataToSend.h"

//Timer 1 control
#define TIMER1_HIGH_VALUE 0b00001011
#define TIMER1_LOW_VALUE  0b11011100 //15540 in total, 250 ms to overflow

//Data classes for switching
BaseDataClass *dataController;
PositionDataToSend postionClass;
DoubleClickDataToSend doubleClickClass;
SingleClickDataToSend singleClickClass;


// External interrupt 0/PORTD Pin 2
void resetTimer1()
{
	TCNT1H = TIMER1_HIGH_VALUE; //Reset counter
	TCNT1L = TIMER1_LOW_VALUE;
}

bool doubleClickFlag = false;//Flag used for double click timing, not an indicator of double click
ISR(INT0_vect)
{
	if(doubleClickFlag) 
	{
		//Timer interrupted, double click
		TCCR1B &= 0b11111000; //Stop timer
		resetTimer1();
		doubleClickFlag = false;
		dataController = &doubleClickClass;
	}
	else
	{
		//Start the timer to wait for double click
		doubleClickFlag = true;
		TCCR1B = (1<<CS10) | (1<<CS11);;  // Timer mode with 64 prescaler
	}
}

// Timer 1 overflow interrupt
ISR(TIMER1_OVF_vect)
{
	//Timer timed out, single click
	TCCR1B &= 0b11111000; //Stop timer
	resetTimer1();
	doubleClickFlag = false;//No double click
	dataController = &singleClickClass;
}


int main(void)
{
	InitUART(UART0, 9600, 8, 0);
	EICRA |= 0b00000010; //Falling edge of PORTD pin 2
	EIMSK |= 1; //Enable INT0 - PORTD pin 2	
	
	DDRD = 0;
	DDRD = (0x01 << 4);
	resetTimer1();

	TCCR1A = 0x00;
	TIMSK1 = (1 << TOIE1) ;   // Enable timer1 overflow interrupt(TOIE1)
	sei();        // Enable global interrupts by setting global interrupt enable bit in SREG

	
	char buffer[20];
	while (1)
	{
		dataController = &postionClass;
		while(dataController->Continue())
		{
			dataController->GetData(buffer);
			SendString(UART0, buffer);
			_delay_ms(50);
		}
	}
	
	
	
}

