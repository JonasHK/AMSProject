/*
 * pin.cpp
 *
 * Created: 27/02/2020 11.48.29
 *  Author: jonas
 */ 
#include "pin.h"

pin::pin(volatile uint8_t* DDRadr, volatile uint8_t* port, uint8_t pinno, bool input){
	if (input==false)
	{
		*DDRadr |= (1<<pinno);
	}
	else
	{
		*DDRadr &= ~(1<<pinno);
	}
	
	port_  = port;
	pinno_ = pinno;
	low();
	state_ = false;
}
// Sets the pin high
void pin::high(){
	*port_ |= 1<<pinno_;
}

// Sets the pin low
void pin::low(){
	*port_ &= ~(1<<pinno_);
}

// Read pin value
bool pin::readValue(){
	unsigned char x = (1 << pinno_);
	return ~(*port_) & x;
}