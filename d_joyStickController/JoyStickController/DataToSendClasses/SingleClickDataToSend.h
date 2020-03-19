/* 
* SingleClickDataToSend.h
*
* Created: 19-03-2020 08:28:00
* Author: troel
*/


#ifndef __SINGLECLICKDATATOSEND_H__
#define __SINGLECLICKDATATOSEND_H__


class SingleClickDataToSend : public BaseDataClass
{

//functions
public:
	SingleClickDataToSend();
	virtual bool Continue();
	virtual void GetData(char* string);
protected:
private:

}; //SingleClickDataToSend

#endif //__SINGLECLICKDATATOSEND_H__
