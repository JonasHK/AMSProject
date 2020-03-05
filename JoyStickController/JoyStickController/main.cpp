/*
 * JoyStickController.cpp
 *
 * Created: 27-02-2020 10:37:08
 * Author : troel
 */ 

#include <avr/io.h>
#define F_CPU 16e6
#include <util/delay.h>
#include "UART.h"
#include "ADC.h"

int main(void)
{
	ADConverter adcx(0);
    /* Replace with your application code */
	UART sender(16e6, 9600);
    while (1) 
    {
		adcx.Read();
		sender.Write("Hello");
		_delay_ms(500);
    }
}

