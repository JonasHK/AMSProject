/*
 * UART.h
 *
 * Created: 30-11-2019 10:02:46
 *  Author:
 */ 


#ifndef UART_H_
#define UART_H_
#include <avr/interrupt.h>


class UART
{
public:
	UART(uint32_t fcpu, uint32_t BAUDRATE);
	uint8_t Write(const char* string);
	char* WaitForReceive();
	
private:
	uint8_t sendChar(char c);
	char getChar();
};




#endif /* UART_H_ */