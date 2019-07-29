/*
 * MppItem.h
 *
 *  Created on: 2013. 7. 3.
 *      Author: jiwon
 */

#ifndef MPPITEM_H_
#define MPPITEM_H_

#include <QtGui>
#include <QGraphicsItem>
#include <QVector>
#include "../LATLON/LatLonConvert.h"
#include "../../lib/Function.h"


class MppItem : public QGraphicsItem
{
	enum { Type = UserType + 4 };
public:
	MppItem();
	MppItem(QPointF point, QString text);
	virtual ~MppItem();
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
	QRectF boundingRect() const;
	void setPoint(QPointF point) { this->point = point; }
	void setStrMpp(QPointF point);
	void setStrMpp(QString text) { this->strMpp = text; }
	int type() const
	{
		return Type;
	}
private:

	QPointF point;
	QString strMpp;
	void drawText(QPainter * painter);
};

#endif /* MPPITEM_H_ */
