/*
 * armGeometry.cpp
 *
 * Created: 12/03/2020 14.07.17
 *  Author: jonas
 */ 
#include "armGeometry.h"
#include <math.h>
armGeometry::armGeometry(){
}

void armGeometry::set(float xmm, float ymm, float zmm){
	xmm_ = xmm;
	ymm_ = ymm;
	zmm_ = zmm;
	calculateAng();
}

float armGeometry::getXmm() const{
	return xmm_;
}

float armGeometry::getYmm() const{
	return ymm_;
}

float armGeometry::getZmm() const{
	return zmm_;
}
float armGeometry::getRotRad() const{
	return rot_;
}

float armGeometry::getLowRad() const{
	return low_;
}

float armGeometry::getHighRad() const{
	return high_;
}

void armGeometry::calculateAng(){
	//Top view radius
	float RTop = sqrt((xmm_*xmm_)+(ymm_*ymm_));
	//Side view radius from base to grapper
	float RSide = sqrt((RTop*RTop)+(zmm_*zmm_));
	
	//Angle of base stepper motor 
	rot_ =asin(xmm_ / RTop);
	//Angle of high stepper motor
	high_ = acos((RSide * 0.5) / 120.0) * 2.0;
	//Angle of low stepper motor
	if (zmm_ > 0)
	{
		low_ = asin(RTop / RSide) + ((M_PI - high_) / 2.0) - (M_PI / 2.0);
	} 
	else {
		low_ = M_PI - asin(RTop / RSide) + ((M_PI - high_) / 2.0) - (M_PI / 2.0);
	}
	
	 //Correct higher Angle as it is mechanically bounded width lower Motor
	 high_ = high_ + low_;
}