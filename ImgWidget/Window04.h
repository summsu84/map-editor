/*
 * Window04.h
 *
 *  Created on: 2013. 1. 17.
 *      Author: jiwon
 */

#ifndef WINDOW04_H_
#define WINDOW04_H_
#include <QtGui>
#include <QWidget>
#include "DrawingExample_04.h"
#include "DrawingScene.h"
#include <QGraphicsView>
#include "MAPINFO/MapInfo.h"
#include "DRAWING/DrawingWidget.h"
#include "MAINMENU/MainMenuDlg.h"
#include "OPENGL/GlWidgetWindow.h"
#include "LATLON/LatLonConvert.h"
#include "../lib/MyScrollBar.h"
#include "../MapWindow.h"

class MapWindow;
class Window04 :  public QWidget
{
	Q_OBJECT

public:
	Window04(MapWindow * mw, QWidget * parent = 0);
	virtual ~Window04();
	DrawingScene * scene;
public slots:
	void printPos(const QString & prt, const QString & prt2);
	void shapeChanged();
	void openMapFile();
	void openMapInfo();
	void clearMap();
	void checkLayerInfo(QStringList unchecked_layer_list, QStringList checked_layer_list, DrawingMode dm);
	void displayLatLon();
	void openMapCoord();
	void openAngleDlg();
	void runZoomIn(const double scale);
	void runZoomOut(const double scale);
	void runGlobe();
	void runUserDrawing();
	void runDeleteUserDrawing();
	void runActionTriggered(int min);
	void runSliderMoveLeft();
	void runSliderMoveRight();
	void runSliderMoveUp();
	void runSliderMoveDown();
	void runUserObject(QVector<UserObject> );
protected:
	void closeEvent(QCloseEvent *event);
	void resizeEvent(QResizeEvent *event);
private:

	MapWindow * mw;
	DrawingExample_04 * drawingArea;
	//QGraphicsView * view;

	QLabel *shapeLabel;
	QLabel *penWidthLabel;
	QLabel *penStyleLabel;
	QLabel *lblPos;
	QLabel * lblLat;
	QLabel * lblLon;
	QPushButton * btnDisplayLatLon;
	QComboBox *shapeComboBox;
	QPushButton * btnLine;
	QPushButton * btnEllipse;
	QPushButton * btnPolygon;
	QPushButton * btnMapFileOpen;
	QPushButton * btnMapInfo;
	QPushButton * btnClear;
	QPushButton * btnMapCoord;
	QPushButton * btnAngle;
	QPushButton * btnGlobe;
	QPushButton * btnUserDrawing;
	QPushButton * btnText;			//Text Drawing

	QSpinBox *penWidthSpinBox;
	QComboBox *penStyleComboBox;
	QPlainTextEdit * txtDebug;
	QScrollArea * scrollArea;
	QLineEdit * txtPos;		//X, Y
	QLineEdit * txtLat_deg;		//Lon
	QLineEdit * txtLat_min;		//Lon
	QLineEdit * txtLat_sec;		//Lon
	QLineEdit * txtLon_deg;		//Lon
	QLineEdit * txtLon_min;		//Lon
	QLineEdit * txtLon_sec;		//Lon

	DrawingWidget * drawingWidget;
	MainMenuDlg * mainMenuWidget;

	//슬라이드 바
	QSlider * sldScale;
	QLineEdit * txtScale;

	//위경도 그리드 현시 여부
	bool drawlatlon;

	//
	MyScrollBar * vScrollBar;
	MyScrollBar * hScrollBar;

};

#endif /* WINDOW04_H_ */
