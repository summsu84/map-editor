/*
 * TrailComponent.cpp
 *
 *  Created on: 2013. 9. 25.
 *      Author: jiwon
 */

#include "TrailComponent.h"
#include "../ImgWidget/LATLON/LatLonConvert.h"
#include <QDebug>
#include <QPainter>

TrailComponent::TrailComponent(int posx, int posy, QGraphicsItem * parent)
{
	// TODO Auto-generated constructor stub

	//qDebug()<<"TrailComponenet construction is called..";
	this->posx = posx;
	this->posy = posy;

}

TrailComponent::~TrailComponent() {
	// TODO Auto-generated destructor stub
}


void TrailComponent::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *  widget )
{
/*	painter->setBrush(brush);
	painter->setPen(pen);*/

	//qDebug()<<"Trail Component painter..";

	painter->setPen(QPen(Qt::gray));
	painter->drawRect(0, 0, 10, 10);

}


QRectF TrailComponent::boundingRect() const
{
	qreal adjust = 0.5;

	QRectF rect = QRectF(adjust, adjust,
			LatLonConvert::getInstance().srcRect().width() * 1.0, LatLonConvert::getInstance().srcRect().height() * 1.0);

	return rect;
}

void TrailComponent::updatePos()
{

	//qDebug()<<"TrailComponenet updatePos is called.. Posx : "<<posx<<", posy : "<<posy;
	setPos(posx, posy);

	//qDebug()<<"Trail Component Pos : "<<this->scenePos();
	//update();
}
