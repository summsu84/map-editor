/*
 * LabelComponent.h
 *
 *  Created on: 2013. 9. 23.
 *      Author: jiwon
 */

#ifndef LABELCOMPONENT_H_
#define LABELCOMPONENT_H_

#include <QLabel>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include "Airplane.h"
#include "../Radar/RadarItem.h" //test
#include "../Radar/ConnectLine.h"
#include <QPainter>
class Airplane;
class RadarItem;
class ConnectLine;
class LabelComponent : public QGraphicsItem
{
public:
	enum { Type = UserType + 10 };
	LabelComponent();
	LabelComponent(Airplane * airplane);
	LabelComponent(RadarItem * airplane, QGraphicsItem * parent = 0);
	virtual ~LabelComponent();
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
	QRectF boundingRect() const;
	void setAirplane(RadarItem * airplane);
	QPoint getAirplanePos();
	QPoint getLabelPos();
	ConnectLine * cline;
	void setAlignment(Qt::Alignment alignment);
	void setBoundingRect4Line(int x, int y, int w, int h);
	int type() const
	{
		return Type;
	}
protected :
	QVariant itemChange(GraphicsItemChange change, const QVariant & value);
	void mousePressEvent(QGraphicsSceneMouseEvent * event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
private:
	//Airplane * airplane;
	RadarItem * airplane;

	QPointF currentPos;
	QPoint realLabelPos;	//실제 드로잉되는 라벨의 위치 (실제 드로잉 될때에는 airplane의 위치)
	QRectF brectf;			//Airplane의 위치에 따라 고정된 렉트
	QRectF tmpRectF;		//item change 이벤트 발생시 임시 렉트
	//QRectF tmpRectF;		//아이템이 이동한뒤의 라벨의 렉탱글
	int gapx;				//아이템을 이동했을 때, x 축 gap
	int gapy;
	bool itemMoved;
	bool isPressed;			//false : Release, true : pressed
};

#endif /* LABELCOMPONENT_H_ */
