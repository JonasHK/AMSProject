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
	ADConverter(uint8_t channel);
	uint16_t Read();
private:
	uint8_t ADCChannel;	
};



#endif /* ADC_H_ */