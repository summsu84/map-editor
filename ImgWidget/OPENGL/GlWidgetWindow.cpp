/*
 * GlWidgetWindow.cpp
 *
 *  Created on: 2013. 6. 25.
 *      Author: jiwon
 */

#include "GlWidgetWindow.h"

GlWidgetWindow::GlWidgetWindow(QWidget * parent)
: QWidget(parent)
{
	// TODO Auto-generated constructor stub
	setUpStatusBar();
	init();
}

GlWidgetWindow::~GlWidgetWindow() {
	// TODO Auto-generated destructor stub
}


void GlWidgetWindow::init()
{

	qDebug()<<"[GlWidgetWindow] init is called..";
	btnDraw = new QPushButton(tr("DRAW"));
	btnOrbit = new QPushButton(tr("ORBIT"));
	btnMove = new QPushButton(tr("MOVE"));




	QHBoxLayout * hbox = new QHBoxLayout;

	hbox->addWidget(btnDraw);
	hbox->addWidget(btnOrbit);
	hbox->addWidget(btnMove);


	glWidget = new GLWidget();
	//emit resizeEvent();

	glWidget->setMinimumSize(500,500);
	glWidget->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
	//glWidget->setMinimumSize(200,200);


//	setCentralWidget(glWidget);
	//setWindowTitle(tr("Spherical ")+fileName);
	setWindowIcon(QIcon(":res/sphere.png"));
	connect(glWidget,SIGNAL(psiChanged(int)),psiBox,SLOT(setValue(int)));
	connect(glWidget,SIGNAL(phiChanged(int)),phiBox,SLOT(setValue(int)));
	//connect(glWidget,SIGNAL(newFileName(QString)),this,SLOT(updateFileName(QString)));

	connect(btnDraw,SIGNAL(clicked()),glWidget,SLOT(enableDrawMode()));
	connect(btnOrbit,SIGNAL(clicked()),glWidget,SLOT(enableOrbitMode()));
	connect(btnMove,SIGNAL(clicked()),glWidget,SLOT(enableMoveMode()));

	QHBoxLayout * hbox2 = new QHBoxLayout;

	hbox->addWidget(phiBox);
	hbox->addWidget(psiBox);

	QVBoxLayout * vbox = new QVBoxLayout;
	vbox->addLayout(hbox);
	vbox->addWidget(glWidget);
	vbox->addLayout(hbox2);

	this->setLayout(vbox);

	qDebug()<<"[GlWidgetWindow] init close..";
}



void GlWidgetWindow::setUpStatusBar()

{
  phiBox = new QSpinBox();
  phiBox->setRange(0,359);
  phiBox->setAccelerated(1);
  phiBox->setWrapping(true);
  phiBox->setPrefix(tr("phi= "));
  psiBox = new QSpinBox();
  psiBox->setRange(0,359);
  psiBox->setAccelerated(1);
  psiBox->setPrefix(tr("psi= "));
  psiBox->setWrapping(true);
  connect(phiBox,SIGNAL(valueChanged (int)),glWidget,SLOT(setPhi(int)));
  connect(psiBox,SIGNAL(valueChanged (int)),glWidget,SLOT(setPsi(int)));

 /* statusBar()->addWidget(phiBox);
  statusBar()->addWidget(psiBox);*/

}


