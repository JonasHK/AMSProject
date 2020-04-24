/* 
* BluetoothCommunicator.h
*
* Created: 02-04-2020 11:06:56
* Author: troel
*/



#ifndef __BLUETOOTHCOMMUNICATOR_H__
#define __BLUETOOTHCOMMUNICATOR_H__
#include "uart.h"
#include "Point.h"


class BluetoothCommunicator
{

//functions
public:
	BluetoothCommunicator();
	bool Connected();
	Point ReadData(Point P);
protected:
private:

}; //BluetoothCommunicator

#endif //__BLUETOOTHCOMMUNICATOR_H__
