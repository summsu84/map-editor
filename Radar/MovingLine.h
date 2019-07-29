/*
 * MovingLine.h
 *
 *  Created on: 2013. 10. 14.
 *      Author: jiwon
 */

#ifndef MOVINGLINE_H_
#define MOVINGLINE_H_

#include <QGraphicsItem>
#include "RadarView.h"
#include <QObject>
#include <QTimer>

class RadarView;
class MovingLine : public QObject, public QGraphicsItem
{
	Q_OBJECT
public:
	MovingLine(RadarView * view);
	virtual ~MovingLine();
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
	QRectF boundingRect() const;
	QPoint rotateLatLon(QPoint cur_point, int angle, QPoint wonjum);
public slots:
	void move();
private :
	RadarView * view;
	QTimer * updateTimer;
	QPoint new_point;
	bool isFirst;
	int cnt;
	bool enableMoving;
};

#endif /* MOVINGLINE_H_ */
