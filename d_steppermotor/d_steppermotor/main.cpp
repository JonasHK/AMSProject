/*
 * d_steppermotor.cpp
 *
 * Created: 27/02/2020 11.37.25
 * Author : jonas
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "d_steppermotor.h"
#include "uart.h"
#include "d_SysTime.h"

int main(void)
{
	
	/* Test of modules: uart and SysTime
	InitUART(UART0,115200,8,0);
	SysTime timer;
	while (1)
	{
		long t1 = timer.Micro();
		_delay_us(500);
		long t2 = timer.Micro();
		SendString(UART0,"t1: ");
		SendInteger(UART0,t1);
		SendString(UART0,"\n\rt2: ");
		SendInteger(UART0,t2);
		SendString(UART0,"\n\n\r");
	}
	*/
	/* Test of modules: pin, stepper;ptpr
	pin p0(&DDRB,&PORTB,0);
	pin p1(&DDRB,&PORTB,1);
	pin p2(&DDRB,&PORTB,2);
	pin p3(&DDRB,&PORTB,3);
	
	pin* pinP[] = {&p0,&p1,&p2,&p3};
	
	stepperMotor base(pinP);
	int counter = 0;
    while(1)
	{
		_delay_ms(300);
		base.rotateDegree(1);
		counter++;
		return 0;
	}
	
	while (counter<10)
	{
		_delay_ms(300);	
		base.step(true);
		counter++;
	}
	counter = 0;

	while (counter<10)
	{
		_delay_ms(300);
		base.step(false);
		counter++;
	 }
	 // Test of modules: Pin
	while (1) 
    {
		p0.low();
		p1.low();
		p2.low();
		p3.low();
		_delay_ms(300);
		p0.high();
		p1.high();
		p2.high();
		p3.high();
		_delay_ms(300);
    }
	return 0;
	*/
}

