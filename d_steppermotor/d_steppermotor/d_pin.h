/*
 * d_pin.h
 *
 * Created: 27/02/2020 11.49.04
 *  Author: jonas
 */ 
#include <stdint.h>
#include <avr/io.h>

class pin
{
	public:
	pin(volatile uint8_t* DDRadr, volatile uint8_t* port, uint8_t pinno, bool input);
	void high();
	void low();
	bool readValue();
	protected:
	private:
	bool state_;
	volatile uint8_t* port_;
	uint8_t pinno_;
};