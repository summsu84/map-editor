/*
 * CPolyLineItem.cpp
 *
 *  Created on: 2013. 7. 9.
 *      Author: jiwon
 */

#include "CPolyLineItem.h"
#include "../LATLON/LatLonConvert.h"

int CPolyLineItem::id = 0;
CPolyLineItem::CPolyLineItem(QPointF initPoint) {
	// TODO Auto-generated constructor stub

	setInitPoint(initPoint);
	org_point_list.append(initPoint);
	isFixed = false;

	qDebug()<<"org_point_list : "<<org_point_list;
	id++;
}

CPolyLineItem::~CPolyLineItem() {
	// TODO Auto-generated destructor stub
}

void CPolyLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * /* widget */)
{
	//qDebug()<<"[CPolyLineItem - paint] paint is called..";

	//painter->setPen(QPen(QBrush(), 4));

	qDebug()<<"[CPolylineItem-paint] called..";
	if(isFixed == true){
		//qDebug()<<"h1";
		QPolygonF polygonF(org_point_list);
		polygon = polygonF;
	}else{
		//qDebug()<<"currentPoitn : "<<currentPoint;
		if(currentPoint.isNull() != true){
			point_list = org_point_list;

			point_list.append(currentPoint);

			QPolygonF polygonF(point_list);
			polygon = polygonF;
		}
	}
	//qDebug()<<"[CPolygonItem-paint] called.. Polygon : "<<polygon;
	painter->setBrush(brush);
	painter->setPen(pen);
	painter->drawPolyline(polygon);
	//drawPolygon(polygon);
	//painter->drawLine(this->line());
}

QRectF CPolyLineItem::boundingRect() const
{
	//qreal adjust = 5;

	qreal adjust = 0.5;

	QRectF rect;
	if(polygon.size() >= 2){
		 rect = polygon.boundingRect();
	}else{
		rect = QRectF(adjust, adjust,
			LatLonConvert::getInstance().srcRect().width() * 1.0, LatLonConvert::getInstance().srcRect().height() * 1.0);
	}

//	QRectF rect = QRectF(adjust, adjust,
//			LatLonConvert::getInstance().srcRect().width() * 1.0, LatLonConvert::getInstance().srcRect().height() * 1.0);

	//qDebug()<<"[CLineItem - boundingRect] rect : "<<rect;
	return rect;
}


/*
 * 마우스 버튼을 클릭시 지점을 고정시킨는 기능.
 */
void CPolyLineItem::setFixedPoint(QPointF fixedPoint)
{
	this->fixedPoint = fixedPoint;
	pointCnt++;
	isFixed = true;

	genPointList(this->fixedPoint);
}

/*
 * 마우스 클릭시 고정된 지점에 대한 리스트
 */
void CPolyLineItem::genPointList(QPointF point)
{
	//point_list.clear();

///	org_point_list.append(initPoint);
	org_point_list.append(fixedPoint);
}

/*
 * 폴리곤 생성을 종료 한다.
 */

void CPolyLineItem::completePoint(QPointF curPoint)
{
	setFixedPoint(curPoint);
}
