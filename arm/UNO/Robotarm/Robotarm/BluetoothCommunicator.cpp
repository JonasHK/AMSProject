/* 
* BluetoothCommunicator.cpp
*
* Created: 02-04-2020 11:06:56
* Author: troel
*/


#include "BluetoothCommunicator.h"
#include <stdlib.h>


// default constructor
BluetoothCommunicator::BluetoothCommunicator()
{
} //BluetoothCommunicator

bool BluetoothCommunicator::Connected()
{
	return true; //Check for high STATE pin from JDY
}
Point BluetoothCommunicator::ReadData(Point oldTargetPoint)
{
	Point toReturn = {0,0,0,0};
	SendString(UART0,"ReadData\n\r");
	char data = {ReadChar(UART0)};
	int hyp_factor = 1;
	int a_factor = 1;
	switch(data)
	{
		case '0'://left-backwards
			return calcPoint(oldTargetPoint,1*a_factor,-1*hyp_factor);
			break;
		case '1'://left
			return calcPoint(oldTargetPoint,1*a_factor,0*hyp_factor);
			break;
		case '2'://left-forward
			return calcPoint(oldTargetPoint,1*a_factor,1*hyp_factor);
			break;
		case '3'://backwards
			return calcPoint(oldTargetPoint,0*a_factor,-1*hyp_factor);
			break;
		case '4'://stay still
			toReturn.xmm_ = 0;
			toReturn.ymm_ = 0;
			toReturn.zmm_ = 0;
			break;
		case '5'://forward
			return calcPoint(oldTargetPoint,0*a_factor,1*hyp_factor);
			break;
		case '6'://right-backwards
			return calcPoint(oldTargetPoint,-1*a_factor,-1*hyp_factor);
			break;
		case '7'://right
			return calcPoint(oldTargetPoint,-1*a_factor,0*hyp_factor);
			break;
		case '8': //right-forward
			return calcPoint(oldTargetPoint,-1*a_factor,1*hyp_factor);
			break;
		case '9': //up
			toReturn.zmm_ = 1;
			break;
		case 'A': //down
			toReturn.zmm_ = -1;
			break;
		default:
			toReturn.zmm_ = 0;
			break;
			
	}
	toReturn.emm_ *= 1;
	toReturn.zmm_ *= 1;
	toReturn.ymm_ *= 1;
	toReturn.xmm_ *= 1;
	return addPoints(toReturn,oldTargetPoint);
}