/*
 * TestView.cpp
 *
 *  Created on: 2013. 10. 23.
 *      Author: jiwon
 */

#include "TestView.h"
#include <QDebug>

TestView::TestView(QWidget * parent)
: QGraphicsView(parent)
{
	// TODO Auto-generated constructor stub

	scene = new QGraphicsScene;

	rect1 = scene->addRect(QRectF(100,100,50,100), QPen(Qt::red), QBrush(Qt::green));
	rect2 = scene->addRect(QRectF(10, 10, 10, 10), QPen(Qt::black), QBrush(Qt::yellow));
	rect2->setParentItem(rect1);
	rect2->setPos(30, 30);

	qDebug()<<"Rect1 - ScenePos : "<<rect1->scenePos();
	qDebug()<<"Rect1 - Pos : "<<rect1->pos();
	qDebug()<<"Rect1 - boundingRect : "<<rect1->boundingRect();

	qDebug()<<"Rect2 - ScenePos : "<<rect2->scenePos();
	qDebug()<<"Rect2 - Pos : "<<rect2->pos();
	qDebug()<<"Rect2 - boundingRect : "<<rect2->boundingRect();
	scene->setSceneRect(0, 0, 400, 400);
	//scene->addRect(0, 0, 400, 400, QPen(), QBrush(QColor(Qt::green)));

	this->setScene(scene);

}

TestView::~TestView() {
	// TODO Auto-generated destructor stub
}
void TestView::setGraphicsSceneRect(QRect rect)
{
	//qDebug()<<"[TestView] setGraphicsSceneRect called..";
//	scene->clear();
	scene->setSceneRect(rect);
//	scene->addRect(rect, QPen(), QBrush(QColor(Qt::green)));
}
