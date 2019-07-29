/*
 * ConnectLine.h
 *
 *  Created on: 2013. 10. 22.
 *      Author: jiwon
 */

#ifndef CONNECTLINE_H_
#define CONNECTLINE_H_

#include <QGraphicsItem>
#include "../Track/LabelComponent.h"


class LabelComponent;
class ConnectLine : public QGraphicsItem
{
public:
	ConnectLine(LabelComponent * label);
	virtual ~ConnectLine();
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
	QRectF boundingRect() const;
	void setLabelComponent(LabelComponent * label);
	void adjust();
private :
	LabelComponent * label;

	QPointF sourcePoint;
	QPointF destPoint;
};

#endif /* CONNECTLINE_H_ */
