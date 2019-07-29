/*
 * CPolyLineItem.h
 *
 *  Created on: 2013. 7. 9.
 *      Author: jiwon
 */

#ifndef CPOLYLINEITEM_H_
#define CPOLYLINEITEM_H_

#include <QtGui>
#include <QGraphicsItem>

class CPolyLineItem : public QGraphicsItem
{
	enum { Type = UserType + 2 };
public:
	CPolyLineItem(QPointF initPoint);
	virtual ~CPolyLineItem();
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
	QRectF boundingRect() const;

	void setPolygon(QPolygonF polygon) { this->polygon = polygon; }
	QPolygonF& getPolygon(){ return this->polygon; }
	void genPointList(QPointF point);
	int& getPointCnt() { return pointCnt; }
	void setInitPoint(QPointF initPoint) { this->initPoint = initPoint; }
	void setCurrentPoint(QPointF currentPoint) { this->currentPoint = currentPoint; isFixed = false;}
	void setFixedPoint(QPointF fixedPoint);
	void completePoint(QPointF curPoint);
	void setPen(QPen pen) { this->pen = pen; }
	void setBrush(QBrush brush) { this->brush = brush; }

	int type() const
	{
		return Type;
	}
	int getId() { return id;}
private:

	QPen pen;
	QBrush brush;

	QPolygonF polygon;
	QVector<QPointF> point_list;
	QVector<QPointF> org_point_list;

	QPointF initPoint;				//최초 포인트 지점
	QPointF currentPoint;			//마우스 무빙시 현재 지점
	QPointF fixedPoint;			//마우스 클릭시 결정된 지점
	bool isFixed;

	int pointCnt;

	static int id;
};

#endif /* CPOLYLINEITEM_H_ */
