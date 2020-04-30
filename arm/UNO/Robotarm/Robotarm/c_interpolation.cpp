/*
 * interpolation.cpp
 *
 * Created: 18/03/2020 17.36.42
 *  Author: jonas
 */ 
#include "c_interpolation.h"
#include "math.h"
#include <stdio.h>
#include "uart.h"
#include "d_SysTime.h"


Interpolation::Interpolation() {
	state_ = 1;
}

void Interpolation::setCurrentPos(float px, float py, float pz, float pe) {
	Point p;
	p.xmm_ =px;
	p.ymm_ =py;
	p.zmm_ =pz;
	p.emm_ =pe;
	setCurrentPos(p);	
}

void Interpolation::setCurrentPos(Point p) {
	xStartmm_ = p.xmm_;
	yStartmm_ = p.ymm_;
	zStartmm_ = p.zmm_;
	eStartmm_ = p.emm_;
	xDelta_ = 0;
	yDelta_ = 0;
	zDelta_ = 0;
	eDelta_ = 0;
}

void Interpolation::setInterpolation(float px, float py, float pz, float pe, float v) {
	Point p;
	p.xmm_ = px;
	p.ymm_ = py;
	p.zmm_ = pz;
	p.emm_ = pe;
	setInterpolation(p, v);
}

void Interpolation::setInterpolation(Point p1, float v) {
	Point p0;
	p0.xmm_ = xStartmm_ + xDelta_;
	p0.ymm_ = yStartmm_ + yDelta_;
	p0.zmm_ = zStartmm_ + zDelta_;
	p0.emm_ = eStartmm_ + eDelta_;
	setInterpolation(p0, p1, v);
}

void Interpolation::setInterpolation(float p1x, float p1y, float p1z, float p1e, float p2x, float p2y, float p2z, float p2e, float v) {
	Point p1;
	Point p2;
	p1.xmm_ = p1x;
	p1.ymm_ = p1y;
	p1.zmm_ = p1z;
	p1.emm_ = p1e;
	p2.xmm_ = p2x;
	p2.ymm_ = p2y;
	p2.zmm_ = p2z;
	p2.emm_ = p2e;
	setInterpolation(p1, p2, v);
}

void Interpolation::setInterpolation(Point p0, Point p1, float av) {
	v_ = av; //mm/s
	
	float a = (p1.xmm_ - p0.xmm_);
	float b = (p1.ymm_ - p0.ymm_);
	float c = (p1.zmm_ - p0.zmm_);
	float e = fabs(p1.emm_ - p0.emm_);
	float dist = sqrt(a*a + b*b + c*c);
	SendInteger(UART0,dist);
	SendString(UART0,"\n\r");
	
	
	if (v_ < 1) { //includes 0 = default value
		v_ = sqrt(dist) * 10; //set a good value for v
	}
	
	if (v_ < 1) {
		v_ = 5;
	}
	
	tmul_ = v_ / dist;
	SendInteger(UART0,tmul_*100000);
	SendString(UART0,"\n\r");	
	xStartmm_ = p0.xmm_;
	yStartmm_ = p0.ymm_;
	zStartmm_ = p0.zmm_;
	eStartmm_ = p0.emm_;
	
	xDelta_ = (p1.xmm_ - p0.xmm_);
	yDelta_ = (p1.ymm_ - p0.ymm_);
	zDelta_ = (p1.zmm_ - p0.zmm_);
	eDelta_ = (p1.emm_ - p0.emm_);
	
	state_ = 0; // Begin moving!
	
	startTime_ = Micro();
	//SendString(UART0,"\n\rstartTime_: ");
	//SendInteger(UART0,startTime_/1000.0);
}

void Interpolation::updateActualPosition() {
  if (state_ != 0) { // Arm is not moving
    return;
  }
  
  unsigned long microsek = Micro();  // Time now
  //SendString(UART0,"\n\rmicrosek: ");
  //SendInteger(UART0,microsek/1000.0);
  float t = (microsek - startTime_) / 1000000.0;  // Time since moving started in sec.

  //ArcTan Approx.
  /*float progress = atan((PI * t * tmul) - (PI * 0.5)) * 0.5 + 0.5;
  if (progress >= 1.0) {
    progress = 1.0; 
    state = 1;
  }*/
  //Cosin Approx.
  float progress = -cos(t * tmul_ * M_PI) * 0.5 + 0.5;
  //SendInteger(UART0,t*1000);
  //SendString(UART0,"\n\r");
  if ((t * tmul_) >= 1.0) {	// Move is done!
    progress = 1.0; 
    state_ = 1;
  }
  xPosmm_ = xStartmm_ + progress * xDelta_;
  yPosmm_ = yStartmm_ + progress * yDelta_;
  zPosmm_ = zStartmm_ + progress * zDelta_;
  ePosmm_ = eStartmm_ + progress * eDelta_;
}

bool Interpolation::isFinished() const{
	return state_ !=0;
}

float Interpolation::getXPosmm() const{
	return xPosmm_;	
}

float Interpolation::getYPosmm() const{
	return yPosmm_;	
}
float Interpolation::getZPosmm() const{
	return zPosmm_;
}

float Interpolation::getEPosmm() const{
	return ePosmm_;	
};
	
Point Interpolation::getPosmm() const{
	 Point p;
	 p.xmm_ = xPosmm_;
	 p.ymm_ = yPosmm_;
	 p.zmm_ = zPosmm_;
	 p.emm_ = ePosmm_;
	 return p;
};
