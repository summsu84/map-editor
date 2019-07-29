/*
 * CPolyGonItem.cpp
 *
 *  Created on: 2013. 7. 8.
 *      Author: jiwon
 */

#include "CPolyGonItem.h"
#include "../LATLON/LatLonConvert.h"


int CPolyGonItem::id = 0;
CPolyGonItem::CPolyGonItem()
{

}
CPolyGonItem::CPolyGonItem(QPointF initPoint) {
	// TODO Auto-generated constructor stub

	setInitPoint(initPoint);
	org_point_list.append(initPoint);
	isFixed = false;

	//qDebug()<<"org_point_list : "<<org_point_list;
	id++;
	isFirst = true;
}

CPolyGonItem::~CPolyGonItem() {
	// TODO Auto-generated destructor stub
}

void CPolyGonItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * /* widget */)
{
	//qDebug()<<"[CLineItem - paint] paint is called..";

	//painter->setPen(QPen(QBrush(), 4));

	qDebug()<<"[CPolygonItem-paint] called..";
	if(isFirst == true){
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
		painter->setBrush(brush);
		painter->setPen(pen);
		painter->drawPolygon(polygon);
	}else{

		QPolygon tmpPolygon;
		for(int i = 0 ; i < latlonPoint_list.size() ; i++){
			QPoint point = LatLonConvert::getInstance().latlonToScreen(latlonPoint_list[i]);
			tmpPolygon.append(point);
		}

		qDebug()<<"Polygon : "<<polygon;
		qDebug()<<"tmpPolygon : "<<tmpPolygon;
		painter->setBrush(brush);
		painter->setPen(pen);
		painter->drawPolygon(tmpPolygon);

	}
	//qDebug()<<"[CPolygonItem-paint] called.. Polygon : "<<polygon;
	//painter->drawLine(this->line());
}

QRectF CPolyGonItem::boundingRect() const
{
	qreal adjust = 0.5;

	QRectF rect;
	if(polygon.size() >= 2){
		 rect = polygon.boundingRect();
	}else{
		rect = QRectF(adjust, adjust,
			LatLonConvert::getInstance().srcRect().width() * 1.0, LatLonConvert::getInstance().srcRect().height() * 1.0);
	}


	//qDebug()<<"[CPolygonItem - boundingRect] rect : "<<rect<<", polygon bounding : "<<polygon.boundingRect()<<", polygon count : "<<polygon.size();
	return rect;
}


void CPolyGonItem::setFixedPoint(QPointF fixedPoint)
{
	this->fixedPoint = fixedPoint;
	pointCnt++;
	isFixed = true;

	genPointList(this->fixedPoint);
}

/*
 * 마우스 클릭시 고정된 지점에 대한 리스트
 */
void CPolyGonItem::genPointList(QPointF point)
{
	//point_list.clear();

///	org_point_list.append(initPoint);
	org_point_list.append(fixedPoint);
}

/*
 * 폴리곤 생성을 종료 한다.
 */

void CPolyGonItem::completePoint(QPointF curPoint)
{
	setFixedPoint(curPoint);
}

/*
 * 마우스가 릴리즈 되었을 때 최종 Polygon 리스트를 위경도 좌표로 변환한다.
 */

void CPolyGonItem::setComplete()
{
	for(int i = 0 ; i < polygon.size() ; i++){
		qDebug()<<"[Polygon List : "<<polygon<<"] ";
		QPointF point = LatLonConvert::getInstance().screenToDecimal(polygon[i].toPoint());
		latlonPoint_list.append(point);
	}

	isFirst = false;
}
