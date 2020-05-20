/*
 * Point.cpp
 *
 * Created: 27-04-2020 15:43:44
 *  Author: troel
 */ 

#include "Point.h"

#define COS_ROT 0.9998
#define SIN_ROT 0.0175

Point calcPoint(Point oldP, double a_ch, double hyp_ch)
{
	//double hyp_old = sqrt(pow(oldP.xmm_,2)+pow(oldP.ymm_,2));
	//double param = (oldP.ymm_/hyp_old);
	//double a_old = 0;
	//if((oldP.xmm_>0 && oldP.ymm_>0) || (oldP.xmm_>0 && oldP.ymm_<0)) // 1. quadrant or 2. quadrant
	//{
		//a_old = acos(param);
	//}
//
	//if((oldP.xmm_<0 && oldP.ymm_<0) || (oldP.xmm_<0 && oldP.ymm_>0)) // 3. quadrant or 4. quadrant
	//{
		//a_old = -acos(param)+2.0*PI;
//
	//}
	//// Cases with x or y equals zero
	//if(oldP.xmm_==0 && oldP.ymm_>0)
	//{
		//a_old = 0; //Radians
	//}
	//if(oldP.xmm_==0 && oldP.ymm_<0)
	//{
		//a_old = PI; //Radians
	//}
	//if(oldP.xmm_>0 && oldP.ymm_==0)
	//{
		//a_old = PI/2; //Radians
	//}
	//if(oldP.xmm_<0 && oldP.ymm_==0)
	//{
		//a_old = 3.0*PI/2.0; //Radians
	//}
	//double a_new = a_old + (((a_ch)/180.0))*PI;
	Point result;
	
	if(a_ch	< 0)
	{
		result.xmm_ = oldP.xmm_*COS_ROT + oldP.ymm_*SIN_ROT;
		result.ymm_ = -oldP.xmm_*SIN_ROT + oldP.ymm_*COS_ROT;
	}
	else if(a_ch > 0)
	{
		result.xmm_ = oldP.xmm_*COS_ROT - oldP.ymm_*SIN_ROT;
		result.ymm_ = oldP.xmm_*SIN_ROT + oldP.ymm_*COS_ROT;
		
	}
	
	float vLength = sqrt((result.xmm_*result.xmm_) + (result.ymm_*result.ymm_));
	float factor = (vLength+hyp_ch)/vLength;
	
	result.xmm_ = result.xmm_*factor;
	result.ymm_ = result.ymm_*factor;
	
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