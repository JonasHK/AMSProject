/*
 * Point.h
 *
 * Created: 06/04/2020 15.09.33
 *  Author: jonas
 */ 

#ifndef POINT_H_
#define POINT_H_
#include "math.h"
#define PI 3.14159265

struct Point {
	float xmm_;
	float ymm_;
	float zmm_;
	float emm_;
};

Point calcPoint(Point oldP, double a_ch, double hyp_ch);

Point addPoints(Point p1, Point p2);
#endif /* POINT_H_ */