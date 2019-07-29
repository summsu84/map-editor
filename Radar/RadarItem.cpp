/*
 * RadarItem.cpp
 *
 *  Created on: 2013. 10. 17.
 *      Author: jiwon
 */


#include "RadarItem.h"
#include "math.h"
#include <ctime>
#include "../ImgWidget/LATLON/LatLonConvert.h"
#include <QTime>
#include <QDebug>
#include <QPainter>
#include <iostream>
#include <QMenu>
using namespace std;

RadarItem::RadarItem() {
	// TODO Auto-generated constructor stub

}



RadarItem::RadarItem(QString call_sign, int climb_rate, int turn_rate, int heading, int alt, QString direct, int speed, int posx, int posy, int accel_rate, QGraphicsItem * parent)
{
	// TODO Auto-generated constructor stub

	//qDebug()<<"RadarItem is called..";
	this->callsign = call_sign;
	this->climbrate = climb_rate;
	this->turnrate = turn_rate;
	this->cu_heading = heading;
	this->cl_heading = heading;
	this->cu_alt = alt;
	this->cl_alt = alt;
	this->cu_speed = speed;
	this->cl_speed = speed;
	this->cu_speed_pix = this->cu_speed * 0.1;
	this->cl_direct = direct;
	this->accel = accel_rate;

	this->posx = posx;
	this->posy = posy;

	//IterTimeStamp = QTime().currentTime().second();
	IterTimeStamp = toMsec();

	toMsec();

	apLabel = new LabelComponent(this);

	updateTimer = new QTimer;

	updateTimer->setInterval(3000);
	QObject::connect(updateTimer, SIGNAL(timeout()), this, SLOT(PlaneProcess()));
	updateTimer->start();

	trail_list[0] = new TrailComponent(posx, posy);
	trail_list[1] = new TrailComponent(posx, posy);
	trail_list[2] = new TrailComponent(posx, posy);
	trail_list[3] = new TrailComponent(posx, posy);

	info = 0;

}


RadarItem::~RadarItem() {
	// TODO Auto-generated destructor stub

	delete info;
}

void RadarItem::PlaneProcess()
{
	// get time
	        // compare time with previous process iteration

			//long TimeDiff = System.currentTimeMillis() / 1000 - IterTimeStamp;
	//int TimeDiff = QTime().currentTime().msec() - IterTimeStamp;

	qint64 TimeDiff = toMsec() - IterTimeStamp;

	//qDebug()<<"TimeDiff : "<<TimeDiff<<", IterTimeStamp : "<<IterTimeStamp;
	qDebug()<<"ACID : "<<callsign<<", clHeading : "<<cl_heading<<", cuHeading : "<<cu_heading;

	//test



	// boundary check. >360 and <0
	if(cl_heading>360)
	{
		cl_heading -=360;
	}
	if(cl_heading<0)
	{
		cl_heading +=360;
	}
	// calculate heading
	if (cl_heading != cu_heading)
	{
		if(cu_heading > cl_heading)
		{
			if((cu_heading - cl_heading) <= 180) // turn left
			{
				int delta = (int)TimeDiff * turnrate;
				if (delta > (cu_heading - cl_heading))
				{
					delta = cu_heading - cl_heading;
				}
				cu_heading = cu_heading - delta;
			}else // turn right
	        {
				int delta = (int)TimeDiff * turnrate;
				if (delta > (cu_heading - cl_heading))
				{
					delta = cu_heading - cl_heading;
				}
				cu_heading = cu_heading + delta;
	        }
		}
		else
		{
			if((cl_heading - cu_heading) <= 180) // turn right
			{
				int delta = (int)TimeDiff * turnrate;

				if (delta > (cl_heading - cu_heading))
				{
					delta = cl_heading - cu_heading;
				}
				cu_heading = cu_heading + delta;
			}
			else // turn left
			{
				int delta = (int)TimeDiff * turnrate;
				if (delta > (cl_heading - cu_heading))
				{
					delta = cl_heading - cu_heading;
				}
				cu_heading = cu_heading - delta;
			}
		}

		//test
		if(cu_heading > 720)
		{
			cu_heading = cu_heading % 360;
		}

		if(cu_heading>360)
		{
			cu_heading -=360;
		}
		if(cu_heading<0)
		{
			cu_heading +=360;
		}
	}
	// calculate alt
	if (cl_alt != cu_alt)
	{
		//System.out.println("adjusting alt by " + (int)TimeDiff * climbrate);
		if (cl_alt > cu_alt)
		{
			cu_alt = cu_alt + (int)TimeDiff * climbrate;
			//check for overshoot
			if (cl_alt < cu_alt)
				cu_alt = cl_alt;

		}
		else
		{
			cu_alt = cu_alt - (int)TimeDiff * climbrate;
			// check for overshoot
			if (cl_alt > cu_alt)
				cu_alt = cl_alt;

		}

	}
	// calculate speed
	if (cl_speed != cu_speed)
	{
		//System.out.println("adjusting accel by " + (int)TimeDiff * accel);
		if (cl_speed > cu_speed)
		{
			cu_speed = cu_speed + (int)TimeDiff * accel;
			//check for overshoot
			if (cl_speed < cu_speed)
				cu_speed = cl_speed;

		}
		else
		{
			cu_speed = cu_speed - (int)TimeDiff * accel;
			// check for overshoot
			if (cl_speed > cu_speed)
				cu_speed = cl_speed;

		}

		cu_speed_pix = cu_speed * 0.1;
	}

	//Tail Component

	for(int i=2; i>=0; i--)
	{
		trail_list[i+1]->setPosX(trail_list[i]->getPosX());
		trail_list[i+1]->setPosY(trail_list[i]->getPosY());

		trail_list[i+1]->updatePos();
	}
	trail_list[0]->setPosX(posx);
	trail_list[0]->setPosY(posy);
	trail_list[0]->updatePos();



	// calculate pos x and y
	//get angle with x axis

	int tempheading;
	if (cu_heading - 270 >= 0)
	{
		tempheading = cu_heading - 270;
		// 2nd quadrant
		double delta_y =0;
		double delta_x =0;
//		delta_y = cu_speed_pix * java.lang.Math.sin(java.lang.Math.toRadians(tempheading));
//		delta_x = cu_speed_pix * java.lang.Math.cos(java.lang.Math.toRadians(tempheading));

		delta_y = cu_speed_pix * sin(LatLonConvert::getInstance().calAir()->toRad(tempheading));
		delta_x = cu_speed_pix * cos(LatLonConvert::getInstance().calAir()->toRad(tempheading));

		posx-=delta_x;
		posy-=delta_y;

	}
	else if (cu_heading - 180 >=0)
	{
		tempheading = 270 - cu_heading;
		// 3rd quadrant
		double delta_y =0;
		double delta_x =0;
		delta_y = cu_speed_pix * sin(LatLonConvert::getInstance().calAir()->toRad(tempheading));
		delta_x = cu_speed_pix * cos(LatLonConvert::getInstance().calAir()->toRad(tempheading));
//		delta_y = cu_speed_pix * java.lang.Math.sin(java.lang.Math.toRadians(tempheading));
//		delta_x = cu_speed_pix * java.lang.Math.cos(java.lang.Math.toRadians(tempheading));

		posx-=delta_x;
		posy+=delta_y;

	}
	else if (cu_heading - 90 >= 0)
	{
		tempheading = cu_heading - 90;
		// 4th quadrant
		double delta_y =0;
		double delta_x =0;

//		delta_y = java.lang.Math.sin(java.lang.Math.toRadians(tempheading));
//		delta_x = java.lang.Math.cos(java.lang.Math.toRadians(tempheading));
		delta_y = sin(LatLonConvert::getInstance().calAir()->toRad(tempheading));
		delta_x = cos(LatLonConvert::getInstance().calAir()->toRad(tempheading));

		delta_y *= cu_speed_pix;
		delta_x *= cu_speed_pix;

		posx+=delta_x;
		posy+=delta_y;

	}
	else
	{
		// 1st quadrant
		tempheading = 90 - cu_heading;
		double delta_y =0;
		double delta_x =0;

		delta_y = cu_speed_pix * sin(LatLonConvert::getInstance().calAir()->toRad(tempheading));
		delta_x = cu_speed_pix * cos(LatLonConvert::getInstance().calAir()->toRad(tempheading));
//		delta_y = cu_speed_pix * java.lang.Math.sin(java.lang.Math.toRadians(tempheading));
//		delta_x = cu_speed_pix * java.lang.Math.cos(java.lang.Math.toRadians(tempheading));

		posx+=delta_x;
		posy-=delta_y;


	}

	//IterTimeStamp = System.currentTimeMillis() / 1000;
	IterTimeStamp = toMsec();
	apLabel->setAirplane(this);
	//setPos(posx, posy);
	prepareGeometryChange();
	//qDebug()<<"RadarItem Posx : "<<posx<<", Posy : "<<posy<<", ScenePos : "<<this->scenePos();

	//레이더 Info화면이 떠있는 경우, 레이더 Info 화면을 업데이트 한다.

	if(info != 0)
	{
		info->setItemInfo(0);
	}
}



/*
 * 휠 이벤트 발생시 재드로잉 하는 방법?
 * 1. 현재 X, Y 좌표를 위경도 좌표로 변환한다.
 * 2. Update시 위경도 좌표를 LatLonConvert에 의해서 새로운 X, Y 좌표를 리턴 받음
 */
void RadarItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *  widget )
{
/*	painter->setBrush(brush);
	painter->setPen(pen);*/

	//qDebug()<<"RadarItem painter.. posx : "<<posx<<", posy : "<<posy<<", Scenepos : "<<scenePos();
//	static bool flag = false;
//	if(flag == false){
//		painter->drawRect(posx, posy, 10, 10);
//		flag = true;
//	}else{
//		painter->drawRect(0, 0, 10, 10);
//	}
	painter->setBrush(QBrush(Qt::blue));
	painter->drawRect(posx, posy, 10, 10);
}


QRectF RadarItem::boundingRect() const
{
	qreal adjust = 0.5;

	QRectF rect = QRectF(posx - adjust, posy - adjust, 10 + adjust, 10 + adjust);

	//qDebug()<<"[RadarBoundingRect] rect : "<<rect;
	return rect;
}

void RadarItem::move()
{
	//qDebug()<<"Move is called..";
	qreal xPos = pos().x();
	qreal yPos = pos().y();

	xPos -= 1;

	setPos(xPos, yPos);
}

/*
 * 현재 시간을 msecond로 변경 한다..
 */
qint64 RadarItem::toMsec()
{
	/*int min = QTime().currentTime().minute();
	int sec = QTime().currentTime().second();
	int msec = QTime().currentTime().msec();

	//qDebug()<<"min : "<<min<<", sec : "<<sec<<", msec : "<<msec;

	long result = (min * 60 * 1000) + (sec * 1000) + msec;

	qDebug()<<"Result : "<<result;

	return result;*/

	//qDebug()<<"CurrentTime : "<<QDateTime::currentMSecsSinceEpoch();

	return QDateTime::currentMSecsSinceEpoch() / 1000;
}


void RadarItem::emitTrailComponent()
{
	emit emitTrailComponents(trail_list);
}

//Context
void RadarItem::contextMenuEvent(QGraphicsSceneContextMenuEvent * event)
{
	QMenu menu;
	QAction * infoAction = menu.addAction("Info");
	connect(infoAction, SIGNAL(triggered()), this, SLOT(runInfo()));
	QAction * selectedAction = menu.exec(event->screenPos());
}

void RadarItem::runInfo()
{
	info = new RaderItemInfo(this);
	//widget->show();
}

//mouse press event
void RadarItem::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	qDebug()<<"[RadarItem] - mousePressEvent - call..";

	QGraphicsItem::mousePressEvent(event);

}

void RadarItem::deleteInfo()
{
	delete info;
	info = 0;
}
