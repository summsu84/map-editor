/*
 * ProgressObj.cpp
 *
 *  Created on: 2013. 6. 13.
 *      Author: jiwon
 */

#include "ProgressObj.h"
#include <QDebug>

ProgressObj::ProgressObj(QObject * parent)
: QObject(parent)
{
	// TODO Auto-generated constructor stub
	step = 0;
	pd = new QProgressDialog("Operation in progress", "cancel", 0, 200);
	pd->show();
	//onnect(pd)
	timer = new QTimer;
	timer->setInterval(100);
	connect(timer, SIGNAL(timeout()), this, SLOT(perform()));
	timer->start();
}

ProgressObj::~ProgressObj() {
	// TODO Auto-generated destructor stub
}

void ProgressObj::perform()
{

	qDebug()<<"[ProgressObj] perfrom called..";
	pd->setValue(step);

	step++;

	if(step > pd->maximum()){
		timer->stop();
	}
}

void ProgressObj::cancel()
{
	pd->setValue(200);
	timer->stop();
}
