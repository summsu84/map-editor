/*
 * Radar.cpp
 *
 *  Created on: 2013. 10. 14.
 *      Author: jiwon
 */

#include "Radar.h"

Radar::Radar() {
	// TODO Auto-generated constructor stub

}

Radar::Radar(RadarView * view)
{
	// TODO Auto-generated constructor stub
	this->view = view;
}


Radar::~Radar() {
	// TODO Auto-generated destructor stub
}

void Radar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *  widget )
{

	//원을 그린다.
	int gap = 50;
	int egap = 50;

	//line을 그린다. - 중심 좌표
	drawLine(painter);
	drawRadarCircle(painter, gap);
	drawBearing(painter);

/*	QRect rect(0+gap, 0+gap, view->width() - gap * 2, view->height() - gap * 2);
	QRect rect1(0+gap * 2, 0+gap * 2, view->width() - gap * 4, view->height() - gap * 4);

	painter->drawEllipse(rect);
	painter->drawEllipse(rect1);*/
	//painter->drawRect(rect);

}

void Radar::drawLine(QPainter * painter)
{
	int cx = view->width() / 2;
	int cy = view->height() / 2;
	QPoint point(cx, cy);			//중심 좌표

	painter->drawLine(QPoint(cx, 0), QPoint(cx, view->height()));
	painter->drawLine(QPoint(0, cy), QPoint(view->width(), cy));

}

void Radar::drawRadarCircle(QPainter * painter, int gap)
{
	//화면의 크기에 따라서
	//width의 크기가 400 이면 3개의 circle을, 5개이면 4개의 circle을 생성한다.
	int view_width = view->width();
	int circle_cnt = view_width / 100 - 1;

	for(int i = 0 ; i < circle_cnt ; i++){
		QRect rect(gap + (gap * i), gap + (gap * i), view->width() - gap * (i+1)*2, view->height() - gap * (i+1)*2);
		painter->drawEllipse(rect);
	}
}

/**
 * Bearing을 표시 한다. 북쪽 - 0, 동쪽 - 180, 남쪽 - 180, 서쪽 - 270
 */
void Radar::drawBearing(QPainter * painter)
{
	QStringList str_bearing;
	str_bearing<<"0"<< "90"<< "180"<< "270";

	int adjust = 20;

	QPoint pos [4]= {QPoint(view->width() / 2, 0), QPoint(view->width() - adjust, view->height() / 2), QPoint(view->width() /2 , view->height() - adjust), QPoint(0 + adjust, view->height() / 2)};
//	QPoint north = QPoint(view->width() / 2, 0);
//	QPoint east = QPoint(view->width(), view->height() / 2);
//	QPoint south = QPoint(view->width() /2 , view->height());
//	QPoint west = QPoint(0, view->height() / 2);

	for(int i = 0 ; i < 4 ; i++){
		painter->drawText(pos[i], str_bearing.at(i));
	}


}

QRectF Radar::boundingRect() const
{
	qreal adjust = 0.5;

	QRectF rect = QRectF(adjust, adjust,
			view->width() * 1.0, view->height() * 1.0);

	//qDebug()<<"[CRectItem - boundingRect] rect : "<<rect;
	return rect;
}
