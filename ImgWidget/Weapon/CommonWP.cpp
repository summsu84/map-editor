/*
 * CommonWP.cpp
 *
 *  Created on: 2013. 5. 9.
 *      Author: jiwon
 */

#include "CommonWP.h"
#include <QPen>

CommonWP::CommonWP(qreal x, qreal y, qreal x1, qreal y1, QGraphicsItem * parent)
:QGraphicsLineItem(x, y, x1, y1, parent)
{
	// TODO Auto-generated constructor stub

}

CommonWP::~CommonWP() {
	// TODO Auto-generated destructor stub
}

void CommonWP::setWPBrush(QColor color)
{
	QPen * pen1 = new QPen(color);
	setPen(*pen1);
}
