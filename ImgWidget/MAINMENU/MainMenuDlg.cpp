/*
 * MainMenuDlg.cpp
 *
 *  Created on: 2013. 6. 12.
 *      Author: jiwon
 */

#include "MainMenuDlg.h"
#include <QHBoxLayout>
#include <QDate>
#include <QVBoxLayout>
#include <QDebug>

MainMenuDlg::MainMenuDlg(QWidget * parent)
: QWidget(parent)
{
	// TODO Auto-generated constructor stub

	init();
}

MainMenuDlg::~MainMenuDlg() {
	// TODO Auto-generated destructor stub
}

void MainMenuDlg::init()
{
	btnInit();


	QHBoxLayout * hbox = new QHBoxLayout;

	hbox->addWidget(btnFpl);
	hbox->addWidget(btnList);
	hbox->addWidget(btnSn);
	hbox->addWidget(btnCom);
	hbox->addWidget(btnSup);
	hbox->addWidget(btnRole);
	hbox->addWidget(btnInOut);
	hbox->addWidget(btnConsole);

	txtDate = new QLineEdit;
	QDate date;
	txtDate->setText(date.currentDate().toString("dd.MM.yyyy"));
	txtDate->setMaximumWidth(100);
	txtFeedBack = new QLineEdit;
	btnCount = new QPushButton(tr("0"));
	btnCount->setMaximumWidth(100);
	btnClear = new QPushButton(tr("Clear"));
	btnClear->setMaximumWidth(100);

	pixLogo = new QPixmap;
	if(pixLogo->load("/home/jiwon/images/sethome.png") == true){
		//qDebug()<<"load success..";
	}else{
		//qDebug()<<"load fail..";
	}

	QHBoxLayout * hbox2 = new QHBoxLayout;

	QVBoxLayout * vbox = new QVBoxLayout;

	hbox2->addWidget(txtDate);
	hbox2->addWidget(txtFeedBack);
	hbox2->addWidget(btnCount);
	hbox2->addWidget(btnClear);

	vbox->addLayout(hbox);
	vbox->addLayout(hbox2);

	QHBoxLayout * mainHbox = new QHBoxLayout;

	QLabel * lblPixmap = new QLabel;
	lblPixmap->setPixmap(*pixLogo);

	mainHbox->addLayout(vbox);
	mainHbox->addWidget(lblPixmap);

	mainHbox->insertSpacing(0, 70);
	//mainHbox->insertSpacing(1, 30);
	//mainHbox->insertStretch(2, 1);
	mainHbox->insertSpacing(-1, 70);



	setLayout(mainHbox);

}


void MainMenuDlg::btnInit()
{
	btnFpl = new QPushButton(tr("FPL"));
	btnFpl->setMaximumHeight(40);
	btnFpl->setMinimumHeight(40);
	btnList = new QPushButton(tr("Lists"));
	btnList->setMaximumHeight(40);
	btnList->setMinimumHeight(40);
	btnSn = new QPushButton(tr("SN"));
	btnSn->setMaximumHeight(40);
	btnSn->setMinimumHeight(40);
	btnCom = new QPushButton(tr("COM"));
	btnCom->setMaximumHeight(40);
	btnCom->setMinimumHeight(40);
	btnSup = new QPushButton(tr("SUP"));
	btnSup->setMaximumHeight(40);
	btnSup->setMinimumHeight(40);
	btnRole = new QPushButton(tr("Role"));
	btnRole->setMaximumHeight(40);
	btnRole->setMinimumHeight(40);
	btnInOut = new QPushButton(tr("In/Out"));
	btnInOut->setMaximumHeight(40);
	btnInOut->setMinimumHeight(40);
	btnConsole = new QPushButton(tr("Console"));
	btnConsole->setMaximumHeight(40);
	btnConsole->setMinimumHeight(40);


}
