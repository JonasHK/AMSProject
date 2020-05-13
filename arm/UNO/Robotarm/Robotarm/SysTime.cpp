/*
 * SysTime.cpp
 *
 * Created: 19/03/2020 11.39.01
 *  Author: jonas
 */ 
#define F_CPU 16000000
#include <stdio.h>
#include <avr/interrupt.h>
#include "SysTime.h"
// Zero overflows at beginning
unsigned long overflowCount = 0;

// When timer1, which is a 16-bit timer, overflows, count one up
ISR(TIMER1_OVF_vect) {
	overflowCount++;
}

void initTimer(){
	TCCR1B |= (1 << CS11); // Set the prescale to 8
	TIMSK1 |= (1 << TOIE1); //Enable the Overflow Interrupt
	TCNT1 = 0; //Resetting the counter
	//Enable global interrupts
	sei();
}

long Micro() {
	// When dividing with 2, and having a prescaler of 8 give: 
	// 16*10^6 / 16 = 1*10^6, which is 1MHz. 
	// One period equals 1 µsec.
	return (TCNT1 / 2) + ((overflowCount * 65534 ) / 2);
}