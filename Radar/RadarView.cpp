/*
 * RadarView.cpp
 *
 *  Created on: 2013. 10. 14.
 *      Author: jiwon
 */

#include "RadarView.h"
#include <QPen>
#include <QBrush>
#include <QDebug>
#include "TestRect.h"

RadarView::RadarView(QWidget * parent)
: QGraphicsView(parent){
	// TODO Auto-generated constructor stub
	qDebug()<<"RadarView is called..";
	this->setMouseTracking(true);
	setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	setInteractive(true);
	setViewportUpdateMode(BoundingRectViewportUpdate);

	scene = new QGraphicsScene(this);
	scene->setSceneRect(0, 0, 400, 400);
	//scene->addRect(0, 0, 400, 400, QPen(), QBrush(QColor(Qt::green)));

	this->setScene(scene);
	//scene->setSceneRect()
	drawRadar();
}

RadarView::~RadarView() {
	// TODO Auto-generated destructor stub
}

void RadarView::setGraphicsSceneRect(QRect rect)
{
	qDebug()<<"[RadarView] setGraphicsSceneRect called..";
//	scene->clear();
	scene->setSceneRect(rect);
//	scene->addRect(rect, QPen(), QBrush(QColor(Qt::green)));
}


void RadarView::drawRadar()
{
	qDebug()<<"DrawRadar is called..";

	Radar * rd = new Radar(this);
	MovingLine * line = new MovingLine(this);

	/*TestRect * trect = new TestRect;
	RadarItem * item = new RadarItem("a1", 50, 5, 100, 30000, "bogus1", 200, 200, 200, 10, trect);
	RadarItem * item1 = new RadarItem("b1", 50, 15, 100, 30000, "test2", 200, 200, 200, 10, trect);
*/
	//scene->addItem(trect);
	scene->addItem(rd);
	scene->addItem(line);

/*	addRadarItem(item, 80);
	addRadarItem(item1, 80);*/
	testRadarItem();
}

void RadarView::testRadarItem()
{
	TestRect * trect = new TestRect;

	for(int i = 0 ; i < 10 ; i++){

		QString acid = "TEST_";
		QString direct = "BOGUS_";
		acid.append(QString().setNum(i, 10));
		direct.append(QString().setNum(i, 10));

		RadarItem * item = new RadarItem(acid, 50, 5, 100, 30000, direct, 100, 100 + (i * 30), 100 + (i * 30), 10, trect);
		addRadarItem(item, 80);
	}



	//RadarItem * item1 = new RadarItem("b1", 50, 15, 100, 30000, "test2", 200, 200, 200, 10, trect);


}


//레이더 아이템을 등록한다.
void RadarView::addRadarItem(RadarItem * item, int direction)
{
	connect(item, SIGNAL(emitTrailComponents(TrailComponent **)), this, SLOT(updateTrack(TrailComponent **)));

	item->emitTrailComponent();
	item->SetClearAlt(1000);
	item->SetClearHeading(direction);

	scene->addItem(item);
	scene->addItem(item->apLabel);
	scene->addItem(item->apLabel->cline);

}

void RadarView::updateTrack(TrailComponent ** trail_list)
{
	/*for(int i = 0 ; i < planeList.size() ; i++){
		Airplane * ap = planeList.at(i);
		ap->PlaneProcess();
	}*/

	qDebug()<<"UpdateTrack is called.";


	scene->addItem(trail_list[0]);
	scene->addItem(trail_list[1]);
	scene->addItem(trail_list[2]);
	scene->addItem(trail_list[3]);
}



//Mouse press event
void RadarView::mousePressEvent(QMouseEvent * event)
{
	qDebug()<<"[RadarView] mousepressevent..call";
	QGraphicsView::mousePressEvent(event);
}


void RadarView::runAddRadarItem(const RDITEM item)
{
	qDebug()<<"=============runAddRadarItem is called. ==============";
	bool ok;
	//RadarItem * item = new RadarItem("a1", 50, 5, 100, 30000, "bogus1", 200, 200, 200, 10);
	RadarItem * rditem = new RadarItem(item.acid, 	50, 			5, 	100,	 item.cu_alt.toInt(&ok, 10),
										    item.to, 	item.cl_spd, 200, 	200,  10);
	connect(rditem, SIGNAL(emitTrailComponents(TrailComponent **)), this, SLOT(updateTrack(TrailComponent **)));
	rditem->emitTrailComponent();
	rditem->SetClearAlt(item.cl_alt.toInt(&ok, 10));
	rditem->SetClearHeading(item.cl_heading);
	scene->addItem(rditem);
	scene->addItem(rditem->apLabel);
	scene->addItem(rditem->apLabel->cline);
}

//View의 모든 라벨을 왼쪽 정렬 시킨다.
void RadarView::runAlignment(Qt::Alignment alignment)
{
	qDebug()<<"[RadarView] runLeftAlignment";
	for(int i = 0 ; i < scene->items().size() ; i++)
	{
		QGraphicsItem * grpItem = scene->items().at(i);
		qDebug()<<"grpItem type : "<<grpItem->type();
		if(grpItem->type() == QGraphicsItem::UserType +10)
		{
			LabelComponent * lblItem = dynamic_cast<LabelComponent *>(grpItem);
			if(lblItem == 0){
				qDebug()<<"casting is failed...";
				return;
			}
			lblItem->setAlignment(alignment);
		}
	}
}
