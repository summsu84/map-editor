/*
 * MyScrollBar.cpp
 *
 *  Created on: 2013. 7. 17.
 *      Author: jiwon
 */

#include "MyScrollBar.h"
#include <QDebug>

MyScrollBar::MyScrollBar() {
	// TODO Auto-generated constructor stub

	qDebug()<<"ScrollBar..";
}

MyScrollBar::~MyScrollBar() {
	// TODO Auto-generated destructor stub
}

void MyScrollBar::sliderChange(SliderChange change)
{
	qDebug()<<"SliderChange..";
}
