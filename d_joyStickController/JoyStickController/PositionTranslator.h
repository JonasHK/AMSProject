/* 
* PositionTranslator.h
*
* Created: 19-03-2020 11:31:54
* Author: troel
*/
#include <avr/io.h>

#ifndef __POSITIONTRANSLATOR_H__
#define __POSITIONTRANSLATOR_H__

struct Vector{
	float x;
	float y;
};

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
float determinant(Vector v1, Vector v2);
Vector normalize(uint16_t x, uint16_t y);
uint8_t angleToData(Vector fromADC, Vector low, Vector high);

}; //PositionTranslator

#endif //__POSITIONTRANSLATOR_H__
