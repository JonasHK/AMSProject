/* 
* PositionTranslator.h
*
* Created: 19-03-2020 11:31:54
* Author: troel
*/
#include <avr/io.h>

#ifndef __POSITIONTRANSLATOR_H__
#define __POSITIONTRANSLATOR_H__


class PositionTranslator
{
//variables
public:
protected:
private:

//functions
public:
	PositionTranslator();
	uint8_t Translate(uint16_t xPos, uint16_t yPos);
protected:
private:
bool InRange(uint16_t num, uint16_t low, uint16_t high);

}; //PositionTranslator

#endif //__POSITIONTRANSLATOR_H__
