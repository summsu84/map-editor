/*
 * GlobalMath.h
 *
 *  Created on: 2014. 3. 10.
 *      Author: jiwon
 */

#ifndef GLOBALMATH_H_
#define GLOBALMATH_H_

#include <QPointF>
#include <QVector>

#include <math.h>
class GlobalMath {
public:
	GlobalMath();
	virtual ~GlobalMath();

	double getAngle(QPointF p1, QPointF p2);
	double getAngle(double dx, double dy, int mode);
	QPointF rotateLatLon(QPointF wonJum, QPointF cur_point, int angle);

	QVector<QPointF> getPoint(QPointF d1, double angle, double dist);		//기울기가 angle이고, 임의점 d1이 주어질때, 거리가 dist인 지점
private:

};

#endif /* GLOBALMATH_H_ */
