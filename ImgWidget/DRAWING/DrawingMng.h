/*
 * DrawingMng.h
 *
 *  Created on: 2013. 6. 4.
 *      Author: jiwon
 */

#ifndef DRAWINGMNG_H_
#define DRAWINGMNG_H_

#include <QObject>
#include <QGraphicsItem>
#include <QPolygonF>
#include <QVector>
#include <QPointF>
#include "../DrawingScene.h"
#include "../lib/Function.h"
#include "../lib/LatLonMng.h"
#include "../LATLON/LatLonConvert.h"
#include "CGraphicsItem.h"
#include "CLineItem.h"
#include "CRectItem.h"
#include "CEllipseItem.h"
#include <QFileDialog>


/**
 * 드로잉 Mng 기능
 * 1. 기본적인 6개의 드로잉 작업을 한다.
 *  1) 마우스 클릭시, 이동시, 릴리즈시 발생되는 이벤트를 처리하여 Polygon, Polyline, 등등을 그린다.
 *
 * 2. 맵 정보를 그리는 기능을 한다.
 *  1) 맵 정보는 폴리곤과 폴리라인만을 그린다.
 *
 * 3. 매뉴얼 그리기 기능을 한다.
 */

class DrawingScene;
class DrawingMng
{
public:
	DrawingMng();
	virtual ~DrawingMng();

	QGraphicsItem * drawItems(DRAWING drawing, QPointF point, QGraphicsItem * curitem);
	void createItems(DRAWING drawing, QPointF point, QGraphicsItem ** curitem, DrawingScene * scene);
	void completeItems(DRAWING drawing, QGraphicsItem * curitem, DrawingScene * scene);

	//Polygon 처리
	void createPolygon(QPointF point, QGraphicsItem ** curitem);
	void drawPolygon(QPointF point, QGraphicsItem * curitem);
	void fixPolygon(QPointF point, QGraphicsItem * curitem);
	void completedPolygon(QPointF point, QGraphicsItem * curitem, DrawingScene * scene);

	//Polyline 처리
	void createPolyline(QPointF point, QGraphicsItem ** curitem);
	void drawPolyline(QPointF point, QGraphicsItem * curitem);
	void fixPolyline(QPointF point, QGraphicsItem * curitem);
	void completedPolyline(QPointF point, QGraphicsItem * curitem, DrawingScene * scene);

	//Arc
	void setArcDrawing(bool mode) { this->enableArcDrawing = mode; }
	bool getArcDrawing() { return this->enableArcDrawing; }

	//2. 맵 정보 그리기 기능을 한다.

	QGraphicsItem * drawMapInfo(LatLonMng latlonmng);				//MapInfo 그린다.
	//QGraphicsItem * drawMapInfo(QVector<QPointF> point_list, MapType type);							//MapInfo 그린다.
	//QGraphicsItem * drawMapInfo(QPolygonF polygonF, MapType type);										//MapInfo 그린다.
	QGraphicsItem * drawMapInfo(void * var1, DS::Shape type, QPen pen, QBrush brush, QPointF *point = 0);										//MapInfo 그린다.

	//텍스트를 드로잉 한다.
	QGraphicsTextItem * drawText(QString id, QPointF point);

	//Polygon, Polyline, Symbol, Circle을 그린다.
	QGraphicsItem * drawMapInfoPolygon(QPolygonF polygonF, QPen pen, QBrush brush);
	QGraphicsItem * drawMapInfoPolyline(QVector<QPointF> point_list, QPen pen);
	QGraphicsItem * drawMapInfoSymbol(QPixmap *pixmap, QPointF pos);
	QGraphicsItem * drawMapInfoCircle(QPointF pos, double dist = 0.0, double bearing = 0.0);

	//Group Return

	QGraphicsItemGroup * getLineItemGroup() { return this->lineItemGroup; }
	QGraphicsItemGroup * getRectItemGroup() { return this->rectItemGroup; }
	QGraphicsItemGroup * getEllipseItemGroup() { return this->ellipseItemGroup; }

	//Object_list

	QVector<UserObject> & getUserObjectList() { return this->object_list; }

	//Modify Drawing
	void reDrawUserObject();

	//UserObject를 파일로 변환..
	void genUserObject2File(SaveMode mode , QString str);									//UserObject를 파일로 변환한다..
	QString findUserObjectLineInfo(UserObject object);
	QString findUserObjectFillInfo(UserObject object);
	QString findUserObjectIdInfo(UserObject object, QStringList &);
	void saveUserObjectInfo(SaveMode mode, QString str);
private:

	//static DrawingMng * pinstance;
	CGraphicsItem * citem;
	bool enableArcDrawing;


	QGraphicsItemGroup * rectItemGroup;
	QGraphicsItemGroup * lineItemGroup;
	QGraphicsItemGroup * ellipseItemGroup;
	QGraphicsItemGroup * polygonItemGroup;
	QGraphicsItemGroup * polylineItemGroup;

	QVector<UserObject> object_list;

	QVector<USER_OBJECT_LAYERINFO> object_layer_list;			//Userobject를 저장하기 위한 리스트
};

#endif /* DRAWINGMNG_H_ */
