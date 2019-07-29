/*
 * MapWindow.cpp
 *
 *  Created on: 2013. 7. 24.
 *      Author: jiwon
 */

#include "MapWindow.h"

MapWindow::MapWindow() {
	// TODO Auto-generated constructor stub
	qDebug()<<"MainWIndow start..";

	mainWindow = new Window04(this);

	leftDock = 0;

	this->setCentralWidget(mainWindow);

	initDrawingWidget();
	initLayerInfoWidget();

	createActions();
	createMenus();
	createToolBars();
	createStatusBar();

}

MapWindow::~MapWindow() {
	// TODO Auto-generated destructor stub
}


/*
 * DrawingWidget을 초기화 한다.
 */
void MapWindow::initDrawingWidget()
{
	//Drawing Tool
	double mpp = LatLonConvert::getInstance().mpp();

	rightLayout = new DrawingWidget(mpp);
	rightDock = new QDockWidget(tr("Object Panel"));
	rightDock->setObjectName("");
	rightDock->setWidget(rightLayout);
	rightDock->setAllowedAreas(Qt::RightDockWidgetArea);
	rightDock->setMinimumWidth(200);
	addDockWidget(Qt::RightDockWidgetArea, rightDock);

	connect(rightLayout, SIGNAL(emitSliderReleassed(int )), mainWindow->scene, SLOT(runSlderReleased(int)));
	connect(rightLayout, SIGNAL(emitDrawingProp(const DRAWING )), mainWindow->scene, SLOT(runDrawing(const DRAWING)));
	//connect(rightLayout, SIGNAL(emitDrawingClose()), this, SLOT(runDeleteUserDrawing()));
	connect(rightLayout, SIGNAL(emitManualDrawingIsDone(QVector<COORDINATE>, DrawingMode, QGraphicsItem *)), mainWindow->scene, SLOT(runManualDrawing(QVector<COORDINATE>, DrawingMode, QGraphicsItem *)));
	connect(rightLayout, SIGNAL(emitRemoveItem(QGraphicsItem * , int)), mainWindow->scene, SLOT(runRemoveItem(QGraphicsItem *, int)));

}

/*
 * Layer Information을 초기화
 */
void MapWindow::initLayerInfoWidget()
{
//	qDebug()<<"open Map Info File is called.."<<scene->latlonmng_list.count();

	QVector<LatLonMng> tmp;

	leftLayout = new MapInfo(mainWindow->scene->latlonmng_list, SMSMap);
	userMapInfo = new MapInfo(tmp, UserMap);
	connect(leftLayout, SIGNAL(emitLayerInfo(QStringList, QStringList, DrawingMode )), mainWindow, SLOT(checkLayerInfo(QStringList, QStringList, DrawingMode )));
	connect(userMapInfo, SIGNAL(emitLayerInfo(QStringList, QStringList, DrawingMode )), mainWindow, SLOT(checkLayerInfo(QStringList, QStringList, DrawingMode )));

	tabWidget.addTab(leftLayout, "Layer");
	tabWidget.addTab(userMapInfo, "User Defined Layer");
	if(leftDock == 0)
		leftDock = new QDockWidget(tr("Map Layer"));

	leftDock->setObjectName("");
	leftDock->setWidget(&tabWidget);
	leftDock->setAllowedAreas(Qt::LeftDockWidgetArea);
	leftDock->setMinimumWidth(200);
	addDockWidget(Qt::LeftDockWidgetArea, leftDock);


	/*if(rightLayout == 0){
		rightLayout = new DrawingWidget(mpp);
		rightLayout->show();
		connect(rightLayout, SIGNAL(emitSliderReleassed(int )), scene, SLOT(runSlderReleased(int)));
		connect(rightLayout, SIGNAL(emitDrawingProp(const DRAWING )), scene, SLOT(runDrawing(const DRAWING)));
		connect(rightLayout, SIGNAL(emitDrawingClose()), this, SLOT(runDeleteUserDrawing()));
		connect(rightLayout, SIGNAL(emitManualDrawingIsDone(QVector<COORDINATE>)), scene, SLOT(runManualDrawing(QVector<COORDINATE>)));
	}
*/
}



void MapWindow::createMenus()
{
	QMenu * mainMenu;
	QMenu * mapMenu;
	QMenu * adminMenu;

	mainMenu = menuBar()->addMenu(tr("Main"));
	mainMenu->addAction(exitAction);
	//mainMenu->addAction(changeAction);
	mainMenu->addAction(openAction);
	mainMenu->addAction(datToMapAction);
	mainMenu->addAction(globalMathAction);
	mainMenu->addAction(mapCoordAction);
	mainMenu->addAction(radarAction);

//	mapMenu = menuBar()->addMenu(tr("Map"));
//	mapMenu->addAction(mapgenAction);
//	mapMenu->addAction(mapEditorAction);
//
//	adminMenu = menuBar()->addMenu(tr("Admin"));
//	adminMenu->addAction(importAction);
//	adminMenu->addAction(adaptationAction);
//	adminMenu->addAction(userMgmtAction);
//	adminMenu->addAction(symbolAction);
//	adminMenu->addAction(rplDistAction);

	windowMenu = menuBar()->addMenu(tr("Window"));
	helpMenu = menuBar()->addMenu(tr("Help"));


}


void MapWindow::createActions()
{
	exitAction = new QAction(tr("&Exit"), this);
	exitAction->setShortcut(tr("Ctrl+E"));
	exitAction->setStatusTip(tr("Exit the application"));
	connect(exitAction, SIGNAL(triggered()),this, SLOT(close()));

	addAction = new QAction(tr("&Change"), this);
	addAction->setShortcut(tr("Ctrl+C"));
	//connect(changeAction, SIGNAL(triggered()), this, SLOT(changeLayout));

	openAction = new QAction(tr("&Open Menu"), this);
	openAction->setShortcut(tr("Ctrl+O"));
	openAction->setIcon(QIcon(":/res/open.png"));
	connect(openAction, SIGNAL(triggered()), this, SLOT(runOpen()));

	saveAction = new QAction(tr("&Save Menu"), this);
	saveAction->setShortcut(tr("Ctrl+O"));
	saveAction->setIcon(QIcon(":/res/save.png"));
	connect(saveAction, SIGNAL(triggered()), this, SLOT(runSave()));

	zoomInAction = new QAction(tr("&Zoom In"), this);
	zoomInAction->setShortcut(tr("Ctrl+O"));
	zoomInAction->setIcon(QIcon(":/res/zoomin_button.png"));
	connect(zoomInAction, SIGNAL(triggered()), this, SLOT(runZoomIn()));

	zoomOutAction = new QAction(tr("&Zoom Out"), this);
	zoomOutAction->setShortcut(tr("Ctrl+O"));
	zoomOutAction->setIcon(QIcon(":/res/zoomout_button.png"));
	connect(zoomOutAction, SIGNAL(triggered()), this, SLOT(runZoomOut()));


	moveLeftAction = new QAction(tr("&Move Left"), this);
	moveLeftAction->setShortcut(tr("Ctrl+O"));
	moveLeftAction->setIcon(QIcon(":/res/arrow_left.png"));
	connect(moveLeftAction, SIGNAL(triggered()), mainWindow, SLOT(runSliderMoveLeft()));

	moveRightAction = new QAction(tr("&Move Right"), this);
	moveRightAction->setShortcut(tr("Ctrl+O"));
	moveRightAction->setIcon(QIcon(":/res/arrow_right.png"));
	connect(moveRightAction, SIGNAL(triggered()), mainWindow, SLOT(runSliderMoveRight()));

	moveUpAction = new QAction(tr("&Move Up"), this);
	moveUpAction->setShortcut(tr("Ctrl+O"));
	moveUpAction->setIcon(QIcon(":/res/arrow_up.png"));
	connect(moveUpAction, SIGNAL(triggered()), mainWindow, SLOT(runSliderMoveUp()));

	moveDownAction = new QAction(tr("&Move Down"), this);
	moveDownAction->setShortcut(tr("Ctrl+O"));
	moveDownAction->setIcon(QIcon(":/res/arrow_down.png"));
	connect(moveDownAction, SIGNAL(triggered()), mainWindow, SLOT(runSliderMoveDown()));

	hideLayerAction = new QAction(tr("&Hide Layer"), this);
	hideLayerAction->setShortcut(tr("Ctrl+O"));
	hideLayerAction->setIcon(QIcon(":/res/layer_blue.png"));
	//connect(hideLayerAction, SIGNAL(triggered()), this, SLOT(openMenu));

	hideObjectAction = new QAction(tr("&Hide Object"), this);
	hideObjectAction->setShortcut(tr("Ctrl+O"));
	hideObjectAction->setIcon(QIcon(":/res/object_blue.png"));
	//connect(hideObjectAction, SIGNAL(triggered()), this, SLOT(openMenu));

	hideObjectAction = new QAction(tr("&Hide Object"), this);
	hideObjectAction->setShortcut(tr("Ctrl+O"));
	hideObjectAction->setIcon(QIcon(":/res/panel_blue.png"));
	//connect(hideObjectAction, SIGNAL(triggered()), this, SLOT(openMenu));

	showCompassAction = new QAction(tr("&Show Compass"), this);
	showCompassAction->setShortcut(tr("Ctrl+O"));
	showCompassAction->setIcon(QIcon(":/res/cross.png"));
	connect(showCompassAction, SIGNAL(triggered()), this, SLOT(runTrack()));

	latlonAction = new QAction(tr("&Display LatLon"), this);
	latlonAction->setShortcut(tr("Ctrl+O"));
	latlonAction->setIcon(QIcon(":/res/latlon.png"));
	connect(latlonAction, SIGNAL(triggered()), mainWindow, SLOT(displayLatLon()));

	textAction = new QAction(tr("&Display Text"), this);
	textAction->setShortcut(tr("Ctrl+O"));
	textAction->setIcon(QIcon(":/res/object_text.png"));
	connect(textAction, SIGNAL(triggered()), this, SLOT(runText()));

	radarAction = new QAction(tr("&Run RadarWidget"), this);
	radarAction->setShortcut(tr("Ctrl+O"));
	//radarAction->setIcon(QIcon(":/res/object_text.png"));
	connect(radarAction, SIGNAL(triggered()), this, SLOT(runRadar()));

	datToMapAction = new QAction(tr("&Run DatToMap"), this);
	datToMapAction->setShortcut(tr("Ctrl+O"));
	//radarAction->setIcon(QIcon(":/res/object_text.png"));
	connect(datToMapAction, SIGNAL(triggered()), this, SLOT(runDatToMap()));


	globalMathAction = new QAction(tr("&Global Math"), this);
	globalMathAction->setShortcut(tr("Ctrl+O"));
	//radarAction->setIcon(QIcon(":/res/object_text.png"));
	connect(globalMathAction, SIGNAL(triggered()), this, SLOT(runGMath()));


	mapCoordAction = new QAction(tr("&Map Coordinate"), this);
	mapCoordAction->setShortcut(tr("Ctrl+O"));
	//radarAction->setIcon(QIcon(":/res/object_text.png"));
	connect(mapCoordAction, SIGNAL(triggered()), this, SLOT(openMapCoord()));
}

void MapWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);

    viewToolBar = addToolBar(tr("&View"));
    viewToolBar->addAction(zoomInAction);
    viewToolBar->addAction(zoomOutAction);
    viewToolBar->addAction(moveLeftAction);
    viewToolBar->addAction(moveRightAction);
    viewToolBar->addAction(moveUpAction);
    viewToolBar->addAction(moveDownAction);

    toolToolBar = addToolBar(tr("&Tools"));
    toolToolBar->addAction(hideLayerAction);
    toolToolBar->addAction(hideObjectAction);
    toolToolBar->addAction(showCompassAction);
    toolToolBar->addAction(latlonAction);
    toolToolBar->addAction(textAction);


}

/*
 * status 바 생
 */
void MapWindow::createStatusBar()
{
	msg = new QLabel;
	msg->setIndent(3);

	latlonMsg = new QLabel;
	latlonMsg->setIndent(3);

	msg->setText("0, 0");
	latlonMsg->setText("N00:00:00.00, E000:00:00.00");

	statusBar()->addWidget(msg);
	statusBar()->addWidget(latlonMsg);
}

/*
 * Open file
 */

void MapWindow::runOpen()
{

	mainWindow->scene->setOpenNewMap(true);
	mainWindow->openMapFile();
	delete leftLayout;
	delete userMapInfo;
	leftLayout = 0;
	userMapInfo = 0;

	this->initLayerInfoWidget();
	//leftLayout->setLatLonMngList(mainWindow->scene->latlonmng_list);

}

void MapWindow::runZoomIn()
{

}

void MapWindow::runZoomOut()
{

}

void MapWindow::runStatusMessage(QString msg1, QString msg2)
{
	msg->setText(msg1);
	latlonMsg->setText(msg2);
}
void MapWindow::runSave()
{
	QMessageBox::StandardButton reply;
		reply = QMessageBox::question(this, tr("save user object"),
				tr("Do you really want to save ?"), QMessageBox::Ok | QMessageBox::Cancel);
		if (reply == QMessageBox::Ok) {

			//UserObject만 세이브 할것인지 아니면 불러온 파일의 맵도 포함할 것인지 판단..
			reply = QMessageBox::question(this, tr("save user object"),
					tr("Do you want to include loaded map file ?"), QMessageBox::Yes | QMessageBox::No);
			if (reply == QMessageBox::Yes) {

				//불러온 맵 파일이 존재 하는 경우 맵 불러온 맵 파일에 추가 한다.
				//해당 경우에는 기존 불러온 파일을 생성하고, 유저 맵파일을 추가 한다.
				mainWindow->scene->getDrawingMng()->genUserObject2File(All, opendFileName);
			}else{
				//UserObject 맵 파일을 새롭게 생성한다..
				mainWindow->scene->getDrawingMng()->genUserObject2File(User, "");
			}
		}
}
/*
 * 텍스트를 현시 또는 비현시 한다.
 */

void MapWindow::runText()
{
	mainWindow->scene->drawText();
}


void MapWindow::runTrack()
{
	mainWindow->scene->runTrack();
}


void MapWindow::runRadar()
{
	RadarWidget * r_widget = new RadarWidget;
	r_widget->show();
}

void MapWindow::runDatToMap()
{
	qDebug()<<"-------------runDatToMap called..-------------";
	DatToMapUtil * util = new DatToMapUtil;
	util->openFile();
}

/*
 * 특정 지점으로 부터 각도와 거리를 알때, 다른 두 지점의 좌표를 구한다.
 */
void MapWindow::runGMath()
{
	qDebug()<<"-----------runGmath called.-------------";
	GlobalMath * gmath = new GlobalMath;

	double result = gmath->getAngle(QPointF(516, 380),  QPointF(516, 279));

	qDebug()<<"Result : "<<result;

	//지점 구하기

	QVector<QPointF> point_list = gmath->getPoint(QPointF(637, 279), 40, 16000);

	qDebug()<<"p1 : "<<point_list.at(0)<<", p2 : "<<point_list.at(1);
}


void MapWindow::openMapCoord()
{
	int result;

	MapCoordDlg * mapCoordDlg = new MapCoordDlg;
	//connect(mapCoordDlg, SIGNAL(emitRunOk(QWidget *, QWidget *, int)), scene, SLOT(goToCoordinate(QWidget *, QWidget * , int)));
	//mapInfo->setLatLonMngList(scene->latlonmng_list);
	//mapInfo->setModal(false);
	result = mapCoordDlg->exec();
	qDebug()<<"MapCoordDlg is closed... "<<result;
	if(result == QDialog::Rejected){
		delete mapCoordDlg;
	}else{
		delete mapCoordDlg;
	}
	/*LatLonConvert::getInstance().setMeterPerPixel(10);
	LatLonConvert::getInstance().setWonJum(QPointF(34,126));*/
	qDebug()<<"Screent To Latlon : "<<LatLonConvert::getInstance().screenToLatLon(227, 197);
}
