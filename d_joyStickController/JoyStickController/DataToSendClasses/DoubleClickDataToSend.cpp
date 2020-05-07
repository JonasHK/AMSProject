/* 
* DoubleClickDataToSend.cpp
*
* Created: 19-03-2020 08:41:54
* Author: troel
*/


#include "DoubleClickDataToSend.h"
#include <string.h>
#include <avr/io.h>


// default constructor
DoubleClickDataToSend::DoubleClickDataToSend()
{
} //DoubleClickDataToSend

void DoubleClickDataToSend::GetData(char* string)
{
	strcpy(string, "A");
}

bool DoubleClickDataToSend::Continue()
{
	return (~PIND & (1 << 2));
}