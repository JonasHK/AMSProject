/*
 * SysTime.h
 *
 * Created: 19/03/2020 11.39.12
 *  Author: jonas
 */ 
#include <stdint.h>

/*
// Implemented with Singleton design pattern
class SysTime {
	private:
	unsigned long ovfCount_;
	SysTime();
	SysTime(SysTime const&);
	void operator=(SysTime const&);
	public:
	static SysTime* getInstance();
	void Overflow();
	long Micro();
	void Reset();
};*/
#pragma once
long Micro();
void initTimer();