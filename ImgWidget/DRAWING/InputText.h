/*
 * InputText.h
 *
 *  Created on: 2013. 7. 10.
 *      Author: jiwon
 */

#ifndef INPUTTEXT_H_
#define INPUTTEXT_H_

#include <QtGui>
#include <QDialog>
#include <QObject>
#include "DrawingWidget.h"

//class DrawingWidget;

class InputText : public QDialog
{
	Q_OBJECT;

public:
	InputText(DrawingWidget * drawingWidget, QDialog * parent = 0);
	virtual ~InputText();

public slots:
	void runInputTextOk();
	void runInputTextCancel();

private:

	QLineEdit * txtText;
	QPushButton * btnOk;
	QPushButton * btnCancel;

	DrawingWidget * drawingWidget;
};

#endif /* INPUTTEXT_H_ */
