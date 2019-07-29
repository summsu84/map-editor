/*
 * GlobalMath.cpp
 *
 *  Created on: 2014. 3. 10.
 *      Author: jiwon
 */

#include "GlobalMath.h"
//#include "GeoData.h"
#include <QDebug>
const double PI = 3.14159265;
GlobalMath::GlobalMath() {
	// TODO Auto-generated constructor stub

}

GlobalMath::~GlobalMath() {
	// TODO Auto-generated destructor stub
}



/*
 *  두 지점을 이용하여 각도를 구한다.
 */
double GlobalMath::getAngle(QPointF p1, QPointF p2)
{
	double dx = p2.x() - p1.x();
	double dy = p2.y() - p1.y();

	dy = 0 - dy;

	int mode;

	if(p1.x() <= p2.x() && p1.y() >= p2.y())
	{
		//1사분면
		mode = 1;
	}else if(p1.x() > p2.x() && p1.y() > p2.y())
	{
		//2사분면
		mode = 2;
	}else if(p1.x() > p2.x() && p1.y() < p2.y())
	{
		//3
		mode = 3;
	}else if(p1.x() < p2.x() && p1.y() < p2.y()){
		mode =4;
	}

	return getAngle(dx, dy, mode);
}
/*
 * 두 거리를 이용하여 각도를 구한다.
 */
double GlobalMath::getAngle(double dx, double dy, int mode){

	bool isEndAngle = false;
	//over90Degree = 0;

	if(dx == 0) dx = 0.00000001;

	double angle = atan(dy/dx) * (180.0 / PI);
	double result = 0;
	double tmp = angle;
	qDebug()<<"[CArcItem - getAngle] angle : "<<angle;


	//1사 분면 체크

	if(isEndAngle == false || isEndAngle == true){
		//start angle case
		if(mode == 2){
			angle = 90 + 90 + angle;
		}else if(mode == 3){
			angle = 180 + angle;
		}else if(mode == 4){
			angle = 270 + 90 + angle;
		}
		qDebug()<<"Mode : "<<mode<<", angle : "<<angle;
	}

	return angle;
}


QVector<QPointF> GlobalMath::getPoint(QPointF d1, double angle, double dist)
{
	double dx = d1.x();
	double dy = d1.y();

	double nx = dist / sqrt(1 + angle * angle);
	double ny = dist * angle / sqrt(1 + angle * angle);

	QVector<QPointF> point_list;

	QPointF point_1 = QPointF(dx+nx, dy + ny);
	QPointF point_2 = QPointF(dx-nx, dy - ny);

	point_list.append(point_1);
	point_list.append(point_2);

	return point_list;


}



/*
 * ANGLE 값만 큼 회전한다..
 */
QPointF GlobalMath::rotateLatLon(QPointF wonJum, QPointF cur_point, int angle)
{
	//qDebug()<<"[LatLonMng] rotateLatLon is called..";
	double u = wonJum.x();
	double v = wonJum.y();

	QPointF new_point;

	double x = cur_point.x();
	double y = cur_point.y();

	new_point.setX((((x - u) * cos(PI/180*angle) + (y - v)*sin(PI/180*angle)) + u ) );
	new_point.setY((((x - u) * -sin(PI/180*angle) + (y - v)*cos(PI/180*angle)) + v ));

	//qDebug()<<"ox : "<<x<<", oy : "<<y;
	//qDebug()<<"nx : "<<new_point.x()<<", yx : "<<new_point.y();
	//qDebug()<<"[LatLonMng] rotateLatLon is close..";

//	latlon_list = tmp;
	if(angle == 180){
		new_point.setX(new_point.x() * -1);
		new_point.setY(new_point.y() * -1);
	}
	return new_point;
}
