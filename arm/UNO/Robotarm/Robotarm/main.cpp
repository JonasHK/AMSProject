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
#include "d_steppermotor.h"
#include "uart.h"
#include "armGeometry.h"
#include "c_interpolation.h"
#include "d_SysTime.h"
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
	
	//pin* pinBase[] = {};
	//pin* pinLow[] = {};
	//pin* pinHigh[] = {};
		
	stepperMotor stepperBase(&X_STEP_PIN,&X_DIR_PIN);
	stepperMotor stepperLow(&Y_STEP_PIN,&Y_DIR_PIN);
	stepperMotor stepperHigh(&Z_STEP_PIN,&Z_DIR_PIN);

	armGeometry geometry;
	Interpolation interpolator;
	
	stepperHigh.setReductionRatio(32.0 / 9.0, 200);  //big gear: 32, small gear: 9, steps per rev: 200,
	stepperLow.setReductionRatio( 32.0 / 9.0, 200);
	stepperBase.setReductionRatio(32.0 / 9.0, 200);
	
	//start positions..
	stepperHigh.setPositionRad(M_PI / 2.0); //90°
	stepperLow.setPositionRad(0);			// 0°
	stepperBase.setPositionRad(0);			// 0°
	
	// Init interpolation and uart
	initTimer();
	InitUART(UART0,9600,8,0);
	interpolator.setCurrentPos(0,120,120,0);
	//interpolator.setInterpolation(0,120,120,0, 0,120,120,0);
	Point targetPoint = {0,120,120,0};
	
	
	//Init test environment
	pin ptest(&DDRC,&PINC,5,true);
	int nPushed = 0;
	BluetoothCommunicator btCom;
	//Loop
	int twice = 0;
	interpolator.setInterpolation(targetPoint,10);
	while (1)
	{	
		//SendString(UART0,"startWhile\n\r");
		interpolator.updateActualPosition();
		geometry.set(interpolator.getXPosmm(), interpolator.getYPosmm(), interpolator.getZPosmm());
		stepperBase.stepToPositionRad(geometry.getRotRad());
		stepperLow.stepToPositionRad(geometry.getLowRad());
		stepperHigh.stepToPositionRad(geometry.getHighRad());
		//SendString(UART0,"stepToPos..\n\r");
		
		stepperBase.update();
		stepperLow.update();
		stepperHigh.update();
		
		if (interpolator.isFinished())
		{
			targetPoint = btCom.ReadData(targetPoint);
			printPoint(targetPoint);
			interpolator.setInterpolation(targetPoint,10);
		}

		
		/*
		if (nPushed == 0)
		{
			_delay_ms(1000);
			nPushed = 1;
			interpolator.setInterpolation(50,120,120,0,10);
		}
		
		
		if ((!ptest.readValue()) && nPushed == 0)
		{
			SendString(UART0,"Trykket ned\n\r");
			SendInteger(UART0,interpolator.getZPosmm());
			SendString(UART0,"\n\r");
			interpolator.setInterpolation(10,120,120,0,6);
			nPushed++;
			_delay_ms(500);
		}
		
		if ((ptest.readValue()) && nPushed == 1)
		{
			SendString(UART0,"Trykket ned\n\r");
			interpolator.setInterpolation(0,120,0,0,6);
			nPushed++;
			_delay_ms(500);
		}

		if ((ptest.readValue()) && nPushed == 2)
		{
			SendString(UART0,"Trykket ned\n\r");
			interpolator.setInterpolation(120,120,120,0,6);
			nPushed++;
			_delay_ms(500);
		}
		*/
	}
	
	/*
	// First test of motor driver	
	int i = 0;
	Y_DIR_PIN.low();
	_delay_us(10);
	_delay_ms(15000);
	SendString(UART0,"H\n\r");
	Y_STEP_PIN.high();
	_delay_ms(1);
	
	SendString(UART0,"L\n\r");
	Y_STEP_PIN.low();
	_delay_ms(1);
	
	i++;
	
	while (1)
	{}
	*/
}

