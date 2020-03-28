/*
 * SysTime.cpp
 *
 * Created: 19/03/2020 11.39.01
 *  Author: jonas
 */ 

#define F_CPU 16000000
#include <stdio.h>
#include <avr/interrupt.h>
#include "d_SysTime.h"

/*
* Constructor, Initializes the System Timer for keeping track
* of the time since start.
*/
SysTime::SysTime() {
	ovfCount_ = 0;
	TCCR4B |= (1 << CS41); //Set Prescale to 8
	TIMSK4 |= (1 << TOIE4); //Enable the Overflow Interrupt
	//Enable Interrupts
	sei();
}
/**
* Increase the Overflow count
*/
void SysTime::Overflow() {
	ovfCount_++;
}
/**
* Resets the SystemTimer
*/
void SysTime::Reset() {
	ovfCount_ = 0;
	TCNT4 = 0;
}
/**
* Returns the number of Microseconds since start
*/
long SysTime::Micro() { 
	return (TCNT4 / 2) + ((ovfCount_ * sizeof(ovfCount_)) / 2);
}
SysTime sysTime;
ISR(TIMER4_OVF_vect) {
	sysTime.Overflow();
}