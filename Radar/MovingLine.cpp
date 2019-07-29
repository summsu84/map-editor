/*
 * MovingLine.cpp
 *
 *  Created on: 2013. 10. 14.
 *      Author: jiwon
 */

#include "MovingLine.h"
#include <QDebug>
#include <QPen>
#include "math.h"
//#define M_PI 3.14

MovingLine::MovingLine(RadarView * view) {
	// TODO Auto-generated constructor stub

	isFirst = true;
	cnt = 0;
	this->view = view;
	updateTimer = new QTimer();
	updateTimer->setInterval(50);
	QObject::connect(updateTimer, SIGNAL(timeout()), this, SLOT(move()));
	updateTimer->start();
	enableMoving = false;
}

MovingLine::~MovingLine() {
	// TODO Auto-generated destructor stub
}


void MovingLine::move()
{
	//qDebug()<<"Move is called..";
	enableMoving = true;
	update();
}

void MovingLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *  widget )
{
	//line을 그린다. - 중심 좌표
	//qDebug()<<"=========================[MovingLine :: paint] ============================";

	if(enableMoving == true){
	int cx = view->width() / 2;
	int cy = view->height() / 2;
	QPoint center_point(cx, cy);			//중심 좌표
	QPen pen(Qt::green);
	painter->setPen(pen);
	new_point = QPoint(cx, view->height());
	if(isFirst == true)
	{
		new_point = QPoint(cx, view->height());
		isFirst = false;
		painter->drawLine(QPoint(cx, 0), new_point);
	}else{
		int x, y;

		QPoint moving_point = this->rotateLatLon(new_point, cnt, center_point);
		painter->drawLine(center_point, moving_point);
		cnt += 5;
	}
	enableMoving = false;
	}

}

QRectF MovingLine::boundingRect() const
{
	qreal adjust = 0.5;

	QRectF rect = QRectF(adjust, adjust,
			view->width() * 1.0, view->height() * 1.0);

	//qDebug()<<"[CRectItem - boundingRect] rect : "<<rect;
	return rect;
}

/*
 * ANGLE 값만 큼 회전한다..
 */
QPoint MovingLine::rotateLatLon(QPoint cur_point, int angle, QPoint wonjum)
{
	//qDebug()<<"[LatLonMng] rotateLatLon is called..";
	double u = wonjum.x();
	double v = wonjum.y();

	QPointF new_point;

	double x = cur_point.x();
	double y = cur_point.y();

	new_point.setX((((x - u) * cos(M_PI/180*angle) + (y - v)*sin(M_PI/180*angle)) + u ) );
	new_point.setY((((x - u) * -sin(M_PI/180*angle) + (y - v)*cos(M_PI/180*angle)) + v ));

	//qDebug()<<"ox : "<<x<<", oy : "<<y;
	//qDebug()<<"nx : "<<new_point.x()<<", yx : "<<new_point.y();
	//qDebug()<<"[LatLonMng] rotateLatLon is close..";

//	latlon_list = tmp;

	//	if(angle == 180){
//		new_point.setX(new_point.x() * -1);
//		new_point.setY(new_point.y() * -1);
//	}

	return new_point.toPoint();
}
