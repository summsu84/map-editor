/*
 * GlWidgetWindow.h
 *
 *  Created on: 2013. 6. 25.
 *      Author: jiwon
 */

#ifndef GLWIDGETWINDOW_H_
#define GLWIDGETWINDOW_H_

#include <QWidget>
#include <QtGui>
#include "glwidget.h"


class GlWidgetWindow : public QWidget
{
	Q_OBJECT
public:
	GlWidgetWindow(QWidget * parent = 0);
	virtual ~GlWidgetWindow();
	void init();
	void setUpStatusBar();

public slots:


private:

	GLWidget *glWidget;
	QSpinBox *phiBox;
	QSpinBox *psiBox;

	QPushButton * btnDraw;
	QPushButton * btnOrbit;
	QPushButton * btnMove;


};



#endif /* GLWIDGETWINDOW_H_ */
