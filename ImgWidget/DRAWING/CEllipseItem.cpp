/*
 * CEllipseItem.cpp
 *
 *  Created on: 2013. 6. 4.
 *      Author: jiwon
 */

#include "CEllipseItem.h"
#include "../LATLON/LatLonConvert.h"

int CEllipseItem::id = 0;

CEllipseItem::CEllipseItem() {
	// TODO Auto-generated constructor stub

	id++;
}

CEllipseItem::CEllipseItem(QRectF rectF) : rectF(rectF)
{
	id++;
	isFirst = true;
	this->setRect(rectF);
}

CEllipseItem::~CEllipseItem() {
	// TODO Auto-generated destructor stub
}



void CEllipseItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * /* widget */)
{
	//qDebug()<<"[CLineItem - paint] paint is called..";

	//painter->setPen(QPen(QBrush(), 4));
//	QPen tmpPen = painter->pen();
//	tmpPen.setWidth(4);
	//painter->setPen(pen);
	painter->setPen(pen);
	painter->setBrush(brush);
	if(isFirst == true){
		painter->drawEllipse(this->rect());
	}else{
		QPoint p1 = LatLonConvert::getInstance().latlonToScreen(latlonPoint[0]);
		QPoint p2 = LatLonConvert::getInstance().latlonToScreen(latlonPoint[1]);

		QRect rect(p1, p2);
		setRect(rect);
		painter->drawEllipse(this->rect());
	}
}

QRectF CEllipseItem::boundingRect() const
{
	qreal adjust = 0.5;

	QRectF rect = QRectF(adjust, adjust,
			LatLonConvert::getInstance().srcRect().width() * 1.0, LatLonConvert::getInstance().srcRect().height() * 1.0);

	//qDebug()<<"[CLineItem - boundingRect] rect : "<<rect;
	return rect;
}

void CEllipseItem::setComplete()
{
	latlonPoint[0] = LatLonConvert::getInstance().screenToDecimal(rect().topLeft().toPoint());
	latlonPoint[1] = LatLonConvert::getInstance().screenToDecimal(rect().bottomRight().toPoint());
	//qDebug()<<"Point : "<<latlonPoint[0]<<", "<<latlonPoint[1];
	isFirst = false;
}
