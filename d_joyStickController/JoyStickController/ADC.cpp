/*
 * ADC.cpp
 *
 * Created: 27-02-2020 20:46:23
 *  Author: troel
 */ 
#include "ADC.h"


ADConverter::ADConverter()
{
	ADMUX |= (1 << REFS0);//REF0 = Vcc
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN);//Enable, set prescaler to 128. f = 16MHz/128
}
uint16_t ADConverter::Read(uint8_t channel)
{
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	
	ADCSRA |= (1 << ADSC);
	
	while(ADCSRA & (1 << ADSC));
	return ADC;
}