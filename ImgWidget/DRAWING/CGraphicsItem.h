/*
 * CGraphicsItem.h
 *
 *  Created on: 2013. 6. 4.
 *      Author: jiwon
 */

#ifndef CGRAPHICSITEM_H_
#define CGRAPHICSITEM_H_

/*
 * QGrapchisItem 클래스의 서브클래스
 */
#include <QtGui>
#include <QPainter>
#include <QGraphicsItem>
#include <QObject>

class CGraphicsItem : public QObject, public QGraphicsItem
{
	Q_OBJECT
public:
	CGraphicsItem(QGraphicsItem * parent = 0);
	virtual ~CGraphicsItem();
//	QRectF boundingRect() const;
//	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget = 0);
};

#endif /* CGRAPHICSITEM_H_ */
