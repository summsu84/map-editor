/*
 * TestView.h
 *
 *  Created on: 2013. 10. 23.
 *      Author: jiwon
 */

#ifndef TESTVIEW_H_
#define TESTVIEW_H_

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

class TestView : public QGraphicsView
{
public:
	TestView(QWidget * parent = 0);
	virtual ~TestView();
	void setGraphicsSceneRect(QRect rect);
private :
	QGraphicsScene * scene;
	QGraphicsRectItem * rect1;
	QGraphicsRectItem * rect2;

};

#endif /* TESTVIEW_H_ */
