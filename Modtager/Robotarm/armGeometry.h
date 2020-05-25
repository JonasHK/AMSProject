/*
 * armGeometry.h
 *
 * Created: 12/03/2020 14.05.44
 *  Author: jonas
 */ 


#ifndef ARMGEOMETRY_H_
#define ARMGEOMETRY_H_

class armGeometry
{
public:
armGeometry();
void set(float xmm, float ymm, float zmm);
float getXmm() const;
float getYmm() const;
float getZmm() const;
float getRotRad() const;
float getLowRad() const;
float getHighRad() const;
private:
 void calculateAng();
 float xmm_;
 float ymm_;
 float zmm_;
 float rot_;
 float low_;
 float high_;
};

#endif /* ARMGEOMETRY_H_ */