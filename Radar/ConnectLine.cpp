/*
 * ConnectLine.cpp
 *
 *  Created on: 2013. 10. 22.
 *      Author: jiwon
 */

#include "ConnectLine.h"

ConnectLine::ConnectLine(LabelComponent * label) {
	// TODO Auto-generated constructor stub

	this->label = label;
	this->setZValue(-1);
}

ConnectLine::~ConnectLine() {
	// TODO Auto-generated destructor stub
}

void ConnectLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *  widget )
{

	//qDebug()<<"[ConnectLien] paint is called..";
	if(!label){
		return;
	}

	QLineF line(sourcePoint, destPoint);
	if(qFuzzyCompare(line.length(), qreal(0.)))
		return;

	//qDebug()<<"[ConnectLine] painter line : "<<line;

	painter->setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

	//QLine line = QLine(label->getAirplanePos(), label->getLabelPos());

	painter->drawLine(line);

}

void ConnectLine::setLabelComponent(LabelComponent * label)
{
	this->label = label;
	sourcePoint = label->getAirplanePos();
	destPoint = label->getLabelPos();
	update();
}

QRectF ConnectLine::boundingRect() const
{
	qreal adjust = 0.5;

	QRectF rect = QRectF(label->getAirplanePos(), label->getLabelPos());

	//qDebug()<<"[LabelComponent] boundingRect : "<<rect;

	return rect;
}

void ConnectLine::adjust()
{
	//qDebug()<<"[ConnectLine] adjust is called..";
	if(!label){
		qDebug()<<"Label is not exsit!";
		return;
	}

	QLineF line(label->getAirplanePos(), label->getLabelPos());
	qreal length = line.length();

	//qDebug()<<"[ConnectLine] line : "<<line;
	prepareGeometryChange();

	 if (length > qreal(20.)) {
		 QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
		 sourcePoint = line.p1() + edgeOffset;
		 destPoint = line.p2() - edgeOffset;
	 } else {
		 sourcePoint = destPoint = line.p1();
	 }
}
