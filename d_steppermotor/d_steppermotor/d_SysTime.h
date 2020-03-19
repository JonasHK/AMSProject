/*
 * SysTime.h
 *
 * Created: 19/03/2020 11.39.12
 *  Author: jonas
 */ 
#include <stdint.h>

#ifndef SYSTIME_H_
#define SYSTIME_H_

class SysTime {
	private:
	unsigned long ovfCount_;
	public:
	SysTime();
	void Overflow();
	uint32_t Micro();
	void Reset();
};

#endif /* SYSTIME_H_ */