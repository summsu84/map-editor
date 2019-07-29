/*
 * MppItem.cpp
 *
 *  Created on: 2013. 7. 3.
 *      Author: jiwon
 */

#include "MppItem.h"
MppItem::MppItem() {
	// TODO Auto-generated constructor stub

}

MppItem::MppItem(QPointF point, QString text)
{
	// TODO Auto-generated constructor stub
	this->point = point;
	strMpp = text;
	//qDebug()<<"Mpp type : "<<type();
}


MppItem::~MppItem() {
	// TODO Auto-generated destructor stub
	//qDebug()<<"[MppItem - ~MppItem] destructor is called..";
}

void MppItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * /* widget */)
{

	//qDebug()<<"scale : "<<scale()<<", scaleX : "<<painter->transform().m11();
	/*double scaleValue = scale();
	double scaleX = painter->transform().m11();
	setScale(scaleValue / scaleX);
	QGraphicsSvgItem::paint(painter, option);*/
	drawText(painter);
}

void MppItem::drawText(QPainter * painter)
{

	painter->setFont(QFont("Times", 10));
	QRect textBox;
	//textBox.setRect(point.x(), point.y(), strMpp.length(), 25);
	painter->drawText(point, strMpp);

}

QRectF MppItem::boundingRect() const
{
	qreal adjust = 0.5;

	QRectF rect = QRectF(adjust, adjust,
			LatLonConvert::getInstance().srcRect().width() * 1.0, LatLonConvert::getInstance().srcRect().height() * 1.0);

	return rect;
}

void MppItem::setStrMpp(QPointF point)
{
	QString strMpp = QString::number(LatLonConvert::getInstance().mpp(), 'f', 2);
	strMpp.prepend("mpp : ");

	QPointF wonjum = LatLonConvert::getInstance().wonjum();
	QString lat = "N";
	lat.append(QString::number((int)wonjum.x(), 10));
	QString lon = "E";
	lon.append(QString::number((int)wonjum.y(), 10));

	strMpp.prepend(lon);
	strMpp.prepend(lat);
	strMpp.prepend("wonjum : ");

	setStrMpp(strMpp);
}
