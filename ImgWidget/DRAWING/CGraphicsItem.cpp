/*
 * CGraphicsItem.cpp
 *
 *  Created on: 2013. 6. 4.
 *      Author: jiwon
 */

#include "CGraphicsItem.h"

CGraphicsItem::CGraphicsItem(QGraphicsItem * parent)
: QGraphicsItem(parent)
{
	// TODO Auto-generated constructor stub

}

CGraphicsItem::~CGraphicsItem() {
	// TODO Auto-generated destructor stub
}

/*

QRectF CGraphicsItem::boundingRect() const
{

	 qreal penWidth = 1;
	 return QRectF(-10 - penWidth / 2, -10 - penWidth / 2,  20 + penWidth, 20 + penWidth);

}

void QGraphicsItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	//painter->drawRoundRect(2500, 2500, 20, 20, 5, 5);
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
*/
