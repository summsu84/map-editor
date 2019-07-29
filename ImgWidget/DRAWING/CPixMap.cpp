/*
 * CPixMap.cpp
 *
 *  Created on: 2013. 6. 10.
 *      Author: jiwon
 */

#include "CPixMap.h"
#include "../LATLON/LatLonConvert.h"
CPixMap::CPixMap(QPixmap pixmap, QPointF point)
{
	// TODO Auto-generated constructor stub

	initPoint = point;
	this->pixmap = pixmap;


}
CPixMap::CPixMap(QString name, QPointF point)
{
	// TODO Auto-generated constructor stub

	initPoint = point;

	pixmap = QPixmap(name);

	enableMoving == false;

}
CPixMap::~CPixMap() {
	// TODO Auto-generated destructor stub
}



void CPixMap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *  widget )
{
//	painter->setBrush(brush);
//	painter->setPen(pen);
//	painter->setFont(font);

	if(enableMoving == false)
		painter->drawPixmap(initPoint, pixmap);
	else
		painter->drawPixmap(currentPoint, pixmap);


}

QRectF CPixMap::boundingRect() const
{
	qreal adjust = 0.5;

	QRectF rect = QRectF(adjust, adjust,
			LatLonConvert::getInstance().srcRect().width() * 1.0, LatLonConvert::getInstance().srcRect().height() * 1.0);

	//qDebug()<<"[CRectItem - boundingRect] rect : "<<rect;
	return rect;
}
