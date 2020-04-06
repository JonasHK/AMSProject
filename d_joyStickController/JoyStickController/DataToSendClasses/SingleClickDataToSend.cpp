/* 
* SingleClickDataToSend.cpp
*
* Created: 19-03-2020 08:28:00
* Author: troel
*/


#include "SingleClickDataToSend.h"
#include <string.h>
#include <avr/io.h>

// default constructor
SingleClickDataToSend::SingleClickDataToSend()
{
} //SingleClickDataToSend

bool SingleClickDataToSend::Continue()
{
	return (~PIND & (1 << 2));
}
void SingleClickDataToSend::GetData(char* string)
{
	string[0] = '9';
	string[1] = '\0';
}