/*
 * d_steppermotor.h
 *
 * Created: 27/02/2020 11.38.43
 *  Author: jonas
 */ 

#include <math.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "d_pin.h"
#define steps_pr_Degree 11


class stepperMotor
{
	public:
	stepperMotor(pin** pinP);
	
	void step(bool clockwice);
	void rotateDegree(int16_t degrees);

	protected:
	private:
	pin* pins_[4];
	bool pinStateMEM_[4] = {false,false,false,false};
	bool pinStateTMP_[4] = {false,false,false,false};
};