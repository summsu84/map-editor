/*
 * WP_1.h
 *
 *  Created on: 2013. 5. 9.
 *      Author: jiwon
 */

#ifndef WP_1_H_
#define WP_1_H_

#include "CommonWP.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsLineItem>
#include <QGraphicsItem>
#include <QThread>
using namespace std;

class WP_1 :  public CommonWP
{
	Q_OBJECT

public:
	WP_1(qreal x, qreal y, qreal x1, qreal y1, int type, QGraphicsItem * parent = 0);
	virtual ~WP_1();
	QGraphicsLineItem *attack();
	QGraphicsLineItem *attack4Node();
	QTimer * updateTimer;
	void move_notimer();
public slots:
	void move();
signals:
	void emitColDetection();
};

#endif /* WP_1_H_ */
