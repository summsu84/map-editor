/*
 * WP_1.cpp
 *
 *  Created on: 2013. 5. 9.
 *      Author: jiwon
 */

#include "WP_1.h"


WP_1::WP_1(qreal x, qreal y, qreal x1, qreal y1, int type, QGraphicsItem * parent)
: CommonWP(x, y, x1, y1, parent)
{
	//qDebug()<<"[WP_1] WP_1 is called..Type : " <<type;
	// TODO Auto-generated constructor stub
	this->setDamage(100);
	this->setDescr("This is basic weapon!");
	this->setWp_name("WP1");
	this->setWPBrush(Qt::red);
	this->nodetype = type;
	setFlag(QGraphicsItem::ItemIsMovable);

	/*QThread * thread = new QThread;
	thread->start();
	moveToThread(thread);*/

	updateTimer = new QTimer();
	updateTimer->setInterval(100);
	QObject::connect(updateTimer, SIGNAL(timeout()), this, SLOT(move()));

	//qDebug()<<"[WP_1] WP_1 is close..Type : " <<type;

}

WP_1::~WP_1() {
	// TODO Auto-generated destructor stub
	delete updateTimer;
	//qDebug()<<"[WP_1] ~WP_1 is called..";
}

QGraphicsLineItem * WP_1::attack()
{
	//qDebug()<<"[WP_1] attack is called..";
	/*sleep(1);
	this->move_notimer();*/
	updateTimer->start();

	//qDebug()<<"[WP_1] attack is closed..";
	return 0;
}
QGraphicsLineItem * WP_1::attack4Node()
{
	//qDebug()<<"[WP_1] attack4Node is called..";
	updateTimer->start();

	return 0;
}
void WP_1::move()
{
	qreal limitX = this->sceneBoundingRect().x();
	//qDebug()<<"[WP_1] move is called..X Pos : " <<limitX;
	qreal xPos = pos().x();
	qreal yPos = pos().y();
	//qDebug()<<"SceneBounding Rect : "<<sceneBoundingRect()<<", X : "<<QString().setNum(sceneBoundingRect().center().x())<<", Y : "<<QString().setNum(sceneBoundingRect().center().y());
	float fx, fy;

	if(nodetype == 0){
		xPos -= 30.0;
		fx = xPos;
		fy = yPos;
		setPos(fx, fy);
		if(limitX < 200){
			this->~WP_1();
		}else{
			emit emitColDetection();
		}
	}else if(nodetype == 1){
		xPos += 10.0;
		fx = xPos;
		fy = yPos;
		setPos(fx, fy);
		if(limitX > 800){
			this->~WP_1();
		}else{
			emit emitColDetection();
		}
	}
}


void WP_1::move_notimer()
{

	while(1){

		qreal limitX = this->sceneBoundingRect().x();
		qreal xPos = pos().x();
		qreal yPos = pos().y();
		float fx, fy;

		if(nodetype == 0){
			xPos -= 10.0;
			fx = xPos;
			fy = yPos;
			setPos(fx, fy);
			if(limitX < 200){
				this->~WP_1();
			}else{
				emit emitColDetection();
			}
		}else if(nodetype == 1){
			xPos += 10.0;
			fx = xPos;
			fy = yPos;
			setPos(fx, fy);
			if(limitX > 800){
				this->~WP_1();
			}else{
				emit emitColDetection();
			}
		}

		//sleep(1);
	}
}
