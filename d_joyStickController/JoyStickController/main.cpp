/*
 * JoyStickController.cpp
 *
 * Created: 27-02-2020 10:37:08
 * Author : troel
 */ 
#include <avr/io.h>
#define F_CPU 16e6
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

//
#include "UART.h"
#include "ADC.h"

//Data to send to arm controller
#include "DataToSendClasses/BaseDataClass.h"


#define TIMER1_HIGH_VALUE 0b00001011
#define TIMER1_LOW_VALUE  0b11011100 //15540 in total, 250 ms 

UART sender(16e6, 9600);

uint8_t counter = 0;
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
		TCCR1B &= 0b11111000; //Stop timer
		resetTimer1();
		doubleClickFlag = false;
	}
	else
	{
		doubleClickFlag = true;
		TCCR1B = (1<<CS10) | (1<<CS11);;  // Timer mode with 64 prescler
	}
}

// Timer 1 overflow interrupt
ISR(TIMER1_OVF_vect)
{
	PORTD ^= (1 << 4);
	TCCR1B &= 0b11111000; //Stop timer
	resetTimer1();
	doubleClickFlag = false;//No double click
}


int main(void)
{
	EICRA |= 0b00000010; //Falling edge of PORTD pin 2
	EIMSK |= 1; //Enable INT0 - PORTD pin 2	
	
	
	DDRD = (0x01 << 4);
	resetTimer1();

	TCCR1A = 0x00;
	TIMSK1 = (1 << TOIE1) ;   // Enable timer1 overflow interrupt(TOIE1)
	sei();        // Enable global interrupts by setting global interrupt enable bit in SREG
    while (1) 
    {
    }
}

