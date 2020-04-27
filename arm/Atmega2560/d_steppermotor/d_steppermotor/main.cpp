/*
 * d_steppermotor.cpp
 *
 * Created: 27/02/2020 11.37.25
 * Author : jonas
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <stdio.h>
#include "d_steppermotor.h"
#include "uart.h"
#include "d_SysTime.h"
#include "armGeometry.h"
#include "c_interpolation.h"

int main(void)
{
	// Init
	pin p0(&DDRB,&PORTB,0,false);
	pin p1(&DDRB,&PORTB,1,false);
	pin p2(&DDRB,&PORTB,2,false);
	pin p3(&DDRB,&PORTB,3,false);
	pin p4(&DDRB,&PORTB,4,false);
	pin p5(&DDRB,&PORTB,5,false);
	pin p6(&DDRB,&PORTB,6,false);
	pin p7(&DDRB,&PORTB,7,false);
	pin p8(&DDRA,&PORTA,0,false);
	pin p9(&DDRA,&PORTA,1,false);
	pin p10(&DDRA,&PORTA,2,false);
	pin p11(&DDRA,&PORTA,3,false);
	
	pin* pin1P[] = {&p0,&p1,&p2,&p3};
	pin* pin2P[] = {&p4,&p5,&p6,&p7};
	pin* pin3P[] = {&p8,&p9,&p10,&p11};
	
	stepperMotor stepperBase(pin1P);
	stepperMotor stepperHigh(pin2P);
	stepperMotor stepperLow(pin3P);
	
	armGeometry geometry;
	Interpolation interpolator;
	
	stepperHigh.setReductionRatio(32.0 / 9.0, 64*32); //200 * 16);  //big gear: 32, small gear: 9, steps per rev: 200, microsteps: 16
	stepperLow.setReductionRatio( 32.0 / 9.0, 64*32);//200 * 16);
	stepperBase.setReductionRatio(32.0 / 9.0, 64*32);//200 * 16);
	
	  //start positions..
	stepperHigh.setPositionRad(M_PI / 2.0); //90°
	stepperLow.setPositionRad(0);			// 0°
	stepperBase.setPositionRad(0);			// 0°
  
	// Init interpolation and uart
	interpolator.setInterpolation(0,120,120,0, 0,120,120,0);
	InitUART(UART0,115200,8,0);
	SendString(UART0,"Init faerdig, start!");
	
	//Init test environment
	pin ptest(&DDRA,&PINA,7,true);
	int nPushed = 0;
	SysTime testTimer;
	
	 //Setting motors back and forth
	/*char buff[50];
	for (int i = 0;i<((64*32)*40.0/60.0);i++)
	{
		stepperLow.step(false);
		_delay_us(1000);
		sprintf(buff,"Antal gange i forlokken: %d\n\r",i);
		SendString(UART0,buff);
	}
	*/
	//Loop
	while (1)
	{
		
		interpolator.updateActualPosition();
		geometry.set(interpolator.getXPosmm(), interpolator.getYPosmm(), interpolator.getZPosmm());
		//SendInteger(UART0,interpolator.getXPosmm());
		stepperBase.stepToPositionRad(geometry.getRotRad());
		//SendString(UART0,"\n\rLowRad: ");
		//SendInteger(UART0,geometry.getLowRad());
		//SendInteger(UART0,interpolator.getYPosmm());
		stepperLow.stepToPositionRad(geometry.getLowRad());
		//SendString(UART0,"\n\rHighRad: ");
		//SendInteger(UART0,geometry.getHighRad());
		//SendInteger(UART0,interpolator.getZPosmm());
		stepperHigh.stepToPositionRad(geometry.getHighRad());
		//stepperExtruder.stepToPositionRad(interpolator.getEPosmm());
		//SendString(UART0,"\n\rSystime: ");
		//SendInteger(UART0,testTimer.Micro());
		
		stepperBase.update();
		stepperLow.update();
		stepperHigh.update();
		
		
		if ((ptest.readValue()) && nPushed == 0)
		{
			SendString(UART0,"Trykket ned\n\r");
			SendInteger(UART0,interpolator.getZPosmm());
			SendString(UART0,"\n\r");
			interpolator.setInterpolation(0,240,60,0,6);
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
			interpolator.setInterpolation(0,120,120,0,6);
			nPushed++;
			_delay_ms(500);
		}

		if ((ptest.readValue()) && nPushed == 3)
		{
			SendString(UART0,"Trykket ned\n\r");
			interpolator.setInterpolation(0,120,120,0,6);
			nPushed++;
			_delay_ms(500);
		}
	}
	
	
	/* Test of modules: uart and SysTime
	InitUART(UART0,115200,8,0);
	SysTime timer;
	while (1)
	{
		long t1 = timer.Micro();
		_delay_us(500);
		long t2 = timer.Micro();
		SendString(UART0,"t1: ");
		SendInteger(UART0,t1);
		SendString(UART0,"\n\rt2: ");
		SendInteger(UART0,t2);
		SendString(UART0,"\n\n\r");
	}
	*/
	
	
	/* Test of modules: pin, stepper;ptpr
	pin p0(&DDRB,&PORTB,0);
	pin p1(&DDRB,&PORTB,1);
	pin p2(&DDRB,&PORTB,2);
	pin p3(&DDRB,&PORTB,3);
	
	pin* pinP[] = {&p0,&p1,&p2,&p3};
	
	stepperMotor base(pinP);
	int counter = 0;
    while(1)
	{
		_delay_ms(300);
		base.rotateDegree(1);
		counter++;
		return 0;
	}
	
	while (counter<10)
	{
		_delay_ms(300);	
		base.step(true);
		counter++;
	}
	counter = 0;

	while (counter<10)
	{
		_delay_ms(300);
		base.step(false);
		counter++;
	 }
	 // Test of modules: Pin
	while (1) 
    {
		p0.low();
		p1.low();
		p2.low();
		p3.low();
		_delay_ms(300);
		p0.high();
		p1.high();
		p2.high();
		p3.high();
		_delay_ms(300);
    }
	return 0;
	*/
}

