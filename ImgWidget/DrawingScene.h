/*
 * DrawingScene.h
 *
 *  Created on: 2013. 1. 21.
 *      Author: jiwon
 */

#ifndef DRAWINGSCENE_H_
#define DRAWINGSCENE_H_

#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>
#include <QGraphicsSceneMouseEvent>
#include <QWheelEvent>
#include <QGraphicsEllipseItem>
#include "Node.h"
#include "DrawingExample_04.h"
#include "ENEMY/EMNode.h"
#include "../lib/LatLonMng.h"
#include "../lib/WGS84_TM.h"
#include "../lib/LatLonDrawer.h"
#include "../lib/ProgressObj.h"
#include "../lib/MyThread.h"
#include "../lib/QGraphicsArcItem.h"
#include "../lib/Function.h"
#include "LATLON/LatLonItem.h"
#include "LATLON/LatLonConvert.h"
#include "DRAWING/DrawingMng.h"
#include "DRAWING/CArcItem.h"
#include "DRAWING/CPolyLineItem.h"
#include "DRAWING/CPolyGonItem.h"
#include "ITEMS/LineItem.h"
#include "ITEMS/MppItem.h"
#include "DRAWING/CLineItem.h"
#include "GeoData.h"
#include "../Track/Airplane.h"
#include "../Track/TrailComponent.h"


//class DrawingExample
class DrawingMng;
class DrawingScene : public QGraphicsScene
{
	Q_OBJECT

public:
	DrawingScene(QObject * parent = 0);
	virtual ~DrawingScene();
	void initLine();
	void drawingEllipse();
	void setMode(int mode){ this->mode = mode;}
	void drawingChart();
	void drawingNodes();
	QString displayToCoordinate(const QPointF& point, int zoom);
	void drawingChildNode(QVector<QGraphicsEllipseItem *> child_list);
	void drawMapInfo();
	void checkLayerInfo(QStringList unchecked_layer_list, QStringList checked_layer_list, DrawingMode);
	void setEnable2AllLayer();
	void displayLatLon();
	void drawText();
	void drawCustomizedItems_mousePress(QPointF p1, QPointF p2);
	void drawCustomizedItems_mouseMove(QPointF p1);
	void drawCustomizedItems_mouseRelease();
	void drawMpp(QPointF point);
	void drawUserComponents();
	void drawUserMapInfo();
	void clearItems();													//scene 에 그려진 아이템들을 제거한다..

	void findItems();
	void findLines(QGraphicsItem * item);
	void findEllipses(QGraphicsItem * item);
	void findRects(QGraphicsItem * item);
	void findPolygons(QGraphicsItem * item);

	QVector<LatLonMng> latlonmng_list;
	int getAngle(){ return angle; }
	int getScale(){ return scale; }

	bool checkUserItems(QPointF point);						//해당 포인에 아이템이 존재 하는지 체크 한다.

	double convertStringLat(QString lat);
	double convertStringLon(QString lon);
	QVector<QPointF> getXYManualPointList(QVector<COORDINATE> coord_list);
	QPointF getXYManualPointList(COORDINATE cn);
	QPointF getXYManualPointList(QString lat, QString lon);
	QRectF getCircleRect(QPointF p1, QPointF p2);
	QRectF getCircleRect(QPointF p1, double r);

	double getAngle(double dx, double dy);
	double getAngle(QPointF p1, QPointF p2);

	DrawingMng * getDrawingMng() { return drawingMng; }

	void setOpenNewMap(bool mode) { openNewMap = mode; }
public slots:
	bool findNode();
	void deleteChildNode(QGraphicsEllipseItem ** child);
	void removeNode(Node * node);
	void addEnemyWP(QGraphicsItem * item);
	void goToCoordinate(QWidget * lat, QWidget * lon, int status);
	void runDrawing(DRAWING drawing);				//사용자 정의 그리기를 위한 슬롯 함수
	void setAngle(int angle);						//회전 각을 받아들이기 위한 슬롯 함수
	void addTextItem(QGraphicsItem * txtItem);
	void movedfromView(const QPointF point);
	void setScale(int value);						//스케일 값을 할당 받는다. 스케일 값은 맵의 스케일 fact로 사용되며, 디폴트로 1이다.

	void setLatLonCovert(LatLonConvert * vp);	//added 20130627
	void updateLatLon();
	//void setView(DrawingExample_04 * view) { this->drawingview = view; }
	bool getDrawingMode() { return drawingMode; }
	bool getLatLonMode()  { return latlonMode; }
	void setLatLoMode(bool mode) { this->latlonMode = mode; }
	void runManualDrawing(QVector<COORDINATE> coord_list, DrawingMode dm, QGraphicsItem * item);
	void runSlderReleased(int value);
	void runUserObject(QVector<UserObject> object_list);
	void runRemoveItem(QGraphicsItem *, int );

	void runTrack();
	void updateTrack(TrailComponent ** trail_list);
protected:
	void keyPressEvent(QKeyEvent * eve);
    void mousePressEvent(QGraphicsSceneMouseEvent *eve);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *eve);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
private:
	//Holds the current centerpoint for the view, used for panning and zooming
	QPointF CurrentCenterPoint;
	QVector<Node *> node_list;
	//From panning the view
	QPoint LastPanPoint;
	QPointF pPoint;
	QPointF cPoint;
	QTimer * colTimer;
	QGraphicsItem * curitem;

	DRAWING drawing;
	DrawingMng * drawingMng;
	LatLonDrawer * latlonDrawer;
	ProgressObj * po;		//Progress Dialog
	MyThread * my;
	LatLonItem * latlonItem;
	MppItem * mppItem;

	QVector<QGraphicsItem *> drawingItem_list;
	QVector<CLineItem * > cline_list;
	QVector<QLineF> line_list;
	QVector<QRectF > ellipse_list;
	QVector<QRectF> rect_list;
	QVector<CArcItem *> arc_list;
	QVector<CPolyGonItem *> polygonitem_list;
	QVector<CPolyLineItem * > polylineitem_list;


	int mode;
	bool drawingMode;											// true: drawingMode,  false : non drawing mode;
	bool latlonMode;											// true : drawlatlon grid,   false : no draw lat lon mode;
	int angle;				//Roate Angle
	int scale;				//Scale value
	//Polygon
	bool enablePolygon;
	//PolyLine
	bool enablePolyline;
	//Arc
	bool enableArc;					//아크 버튼 클릭
	bool enableArcDrawing;		//라인 이후 호를 그린다.

	DrawingMode drMode;
	QGraphicsItemGroup * rectItemGroup;
	QGraphicsItemGroup * lineItemGroup;
	QGraphicsItemGroup * ellipseItemGroup;
	QGraphicsItemGroup * polygonItemGroup;
	QGraphicsItemGroup * polylineItemGroup;

	bool openNewMap;				//true : 맵 파일을 첨 오픈 한 경우,  false : 맵파일을 오픈한뒤 false로 변경 한다.
	bool enableText;				//true : 텍스틀를 현시,	false : 텍스트를 비현시

	bool enableRightButton;

	QVector<Airplane *> planeList;
signals:
	//void emitDebug(const QString & prt);
	void emitPos(const QString & prt, const QString & prt2);
	void emitCoordPos(const QPointF & point);
	void emitLatLonGrid(const bool mode);
	void emitDrawMpp();
	void emitUserObject(QVector<UserObject> object_list);
	//void emitGenTable(QVector<UserObject> object_list);

};

#endif /* DRAWINGSCENE_H_ */
