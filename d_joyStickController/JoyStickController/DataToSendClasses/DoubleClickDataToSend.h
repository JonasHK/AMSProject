/* 
* DoubleClickDataToSend.h
*
* Created: 19-03-2020 08:41:54
* Author: troel
*/

#include "BaseDataClass.h"
#ifndef __DOUBLECLICKDATATOSEND_H__
#define __DOUBLECLICKDATATOSEND_H__


class DoubleClickDataToSend : public BaseDataClass
{

//functions
public:
	DoubleClickDataToSend();
	virtual bool Continue();
	virtual void GetData(char* string);
protected:
private:

}; //DoubleClickDataToSend

#endif //__DOUBLECLICKDATATOSEND_H__
