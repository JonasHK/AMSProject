/*
 * Robotarm.cpp
 *
 * Created: 02/04/2020 08.54.04
 * Author : jonas
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "steppermotor.h"
#include "uart.h"
#include "armGeometry.h"
#include "interpolation.h"
#include "SysTime.h"
#include "BluetoothCommunicator.h"
#include "Point.h"

void printPoint(Point p1)
{
	SendString(UART0,"Point:\n\rx: ");
	SendInteger(UART0,p1.xmm_);
	SendString(UART0,"\n\ry: ");
	SendInteger(UART0,p1.ymm_);
	SendString(UART0,"\n\rz: ");
	SendInteger(UART0,p1.zmm_);
	SendString(UART0,"\n\r");
	return;
}

int main(void)
{
	// Init
	pin X_STEP_PIN(&DDRD,&PORTD,2,false);
	pin Y_STEP_PIN(&DDRD,&PORTD,3,false);
	pin Z_STEP_PIN(&DDRD,&PORTD,4,false);
	pin X_DIR_PIN(&DDRD,&PORTD,5,false);
	pin Y_DIR_PIN(&DDRD,&PORTD,6,false);
	pin Z_DIR_PIN(&DDRD,&PORTD,7,false);
		
	stepperMotor stepperBase(&X_STEP_PIN,&X_DIR_PIN);
	stepperMotor stepperLow(&Y_STEP_PIN,&Y_DIR_PIN);
	stepperMotor stepperHigh(&Z_STEP_PIN,&Z_DIR_PIN);

	armGeometry geometry;
	Interpolation interpolator;
	BluetoothCommunicator btCom;
	
	// Setting up gearRatio
	stepperHigh.setReductionRatio(32.0 / 9.0, 200*8);  //big gear: 32, small gear: 9, steps per rev: 200*8 - 1/8th step
	stepperLow.setReductionRatio( 32.0 / 9.0, 200*8);
	stepperBase.setReductionRatio(32.0 / 9.0, 200*8);
	
	//start positions..
	stepperHigh.setPositionRad(M_PI / 2.0); //90�
	stepperLow.setPositionRad(0);			// 0�
	stepperBase.setPositionRad(0);			// 0�
	
	// Init micros(), uart and interpolation
	initTimer();
	InitUART(UART0,9600,8,0);
	Point targetPoint = {0,120,120,0};	
	interpolator.setCurrentPos(0,120,120,0);
	interpolator.setInterpolation(targetPoint,10);
	
	while (1)
	{	
		// Calc. where to be ATM
		interpolator.updateActualPosition();
		// Where to position the 3 motors
		geometry.set(interpolator.getXPosmm(), interpolator.getYPosmm(), interpolator.getZPosmm());

		stepperBase.stepToPositionRad(geometry.getRotRad());
		stepperLow.stepToPositionRad(geometry.getLowRad());
		stepperHigh.stepToPositionRad(geometry.getHighRad());
		
		stepperBase.update();
		stepperLow.update();
		stepperHigh.update();
		
		if (interpolator.isFinished())
		{
			targetPoint = btCom.ReadData(targetPoint);
			interpolator.setInterpolation(targetPoint, 100);
		}
	}
}