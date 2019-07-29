/*
 * InputText.cpp
 *
 *  Created on: 2013. 7. 10.
 *      Author: jiwon
 */

#include "InputText.h"

InputText::InputText(DrawingWidget * drawingWidget, QDialog * parent) :
 QDialog(parent)
{
	// TODO Auto-generated constructor stub

	this->drawingWidget = drawingWidget;

	QHBoxLayout * hbox = new QHBoxLayout;

	btnOk = new QPushButton(tr("Ok"));
	btnCancel = new QPushButton(tr("Cancel"));

	hbox->addWidget(btnOk);
	hbox->addWidget(btnCancel);

	connect(btnOk, SIGNAL(clicked()), this, SLOT(runInputTextOk()));
	connect(btnCancel, SIGNAL(clicked()), this, SLOT(runInputTextCancel()));

	QVBoxLayout * vbox = new QVBoxLayout;

	txtText = new QLineEdit;

	vbox->addWidget(txtText);
	vbox->addLayout(hbox);

	setLayout(vbox);

}

InputText::~InputText() {
	// TODO Auto-generated destructor stub
}


void InputText::runInputTextCancel()
{
	qDebug()<<"[InputText - runCancel] called..";
	close();
}

void InputText::runInputTextOk()
{
	qDebug()<<"[InputText - runOk] called..widget : "<<drawingWidget;
	drawingWidget->getDrawing().strText = txtText->text();

	qDebug()<<"[InputText - runOk] close..text"<<txtText->text();
	accept();
}
