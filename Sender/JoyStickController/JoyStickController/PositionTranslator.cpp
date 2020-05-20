/* 
* PositionTranslator.cpp
*
* Created: 19-03-2020 11:31:54
* Author: troel
*/


#include "PositionTranslator.h"
#include <avr/io.h>
#include <math.h>

#define COS_TURN 0.7071
#define SIN_TURN COS_TURN //sin(45 deg) cos(45deg)

static uint8_t dataArray[] = {7, 8, 5, 2, 1, 0, 3, 6};
	
#include "uart.h"

// default constructor
PositionTranslator::PositionTranslator()
{
} //PositionTranslator

uint8_t PositionTranslator::Translate(uint16_t xPos, uint16_t yPos)
{
	Vector highStart = {0.9239, 0.3827};//22.5 degree from x-axis
	Vector lowStart = {0.9239, -0.3827};//-22.5 degree from x-axis
	
	Vector fromADC = normalize(xPos, yPos);
	
	if(length(fromADC) >= 0.4)
		return angleToData(fromADC, lowStart, highStart); 
	else
		return 4;
}

float PositionTranslator::determinant(Vector v1, Vector v2)
{
	return v1.x*v2.y - v2.x*v1.y;
}

Vector PositionTranslator::normalize(uint16_t x, uint16_t y)
{
	Vector result;
	result.x = ((y-512.0)/512.0);
	result.y = ((x-512.0)/512.0);
	return result;			
}
uint8_t PositionTranslator::angleToData(Vector fromADC, Vector low, Vector high)
{
	static int i = 0;

	if(determinant(low, fromADC) > 0 && determinant(high, fromADC) < 0)
	{
		char toReturn = dataArray[i];
		i = 0;
		return toReturn;
	}
	else
	{
		low.x = high.x*COS_TURN-high.y*SIN_TURN;
		low.y = high.x*SIN_TURN+high.y*COS_TURN;
		i++;
		return angleToData(fromADC, high, low);
	}
}

float PositionTranslator::length(Vector v)
{
	return sqrt((v.x*v.x)+(v.y*v.y));
}