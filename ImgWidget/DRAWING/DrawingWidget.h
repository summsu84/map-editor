/*
 * DrawingWidget.h
 *
 *  Created on: 2013. 6. 3.
 *      Author: jiwon
 */

#ifndef DRAWINGWIDGET_H_
#define DRAWINGWIDGET_H_

#include <QtGui>
#include "../lib/Function.h"
#include "ManualCoord.h"
#include "SymbolSelector.h"

class DrawingWidget : public QWidget
{
	Q_OBJECT
public:
	DrawingWidget(QWidget * parent=0);
	DrawingWidget(double mpp, QWidget * parent = 0);
	virtual ~DrawingWidget();
	void initButton();
	QWidget * initLineProp();
	QWidget * initFillProp();
	QWidget * initFontProp();
	QWidget * initZoomProp();
	QWidget * initUserProp();

	DRAWING & getDrawing() { return this->drawing; }
	bool isDone;
	void setMpp(double mpp) { this->mpp = mpp;}
	void adjustMpp(double mpp);
	void genTable();
	void addRows();
protected:
	void closeEvent(QCloseEvent * event);
public slots:
	void shapeChanged();
	void penChanged();
	void brushChanged();
	void fontChanged();
	void runDraw();
	void runRect();
	void runCircle();
	void runEllipse();
	void runLine();
	void runPolygon();
	void runPolyline();
	void runArc();
	void runManualCoord();
	void runText();
	void runSymbol();
	void runDone(QVector<COORDINATE> coord_list, DrawingMode dm, QGraphicsItem * item);
	void scaleChanged(int value);
	void scaleChanged_2(int value);
	void runSliderReleased();
	void runUserObject(QVector<UserObject>  object_list);
	void processTable(const QModelIndex & index);
	void runDelete();
	void runChange();
	void runModify();
private:
	QLabel * shapeLabel;
	QLabel * penWidthLabel;
	QLabel * penStyleLabel;
	QLabel * penCapLabel;
	QLabel * penJoinLabel;
	QLabel * brushStyleLabel;
	QLabel * otherOptionsLabel;
	QComboBox * shapeComboBox;
	QSpinBox * penWidthSPinBox;
	QComboBox * penStyleComboBox;
	QComboBox * penCapCombobox;
	QComboBox * penJoinComboBox;
	QComboBox * brushStyleComboBox;
	QCheckBox * antialiasingCheckBox;
	QCheckBox * transformationCheckBox;

	QPushButton * btnDraw;
	//Button
	QPushButton * btnSelect;
	QPushButton * btnRect;
	QPushButton * btnCircle;
	QPushButton * btnEllipse;
	QPushButton * btnLine;
	QPushButton * btnArc;
	QPushButton * btnPolygon;
	QPushButton * btnPolyline;
	QPushButton * btnText;
	QPushButton * btnSymbol;

	QPushButton * btnManual;


	DRAWING drawing;

	//Pen Color
	QSpinBox * spnPenR;
	QSpinBox * spnPenG;
	QSpinBox * spnPenB;

	//Fill Color
	QSpinBox * spnFillR;
	QSpinBox * spnFillG;
	QSpinBox * spnFillB;

	//Font Color
	QSpinBox * spnFontR;
	QSpinBox * spnFontG;
	QSpinBox * spnFontB;

	QComboBox * cboFont;
	QSpinBox * spnFontSize;

	QTableWidget * tblWidget;
	QPushButton * btnDelete;
	QPushButton * btnModify;
	QPushButton * btnChange;


	//슬라이드 바
	QSlider * sldScale;
	QSpinBox * txtScale;

	double mpp;
	QVector<UserObject> object_list;



signals:
	void emitDrawingProp(DRAWING drawing);
	void emitDrawingPen(QPen pen);
	void emitDrawingBrush(QBrush brush);
	void emitDrawingClose();
	void emitManualDrawingIsDone(QVector<COORDINATE> coord_list, DrawingMode dm, QGraphicsItem * item);				//Manual 드로잉을 Done
	void emitSliderReleassed(int value);
	void emitRemoveItem(QGraphicsItem * item, int idx);

};

#endif /* DRAWINGWIDGET_H_ */
