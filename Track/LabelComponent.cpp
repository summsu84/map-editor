/*
 * LabelComponent.cpp
 *
 *  Created on: 2013. 9. 23.
 *      Author: jiwon
 */

#include "LabelComponent.h"
#include "../ImgWidget/LATLON/LatLonConvert.h"
#include <QRect>

#define MAX_X 60
#define MAX_Y 60

LabelComponent::LabelComponent(){
	// TODO Auto-generated constructor stub

}

LabelComponent::LabelComponent(Airplane * airplane)
{
	// TODO Auto-generated constructor stub

	//this->airplane = airplane;
}
LabelComponent::LabelComponent(RadarItem * airplane, QGraphicsItem * parent):
QGraphicsItem(parent)
{
	// TODO Auto-generated constructor stub

	gapx = 0;
	gapy = 0;
	isPressed = false;
	this->airplane = airplane;
	setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(ItemSendsGeometryChanges);
	this->setCacheMode(DeviceCoordinateCache);
	//this->setZValue(-1);
	cline = new ConnectLine(this);
	itemMoved = false;

}

LabelComponent::~LabelComponent() {
	// TODO Auto-generated destructor stub
}

void LabelComponent::setAirplane(RadarItem * airplane)
{
	this->airplane = airplane;
	this->cline->setLabelComponent(this);
	//qDebug()<<"[LabelComponent - setAirplane] posx : "<<airplane->getPosX();
	//prepareGeometryChange();
	update();
}

void LabelComponent::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *  widget )
{
/*	painter->setBrush(brush);
	painter->setPen(pen);*/
//	setPos(QPointF( 0, 0));
	int x = airplane->getPosX();
	int y = airplane->getPosY();
	int w = 60;
	int h = 40;
	QRect rect(x, y , w, h);				//드로잉 Rect 아이템의 Rect

	//length check
	if(gapx > MAX_X || gapx < -MAX_X)
	{
		if(gapx > MAX_X)
			gapx = MAX_X;
		else
			gapx = - MAX_X;
		setPos(gapx, gapy);
	}
	if(gapy > MAX_Y){
		gapy = MAX_Y;
		setPos(gapx, gapy);
	}else if(gapy < -MAX_Y){
		gapy = -MAX_Y;
		setPos(gapx, gapy);
	}



	QRect boundingRect(x + gapx, y + gapy, w, h);				//현재 아이템이 이동했을 때 (setPos) gap을 반영한 rect -> 라인을 드로잉 하기 위해 사용
	brectf = boundingRect;

	realLabelPos = QPoint(x, y);
	//qDebug()<<"[LabelComponent] paitn brectf : "<<brectf<<", item pos : "<<this->scenePos()<<", gapx : "<<gapx<<", gapy : "<<gapy;

	//airplane점과 렉트의점 사이의 거리가 일정 값 이상일 때
	QLineF line(QPoint(airplane->getPosX(), airplane->getPosY()), QPoint(rect.topLeft()));
	qDebug()<<"[LabelComponent - paitn] linelength : "<<line.length();
	qDebug()<<"[LabelComponent - paint] airplanePoint : "<<QPoint(airplane->getPosX(), airplane->getPosY())<<", brectf : "<<brectf<<", TmpRectF : "<<tmpRectF<<", Ismoved : "<<itemMoved<<", pos : "<<pos();


	painter->setBrush(Qt::white);
	painter->drawRect(rect);
	//qDebug()<<"[LabelComponent] callsign : "<<airplane->getCallSign()<<", heading : "<<airplane->getCuHeading()<<", rect : "<<rect;
	QString lbl = airplane->getCallSign();
	lbl.append(" ");
	lbl.append(QString::number(airplane->getCuHeading(), 10));
	lbl.append("\n");
	lbl.append(QString::number(airplane->getCuSpeed(), 10));
	painter->drawText(rect, lbl);

	if(itemMoved == false)
		cline->adjust();

}


QRectF LabelComponent::boundingRect() const
{
	qreal adjust = 0.5;

//	QRectF rect = QRectF(adjust, adjust,
//			LatLonConvert::getInstance().srcRect().width() * 1.0, LatLonConvert::getInstance().srcRect().height() * 1.0);
	QRectF rect = QRectF(airplane->getPosX(), airplane->getPosY(), 60, 40);
	//QRectF rect = QRectF(0,0,800,800);

	//qDebug()<<"[LabelComponent] boundingRect : "<<rect;

	return rect;
}

//Airplane의 위치를 리턴한다.
QPoint LabelComponent::getAirplanePos()
{
	return QPoint(airplane->getPosX() + 5, airplane->getPosY() + 5);
}

QPoint LabelComponent::getLabelPos()
{
	//qDebug()<<"[LabelComponent - getLabelPos] brect : "<<brectf;
//	if(itemMoved == false){
//		return tmpRectF.center().toPoint();
//	}else
//	{
//		return tmpRectF.center().toPoint();
//	}

	return brectf.center().toPoint();

}

//ItemChange

QVariant LabelComponent::itemChange(GraphicsItemChange change, const QVariant & value)
{
	//qDebug()<<"Item change is called..";
//	qDebug()<<"Change value : "<<change;
	switch(change){
	//qDebug()<<"Change value : "<<change;
		case ItemPositionHasChanged:
		{
			//qDebug()<<"[LabelComponent] itemhascanged is called..";
			itemMoved = true;
			QPointF newPos = value.toPointF();

			QRectF rect = scene()->sceneRect();

			qDebug()<<"[ItemChagne] - OrignalPos : "<<QPoint(airplane->getPosX(), airplane->getPosY())<<", newPos : "<<newPos;

			//아이템이 원점에서 이동한 좌표 x, y
			gapx = newPos.x();
			gapy = newPos.y();

			int x = airplane->getPosX() + gapx;
			int y = airplane->getPosY() + gapy;
			int w = 60;
			int h = 40;

			//사용자가 마우스로 이동시킨 렉트
			QRectF tmp(x, y, w, h);
			brectf = tmp;
			//qDebug()<<"[item change] brectf : "<<tmpRectF<<", gapx : "<<gapx<<", gapy : "<<gapy;
//
//			QPointF tmp = brectf.topLeft();
//			tmp.setX(tmp.x() + newPos.x());
//			tmp.setY(tmp.y() + newPos.y());
//
//			tmpRectF = QRectF(tmp.x(), tmp.y(), 60, 40);
			cline->adjust();
			if(!rect.contains(newPos))
			{
				newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
				newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
				qDebug()<<"=======================test====================";
				qDebug()<<"newPos : "<<newPos;
				qDebug()<<"===============================================";
				return newPos;
			}


			break;
		}
		default :
			break;
	}

	return QGraphicsItem::itemChange(change, value);
}

void LabelComponent::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	isPressed = true;
	update();
	QGraphicsItem::mousePressEvent(event);
}

void LabelComponent::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
	qDebug()<<"MouseReleaseEvent is called..";
	itemMoved = false;
	isPressed = false;
//	gapx = 0;
//	gapy = 0;
	update();
	QGraphicsItem::mouseReleaseEvent(event);
}

void LabelComponent::setAlignment(Qt::Alignment alignment)
{

	qDebug()<<"[LabelComponent] setAlignment is called.. alignment : "<<alignment;
	int posx = pos().x();
	int posy = pos().y();
	switch(alignment)
	{
		case Qt::AlignLeft  :
		{
			this->setPos(-120, -20);
			gapx = -120;
			gapy = -20;
			break;
		}
		case Qt::AlignRight :
		{
			this->setPos(60, -20);
			gapx = 60;
			gapy = -20;

			break;
		}
		case Qt::AlignCenter :
		{
			this->setPos(0, -20);
			gapx = 0;
			gapy = -20;
			break;
		}

	}
	setBoundingRect4Line(realLabelPos.x() + gapx, realLabelPos.y() + gapy, 60, 40);
	cline->adjust();
}

void LabelComponent::setBoundingRect4Line(int x, int y, int w, int h)
{
	QRect tmp(x, y, w, h);
	brectf = tmp;
}
