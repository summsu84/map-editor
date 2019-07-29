/*
 * QGraphicsArcItem.h
 *
 *  Created on: 2013. 6. 19.
 *      Author: jiwon
 */

#ifndef QGRAPHICSARCITEM_H_
#define QGRAPHICSARCITEM_H_

#include <QGraphicsEllipseItem>
#include <QPointF>
#include <QPainter>
//#include <>

class QGraphicsArcItem : QGraphicsEllipseItem
{
public:
	QGraphicsArcItem(QPointF topLeft, QPointF bottomRight, QGraphicsItem * parent = 0);
	QGraphicsArcItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = 0);
	virtual ~QGraphicsArcItem();

protected:
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
};

#endif /* QGRAPHICSARCITEM_H_ */
