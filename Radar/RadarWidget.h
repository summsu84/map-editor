/*
 * RadarWidget.h
 *
 *  Created on: 2013. 10. 14.
 *      Author: jiwon
 */

#ifndef RADARWIDGET_H_
#define RADARWIDGET_H_

#include <QWidget>
#include <QtGui>
#include "RadarView.h"
#include "../lib/Function.h"
#include "TestView.h"

class RadarWidget : public QWidget
{
	Q_OBJECT
public:
	RadarWidget(QWidget * parent = 0);
	virtual ~RadarWidget();

public slots:
	void runAdd();
	void runRight();
	void runLeft();
protected:
	void resizeEvent(QResizeEvent *event);

private:
	RadarView * rd_view;
	TestView * test_view;
	QPushButton * btnAdd;
	QPushButton * btnRemove;
	QPushButton * btnShowList;
	QPushButton * btnLeft;
	QPushButton * btnRight;
};

#endif /* RADARWIDGET_H_ */
