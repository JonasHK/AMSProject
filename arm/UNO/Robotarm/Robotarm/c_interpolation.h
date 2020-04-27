/*
 * interpolation.h
 *
 * Created: 18/03/2020 17.36.55
 *  Author: jonas
 */ 
#include "Point.h"

class Interpolation
{
public:
	Interpolation();
	void setCurrentPos(float px, float py, float pz, float pe);
	void setInterpolation(float px, float py, float pz, float pe, float v = 0);
	void setInterpolation(float p1x, float p1y, float p1z, float p1e, float p2x, float p2y, float p2z, float p2e, float av = 0);

	void setCurrentPos(Point p);
	void setInterpolation(Point p1, float v = 0);
	void setInterpolation(Point p0, Point p1, float v = 0);
	
	void updateActualPosition();
	bool isFinished() const;
	  
	float getXPosmm() const;
	float getYPosmm() const;
	float getZPosmm() const;
	float getEPosmm() const;
	Point getPosmm() const;

private:
	float getDistance() const;
	char state_;
  
	unsigned long startTime_;
  
	float xStartmm_;
	float yStartmm_;
	float zStartmm_;
	float eStartmm_;
	float xDelta_;
	float yDelta_;
	float zDelta_;
	float eDelta_;
	float xPosmm_;
	float yPosmm_;
	float zPosmm_;
	float ePosmm_;
	float v_;
	float tmul_;
};