/*
 * ManualCoord.h
 *
 *  Created on: 2013. 7. 10.
 *      Author: jiwon
 */

#ifndef MANUALCOORD_H_
#define MANUALCOORD_H_

#include <QtGui>
#include <QObject>
#include "DrawingWidget.h"
#include <QTableWidget>
#include <QVector>
#include "../../lib/Function.h"
#include "ManualCoordDbProcess.h"

class DrawingWidget;

class ManualCoord : public QWidget
{
	Q_OBJECT
public:
	ManualCoord(DrawingWidget * drawingWidget);
	ManualCoord(DrawingWidget * drawingWidget, QVector<COORDINATE> cn_list, QGraphicsItem * item);
	virtual ~ManualCoord();

	void init();			//init
	QWidget * initDrawType();
	QWidget * initBondaryVia();
	QWidget * initLatLon();
	QWidget * initCenterLatLon();
	QWidget * initPoint();
	QWidget * initArcCircle();
	QLayout * initButtons();

	void genTable();
	void addRows();
	void deleteRows();
	void clear();

	void processMCDB();			//db로 부터 데이터를 가져온다..
public slots:

	void rdo_click();
	void runInsert();
	void runUpdate();
	void runDelete();
	void runClear();
	void runPreview();
	void runDone();
	void runCancel();
	void runBndryChanged(int index);
	void runTblClicked(const QModelIndex & index);
	void runCurrentIndexChanged(int index);
	void runApply();
	void runCenterApply();

private:

	QRadioButton * rdoPolyline;
	QRadioButton * rdoPolygon;
	QRadioButton * rdoCircle;
	QRadioButton * rdoSymbol;

	//BoundaryVia

	QComboBox * cboBndryVia;
	QLineEdit * txtBndryVia;

	//Reference for Lat/Lon
	QComboBox * cboAirport;
	QComboBox * cboFix;
	QComboBox * cboNavaid;

	QLineEdit * txtRhoAirport;
	QLineEdit * txtRhoFix;
	QLineEdit * txtRhoNavaid;

	QLineEdit * txtThetaAirport;
	QLineEdit * txtThetaFix;
	QLineEdit * txtThetaNavaid;

	QPushButton * btnApply;

	//Reference for center Lat/Lon

	QComboBox * cboCenterAirport;
	QComboBox * cboCenterFix;
	QComboBox * cboCenterNavaid;

	QLineEdit * txtCenterRhoAirport;
	QLineEdit * txtCenterRhoFix;
	QLineEdit * txtCenterRhoNavaid;

	QLineEdit * txtCenterThetaAirport;
	QLineEdit * txtCenterThetaFix;
	QLineEdit * txtCenterThetaNavaid;

	QPushButton * btnCenterApply;

	//Point
	QLineEdit * txtLat;
	QLineEdit * txtLon;

	//Arc/Circle

	QLineEdit * txtCenterLat;
	QLineEdit * txtCenterLon;
	QLineEdit * txtDist;
	QLineEdit * txtBearing;

	//Buttons
	QPushButton * btnInsert;
	QPushButton * btnUpdate;
	QPushButton * btnDelete;
	QPushButton * btnClear;
	QPushButton * btnDone;
	QPushButton * btnPreview;
	QPushButton * btnCancel;

	//TableWidget or TableView


	//Group
	QGroupBox * grpLatLon;
	QGroupBox * grpCenterLatLon;
	QGroupBox * grpPoint;
	QGroupBox * grpArcCircle;

	DrawingWidget * drawingWidget;


	QTableWidget * tblWidget;

	//위젯을 리프레쉬 하기 위해서 벡터에 Insert한것을 담는다.

	QVector<COORDINATE> coord_list;

	QVBoxLayout * vboxMain;

	int index;

	ManualCoordDbProcess * mcdb;

	QString tmpLon;
	QString tmpLat;

	DrawingMode dm;					//Initial - 새로운 매뉴얼 오브젝트생성시, ReDrawing - Modify 실행시
	QGraphicsItem * grpItem;		//DrawingWidget에서 Modify를 수행할때 해당 아이템의 포인터

signals:
	void emitDone(QVector<COORDINATE> coord_list, DrawingMode dm, QGraphicsItem * item = 0);
};

#endif /* MANUALCOORD_H_ */
