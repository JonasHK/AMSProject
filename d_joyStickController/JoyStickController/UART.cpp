/*
 * UART.cpp
 *
 * Created: 27-02-2020 20:43:18
 *  Author: troel
 */ 
#include "UART.h"

UART::UART(uint32_t fcpu, uint32_t BAUDRATE)
{
	UBRR0 = fcpu/16/BAUDRATE-1; //Sets the Baudrate
	
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); //Enables input and output
	UCSR0C = (3<<UCSZ00); 	//Set communication as 8bit(And 1 stop bit is default.)
	
	Write("Initialized\n");
	//Test

}
uint8_t UART::Write(const char* string)
{
	uint16_t i = 0;
	
	while(*(string + i) != '\0')
	{
		sendChar(*(string + i));
		++i;
	}
	
	return 0;
}
char* UART::WaitForReceive()
{
	static char line[40];
	uint8_t i = 0;
	while(1)
	{
		line[i] = getChar();
		if(line[i] == 13)
		break;
		
		++i;
	}
	Write("\n");
	return line;
}
uint8_t UART::sendChar(char c)
{
	if (c == '\n')
	{
		sendChar('\r');
	}
	while (!(UCSR0A & (1<<UDRE0))); //waits between transmissions
	UDR0 = c; //Sends the UART transmission
	return 0;
}
char UART::getChar()
{
	while(!(UCSR0A & (1<<RXC0)));
	char udr = UDR0;
	UDR0 = udr;
	return (udr);
}

void UART::SendNewLine()
{
	sendChar(13);
}