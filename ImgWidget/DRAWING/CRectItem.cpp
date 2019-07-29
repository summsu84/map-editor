/*
 * CRectItem.cpp
 *
 *  Created on: 2013. 6. 4.
 *      Author: jiwon
 */

#include "CRectItem.h"
#include "../LATLON/LatLonConvert.h"

int CRectItem::id = 0;
using namespace::DS;

CRectItem::CRectItem() {
	// TODO Auto-generated constructor stub

	id++;
	isFirst = true;
}

CRectItem::CRectItem(QRectF rectF) : rectF(rectF)
{
	// TODO Auto-generated constructor stub
	id++;
	this->setRect(rectF);

}
CRectItem::~CRectItem() {
	// TODO Auto-generated destructor stub
}


/*
 * 휠 이벤트 발생시 재드로잉 하는 방법?
 * 1. 현재 X, Y 좌표를 위경도 좌표로 변환한다.
 * 2. Update시 위경도 좌표를 LatLonConvert에 의해서 새로운 X, Y 좌표를 리턴 받음
 */
void CRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *  widget )
{
	/*painter->setPen(pen);
	painter->setBrush(brush);*/

	//pen.setBrush(brush);
	painter->setBrush(brush);
	painter->setPen(pen);
	if(shape == Rect){
		if(isFirst == true){
			painter->drawRect(rect());

			//isFirst = false;
		}else{
			QPoint p1 = LatLonConvert::getInstance().latlonToScreen(latlonPoint[0]);
			QPoint p2 = LatLonConvert::getInstance().latlonToScreen(latlonPoint[1]);

			QRect rect(p1, p2);
			setRect(rect);
			painter->drawRect(rect);
		}

	}else if(shape == RoundedRect){
		painter->drawRoundedRect(rect(), 25, 25, Qt::RelativeSize);
	}
}

void CRectItem::setCompleteRect()
{
	latlonPoint[0] = LatLonConvert::getInstance().screenToDecimal(rect().topLeft().toPoint());
	latlonPoint[1] = LatLonConvert::getInstance().screenToDecimal(rect().bottomRight().toPoint());
	qDebug()<<"Point : "<<latlonPoint[0]<<", "<<latlonPoint[1];
	isFirst = false;
}

QRectF CRectItem::boundingRect() const
{
	qreal adjust = 0.5;

	QRectF rect = QRectF(adjust, adjust,
			LatLonConvert::getInstance().srcRect().width() * 1.0, LatLonConvert::getInstance().srcRect().height() * 1.0);

	//qDebug()<<"[CRectItem - boundingRect] rect : "<<rect;
	return rect;
}

