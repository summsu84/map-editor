/*
 * CLineItem.cpp
 *
 *  Created on: 2013. 6. 4.
 *      Author: jiwon
 */

#include "CLineItem.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QAction>
#include <math.h>
#include "../lib/WGS84_TM.h"
#include "../LATLON/LatLonConvert.h"

int CLineItem::id = 0;
CLineItem::CLineItem(QGraphicsLineItem * parent )
: QGraphicsLineItem(parent)
{
	// TODO Auto-generated constructor stub
	/*this->setFlag(QGraphicsItem::ItemIsMovable, true);
	this->setFlag(QGraphicsItem::ItemIsSelectable, true);*/
	id++;
	qDebug()<<"CLine Item Id : "<<id;
	isFirst = true;
}



CLineItem::CLineItem(const QLineF &line, QGraphicsLineItem * parent )
: QGraphicsLineItem(line, parent)
{
	// TODO Auto-generated constructor stub
	/*this->setFlag(QGraphicsItem::ItemIsMovable, true);
	this->setFlag(QGraphicsItem::ItemIsSelectable, true);*/

	qDebug()<<"CLine Item Id : "<<id;
	id++;
	isFirst = true;
}

CLineItem::~CLineItem() {
	// TODO Auto-generated destructor stub
}



void CLineItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	qDebug()<<"[CLineItem] mouse press event is called..";
	//drawDesc();
	if (event->buttons() & Qt::LeftButton)
	{
		//menu->popup(event->pos());
		//qDebug()<<"Item : "<<node_nm<<" is clicked..";
		//event->
	}

	//menu->popup(QPoint(500,500));
	QGraphicsItem::mousePressEvent(event);



}

void CLineItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
 {
     QMenu menu;
     QAction *removeAction = menu.addAction("Remove");
     connect(removeAction, SIGNAL(triggered()), this, SLOT(removeNode()));
     QAction *markAction = menu.addAction("Distance");
     connect(markAction, SIGNAL(triggered()), this, SLOT(getDistance()));
     QAction *selectedAction = menu.exec(event->screenPos());

 }

void CLineItem::removeNode()
{
	qDebug()<<"remove Node...";
	//emitRemoveNode(this);
}

void CLineItem::getLine()
{
	QLineF line = this->line();

	qDebug()<<"CLineItem Line : "<<line;
}

/*
 * 두 포인트 간의 거리를 구한다.
 */
/*QGraphicsItem * CLineItem::getDistance()
{
	qDebug()<<"Get Distance is called..";

	QLineF line = this->line();

	QPointF p1 = line.p1();
	QPointF p2 = line.p2();

	double x1 = p1.x();
	double y1 = p1.y();

	double x2 = p2.x();
	double y2 = p2.y();

	double dist = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));

	WGS84_TM::getInstance().getDistance(x1, y1, x2, y2);
	qDebug()<<"dist : "<<dist;

	QGraphicsTextItem * txtItem = new QGraphicsTextItem(QString::number(dist, 'f', 2).append(" km"), this);
	txtItem->setPos(QPointF(x1 + 20, y1 + 20));

	emit emitAddTextItem(static_cast<QGraphicsItem *>(txtItem));
}*/

QGraphicsItem * CLineItem::getDistance()
{
	qDebug()<<"Get Distance is called..";

	QLineF line = this->line();

	QPointF p1 = line.p1();
	QPointF p2 = line.p2();

	qDebug()<<"p1 : "<<p1<<", p2 : "<<p2;
	double dist = LatLonConvert::getInstance().distance(p1.toPoint(), p2.toPoint());



	//아래 생략
	/*double x1 = p1.x();
	double y1 = p1.y();

	double x2 = p2.x();
	double y2 = p2.y();

	double dist = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));

	WGS84_TM::getInstance().getDistance(x1, y1, x2, y2);*/
	qDebug()<<"dist : "<<dist;

	dist /= 1000;
	QGraphicsTextItem * txtItem = new QGraphicsTextItem(QString::number(dist, 'f', 2).append(" km"), this);
	txtItem->setPos(QPointF(p1.x()+10, p1.y()+10));

	emit emitAddTextItem(static_cast<QGraphicsItem *>(txtItem));
}

//현재 두 포인트의 Pos를 LatLon으로 변환 시킨다.
void CLineItem::genLatLonPos()
{
/*	QLineF line = initLine;

	QPoint p1 = line.p1().toPoint();
	QPoint p2 = line.p2().toPoint();

	QPointF latlon_1 = LatLonConvert::getInstance().screenToDecimal(p1);
	QPointF latlon_2 = LatLonConvert::getInstance().screenToDecimal(p2);

	//QLineF new_line(LatLonConvert::getInstance().latlonToScreen2(latlon_1), LatLonConvert::getInstance().latlonToScreen2(latlon_2));

	QPointF nlatlon_1 = LatLonConvert::getInstance().latlonToScreen2(latlon_1);
	QPointF nlatlon_2 = LatLonConvert::getInstance().latlonToScreen2(latlon_2);

	qDebug()<<"latlon_1 : "<<latlon_1<<", latlon_2 : "<<latlon_2;
	qDebug()<<"org_line : "<<line<<", new_line : "<<nlatlon_1<<", "<<nlatlon_2;*/

	//QLineF new_line(latlon_1, latlon_2);


	//this->setLine(new_line);

}


//최초 생성된 라인을 저장한다..
void CLineItem::setInitLine()
{
	initLine = this->line();
}




void CLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * /* widget */)
{
	//qDebug()<<"[CLineItem - paint] paint is called..";

	//painter->setPen(QPen(QBrush(), 4));
//	QPen tmpPen = painter->pen();
//	tmpPen.setWidth(4);
	//pen.setBrush(brush);

	painter->setPen(pen);
	painter->setBrush(brush);
	if(isFirst == true){
		painter->drawLine(this->line());

//		latlonPoint[0] = LatLonConvert::getInstance().screenToDecimal(line().p1().toPoint());
//		latlonPoint[1] = LatLonConvert::getInstance().screenToDecimal(line().p2().toPoint());

		//isFirst = false;
	}else{
		QPoint p1 = LatLonConvert::getInstance().latlonToScreen(latlonPoint[0]);
		QPoint p2 = LatLonConvert::getInstance().latlonToScreen(latlonPoint[1]);

		QLine line(p1, p2);
		this->setLine(line);
		painter->drawLine(line);

	}
}

QRectF CLineItem::boundingRect() const
{
	qreal adjust = 5;

	QRectF rect = QRectF(adjust, adjust,
			LatLonConvert::getInstance().srcRect().width() * 1.0, LatLonConvert::getInstance().srcRect().height() * 1.0);

	//qDebug()<<"[CLineItem - boundingRect] rect : "<<rect;
	return rect;
}

void CLineItem::setComplete()
{
	latlonPoint[0] = LatLonConvert::getInstance().screenToDecimal(line().p1().toPoint());
	latlonPoint[1] = LatLonConvert::getInstance().screenToDecimal(line().p2().toPoint());
	//qDebug()<<"Point : "<<latlonPoint[0]<<", "<<latlonPoint[1];
	isFirst = false;
}
