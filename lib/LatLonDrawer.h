/*
 * LatLonDrawer.h
 *
 *  Created on: 2013. 5. 22.
 *      Author: jiwon
 */

#ifndef LATLONDRAWER_H_
#define LATLONDRAWER_H_

#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include "QGraphicsArcItem.h"
class LatLonDrawer
{
public:
	LatLonDrawer(int angle, int scale);
	virtual ~LatLonDrawer();

	//QVector<QGraphicsLineItem * > drawLat();		//위도
	QVector<QGraphicsArcItem * > drawLat();		//위도
	QVector<QGraphicsLineItem * >  drawLon();		//경도

private:
	qreal wx;
	qreal wy;

	int angle;
	int scale;

};

#endif /* LATLONDRAWER_H_ */
