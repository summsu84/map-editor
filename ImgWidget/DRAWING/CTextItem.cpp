/*
 * CTextItem.cpp
 *
 *  Created on: 2013. 7. 10.
 *      Author: jiwon
 */

#include "CTextItem.h"
#include "../LATLON/LatLonConvert.h"

CTextItem::CTextItem(QPointF initPoint, QString strText, QFont font) {
	// TODO Auto-generated constructor stub
	this->initPoint = initPoint;
	this->strText = strText;
	this->font = font;

	enableMoving = false;
}

CTextItem::~CTextItem() {
	// TODO Auto-generated destructor stub
}



void CTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *  widget )
{
	/*painter->setPen(pen);
	painter->setBrush(brush);*/

	//pen.setBrush(brush);
	painter->setBrush(brush);
	painter->setPen(pen);
	painter->setFont(font);
	if(enableMoving == false){
		painter->drawText(initPoint, strText);
	}else{
		painter->drawText(currentPoint, strText);
	}
}

QRectF CTextItem::boundingRect() const
{
	qreal adjust = 0.5;

	QRectF rect = QRectF(adjust, adjust,
			LatLonConvert::getInstance().srcRect().width() * 1.0, LatLonConvert::getInstance().srcRect().height() * 1.0);

	//qDebug()<<"[CRectItem - boundingRect] rect : "<<rect;
	return rect;
}

