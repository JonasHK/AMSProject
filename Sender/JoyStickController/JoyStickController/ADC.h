/*
 * ADC.h
 *
 * Created: 25-01-2020 15:34:59
 *  Author: troel
 */ 


#ifndef ADC_H_
#define ADC_H_
#include <avr/io.h>

class ADConverter
{
public:
	ADConverter();
	uint16_t Read(uint8_t channel);
private:
};



#endif /* ADC_H_ */