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
	stepperMotor(pin* stepP, pin* dirP);
	
	bool isOnPosition() const;
	int getPosition() const;
	void setPosition(int value);
	void stepToPosition(int value);
	void stepRelative(int value);
	  
	float getPositionRad() const;
	void setPositionRad(float rad);
	void stepToPositionRad(float rad);
	void stepRelativeRad(float rad);
	  
	void update();
	void rotateDegree(int16_t degrees);
	void setReductionRatio(float gearRatio, int stepsPerRev);
	void step(bool clockwice);
	protected:
	private:
	
	
	int stepperStepTargetPosition_;
	int stepperStepPosition_;
	  
	pin* stepPinP_;
	pin* dirPinP_;
	//pin enablePin_;
	  
	float radToStepFactor_;
	
	pin* pins_[4];
	unsigned char currentPin_;
	bool pinStateMEM_[4]; //= {false,false,false,false};
	bool pinStateTMP_[4]; // = {false,false,false,false};
};