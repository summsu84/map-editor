/*
 * QGraphicsArcItem.cpp
 *
 *  Created on: 2013. 6. 19.
 *      Author: jiwon
 */

#include "QGraphicsArcItem.h"

QGraphicsArcItem::QGraphicsArcItem(QPointF topLeft, QPointF bottomRight, QGraphicsItem * parent) :
QGraphicsEllipseItem(QRectF(topLeft, bottomRight),  parent)
{
	// TODO Auto-generated constructor stub

}


QGraphicsArcItem::QGraphicsArcItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent) :
QGraphicsEllipseItem(x, y, width, height, parent)
{
	// TODO Auto-generated constructor stub

}

QGraphicsArcItem::~QGraphicsArcItem() {
	// TODO Auto-generated destructor stub
}

void QGraphicsArcItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	painter->setPen(pen());
   painter->setBrush(brush());
   painter->drawArc(rect(), startAngle(), spanAngle());

//        if (option->state & QStyle::State_Selected)
//            qt_graphicsItem_highlightSelected(this, painter, option);

}
