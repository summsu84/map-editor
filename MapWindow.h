/*
 * MapWindow.h
 *
 *  Created on: 2013. 7. 24.
 *      Author: jiwon
 */

#ifndef MAPWINDOW_H_
#define MAPWINDOW_H_

#include <QtGui>
#include <QMainWindow>
#include "ImgWidget/Window04.h"
#include "ImgWidget/DRAWING/DrawingWidget.h"
#include "ImgWidget/MAPINFO/MapInfo.h"
#include "ImgWidget/MAPINFO/UserMapInfo.h"
#include "ImgWidget/LATLON/LatLonConvert.h"
#include "Radar/RadarWidget.h"
#include "lib/Function.h"
#include "lib/GlobalMath.h"		//test
#include "ImgWidget/COORDINATE/MapCoordDlg.h"
#include <QMenu>
#include <QAction>
#include "map/util/DatToMapUtil.h"
class Window04;
class MapWindow : public QMainWindow
{
	Q_OBJECT
public:
	MapWindow();
	virtual ~MapWindow();
	//void createToolBox();
	void createActions();
	void createMenus();
	void createToolBars();
	void createStatusBar();
	void initDrawingWidget();
	void initLayerInfoWidget();
	DrawingWidget * getDrawingWidget(){ return this->rightLayout; }
	void setUserObjectList(QVector<UserObject> obj_list) { this->object_list = obj_list; }
	MapInfo * getUserMapInfo() { return this->userMapInfo; }
	QString opendFileName;
public slots:
	void runOpen();
	void runZoomIn();
	void runZoomOut();
	void runStatusMessage(QString msg1, QString msg2);
	void runSave();
	void runText();
	void runTrack();
	void runRadar();
	void runDatToMap();
	void runGMath();
	void openMapCoord();

private:

	Window04 * mainWindow;
	DrawingWidget * rightLayout;
	MapInfo * leftLayout;
	//UserMapInfo * userMapInfo;
	MapInfo * userMapInfo;

	QDockWidget * leftDock;
	QDockWidget * rightDock;

	QMenu * windowMenu;
	QMenu * helpMenu;

	QAction * exitAction;
	QAction * addAction;
	QAction * openAction;
	QAction * saveAction;
	QAction * zoomInAction;
	QAction * zoomOutAction;
	QAction * initAction;
	QAction * moveLeftAction;
	QAction * moveRightAction;
	QAction * moveUpAction;
	QAction * moveDownAction;
	QAction * hideLayerAction;
	QAction * hideObjectAction;
	QAction * showCompassAction;
	QAction * latlonAction;
	QAction * textAction;
	QAction * radarAction;
	QAction * datToMapAction;		//dat->map
	QAction * globalMathAction;
	QAction * mapCoordAction;

	QToolBar *fileToolBar;
	QToolBar *viewToolBar;
	QToolBar * toolToolBar;

	QTabWidget tabWidget;

	QVector<UserObject> object_list;

	QLabel * msg;		//XY
	QLabel * latlonMsg;
};

#endif /* MAPWINDOW_H_ */
