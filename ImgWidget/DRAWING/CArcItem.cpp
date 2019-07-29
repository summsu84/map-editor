/*
 * CArcItem.cpp
 *
 *  Created on: 2013. 7. 9.
 *      Author: jiwon
 */

#include "CArcItem.h"
#include "../LATLON/LatLonConvert.h"
#include <math.h>

int CArcItem::id = 0;
CArcItem::CArcItem(QPointF initPoint) {
	// TODO Auto-generated constructor stub
	over180 = false;
	arcDrawing = false;
	setInitPoint(initPoint);
	org_point_list.append(initPoint);
	isFixed = false;
	this->initPoint = initPoint;
	finishArcDrawing = false;
	//path.moveTo(initPoint);

	clockWise = true;
	isUp = false;
	isDown = false;
	currentAngle = 0;
	prevAngle = 0;
	qDebug()<<"org_point_list : "<<org_point_list<<", initpoint : "<<initPoint;;
}

CArcItem::~CArcItem() {
	// TODO Auto-generated destructor stub
}


void CArcItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * /* widget */)
{

	flag = false;

/*
	static bool isFirst = true;
	QPen tmpPen = painter->pen();
	tmpPen.setWidth(4);
	painter->setPen(tmpPen);
*/

	painter->setPen(pen);
	painter->setBrush(brush);

//	if(isFirst == true)
//	{
//		path.moveTo(initPoint);
//		isFirst = false;
//		return;
//	}

	QPainterPath tmpPath;
	QPainterPath arcPath;
	tmpPath.moveTo(initPoint);

	if(arcDrawing == true)
	{
		arcPath = path;

		isEndAngle = false;
		double startAngle = this->getAngle(initPoint, fixedPoint);
		isEndAngle = true;
		double endAngle = getAngle(initPoint, currentPoint);
		QRectF rectF = getRectF();
		arcBoundingRect = rectF;


		//double roundAngle = fmod((720 + endAngle - startAngle), 360);
		double roundAngle = endAngle - startAngle;


		//flag
		prevAngle = currentAngle;
		currentAngle = endAngle;
		double gap = fabs(endAngle - startAngle);
		qDebug()<<"===================gap : "<<gap;
		if(endAngle == startAngle || (int)gap < 2)
		{
			qDebug()<<"=====================EndAngle is same with StartAngle=============";
			isUp = false;
			isDown = false;

		}

		if(endAngle > 0 && endAngle < startAngle){
			if(isUp == true){
				clockWise = false;
			}else{
				isDown = true;
				isUp = false;
				clockWise = true;
			}
		}else if(endAngle > startAngle){
			if(isDown == true){
				clockWise = true;
			}else{
				clockWise = false;
				isDown = false;
				isUp = true;
			}
		}
		qDebug()<<"---start---- clockWise : "<<clockWise<<", isDown : "<<isDown<<", isUp : "<<isUp;

		//endAngle이 0보다 크고 시작 각도 보다 작은경우에
		/*if(endAngle > 0 && endAngle < startAngle){
			currentAngle = endAngle;
			if(currentAngle <= prevAngle){
				if(clockWise == true){
					qDebug()<<"================clockwise===========";
					isDown = true;
					isUp = false;
				}else{
					qDebug()<<"===============counter clock wise==========";
					isDown = false;
					isUp = true;
				}
			}else{
				isDown = false;
				isUp = true;
			}
			flag = true;
		}else{
			qDebug()<<"==============endAngle is over than startAngle..=======";
			if(isDown = true) clockWise = true;
			clockWise = false;

		}
		qDebug()<<"prevAnggle : "<<prevAngle<<", currentAngle : "<<currentAngle;

		if(flag == true){
			if(endAngle >= startAngle){
				if(isDown == true){
					clockWise = true;
				}else{
					clockWise = false;
				}
			}else{
				if(isUp == true){
					clockWise = false;
				}else{
					clockWise = true;
				}
			}
		}*/
		//clockWise = checkClockWise(fixedPoint, currentPoint);
		double tmp;
		//clockwise
	/*	if(endAngle > startAngle){
			tmp = 360 - endAngle + startAngle;
		}else{
			tmp = startAngle - endAngle;
		}*/

		if(clockWise == true){
			if(endAngle > 0 && startAngle > endAngle){
				tmp = startAngle - endAngle;
			}else if(endAngle > startAngle){
				tmp = 360 - endAngle + startAngle;
			}
		}else{
			if(endAngle > 0 && startAngle > endAngle){
				tmp = 360 - startAngle + endAngle;
			}else{
				tmp = endAngle - startAngle;
			}
		}


		qDebug()<<"rect : "<<rectF<<", sa : "<<startAngle<<", ea : "<<endAngle<<", roundAngle : "<<roundAngle;
		qDebug()<<"TmpAngle : "<<tmp;


		//double roundAngle = fmod((720 + endAngle - startAngle), 360);


		/*if(roundAngle < 0){
			clockWise = false;
		}else{
			clockWise = true;
		}*/

		bearing = tmp;

		if(clockWise == true)
			arcPath.arcTo(rectF, startAngle, -tmp);
		else
			arcPath.arcTo(rectF, startAngle, tmp);
/*
		if(clockWise == true)
			arcPath.arcTo(rectF, startAngle, (roundAngle));		// Right wise
		else
			arcPath.arcTo(rectF, startAngle, (roundAngle));		// Right wise
*/
		//path.arcTo(rectF, startAngle, roundAngle);
	//	path.arcTo(rectF, startAngle, (roundAngle));		// Right wise

		if(finishArcDrawing == true)
		{
			qDebug()<<"======finishArc Drawing=====";
			arcPath.closeSubpath();
		}
		//qDebug()<<"RectF : "<<rectF<<"P1 : "<<lineF.p2()<<", P2 : "<<currentPoint<<", cangle : "<<cangle<<", initAngle : "<<initAngle;
		painter->drawPath(arcPath);
	}else{
		tmpPath.lineTo(currentPoint);
		path = tmpPath;
		//painter->drawLine(lineF);
		painter->drawPath(tmpPath);
	}
}

QRectF CArcItem::boundingRect() const
{
	qreal adjust = 5;
	QRectF rect;
	if(finishArcDrawing == false){
		 rect = QRectF(adjust, adjust,
			LatLonConvert::getInstance().srcRect().width() * 1.0, LatLonConvert::getInstance().srcRect().height() * 1.0);
	}else{
		rect =  arcBoundingRect;
	}

	qDebug()<<"[CArcItem - boundingRect] rect : "<<rect;
	return rect;
}


void CArcItem::setFixedPoint(QPointF fixedPoint)
{
	this->fixedPoint = fixedPoint;
	pointCnt++;
	isFixed = true;

	genPointList(this->fixedPoint);

	//두점 사이의 거리를 구한다.
}

/*
 * 마우스 클릭시 고정된 지점에 대한 리스트
 */
void CArcItem::genPointList(QPointF point)
{
	//point_list.clear();

///	org_point_list.append(initPoint);
	org_point_list.append(fixedPoint);
}

/*
 * 폴리곤 생성을 종료 한다.
 */

void CArcItem::completePoint(QPointF curPoint)
{
	setFixedPoint(curPoint);
}

/*
 * 두 점 사이의 각을 구한다. - 미사용
 */

double CArcItem::getAngle(QPointF p1, QPointF p2, bool isClockWise)
{

	/*qreal dx = p2.x() - p1.x();
	qreal dy = p2.y() - p1.y();

	double rad = atan2(dx, dy);

	double dAng = (rad * 180) / 3.14;
*/

	QPointF rotated90Point;

	if(isClockWise){

//		rotated90Point.setX(2500 - (2500 - p1.y()));
		rotated90Point.setX(-p1.y());
		rotated90Point.setY(p1.x());

	}else{
		rotated90Point.setX(p1.y());
		rotated90Point.setY(2500-p1.x());
	}

	qDebug()<<"Rotated90Point : "<<rotated90Point;

	double dAng = acos((rotated90Point.x() * p2.x() + rotated90Point.y() * p2.y()) / (sqrt(rotated90Point.x() * rotated90Point.x()
			+ rotated90Point.y() * rotated90Point.y()) * sqrt(p2.x() * p2.x() + p2.y() * p2.y()))) * 360 / (3.14 * 2);

	if(dAng > 90){
		return 360 - acos((p1.x() * p2.x() + p1.y() * p2.y()) / (sqrt(p1.x() * p1.x() + p1.y() * p1.y()) * sqrt(p2.x() * p2.x() + p2.y() * p2.y()))) * 360 / (3.14 * 2);

	}else
	{
		return acos((p1.x() * p2.x() + p1.y() * p2.y()) / (sqrt(p1.x() * p1.x() + p1.y() * p1.y()) * sqrt(p2.x() * p2.x() + p2.y() * p2.y()))) * 360 / (3.14 * 2);
	}

	return dAng;
}



/*
 *  두 지점을 이용하여 각도를 구한다.
 */
double CArcItem::getAngle(QPointF p1, QPointF p2)
{
	double dx = p2.x() - p1.x();
	double dy = p2.y() - p1.y();

	dy = 0 - dy;

	int mode;

	if(p1.x() <= p2.x() && p1.y() >= p2.y())
	{
		//1사분면
		mode = 1;
	}else if(p1.x() > p2.x() && p1.y() > p2.y())
	{
		//2사분면
		mode = 2;
	}else if(p1.x() > p2.x() && p1.y() < p2.y())
	{
		//3
		mode = 3;
	}else if(p1.x() < p2.x() && p1.y() < p2.y()){
		mode =4;
	}

	return getAngle(dx, dy, mode);
}
/*
 * 두 거리를 이용하여 각도를 구한다.
 */
double CArcItem::getAngle(double dx, double dy, int mode){


	//over90Degree = 0;

	if(dx == 0) dx = 0.00000001;

	double angle = atan(dy/dx) * rad2deg;
	double result = 0;
	double tmp = angle;
	qDebug()<<"[CArcItem - getAngle] angle : "<<angle;


	//1사 분면 체크

	if(isEndAngle == false || isEndAngle == true){
		//start angle case
		if(mode == 2){
			angle = 90 + 90 + angle;
		}else if(mode == 3){
			angle = 180 + angle;
		}else if(mode == 4){
			angle = 270 + 90 + angle;
		}
		qDebug()<<"Mode : "<<mode<<", angle : "<<angle;
	}




	/*if(angle < 0){
		angle += 180;
		over180 = true;
		//over270 = false;
		over180Degree = angle;
		//qDebug()<<"[angle += 180] : "<<angle;
	}

	if(over180 == true && tmp > 0 && isEndAngle == true){

		angle = over180Degree + tmp;
		//qDebug()<<"over180 is called.. angle : "<<over180Degree<<", tmp : "<<tmp<<", result : "<<angle;
		over270 = true;
		over270Degree = angle;
	}

	if(over270 == true && tmp < 0 && isEndAngle == true){
		tmp += 90;
		over180 = false;
		angle = over270Degree + tmp;
		//qDebug()<<"over270 is called.. angle : "<<over270Degree<<", tmp : "<<tmp<<", result : "<<angle;
	}*/





	//over270 = false;

	return angle;
}


/**
 * p2가 중심일때, p1과의 반지름을 구하여 정사각형 Rect를 반환한다..
 */
QRectF CArcItem::getCircleRect(QPointF p1, QPointF p2)
{
	double dx = p2.x() - p1.x();
	double dy = p2.y() - p1.y();

	dy = 0 - dy;
	//double r = sqrt((p2.x() - p1.x()) * (p2.x() - p1.x()) + (p2.y() - p1.y()) * (p2.y() - p1.y()));

	double r= sqrt(dx*dx + dy*dy);

	radius = r;
	//qDebug()<<"r : "<<r;

	return getCircleRect(p2, r);


}

QRectF CArcItem::getCircleRect(QPointF centerPoint, double r)
{
	QPointF topLeft;
	topLeft = QPointF((centerPoint.x() - r), (centerPoint.y() -r));

	QPointF bottomRight(QPointF((centerPoint.x() + r), (centerPoint.y() +r)));

	return QRectF(topLeft, bottomRight);
}

//정사각형 렉트를 반환한다..
QRectF CArcItem::getRectF()
{
	qDebug()<<"fixed Point : "<<fixedPoint<<", initPoint : "<<initPoint;
	return getCircleRect(fixedPoint,initPoint);
}

/*
 * clock wise check
 *
 */

bool CArcItem::checkClockWise(QPointF p1, QPointF p2)
{
	//p1 -> fixed, p2 -> cuurentPoint

	if(p1.y() > p2.y()){
		qDebug()<<"==============counterclcok=========p1 : "<<p1<<", p2 : "<<p2;
		return false;
	}else{
		qDebug()<<"==============clcok=========p1 : "<<p1<<", p2 : "<<p2;
		return true;
	}
}


void CArcItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
 {
     QMenu menu;
     QAction *removeAction = menu.addAction("Remove");
    // connect(removeAction, SIGNAL(triggered()), this, SLOT(removeNode()));
     QAction *markAction = menu.addAction("Bearing");
     connect(markAction, SIGNAL(triggered()), this, SLOT(getBearing()));
     QAction *selectedAction = menu.exec(event->screenPos());

 }



QGraphicsItem * CArcItem::getBearing()
{
	qDebug()<<"Get Bearing is called..";

	QString strBearing = QString::number(bearing, 'f', 1);


	QGraphicsTextItem * txtItem = new QGraphicsTextItem(strBearing.append(" degree"), this);
	txtItem->setPos(fixedPoint.x() + 10, fixedPoint.y());

	emit emitAddTextItem(static_cast<QGraphicsItem *>(txtItem));
}

