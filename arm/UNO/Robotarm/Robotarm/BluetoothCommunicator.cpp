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
	char buf[2] = {ReadChar(UART0)};
	int data = atoi(buf);
	SendString(UART0,"\n\r");
	SendInteger(UART0,data);
	switch(data)
	{
		case 100://left-backwards - NOT HANDLED
			toReturn.xmm_ = 1;
			toReturn.ymm_ = -1;
			break;
		case 1://left
			return calcPoint(oldTargetPoint,1);
			break;
		case 2://left-forward - NOT HANDLED
			toReturn.xmm_ = 1;
			toReturn.ymm_ = 1;
			break;
		case 3://backwards
			toReturn.ymm_ = -1;
			break;
		case 4://stay still
			toReturn.xmm_ = 0;
			toReturn.ymm_ = 0;
			toReturn.zmm_ = 0;
			break;
		case 5://forward
			toReturn.ymm_ = 1;
			break;
		case 6://right-backwards - NOT HANDLED
			toReturn.xmm_ = -1;
			toReturn.ymm_ = -1;
			break;
		case 7://right
			return calcPoint(oldTargetPoint,-1);
			break;
		case 8: //right-forward - NOT HANDLED
			toReturn.xmm_ = -1;
			toReturn.ymm_ = 1;
			break;
		case 9: //up
			toReturn.zmm_ = 1;
			break;
		case 10: //down
			toReturn.zmm_ = -1;
			break;
		default:
			toReturn.emm_ = 0;
			toReturn.zmm_ = 0;
			toReturn.ymm_ = 0;
			toReturn.xmm_ = 0;
			break;
			
	}
	toReturn.emm_ *= 40;
	toReturn.zmm_ *= 40;
	toReturn.ymm_ *= 40;
	toReturn.xmm_ *= 40;
	return addPoints(toReturn,oldTargetPoint);
}