/*
 * CEllipseItem.h
 *
 *  Created on: 2013. 6. 4.
 *      Author: jiwon
 */

#ifndef CELLIPSEITEM_H_
#define CELLIPSEITEM_H_

#include <QtGui>
#include <QGraphicsItem>

class CEllipseItem : public QGraphicsEllipseItem
{
public:
	CEllipseItem();
	CEllipseItem(QRectF rectF);
	virtual ~CEllipseItem();
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
	QRectF boundingRect() const;
	void setPen(QPen pen) { this->pen = pen;}
	void setBrush(QBrush brush) { this->brush = brush; }
	int getId() { return this->id; }
	void setComplete();
	bool isFirst;
private:
	QRectF rectF;
	QPen pen;
	QBrush brush;
	static int id;
	QPointF latlonPoint[2];
};

#endif /* CELLIPSEITEM_H_ */
