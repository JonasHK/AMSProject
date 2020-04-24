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
/*
SysTime::SysTime() {
	ovfCount_ = 0;
	TCCR1B |= (1 << CS11); //Set Prescale to 8
	TIMSK1 |= (1 << TOIE1); //Enable the Overflow Interrupt
	//Enable Interrupts
	sei();
}

SysTime* SysTime::getInstance(){
	static SysTime instance_;
	return &instance_;
}

void SysTime::Overflow() {
	ovfCount_++;
}

void SysTime::Reset() {
	ovfCount_ = 0;
	TCNT1 = 0;
}

long SysTime::Micro() { 
	return (TCNT1 / 2) + ((ovfCount_ * sizeof(ovfCount_)) / 2);
}
ISR(TIMER1_OVF_vect) {
	SysTime::getInstance()->Overflow();
}
*/

unsigned long ovfCount = 0;
void initTimer(){
	TCCR1B |= (1 << CS11); //Set Prescale to 8
	TIMSK1 |= (1 << TOIE1); //Enable the Overflow Interrupt
	TCNT1 = 0;
	//Enable Interrupts
	sei();
}

long Micro() {
	return (TCNT1 / 2) + ((ovfCount * 65534 ) / 2);
}

ISR(TIMER1_OVF_vect) {
	ovfCount++;
}