/*
 * CPolyGonItem.h
 *
 *  Created on: 2013. 7. 8.
 *      Author: jiwon
 */

#ifndef CPOLYGONITEM_H_
#define CPOLYGONITEM_H_

#include <QtGui>
#include <QGraphicsItem>

class CPolyGonItem : public QGraphicsItem
{
	enum { Type = UserType + 1 };

public:
	CPolyGonItem();
	CPolyGonItem(QPointF initPoint);
	virtual ~CPolyGonItem();
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
	QRectF boundingRect() const;

	void setPolygon(QPolygonF polygon) { this->polygon = polygon; }
	QPolygonF& getPolygon(){ return this->polygon; }
	QPolygonF getPolygonNR() { return this->polygon; }
	void genPointList(QPointF point);
	int& getPointCnt() { return pointCnt; }
	void setInitPoint(QPointF initPoint) { this->initPoint = initPoint; }
	QPointF getInitPoint(){ return this->initPoint; }
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
	void setComplete();
	bool isFirst;
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

	QVector<QPointF> latlonPoint_list;

};



#endif /* CPOLYGONITEM_H_ */
