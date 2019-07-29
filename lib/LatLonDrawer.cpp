/*
 * LatLonDrawer.cpp
 *
 *  Created on: 2013. 5. 22.
 *      Author: jiwon
 */

#include "LatLonDrawer.h"
#include "WGS84_TM.h"
#include <QDebug>
#include <QPen>

LatLonDrawer::LatLonDrawer(int angle, int scale)
: angle(angle), scale(scale)
{
	// TODO Auto-generated constructor stub

	wx = 2500;
	wy = 2500;
}

LatLonDrawer::~LatLonDrawer() {
	// TODO Auto-generated destructor stub
}

/*
 * 위도를 그린다.
 */
/*QVector<QGraphicsLineItem * > LatLonDrawer::drawLat()
{
	qDebug()<<"[LatLonDrawer] drawLat is called..";
	//1. 1도의 값을 알아온다.
	double minlon = 100.0;
	double maxlon = 140.0;
	double lat = 23.0;   //y value
	//WGS84_TM::getInstance().getDistanceFromOneDegree(x, y);

	QVector<QGraphicsLineItem *> line_list;

	for(int i = 0 ; i < 60; i ++){
		QPointF point;
		QPointF nPoint;

		WGS84_TM::getInstance().LatLonConvert(point.rx(), point.ry(), minlon, lat);
		WGS84_TM::getInstance().LatLonConvert(nPoint.rx(), nPoint.ry(), maxlon, lat);

		point = WGS84_TM::getInstance().rotateLatLon(point, angle);
		nPoint = WGS84_TM::getInstance().rotateLatLon(nPoint, angle);

		point.setX(point.x() + 2500);
		point.setY(point.y() + 2500);

		nPoint.setX(nPoint.x() + 2500);
		nPoint.setY(nPoint.y() + 2500);

		qDebug()<<"point : "<<point;
		qDebug()<<"nPoint : "<<nPoint;


		//원을 그리기 위한 변수
		QPointF centerPoint(2500, -3300);

		qreal ygap = point.y() - centerPoint.y();
		QPointF e_leftTop(point.x(), point.y() - (ygap*2));
		QPointF e_rightBottom = nPoint;

		QGraphicsEllipseItem * ellipse = new QGraphicsEllipseItem(QRectF(e_leftTop, e_rightBottom));


		QGraphicsLineItem * line = new QGraphicsLineItem(QLineF(point, nPoint));
		line->setPen(QPen(Qt::black));
		line_list.append(line);

		lat += 1.0;
	}

	return line_list;


	//qDebug()<<"Lat : "<<y<<", Lon : "<<x;

}*/

/*
 * 위도를 그린다.
 */
QVector<QGraphicsArcItem * > LatLonDrawer::drawLat()
{
	qDebug()<<"[LatLonDrawer] drawLat is called..";
	//1. 1도의 값을 알아온다.
	double minlon = 60.0;
	double maxlon = 170.0;
	double lat = 23.0;   //y value
	//WGS84_TM::getInstance().getDistanceFromOneDegree(x, y);

	QVector<QGraphicsArcItem *> line_list;

	for(int i = 0 ; i < 60; i ++){
		QPointF point;
		QPointF nPoint;

		WGS84_TM::getInstance().LatLonConvert(point.rx(), point.ry(), minlon, lat);
		WGS84_TM::getInstance().LatLonConvert(nPoint.rx(), nPoint.ry(), maxlon, lat);

		point = WGS84_TM::getInstance().rotateLatLon(point, angle);
		nPoint = WGS84_TM::getInstance().rotateLatLon(nPoint, angle);

		point.setX(point.x() + 2500);
		point.setY(point.y() + 2500);

		nPoint.setX(nPoint.x() + 2500);
		nPoint.setY(nPoint.y() + 2500);

		qDebug()<<"point : "<<point;
		qDebug()<<"nPoint : "<<nPoint;


		//원을 그리기 위한 변수
		QPointF centerPoint(2500, -3300);

		qreal ygap = point.y() - centerPoint.y();
		QPointF e_leftTop(point.x(), point.y() - (ygap*2));
		QPointF e_rightBottom = nPoint;

		//QGraphicsEllipseItem * ellipse = new QGraphicsEllipseItem(QRectF(e_leftTop, e_rightBottom));

		QGraphicsArcItem * ellipse = new QGraphicsArcItem(e_leftTop, e_rightBottom);

	/*	ellipse->setStartAngle(200 * 16);
		ellipse->setSpanAngle(130 * 16);*/

		//ellipse->setPen(QPen(Qt::black));
		line_list.append(ellipse);

		lat += 1.0;
	}

	return line_list;


	//qDebug()<<"Lat : "<<y<<", Lon : "<<x;

}




/*
 * 위도를 그린다.
 */
QVector<QGraphicsLineItem * > LatLonDrawer::drawLon()
{
	//1. 1도의 값을 알아온다.
	qDebug()<<"[LatLonDrawer] drawLat is called..";
		//1. 1도의 값을 알아온다.
	double minlat = 0.0;
	double maxlat = 90.0;
	double lon = 100.0;   //y value
	//WGS84_TM::getInstance().getDistanceFromOneDegree(x, y);

	QVector<QGraphicsLineItem *> line_list;

	for(int i = 0 ; i < 70; i ++){
		QPointF point;
		QPointF nPoint;

		WGS84_TM::getInstance().LatLonConvert(point.rx(), point.ry(), lon, minlat);
		WGS84_TM::getInstance().LatLonConvert(nPoint.rx(), nPoint.ry(), lon, maxlat);

		point = WGS84_TM::getInstance().rotateLatLon(point, angle);
		nPoint = WGS84_TM::getInstance().rotateLatLon(nPoint, angle);

		point.setX(point.x() + 2500);
		point.setY(point.y() + 2500);

		nPoint.setX(nPoint.x() + 2500);
		nPoint.setY(nPoint.y() + 2500);

		qDebug()<<"point : "<<point;
		qDebug()<<"nPoint : "<<nPoint;




		QGraphicsLineItem * line = new QGraphicsLineItem(QLineF(point, nPoint));
		line->setPen(QPen(Qt::black));
		line_list.append(line);

		lon += 1.0;
	}

	return line_list;


}
