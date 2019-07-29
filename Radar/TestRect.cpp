/*
 * TestRect.cpp
 *
 *  Created on: 2013. 10. 23.
 *      Author: jiwon
 */

#include "TestRect.h"
#include <QBrush>
#include <QPainter>
TestRect::TestRect() {
	// TODO Auto-generated constructor stub

	this->setZValue(-1);
}

TestRect::~TestRect() {
	// TODO Auto-generated destructor stub
}

void TestRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *  widget )
{

	QBrush brush(Qt::green);
	QRectF rect(100, 100, 400, 400);
	painter->setBrush(brush);
	painter->drawRect(rect);
}


QRectF TestRect::boundingRect() const
{
	qreal adjust = 0.5;

//	QRectF rect = QRectF(adjust, adjust,
//			LatLonConvert::getInstance().srcRect().width() * 1.0, LatLonConvert::getInstance().srcRect().height() * 1.0);
	QRectF rect = QRectF(100, 100, 400, 400);

	//qDebug()<<"[LabelComponent] boundingRect : "<<rect;

	return rect;
}
