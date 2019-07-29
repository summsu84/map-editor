/*
 * RaderItemInfo.cpp
 *
 *  Created on: 2013. 10. 22.
 *      Author: jiwon
 */

#include "RaderItemInfo.h"

#define TXT_WIDTH 80
#define TXT_HEIGHT 20

RaderItemInfo::RaderItemInfo(QWidget * parent)
: QWidget(parent)
{
	// TODO Auto-generated constructor stub

	initUi();
}

RaderItemInfo::RaderItemInfo(RadarItem * item, QWidget * parent)
: QWidget(parent)
{
	// TODO Auto-generated constructor stub

	curRadarItem = item;
	initUi();
	setItemInfo(1);
}


RaderItemInfo::RaderItemInfo(QString type, QWidget * parent)
: QWidget(parent)
{
	// TODO Auto-generated constructor stub
	this->type = type;
	initUi();
}

RaderItemInfo::~RaderItemInfo() {
	// TODO Auto-generated destructor stub
	curRadarItem->deleteInfo();
}

void RaderItemInfo::initUi()
{
	//Label
	lblAcid = new QLabel("ACID : ");
	lblSrc = new QLabel ("From : ");
	lblDst = new QLabel("To : ");
	lblCuAlt = new QLabel("Current Alt : ");
	lblClAlt = new QLabel("Clear Alt : ");
	lblCuSpd = new QLabel("Current Spd : ");
	lblClSpd = new QLabel("Clear Spd : ");
	lblClHeading = new QLabel("Clear Heading : ");		//Clear Heading
	lblCuHeading = new QLabel("Current Heading : ");

	//txt
	txtAcid = new QLineEdit;
	txtAcid->resize(TXT_WIDTH, TXT_HEIGHT);
	txtSrc = new QLineEdit;
	txtDst = new QLineEdit;
	txtCuAlt = new QLineEdit;
	txtClAlt = new QLineEdit;
	txtCuSpd = new QLineEdit;
	txtClSpd = new QLineEdit;
	txtClHeading = new QLineEdit;
	txtCuHeading = new QLineEdit;

	txtAcid->setEnabled(false);
	txtSrc->setEnabled(false);
	txtDst->setEnabled(false);
	txtCuAlt->setEnabled(false);
	txtCuSpd->setEnabled(false);
	txtCuHeading->setEnabled(false);

	QHBoxLayout * hbox1 = new QHBoxLayout;
	hbox1->addWidget(lblAcid);
	hbox1->addWidget(txtAcid);
	hbox1->addWidget(lblSrc);
	hbox1->addWidget(txtSrc);
	hbox1->addWidget(lblDst);
	hbox1->addWidget(txtDst);

	QGridLayout * grid1 = new QGridLayout;
	grid1->addWidget(lblCuAlt, 0, 0);
	grid1->addWidget(txtCuAlt, 0, 1);
	grid1->addWidget(lblClAlt, 1, 0);
	grid1->addWidget(txtClAlt, 1, 1);
	grid1->addWidget(lblCuHeading, 2, 0);
	grid1->addWidget(txtCuHeading, 2, 1);
	grid1->addWidget(lblClHeading, 3, 0);
	grid1->addWidget(txtClHeading, 3, 1);

	QGridLayout * grid2 = new QGridLayout;
	grid2->addWidget(lblCuSpd, 0, 0);
	grid2->addWidget(txtCuSpd, 0, 1);
	grid2->addWidget(lblClSpd, 1, 0);
	grid2->addWidget(txtClSpd, 1, 1);


	QHBoxLayout * hbox2 = new QHBoxLayout;
	hbox2->addItem(grid1);
	hbox2->addItem(grid2);

	QVBoxLayout * main = new QVBoxLayout;



	main->addLayout(hbox1);
	main->addLayout(hbox2);
	if(type == "Add")
	{
		btnAdd = new QPushButton("Add");
		btnAdd->setMaximumSize(120, 80);
		connect(btnAdd, SIGNAL(clicked()), this, SLOT(runAdd()));
		main->addWidget(btnAdd);
	}

	btnSet = new QPushButton("Set");
	btnSet->setMaximumSize(120, 80);
	connect(btnSet, SIGNAL(clicked()), this, SLOT(runSet()));
	main->addWidget(btnSet);

	btnCancel = new QPushButton("Cancel");
	btnCancel->setMaximumSize(120, 80);
	connect(btnCancel, SIGNAL(clicked()), this, SLOT(close()));
	main->addWidget(btnCancel);


	//Default value
/*
	txtCuAlt->setText("100");
	txtClAlt->setText("100");
	txtCuSpd->setText("100");
	txtClSpd->setText("100");
*/

	this->setLayout(main);
	//this->setItemInfo(1);
	show();

}


/**
 *  아이템 정보를 바탕으로 위젯 하면 보여 준다.
 */
void RaderItemInfo::setItemInfo(int flag)
{

	txtAcid->setText(curRadarItem->getCallSign());
	txtCuAlt->setText(QString().setNum(curRadarItem->getCuAlt(), 10));
	txtCuHeading->setText(QString().setNum(curRadarItem->getCuHeading(), 10));
	txtCuSpd->setText(QString().setNum(curRadarItem->getCuSpeed(), 10));

	if(flag == 1)
	{
		txtClAlt->setText(QString().setNum(curRadarItem->getClAlt(), 10));
		txtClSpd->setText(QString().setNum(curRadarItem->getClSpeed(), 10));
		txtClHeading->setText(QString().setNum(curRadarItem->getClHeading(), 10));
	}

}

void RaderItemInfo::runAdd()
{
	qDebug()<<"=============RaderItemInfo runAdd..===========";
	RDITEM item;
	bool ok;
	item.acid = txtAcid->text();
	item.cl_alt = txtClAlt->text();
	item.cl_spd = txtClSpd->text().toInt(&ok, 10);
	item.cu_alt = txtCuAlt->text();
	item.cu_spd = txtCuSpd->text().toInt(&ok, 10);
	item.from = txtSrc->text();
	item.to = txtDst->text();
	item.cl_heading = txtClHeading->text().toInt(&ok, 10);

	emitAddRadarItem(item);

	close();
}

void RaderItemInfo::runSet()
{

	//Clear 정보를 업데이트 한다.
	bool ok;
	curRadarItem->SetClearAlt(txtClAlt->text().toInt(&ok, 10));

	//curRadarItem->SetClearDirect(txt);

	curRadarItem->SetClearHeading(txtClHeading->text().toInt(&ok, 10));

	curRadarItem->SetClearSpeed(txtClSpd->text().toInt(&ok, 10));



}
