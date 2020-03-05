/*
 * d_steppermotor.cpp
 *
 * Created: 27/02/2020 11.37.56
 *  Author: jonas
 */ 

#include "d_steppermotor.h"

stepperMotor::stepperMotor(pin** pinP){
	for (uint8_t i = 0; i<4;i++){
		pins_[i] = pinP[i];
	}
	
	pins_[0]->high();
	pinStateMEM_[0] = true;
}

void stepperMotor::step(bool clockwice){
	if (clockwice){
		for (uint8_t i = 0;i<4;i++){
			if (pinStateMEM_[i]==true){
				if (i==3){
					pins_[i]->low();
					pinStateTMP_[i] = false;
					pins_[0]->high();
					pinStateTMP_[0] = true;
				}
				else{
					pins_[i]->low();
					pinStateTMP_[i] = false;
					pins_[i+1]->high();
					pinStateTMP_[i+1] = true;
				}
			}
		}
	}
	else
	{
		for (uint8_t i = 0;i<4;i++){
			if (pinStateMEM_[i]==true){
				if (i==0)
				{
					pins_[i]->low();
					pinStateTMP_[i] = false;
					pins_[3]->high();
					pinStateTMP_[3] = true;
				}
				else{
					pins_[i]->low();
					pinStateTMP_[i] = false;
					pins_[i-1]->high();
					pinStateTMP_[i-1] = true;
				}
			}
		}
	}
	// Updating memory
	pinStateMEM_[0]=pinStateTMP_[0];
	pinStateMEM_[1]=pinStateTMP_[1];
	pinStateMEM_[2]=pinStateTMP_[2];
	pinStateMEM_[3]=pinStateTMP_[3];
}
void stepperMotor::rotateDegree(int16_t degrees){
	bool orientation = (degrees > 0 ? true : false);
	int16_t stepCount = fabs(degrees)*steps_pr_Degree;
	for (stepCount;stepCount!=0;stepCount--){
		step(orientation);
		_delay_ms(300);	
	}
}