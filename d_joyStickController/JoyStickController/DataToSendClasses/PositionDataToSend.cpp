/* 
* PositionDataToSend.cpp
*
* Created: 19-03-2020 08:51:01
* Author: troel
*/


#include "PositionDataToSend.h"
#include "../PositionTranslator.h"
#include <string.h>
#include <stdio.h>

// default constructor
PositionDataToSend::PositionDataToSend()
{
} //PositionDataToSend

bool PositionDataToSend::Continue()
{
	return true;
}

void PositionDataToSend::GetData(char* string)
{
	uint16_t xPos = voltageReader.Read(0);
	uint16_t yPos = voltageReader.Read(1);
	
	PositionTranslator t;
	
	string[0] = t.Translate(xPos, yPos);
	string[1] = '\0';
}
