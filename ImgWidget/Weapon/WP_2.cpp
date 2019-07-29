/*
 * WP_1.cpp
 *
 *  Created on: 2013. 5. 9.
 *      Author: jiwon
 */

#include "WP_2.h"


WP_2::WP_2(qreal x, qreal y, qreal x1, qreal y1, int type, QGraphicsItem * parent)
: CommonWP(x, y, x1, y1, parent)
{
	qDebug()<<"[WP_2] WP_2 is called..";
	// TODO Auto-generated constructor stub
	this->setDamage(100);
	this->setDescr("This is basic weapon!");
	this->setWp_name("WP1");
	this->setWPBrush(Qt::green);
	this->nodetype = type;
	//setBrush(Qt::red);
	updateTimer = new QTimer();
	updateTimer->setInterval(100);
	QObject::connect(updateTimer, SIGNAL(timeout()), this, SLOT(move()));

}

WP_2::~WP_2() {
	// TODO Auto-generated destructor stub
	qDebug()<<"[WP_2] ~WP_2 is called..";
}

QGraphicsLineItem * WP_2::attack()
{
	qDebug()<<"[WP_2] attack is called..";
	//QGraphicsLineItem * item = new QGraphicsLineItem(xPos, yPos, xPos + 30,yPos);
	updateTimer->start();

	return 0;
}

QGraphicsLineItem * WP_2::attack4Node()
{
	qDebug()<<"[WP_2] attack is called..";
	//QGraphicsLineItem * item = new QGraphicsLineItem(xPos, yPos, xPos + 30,yPos);
	updateTimer->start();

	return 0;
}
void WP_2::move()
{
	qreal limitX = this->sceneBoundingRect().x();
	qDebug()<<"[WP_2] move is called..X Pos : " <<limitX;
	qreal xPos = pos().x();
	qreal yPos = pos().y();
	//qDebug()<<"SceneBounding Rect : "<<sceneBoundingRect()<<", X : "<<QString().setNum(sceneBoundingRect().center().x())<<", Y : "<<QString().setNum(sceneBoundingRect().center().y());
	float fx, fy;

	xPos += 10.0;

	fx = xPos;
	fy = yPos;
	setPos(fx, fy);
	if(limitX > 800){
		this->~WP_2();
	}
}
