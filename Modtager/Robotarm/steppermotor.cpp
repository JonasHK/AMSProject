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
