/* 
* BluetoothCommunicator.h
*
* Created: 02-04-2020 11:06:56
* Author: troel
*/



#ifndef __BLUETOOTHCOMMUNICATOR_H__
#define __BLUETOOTHCOMMUNICATOR_H__
#include "UART.h"

struct Point {
	float xmm_;
	float ymm_;
	float zmm_;
	float emm_;
};

class BluetoothCommunicator
{

//functions
public:
	BluetoothCommunicator();
	bool Connected();
	Point ReadData();
protected:
private:
	UART bluetoothModule;

}; //BluetoothCommunicator

#endif //__BLUETOOTHCOMMUNICATOR_H__
