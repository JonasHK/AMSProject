/*
 * Point.cpp
 *
 * Created: 27-04-2020 15:43:44
 *  Author: troel
 */ 

#include "Point.h"

Point calcPoint(Point oldP, double v_ch)
{
	double hyp = sqrt(pow(oldP.xmm_,2)+pow(oldP.ymm_,2));
	double param = (oldP.ymm_/hyp);
	double v_old = 0;
	if((oldP.xmm_>0 && oldP.ymm_>0) || (oldP.xmm_>0 && oldP.ymm_<0)) // 1. quadrant or 2. quadrant
	{
		v_old = acos(param);
	}

	if((oldP.xmm_<0 && oldP.ymm_<0) || (oldP.xmm_<0 && oldP.ymm_>0)) // 3. quadrant or 4. quadrant
	{
		v_old = -acos(param)+2.0*PI;

	}
	// Cases with x or y equals zero
	if(oldP.xmm_==0 && oldP.ymm_>0)
	{
		v_old = 0; //Radians
	}
	if(oldP.xmm_==0 && oldP.ymm_<0)
	{
		v_old = PI; //Radians
	}
	if(oldP.xmm_>0 && oldP.ymm_==0)
	{
		v_old = PI/2; //Radians
	}
	if(oldP.xmm_<0 && oldP.ymm_==0)
	{
		v_old = 3.0*PI/2.0; //Radians
	}
	double v_new = v_old + (((v_ch)/180.0))*PI;
	

	Point result;
	result.xmm_ = sin(v_new)*hyp;
	result.ymm_ = cos(v_new)*hyp;
	result.zmm_ = oldP.zmm_;
	result.emm_ = oldP.emm_;
	return result;
}

Point addPoints(Point p1, Point p2)
{
	Point result;
	result.emm_ = p1.emm_ + p2.emm_;
	result.xmm_ = p1.xmm_ + p2.xmm_;
	result.ymm_ = p1.ymm_ + p2.ymm_;
	result.zmm_ = p1.zmm_ + p2.zmm_;
	
	return result;
}