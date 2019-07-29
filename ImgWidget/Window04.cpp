/*
 * Window04.cpp
 *
 *  Created on: 2013. 1. 17.
 *      Author: jiwon
 */

#include "Window04.h"
#include "DrawingScene.h"
#include "../lib/LatLonToPixel.h"
#include "COORDINATE/MapCoordDlg.h"
#include "ANGLE/AngleInfo.h"

#define POS_MAX_WIDTH 200

Window04::Window04(MapWindow * mw, QWidget * parent)
: QWidget(parent)
{
	// TODO Auto-generated constructor stub
	qDebug()<<"[Window04] start..";
	this->mw = mw;
	drawingWidget = 0;
	scene = new DrawingScene;
	drawingArea = new DrawingExample_04;
	drawlatlon = false;
	scene->setSceneRect(0, 0, 600, 600);
	//scene->addRect(0, 0, 600, 600, QPen(), QBrush(QColor(Qt::green)));
	drawingArea->setDrawingScene(scene);
	//scene->setView(drawingArea);

	connect(scene, SIGNAL(emitDrawMpp()), drawingArea, SLOT(drawMpp()));
	connect(scene, SIGNAL(emitUserObject(QVector<UserObject> )), this, SLOT(runUserObject(QVector<UserObject>)));
	connect(drawingArea, SIGNAL(emitZoomIn(const double)), this, SLOT(runZoomIn(const double)));
	connect(drawingArea, SIGNAL(emitZoomOut(const double)), this, SLOT(runZoomOut(const double)));
	drawingArea->setScene(scene);

	shapeLabel = new QLabel(tr("Shape:"));
	btnLine = new QPushButton(tr("NODE"));
	//btnLine->setMaximumSize(50,20);
	btnLine->setObjectName("btnLine");
	btnEllipse = new QPushButton(tr("MAP"));
	btnEllipse->setObjectName("btnEllipse");
	//btnEllipse->setMaximumSize(50,20);
	btnMapFileOpen = new QPushButton(tr("OPEN"));
	btnMapFileOpen->setObjectName("btnMapFileOpen");
	btnMapInfo = new QPushButton(tr("LAYER"));
	btnMapInfo->setObjectName("btnMapInfo");

	btnClear = new QPushButton(tr("CLEAR"));


	txtDebug = new QPlainTextEdit;
	scrollArea = new QScrollArea;

	//ScrolBar
	/*vScrollBar = new MyScrollBar;
	hScrollBar = new MyScrollBar;*/



	/*scrollArea->setHorizontalScrollBar(hScrollBar);
	scrollArea->setVerticalScrollBar(vScrollBar);*/



	lblPos = new QLabel(tr("Pos:"));
	txtPos = new QLineEdit;
	txtPos->setMaximumWidth(140);

	//Display LatLon
	btnDisplayLatLon = new QPushButton(tr("DSP LATLON"));

	//lat lon init
	lblLat = new QLabel(tr("LatLon : "));
	lblLon = new QLabel(tr("Lon : "));

	txtLat_deg = new QLineEdit;
	/*txtLat_min = new QLineEdit;
	txtLat_sec = new QLineEdit;

	txtLon_deg = new QLineEdit;
	txtLon_min = new QLineEdit;
	txtLon_sec = new QLineEdit;
*/

	btnUserDrawing = new QPushButton(tr("DRAWING"));

//	//Drawing Tool
//	drawingWidget = new DrawingWidget;

	//MainMenu Widget
	mainMenuWidget = new MainMenuDlg;

	//Slider Widget

/*	QLabel * lblZoom = new QLabel(tr("Zoom : "));
	sldScale = new QSlider(Qt::Horizontal);
	sldScale->setMaximum(400);
	sldScale->setMinimum(10);
	sldScale->setValue(100);

	txtScale = new QLineEdit;
	txtScale->setText(QString::number(10, 10));
	txtScale->setMaximumWidth(40);
	QHBoxLayout * sldLayout = new QHBoxLayout;
	sldLayout->addWidget(lblZoom);
	sldLayout->addWidget(sldScale);
	sldLayout->addWidget(txtScale); 삭제 20130716 */

	//qDebug()<<"DrawingWidget Size : "<<drawingWidget->size()<<", MainMenuWidgetSize : "<<mainMenuWidget->size();


	//Globe
	btnGlobe = new QPushButton(tr("GLOBE"));
	connect(btnGlobe, SIGNAL(clicked()), this, SLOT(runGlobe()));


	connect(btnLine, SIGNAL(clicked()), this, SLOT(shapeChanged()));
	connect(btnEllipse, SIGNAL(clicked()), this, SLOT(shapeChanged()));
	connect(btnMapFileOpen, SIGNAL(clicked()), this, SLOT(openMapFile()));
	connect(btnMapInfo, SIGNAL(clicked()), this, SLOT(openMapInfo()));
	connect(btnUserDrawing, SIGNAL(clicked()), this, SLOT(runUserDrawing()));
	connect(btnClear, SIGNAL(clicked()), this, SLOT(clearMap()));
	connect(btnDisplayLatLon, SIGNAL(clicked()), this, SLOT(displayLatLon()));
	connect(scene, SIGNAL(emitPos(const QString &, const QString &)),this, SLOT(printPos(const QString &, const QString &)));
	connect(scene, SIGNAL(emitCoordPos(const QPointF&)), drawingArea, SLOT(SetCenter(const QPointF &)));

	//connect(drawingWidget, SIGNAL(emitDrawingProp(const DRAWING )), scene, SLOT(runDrawing(const DRAWING)));


	//scrollArea->setWidget(drawingArea);
	//scrollArea->setWidgetResizable(true);

	QBoxLayout * pos_box = new QBoxLayout(QBoxLayout::LeftToRight);
	QGridLayout *mainLayout = new QGridLayout;
	//Layout

	//mainLayout->setColumnStretch(1, 1);
	//mainLayout->addWidget(mainMenuWidget, 0, 0);
	//mainLayout->setColumnStretch(1, 1);
	mainLayout->addWidget(drawingArea, 1, 0, 1, 0);
	//mainLayout->setRowMinimumHeight(1, 6);
	//mainLayout->addWidget(shapeLabel, 2, 1);
	mainLayout->addWidget(btnDisplayLatLon, 2, 1);
	mainLayout->addWidget(btnLine, 2, 2);
	mainLayout->addWidget(btnEllipse, 2, 3);
	mainLayout->addWidget(btnMapFileOpen, 2, 4);
	mainLayout->addWidget(btnMapInfo, 2, 5);
	mainLayout->addWidget(btnClear, 2, 6);

	mainLayout->addWidget(lblPos, 2, 7);
	mainLayout->addWidget(txtPos, 2, 8);
	mainLayout->addWidget(lblLat, 2, 9);
	mainLayout->addWidget(txtLat_deg, 2, 10);
	//txtLat_deg->setMaxLength(2);
	txtLat_deg->setMaximumWidth(POS_MAX_WIDTH);
	/*mainLayout->addWidget(txtLat_min, 2, 11);
	txtLat_min->setMaxLength(2);
	txtLat_min->setMaximumWidth(POS_MAX_WIDTH);
	mainLayout->addWidget(txtLat_sec, 2, 12);
	txtLat_sec->setMaxLength(2);
	txtLat_sec->setMaximumWidth(POS_MAX_WIDTH);

	mainLayout->addWidget(lblLon, 2, 13);


	mainLayout->addWidget(txtLon_deg, 2, 14);
	txtLon_deg->setMaxLength(3);
	txtLon_deg->setMaximumWidth(POS_MAX_WIDTH);
	mainLayout->addWidget(txtLon_min, 2, 15);
	txtLon_min->setMaxLength(2);
	txtLon_min->setMaximumWidth(POS_MAX_WIDTH);
	mainLayout->addWidget(txtLon_sec, 2, 16);
	txtLon_sec->setMaxLength(2);
	txtLon_sec->setMaximumWidth(POS_MAX_WIDTH);
*/
	btnMapCoord = new QPushButton(tr("SET COORD"));
	connect(btnMapCoord, SIGNAL(clicked()), this, SLOT(openMapCoord()));
	btnAngle = new QPushButton(tr("ROTATE"));
	connect(btnAngle, SIGNAL(clicked()), this, SLOT(openAngleDlg()));
	mainLayout->addWidget(btnMapCoord, 2, 11);
	mainLayout->addWidget(btnAngle, 2, 12);
	mainLayout->addWidget(btnGlobe, 2, 13);
	mainLayout->addWidget(btnUserDrawing, 2, 14);
/*
	pos_box->addWidget(lblPos);
	pos_box->addWidget(txtPos);

	pos_box->addWidget(lblLat);
	pos_box->addWidget(txtPos_2);
	pos_box->addWidget(lblLon);
	pos_box->addWidget(txtPos_3);

	mainLayout->addLayout(pos_box, 3, 0);
*/

	QVBoxLayout * vbox = new QVBoxLayout;
	vbox->addWidget(drawingArea);
	//vbox->addWidget(mainMenuWidget);
//	vbox->addLayout(mainLayout);
//	vbox->addWidget(drawingWidget);
	//vbox->addLayout(sldLayout);

	setLayout(vbox);

	setWindowTitle(tr("Basic Drawing"));


	//LatLonConvert..
	double north    = 35;
	double greenich = 127;
	double mpp      = EarthRadius / 5000;;	// default : 2000

	LatLonConvert::getInstance().setWonjumNorthGreenich(QPointF(north, greenich));
	QRect rect(0, 0, drawingArea->width(), drawingArea->height());

	LatLonConvert::getInstance().setScreenRect(rect);
	drawingArea->drawMpp();

	qDebug()<<"[Window04] constructor closed..";

	/*QScrollBar * vBar = drawingArea->verticalScrollBar();
	QScrollBar * hBar = drawingArea->horizontalScrollBar();
	qDebug()<<"Vertical Bar : "<<vBar;

	connect(vBar, SIGNAL(valueChanged(int)), this, SLOT(runActionTriggered(int )));
	connect(hBar, SIGNAL(valueChanged(int)), this, SLOT(runActionTriggered(int )));*/

	this->setWindowTitle("Map Editor Test");
	//runUserDrawing();
}

Window04::~Window04() {
	// TODO Auto-generated destructor stub
	qDebug()<<"[Window04] destructor is called..";

	delete drawingArea;
		//QGraphicsView * view;
	delete scene;
	delete txtDebug;
	delete scrollArea;
	delete txtPos;


	qDebug()<<"[Window04] destructor is close..";
}

void Window04::closeEvent(QCloseEvent *event)
{
	qDebug()<<"-----------[Window04] close is called..";
	this->~Window04();

}

void Window04::printPos(const QString & prt, const QString & prt2)
{
	txtPos->setText(prt);
	/*QStringList latlon = prt2.split('/');
	QString lat_deg = latlon.at(0).left(2);
	QString lat_min = latlon.at(0).mid(3, 2);
	QString lat_sec = latlon.at(0).mid(5, 2);

	QString lon_deg = latlon.at(1).left(3);
	QString lon_min = latlon.at(1).mid(4, 2);
	QString lon_sec = latlon.at(1).mid(6, 2);*/

	QString tmp = prt2;
	tmp.insert(3, ":");
	tmp.insert(6, ":");
	tmp.insert(9, ".");
	tmp.insert(12, " , ");
	tmp.insert(19, ":");
	tmp.insert(22, ":");
	tmp.insert(25, ".");

	txtLat_deg->setText(tmp);
	/*txtLat_min->setText(lat_min);
	txtLat_sec->setText(lat_sec);

	txtLon_deg->setText(lon_deg);
	txtLon_min->setText(lon_min);
	txtLon_sec->setText(lon_sec);*/

	mw->runStatusMessage(txtPos->text(), txtLat_deg->text());

}

/*
 * Map file을 연다..
 */

void Window04::openMapFile()
{
	qDebug()<<"open Map File is called..";
	LatLonToPixel * toPixel = new LatLonToPixel;
	if(!toPixel->readFile()){
		qDebug()<<"Opening map file is failed..";
		return;
	}
	mw->opendFileName = toPixel->getFileName();
	//toPixel->toPixel();
	//scene->latlon_list.clear();
	//scene->latlon_list = toPixel->getConvertedLatLonList();
	//scene->clear();
	//scene->addRect(0, 0, 600, 600, QPen(), QBrush(QColor(Qt::green)));
	scene->latlonmng_list.clear();
	scene->latlonmng_list = toPixel->getLatLonMngList();

	delete toPixel;
	//scene->setMode(0);
	scene->drawingChart();
	scene->setMode(-1);
	qDebug()<<"open Map File is closed.. sceneRect : "<<drawingArea->sceneRect();
}
/*
 * MapInfo를 연다..
 */
void Window04::openMapInfo()
{
	/*qDebug()<<"open Map Info File is called.."<<scene->latlonmng_list.count();
	//test
	for(int i = 0 ; i < scene->latlonmng_list.count() ; i++)
	{
		qDebug()<<"["<<i<<"] "<<&(scene->latlonmng_list[i]);
	}

	int result;
	MapInfo * mapInfo = new MapInfo(scene->latlonmng_list);
	connect(mapInfo, SIGNAL(emitLayerInfo(QStringList, QStringList)), this, SLOT(checkLayerInfo(QStringList, QStringList )));
	//mapInfo->setLatLonMngList(scene->latlonmng_list);
	//mapInfo->setModal(false);
	result = mapInfo->exec();
	qDebug()<<"XML Parser is closed... "<<result;
	if(result == QDialog::Rejected){
		delete mapInfo;
	}else{
		delete mapInfo;
	}*/

}

/*
 * Scene를 Clear 한다.
 */
void Window04::clearMap()
{
	scene->clear();
}

void Window04::shapeChanged()
{
	qDebug()<<"Shape Changed is called..";
	QPushButton * tmp = (QPushButton *)sender();
	if(tmp->objectName() == "btnEllipse"){
		qDebug()<<"Btn Ellipse is called.";
		scene->setMode(0);
	}
	else if(tmp->objectName() == "btnLine"){
		qDebug()<<"Btn Line is called..";
		scene->setMode(1);
	}
	else
		scene->setMode(-1);
}

/*
 * 체크된 레이어 정보를 바탕으로 disable 된것은 지운다
 */

void Window04::checkLayerInfo(QStringList unchecked_layer_list, QStringList checked_layer_list, DrawingMode dm)
{
	scene->checkLayerInfo(unchecked_layer_list, checked_layer_list, dm);
}

void Window04::displayLatLon()
{
	if(drawlatlon == true){
		drawlatlon = false;
	}else{
		drawlatlon = true;
	}
	scene->setLatLoMode(drawlatlon);
	scene->displayLatLon();
}


/*
 * 좌표 입력 창을 연다.
 */
void Window04::openMapCoord()
{
	int result;

	MapCoordDlg * mapCoordDlg = new MapCoordDlg;
	connect(mapCoordDlg, SIGNAL(emitRunOk(QWidget *, QWidget *, int)), scene, SLOT(goToCoordinate(QWidget *, QWidget * , int)));
	//mapInfo->setLatLonMngList(scene->latlonmng_list);
	//mapInfo->setModal(false);
	result = mapCoordDlg->exec();
	qDebug()<<"MapCoordDlg is closed... "<<result;
	if(result == QDialog::Rejected){
		delete mapCoordDlg;
	}else{
		delete mapCoordDlg;
	}
}

/*
 * 회전과 스케일 관련 다이얼로그
 */

void Window04::openAngleDlg()
{
	int result;

	AngleInfo * angleInfo = new AngleInfo(scene->getAngle(), scene->getScale());
	connect(angleInfo, SIGNAL(emitRunOk(int)), scene, SLOT(setAngle(int)));
	connect(angleInfo, SIGNAL(emitSetScale(int)), scene, SLOT(setScale(int)));
	//mapInfo->setLatLonMngList(scene->latlonmng_list);
	//mapInfo->setModal(false);
	result = angleInfo->exec();
	qDebug()<<"AngleInfo is closed... "<<result;
	if(result == QDialog::Rejected){
		delete angleInfo;
	}else{
		delete angleInfo;
	}

}

/*
 * ZoomIn 발생시
 */
void Window04::runZoomIn(const double scale)
{
	//drawingArea->setSceneRect(QRectF(0, 0, 5000, 5000));
	//qDebug()<<"runZoomIn..";

	double mpp = LatLonConvert::getInstance().mpp();
	double percent = 10;
	mpp -= (mpp * percent / 100);
	if (mpp <= 10) { mpp = 10; }
	LatLonConvert::getInstance().setMeterPerPixel((int)floor(mpp));

	mw->getDrawingWidget()->adjustMpp(mpp);

	scene->setAngle(0);
	if(drawlatlon == true){
		//qDebug()<<"drawLatLon is true;";
		scene->updateLatLon();
	}


}

/*
 * ZoomOut 발생시
 */
void Window04::runZoomOut(const double scale)
{

	//qDebug()<<"[Window04] runZoomOut is called..";
	//drawingArea->setSceneRect(QRectF(0, 0, 5000, 5000));
	//added...
	double mpp = LatLonConvert::getInstance().mpp();
	double percent = 10;
	mpp += (mpp * percent / 100);
	if (mpp > 46000) { mpp = 46000; }
	LatLonConvert::getInstance().setMeterPerPixel((int)floor(mpp));
	//LatLonConvert::getInstance().setMeterPerPixel_2((int)floor(mpp));
	//qDebug()<<"h2..";

	mw->getDrawingWidget()->adjustMpp(mpp);

	//drawingArea->setSceneRect(QRectF(0, 0, 100, 100));

	scene->setAngle(0);

	if(drawlatlon == true)
		scene->updateLatLon();

}

void Window04::runGlobe()
{
	 GlWidgetWindow * glWidget = new GlWidgetWindow;
	 glWidget->show();
}

/**
 * 드로잉 위젯을 호출 한다.
 */
void Window04::runUserDrawing()
{
	//Drawing Tool
	double mpp = LatLonConvert::getInstance().mpp();

	if(drawingWidget == 0){
		drawingWidget = new DrawingWidget(mpp);
		drawingWidget->show();
		connect(drawingWidget, SIGNAL(emitSliderReleassed(int )), scene, SLOT(runSlderReleased(int)));
		connect(drawingWidget, SIGNAL(emitDrawingProp(const DRAWING )), scene, SLOT(runDrawing(const DRAWING)));
		connect(drawingWidget, SIGNAL(emitDrawingClose()), this, SLOT(runDeleteUserDrawing()));
		connect(drawingWidget, SIGNAL(emitManualDrawingIsDone(QVector<COORDINATE>)), scene, SLOT(runManualDrawing(QVector<COORDINATE>)));
	}

}

void Window04::runDeleteUserDrawing()
{
	disconnect(drawingWidget, SIGNAL(emitDrawingClose()), this, SLOT(runDeleteUserDrawing()));
	disconnect(drawingWidget, SIGNAL(emitDrawingProp(const DRAWING )), scene, SLOT(runDrawing(const DRAWING)));
	drawingWidget = 0;
}

/**
 * 뷰의 스크롤을 움직일때 마다 발생되는 이벤트 처리 함수
 */
void Window04::runActionTriggered(int min)
{
	Q_UNUSED(min);
	//qDebug()<<"runActionTriggered..min : "<<min;
	QPointF drawingCenter = drawingArea->GetCenter();
	QPointF mtsCenter = drawingArea->mapToScene(drawingArea->frameRect().center());
	//qDebug()<<"Drawing Center : "<<drawingCenter<<", scenePoint : "<<;
	drawingArea->SetCenter(mtsCenter);
	drawingArea->drawMpp();
}

void Window04::runSliderMoveLeft()
{
	//QScrollBar * vBar = drawingArea->verticalScrollBar();
	QScrollBar * hBar = drawingArea->horizontalScrollBar();

	hBar->setValue(hBar->value() - 20);

}

void Window04::runSliderMoveRight()
{
	QScrollBar * hBar = drawingArea->horizontalScrollBar();

	hBar->setValue(hBar->value() + 20);

}

void Window04::runSliderMoveUp()
{
	QScrollBar * vBar = drawingArea->verticalScrollBar();

	vBar->setValue(vBar->value() - 20);

}

void Window04::runSliderMoveDown()
{
	QScrollBar * vBar = drawingArea->verticalScrollBar();

	vBar->setValue(vBar->value() + 20);

}

/*
 * 사용자 오브젝트를 완료 했을 때 호출 되는 함수
 */
void Window04::runUserObject(QVector<UserObject> object_list)
{
	qDebug()<<"[Window04-runUserObject] obj_list count : "<<object_list.count();
	mw->getUserMapInfo()->setUserObjectList(object_list);
	mw->getDrawingWidget()->runUserObject(object_list);
}

/*
 * Resize Event
 */

void Window04::resizeEvent(QResizeEvent *event)
{
	//view size
	QRect rect(0, 0, drawingArea->width(), drawingArea->height());

	LatLonConvert::getInstance().setScreenRect(rect);
	scene->setSceneRect(rect);
	//scene->clear();
	//scene->addRect(rect, QPen(), QBrush(QColor(Qt::green)));

	drawingArea->resize(rect.size());


	QString strView = QString::number(drawingArea->size().height(), 10);
	strView.append(" X ");
	strView.append(QString::number(drawingArea->size().width(), 10));

	QString strScene = QString::number((int)scene->sceneRect().height(), 10);
	strScene.append(" X ");
	strScene.append(QString::number((int)scene->sceneRect().width(), 10));

	//QMessageBox::information(this, tr("Test"), tr("View : %1, Scene %2").arg(strView).arg(strScene));

	qDebug()<<"view : "<<drawingArea->rect()<<", scene : "<<scene->sceneRect();
}
