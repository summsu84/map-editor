/*
 * TestRect.h
 *
 *  Created on: 2013. 10. 23.
 *      Author: jiwon
 */

#ifndef TESTRECT_H_
#define TESTRECT_H_

#include <QGraphicsItem>

class TestRect : public QGraphicsItem
{
public:
	TestRect();
	virtual ~TestRect();
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
	QRectF boundingRect() const;
};

#endif /* TESTRECT_H_ */
