/*
 * AngleInfo.cpp
 *
 *  Created on: 2013. 6. 5.
 *      Author: jiwon
 */

#include "AngleInfo.h"

AngleInfo::AngleInfo(int angle, int scale, QDialog * parent)
: QDialog(parent)
{
	// TODO Auto-generated constructor stub

	init(angle, scale);
}

AngleInfo::~AngleInfo() {
	// TODO Auto-generated destructor stub
}

void AngleInfo::init(int angle, int scale)
{

	btnOk = new QPushButton(tr("Ok"));
	btnCancel = new QPushButton(tr("Cancel"));

	connect(btnOk, SIGNAL(clicked()), this, SLOT(runOk()));
	connect(btnCancel, SIGNAL(clicked()), this, SLOT(close()));
	//Label
	QLabel * lblHead = new QLabel(tr("<h2>ANGLE SET"));
	QLabel * lblAngle = new QLabel(tr("<h4>Angle : "));

	txtAngle = new QLineEdit;
	txtAngle->setText(QString::number(angle, 10));

	//Slider
	QLabel * lblScale = new QLabel(tr("<h4>Scale"));

	txtScale = new QLineEdit;
	txtScale->setMaximumWidth(40);
	sldScale = new QSlider(Qt::Horizontal);
	sldScale->setMaximum(10);
	sldScale->setMinimum(1);
	sldScale->setValue(scale);
	txtScale->setText(QString::number(sldScale->value(), 10));
	connect(sldScale, SIGNAL(valueChanged(int)), this, SLOT(runValueChanged(int)));
	connect(sldScale, SIGNAL(sliderReleased()), this, SLOT(runSliderReleased()));
	qDebug()<<"TickInterval : "<<sldScale->tickInterval();
	//layout

	QHBoxLayout * hbox = new QHBoxLayout;
	QHBoxLayout * hbox2 = new QHBoxLayout;
	QVBoxLayout * vbox = new QVBoxLayout;
	QVBoxLayout * vboxSld = new QVBoxLayout;
	QHBoxLayout * hbox3 = new QHBoxLayout;
	hbox->addWidget(lblAngle);
	hbox->addWidget(txtAngle);

	hbox2->addWidget(btnOk);
	hbox2->addWidget(btnCancel);

	hbox3->addWidget(sldScale);
	hbox3->addWidget(txtScale);

	vboxSld->addWidget(lblScale);
	vboxSld->addLayout(hbox3);

	vbox->addWidget(lblHead);
	vbox->addLayout(hbox);
	vbox->addLayout(hbox2);
	vbox->addLayout(vboxSld);

	this->setLayout(vbox);
}


void AngleInfo::runOk()
{
	//좌표 입력 한뒤 close 한다..
	bool ok;

	qDebug()<<"Dialog will be closed..";
	emit emitRunOk(txtAngle->text().toInt(&ok, 10));
	close();
}

void AngleInfo::runValueChanged(int value)
{
	txtScale->setText(QString::number(value, 10));
	//emit emitSetScale(value);
}

void AngleInfo::runSliderReleased()
{
	bool ok;
	int value = txtScale->text().toInt(&ok, 10);
	emit emitSetScale(value);
}
