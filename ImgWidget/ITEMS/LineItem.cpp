/*
 * LineItem.cpp
 *
 *  Created on: 2013. 7. 2.
 *      Author: jiwon
 */

#include "LineItem.h"

LineItem::LineItem(MapType type) {
	// TODO Auto-generated constructor stub
	//qDebug()<<"[LineItem - LineItem] called..";

	this->type = type;
}

LineItem::~LineItem() {
	// TODO Auto-generated destructor stub
}



void LineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * /* widget */)
{
	//qDebug()<<"[LatLonItem] paint is called..";
	/*if (isShow) {
		painter->setPen(QPen(QColor(225, 227, 127), 1));
		drawLatLon(painter);
	}*/
	//qDebug()<<"[LineItem-paint] call.";

	if(type == POLYLINE){
	//	qDebug()<<"pl";
		painter->setPen(pen);
		drawPolyLines(painter);
	//	qDebug()<<"pl finish";
	}
	else if(type == POLYGON)
	{
	//	qDebug()<<"pg";
		painter->setPen(pen);
		painter->setBrush(brush);
		drawPolyGons(painter);
	}
	else if(type == POINTnSYMBOL)
	{
		//qDebug()<<"ps";
		drawPixmaps(painter);
		//qDebug()<<"ps fnish";
	}
}


void LineItem::drawPolyLines(QPainter * painter)
{
	painter->drawLines(polyline_list);
}

void LineItem::drawPolyGons(QPainter * painter)
{
	painter->drawPolygon(polygon);
}

void LineItem::drawPixmaps(QPainter * painter)
{
	//qDebug()<<"[LineItem - drawPixmaps] PixPos : "<<pixmapPoint<<", pixmap : "<<pixmap;
	painter->drawPixmap(pixmapPoint, *pixmap);
	//qDebug()<<"[LineItem - drawPixmaps] finished..";
}


QRectF LineItem::boundingRect() const
{
	qreal adjust = 0.5;

	QRectF rect = QRectF(adjust, adjust,
			LatLonConvert::getInstance().srcRect().width() * 1.0, LatLonConvert::getInstance().srcRect().height() * 1.0);
	//qDebug()<<"[LineItem ] boundingRect : "<<rect;

	return rect;
}

