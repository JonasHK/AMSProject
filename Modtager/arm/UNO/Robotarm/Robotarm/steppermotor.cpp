/*
 * d_steppermotor.cpp
 *
 * Created: 27/02/2020 11.37.56
 *  Author: jonas
 */ 

#include "steppermotor.h"
#include "uart.h"

stepperMotor::stepperMotor(pin* stepP, pin* dirP){
	stepPinP_ = stepP;
	dirPinP_ = dirP;
}

bool stepperMotor::isOnPosition() const {
	return stepperStepPosition_ == stepperStepTargetPosition_;
}

int stepperMotor::getPosition() const {
	return stepperStepPosition_;
}

void stepperMotor::setPosition(int value) {
	stepperStepPosition_ = value;
	stepperStepTargetPosition_ = value;
}

void stepperMotor::stepToPosition(int value) {
	stepperStepTargetPosition_ = value;
}

void stepperMotor::stepRelative(int value) {
	value += stepperStepPosition_;
	stepToPosition(value);
}

float stepperMotor::getPositionRad() const {
	return stepperStepPosition_ / radToStepFactor_;
}

void stepperMotor::setPositionRad(float rad) {
	setPosition(rad * radToStepFactor_);
}

void stepperMotor::stepToPositionRad(float rad) {
	stepperStepTargetPosition_ = rad * radToStepFactor_;
}

void stepperMotor::stepRelativeRad(float rad) {
	stepRelative(rad * radToStepFactor_);
}

void stepperMotor::update() {
	while (stepperStepTargetPosition_ < stepperStepPosition_) {
		dirPinP_->high();
		_delay_us(5);
		stepPinP_->high();
		_delay_us(250);
		stepPinP_->low();
		_delay_us(250);
		stepperStepPosition_--;

	}
	while (stepperStepTargetPosition_ > stepperStepPosition_) {
		dirPinP_->low();
		_delay_us(5);
		stepPinP_->high();
		_delay_us(500);
		stepPinP_->low();
		_delay_us(500);
		stepperStepPosition_++;
	}
}

void stepperMotor::setReductionRatio(float gearRatio, int stepsPerRev) {
	radToStepFactor_ = gearRatio * stepsPerRev / 2 / M_PI;
};

void stepperMotor::step(bool clockwise){
	unsigned char increment = clockwise ? 1 : -1;
	uint8_t nextPin = (currentPin_ + increment) % 4;
	pins_[currentPin_]->low();
	pins_[nextPin]->high();
	currentPin_ = nextPin;
	/*
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
	*/
}
/*
void stepperMotor::rotateDegree(int16_t degrees){
	bool orientation = (degrees > 0 ? true : false);
	for (int16_t stepCount = fabs(degrees)*steps_pr_Degree;stepCount!=0;stepCount--){
		step(orientation);
		_delay_ms(300);	
	}
}
*/