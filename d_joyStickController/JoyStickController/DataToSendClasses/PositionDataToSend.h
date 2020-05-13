/* 
* PositionDataToSend.h
*
* Created: 19-03-2020 08:51:01
* Author: troel
*/
#include "BaseDataClass.h"
#include "../ADC.h"
#ifndef __POSITIONDATATOSEND_H__
#define __POSITIONDATATOSEND_H__




class PositionDataToSend : public BaseDataClass
{
//variables
public:
protected:
private:

//functions
public:
	PositionDataToSend();
	virtual bool Continue();
	virtual void GetData(char* string);
protected:
private:
ADConverter voltageReader;


}; //PositionDataToSend

#endif //__POSITIONDATATOSEND_H__
