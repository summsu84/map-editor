/*
 * WP_1.h
 *
 *  Created on: 2013. 5. 9.
 *      Author: jiwon
 */

#ifndef WP_2_H_
#define WP_2_H_

#include "CommonWP.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsLineItem>
#include <QGraphicsItem>
using namespace std;

class WP_2 :  public CommonWP
{
	Q_OBJECT

public:
	WP_2(qreal x, qreal y, qreal x1, qreal y1, int type, QGraphicsItem * parent = 0);
	virtual ~WP_2();
	QGraphicsLineItem *attack();
	QGraphicsLineItem *attack4Node();
	QTimer * updateTimer;
public slots:
	void move();
};

#endif /* WP_2_H_ */
