/*
 * CRectItem.h
 *
 *  Created on: 2013. 6. 4.
 *      Author: jiwon
 */

#ifndef CRECTITEM_H_
#define CRECTITEM_H_

#include <QtGui>
#include <QGraphicsItem>
#include "../../lib/Function.h"

class CRectItem : public QGraphicsRectItem
{
public:
	CRectItem();
	CRectItem(QRectF rectF);
	virtual ~CRectItem();
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
	QRectF boundingRect() const;
	void setShape(DS::Shape shape) { this->shape = shape;}
	void setCRectF(QRectF rectF) { this->rectF = rectF; }
	void setPen(QPen pen) { this->pen = pen; }
	void setBrush(QBrush brush) { this->brush = brush; }
	QPen getPen() { return this->pen; }
	QBrush getBrush() { return brush; }
	int getId() { return this->id; }
	//QPointF getLatLonPoint() { return latlonPoint; }
	void setCompleteRect();
	bool isFirst;
private:
	QPen pen;
	QBrush brush;
	DS::Shape shape;
	QRectF rectF;
	static int id;

	QPointF latlonPoint[2];

};

#endif /* CRECTITEM_H_ */
