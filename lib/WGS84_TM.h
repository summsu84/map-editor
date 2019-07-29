/*
 * WGS84_TM.h
 *
 *  Created on: 2013. 5. 15.
 *      Author: jiwon
 */

#ifndef WGS84_TM_H_
#define WGS84_TM_H_

#include "WGS84_TMLib.h"
#include <iostream>
#include <math.h>
#include <QPointF>

using namespace std;

class WGS84_TM {
public:
	static WGS84_TM & getInstance()
	{
		if(pinstance == NULL){
			pinstance = new WGS84_TM;
		}

		return * pinstance;
	}
	WGS84_TM();
	virtual ~WGS84_TM();

	double Deg2Rad(double Degree);
	double Rad2Deg(double Radian);
	void _TM2Bessel(double tm_x, double tm_y, double lonOrg, double latOrg, double *lon, double *lat);
	void _Bessel2TM(double lon, double lat, double lonOrg, double latOrg, double *tm_x, double *tm_y);
	void Bessel2TM (double alt, double lon, double lat, double lonOrg, double latOrg, double *tm_x, double *tm_y);
	void TM2Bessel(double alt, double * lon, double  * lat, double lonOrg, double latOrg, double tm_x, double tm_y);
	void test();
	double MinSecond2Degree(double num);
	double LatLon2DMS(double *num);
	void LatLonConvert(double & x, double &y, double lon, double lat);
	void XYConvert(double tm_x, double tm_y, double *lon, double *lat, int angle = 0);

	void getDistanceFromOneDegree(double &x, double &y);					//위도에서 1도에 해당하는 거리를 리턴한다.
	void getDistance(double x1, double y1, double x2, double y2);		//지도상의 좌표를 바탕으로 두 지점의 거리를 구한다.
	void getDistance(QPointF p1, QPointF p2);

	QPointF rotateLatLon(QPointF cur_point, int angle);	//회전 시킨다..
	void setScale(int value) { scale = value; }
	int  getScale() { return scale;}
private:
	static WGS84_TM * pinstance;

	int scale;

};

#endif /* WGS84_TM_H_ */
