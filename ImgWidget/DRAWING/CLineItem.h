/*
 * CLineItem.h
 *
 *  Created on: 2013. 6. 4.
 *      Author: jiwon
 */

#ifndef CLINEITEM_H_
#define CLINEITEM_H_

#include <QtGui>
#include <QGraphicsLineItem>
#include <QObject>
#include "PosMng.h"
//#include "CGraphicsItem.h"

class CLineItem : public QObject, public QGraphicsLineItem, public PosMng
{
	Q_OBJECT

public:
	CLineItem(QGraphicsLineItem * parent=0);
	CLineItem(const QLineF &line, QGraphicsLineItem * parent = 0);
	virtual ~CLineItem();
	void getLine();
	void genLatLonPos();
	void setInitLine();
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
	QRectF boundingRect() const;
	void setPen(QPen pen) { this->pen = pen; }
	void setBrush(QBrush brush) { this->brush = brush; }
	QPen getPen() { return this->pen; }
	QBrush getBrush() { return brush; }
	int getId(){ return this->id; }
	void setComplete();
	bool isFirst;
public slots:
	void removeNode();
	QGraphicsItem * getDistance();
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

signals:
	void emitAddTextItem(QGraphicsItem * txtItem);

private:
	QPen pen;
	QBrush brush;

	QPointF latlonPoint_1;
	QPointF latlonPoint_2;

	QLineF initLine;
	QLineF prevLine;
	QLineF curLine;

	static int id;

	QPointF latlonPoint[2];

};

#endif /* CLINEITEM_H_ */
