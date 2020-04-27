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
	pins_[1]->low();
	pins_[2]->low();
	pins_[3]->low();
	currentPin_ = 0;
	pinStateMEM_[0] = true;
	pinStateMEM_[1] = false;
	pinStateMEM_[2] = false;
	pinStateMEM_[3] = false;
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
		step(true);
		/*
		digitalWrite(dirPin, HIGH);
		delayMicroseconds(5);
		digitalWrite(stepPin, HIGH);
		delayMicroseconds(20);
		digitalWrite(stepPin, LOW);
		delayMicroseconds(5);*/
		stepperStepPosition_--;
		_delay_ms(5);
	}
	while (stepperStepTargetPosition_ > stepperStepPosition_) {
		step(false);
		/*
		digitalWrite(dirPin, LOW);
		delayMicroseconds(5);
		digitalWrite(stepPin, HIGH);
		delayMicroseconds(20);
		digitalWrite(stepPin, LOW);
		delayMicroseconds(5);*/
		stepperStepPosition_++;
		_delay_ms(5);
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
void stepperMotor::rotateDegree(int16_t degrees){
	bool orientation = (degrees > 0 ? true : false);
	for (int16_t stepCount = fabs(degrees)*steps_pr_Degree;stepCount!=0;stepCount--){
		step(orientation);
		_delay_ms(300);	
	}
}