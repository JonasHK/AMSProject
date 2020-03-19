/* 
* BaseDataClass.h
*
* Created: 19-03-2020 08:23:31
* Author: troel
*/


#ifndef __BASEDATACLASS_H__
#define __BASEDATACLASS_H__


class BaseDataClass
{

//functions
public:
	BaseDataClass();
	virtual bool Continue();
	virtual void GetData(char* string) = 0;
protected:
private:

}; //BaseDataClass

#endif //__BASEDATACLASS_H__
