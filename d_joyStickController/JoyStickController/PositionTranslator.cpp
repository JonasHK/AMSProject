/* 
* PositionTranslator.cpp
*
* Created: 19-03-2020 11:31:54
* Author: troel
*/


#include "PositionTranslator.h"
#include <avr/io.h>

// default constructor
PositionTranslator::PositionTranslator()
{
} //PositionTranslator

uint8_t PositionTranslator::Translate(uint16_t xPos, uint16_t yPos)
{
	uint16_t mappedProduct = (xPos*2)+(yPos*5);
	
	if(InRange(mappedProduct, 0, 400))
		return 0;
	else if (InRange(mappedProduct,954, 1054))
		return 1;
	else if(InRange(mappedProduct, 1946, 2150))
		return 2;
	else if(InRange(mappedProduct, 2385, 2636))
		return 3;
	else if(InRange(mappedProduct, 3338, 3690))
		return 4;
	else if(InRange(mappedProduct, 4330, 4786))
		return 5;
	else if(InRange(mappedProduct, 4864, 5376))
		return 6;
	else if(InRange(mappedProduct, 5818, 6430))
		return 7;
	else if(InRange(mappedProduct, 6810, 7526))
		return 7;
	else
		return 4;
	
}

float PositionTranslator::determinant(Vector v1, Vector v2)
{
	
}

Vector PositionTranslator::normalize(uint16_t x, uint16_t y)
{
	
}
uint8_t PositionTranslator::angleToData(Vector fromADC, Vector low, Vector high)
{
	
}