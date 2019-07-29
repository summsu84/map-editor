/*
 * RadarWidget.cpp
 *
 *  Created on: 2013. 10. 14.
 *      Author: jiwon
 */

#include "RadarWidget.h"
#include <QDebug>
#include <QHBoxLayout>

RadarWidget::RadarWidget(QWidget * parent)
: QWidget(parent)
{
	// TODO Auto-generated constructor stub
	qDebug()<<"[RadarWidget] start..";

	//Btn 생성 및 connect 연결
	btnAdd = new QPushButton("Add");
	connect(btnAdd, SIGNAL(clicked()), this, SLOT(runAdd()));
	btnRemove = new QPushButton("Remove");
	btnShowList = new QPushButton("List");
	btnRight = new QPushButton("Right");
	btnLeft = new QPushButton("Left");

	btnAdd->setMaximumSize(60, 40);
	btnRemove->setMaximumSize(60, 40);
	btnShowList->setMaximumSize(60, 40);
	btnRight->setMaximumSize(60, 40);
	btnLeft->setMaximumSize(60, 40);

	QGridLayout * hbox1 = new QGridLayout;
	hbox1->addWidget(btnAdd, 0, 0);
	hbox1->addWidget(btnRemove, 0 , 1);
	hbox1->addWidget(btnShowList, 0 , 2);
	hbox1->addWidget(btnRight, 0 , 3);
	hbox1->addWidget(btnLeft, 0 , 4);



	rd_view = new RadarView;
	test_view = new TestView;	//test

	//Layout
	QVBoxLayout * vbox = new QVBoxLayout;
	vbox->addItem(hbox1);
	vbox->addWidget(rd_view);
//	vbox->addWidget(test_view);

	this->setLayout(vbox);

	//connect
	connect(btnLeft, SIGNAL(clicked()), this, SLOT(runLeft()));
	connect(btnRight, SIGNAL(clicked()), this, SLOT(runRight()));


//scene->addRect(0, 0, 600, 600, QPen(), QBrush(QColor(Qt::green)));
	//scene->setView(drawingArea);




}

RadarWidget::~RadarWidget() {
	// TODO Auto-generated destructor stub
}


//Resize
void RadarWidget::resizeEvent(QResizeEvent *event)
{
	//view size
	QRect rect(0, 0, rd_view->width(), rd_view->width());
	rd_view->setGraphicsSceneRect(rect);
	rd_view->resize(rect.size());

//	QRect rect(0, 0, test_view->width(), test_view->width());
//	test_view->setGraphicsSceneRect(rect);
//	test_view->resize(rect.size());


	//qDebug()<<"Widget: "<<this->size()<<", view : "<<rd_view->rect()<<", scene : "<<rd_view->getGraphcisScene()->sceneRect();

}

//Add
void RadarWidget::runAdd()
{
	RaderItemInfo * info = new RaderItemInfo("Add");
	connect(info, SIGNAL(emitAddRadarItem(const RDITEM )), rd_view, SLOT(runAddRadarItem(const RDITEM)));
}

void RadarWidget::runLeft()
{
	rd_view->runAlignment(Qt::AlignLeft);
}

void RadarWidget::runRight()
{
	rd_view->runAlignment(Qt::AlignRight);
}

