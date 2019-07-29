/*
 * DrawingMng.cpp
 *
 *  Created on: 2013. 6. 4.
 *      Author: jiwon
 */

#include "DrawingMng.h"
#include <QDebug>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include "CPixMap.h"
#include "CRectItem.h"
#include "CEllipseItem.h"
#include "CPolyGonItem.h"
#include "CPolyLineItem.h"
#include "CArcItem.h"
#include "CTextItem.h"
#include "CPixMap.h"

using namespace::DS;

//DrawingMng * DrawingMng::pinstance = NULL;
DrawingMng::DrawingMng() {
	// TODO Auto-generated constructor stub

	enableArcDrawing = false;
	//item group 생성
	rectItemGroup = new QGraphicsItemGroup;
	lineItemGroup = new QGraphicsItemGroup;
	ellipseItemGroup = new QGraphicsItemGroup;
	polygonItemGroup = new QGraphicsItemGroup;
	polylineItemGroup = new QGraphicsItemGroup;
}

DrawingMng::~DrawingMng() {
	// TODO Auto-generated destructor stub
}


/*
 * 각종 오브젝트를 처음 생성할때 호출된다. 즉, 오브젝트 버튼을 클릭 후 마우스 버튼(왼쪽)을 눌렀을 때 호출
 */
void DrawingMng::createItems(DRAWING drawing, QPointF point, QGraphicsItem ** curitem, DrawingScene * scene)
{

	Shape shape = drawing.shape;

	QGraphicsItem * custitem;

	switch(shape)
	{
		case Line:{
			//qDebug()<<"Line..";
			*curitem = new CLineItem(QLineF(point, point));
			CLineItem * tmp = static_cast<CLineItem *>(* curitem);
			QObject::connect(tmp, SIGNAL(emitAddTextItem(QGraphicsItem *)), scene, SLOT(addTextItem(QGraphicsItem *)));
			//qDebug()<<"curitem : "<<curitem;
			break;
		}
		case Rect:
		case RoundedRect:
		{
			//*curitem = new QGraphicsRectItem(QRectF(point, point));
			*curitem = new CRectItem(QRectF(point, point));
			break;
		}
		case Ellipse:
		{
			//*curitem = new QGraphicsEllipseItem(QRectF(point, point));
			*curitem = new CEllipseItem(QRectF(point, point));
			//curitem->setFlag(QGraphicsItem::ItemIsMovable, true);
			break;
		}
		case Arc:
		{
			*curitem = new CArcItem(point);				//아크를 그리기 위해 객체 생성함.
			CArcItem * tmp1 = static_cast<CArcItem *>(*curitem);
			QObject::connect(tmp1, SIGNAL(emitAddTextItem(QGraphicsItem *)), scene, SLOT(addTextItem(QGraphicsItem *)));
			//curitem->setFlag(QGraphicsItem::ItemIsMovable, true);
			break;
		}
		case Circle:
		{
			* curitem = new QGraphicsEllipseItem(QRectF(point, point));
			break;
		}
		case Text:
		{
			* curitem = new CTextItem(point, drawing.strText, drawing.font);
		}
		case Symbol:
		{
			* curitem = new CPixMap(drawing.strText, point);
		}
		default:
		{
			custitem = new QGraphicsEllipseItem;
			break;
		}
	}

}


/*
 * 마우스 커서를 움직일때 사용되는 함수
 */
QGraphicsItem * DrawingMng::drawItems(DRAWING drawing, QPointF point, QGraphicsItem * curitem)
{
	Shape shape = drawing.shape;

	switch(shape)
	{
		case Line:
		{
			//qDebug()<<"Line..";
			CLineItem * line = static_cast<CLineItem *> (curitem);
			//QGraphicsLineItem * line = static_cast<QGraphicsLineItem *> (curitem);
			line->setPen(drawing.pen);
			line->setBrush(drawing.brush);
			QLineF newLine(line->line().p1(), point);
			line->setLine(newLine);
			//qDebug()<<"Line : "<<line->line()<<", CurItem : "<<curitem;
			break;
		}
		case Rect:
		case RoundedRect:
		{
			CRectItem * rect = dynamic_cast<CRectItem *>(curitem);

			if(rect == 0){
				//qDebug()<<"=======================[DrawingMng - drawItems] casting process is failed..==================";
				return 0;
			}

			rect->setPen(drawing.pen);
			rect->setBrush(drawing.brush);
			if(shape == Rect){
				rect->setShape(Rect);
			}else if(shape == RoundedRect){
				rect->setShape(RoundedRect);
			}
			QRectF newRect(rect->rect().topLeft(), point);
			//qDebug()<<"newrect : "<<newRect;
			rect->setRect(newRect);
			break;
		}case Ellipse:
		{
			CEllipseItem * rect = static_cast<CEllipseItem *> (curitem);
			rect->setPen(drawing.pen);
			rect->setBrush(drawing.brush);
			QRectF newRect(rect->rect().topLeft(), point);
			rect->setRect(newRect);
			break;
		}case Circle:
		{
			QGraphicsEllipseItem * item = static_cast<QGraphicsEllipseItem *>(curitem);
			item->setPen(drawing.pen);
			item->setBrush(drawing.brush);
			//정사각형을 생성해야 한다. 최초 topLeft점을 기반으로 움직인 거리만큼(좌표)의 길이를 이용하여 정사각형을 생성한다..
			QRectF rect = item->rect();
			qDebug()<<"topLeft : "<<rect.topLeft().toPoint()<<", point : "<<point.toPoint();
			double dist = LatLonConvert::getInstance().distanceXY(rect.topLeft().toPoint(), point.toPoint());
			QPointF newPoint = QPointF(rect.topLeft().x() + dist, rect.topLeft().y() + dist);

			QRectF newRect = QRectF(rect.topLeft(), newPoint);
			qDebug()<<"newRect : "<<newRect<<", dist : "<<dist;
			item->setRect(newRect);
			break;

		}
		case Arc:
		{
			CArcItem * arc = dynamic_cast<CArcItem * >(curitem);
			if(arc == 0){
			//	qDebug()<<"casting is failed..";
				return 0;
			}
			arc->setPen(drawing.pen);
			arc->setBrush(drawing.brush);
			arc->setCurrentPoint(point);
			//qDebug()<<"[Arc] arc : "<<arc;
			//마우스르 릴리즈하여 아크를 그리는 단계이다.
			if(enableArcDrawing == true){
				//아크를 그린다. 렉트를 먼저 생성한다.

				arc->setArcDrawing(true);

				arc->update();

//				qreal xgap = arc->getLineF().p2().x() - arc->getInitPoint().x();
//				qreal ygap = arc->getLineF().p2().y() - arc->getInitPoint().y();
//
//				//qDebug()<<"xgap : "<<xgap<<", ygap : "<<ygap;
//				QPointF topLeft(arc->getInitPoint().x() - xgap, arc->getInitPoint().y() - xgap);
//				QPointF bottomRight(arc->getInitPoint().x() + xgap, arc->getInitPoint().y() + xgap);
//				QRectF rect(topLeft, bottomRight);
				//qDebug()<<"[drawingMng] drawing Arc process....Rect : "<<rect<<", LineF : "<<arc->getLineF();
				/*arc->setRectF(rect);
				arc->update();*/

			}else{
				//qDebug()<<"[drawingMng] drawing Line process....";
				arc->setArcDrawing(false);
				//먼저 라인을 그린다.
				QLineF newLine(arc->getInitPoint(), point);
				arc->setLineF(newLine);
				arc->update();
			}

			break;
		}
		case Text:
		{
			CTextItem * text = static_cast<CTextItem *> (curitem);

			text->setPen(drawing.pen);
			text->setBrush(drawing.brush);
			text->setCurrentPoint(point);
			text->setText(drawing.strText);
			text->update();
			//qDebug()<<"Line : "<<line->line()<<", CurItem : "<<curitem;
			break;

		}
		case Symbol:
		{
			CPixMap * pix = static_cast<CPixMap *> (curitem);
			pix->setCurrentPoint(point);
			//text->setText(drawing.strText);
			pix->update();
			//qDebug()<<"Line : "<<line->line()<<", CurItem : "<<curitem;
			break;
		}
		default:
		{
			//custitem = new QGraphicsEllipseItem;
			break;
		}
	}

}

/**
 * 마우스 버튼을 놓았을 때 실행한다..
 */
void DrawingMng::completeItems(DRAWING drawing, QGraphicsItem * curitem, DrawingScene * scene)
{
	Shape shape = drawing.shape;

	switch(shape)
	{
		case Line:
		{
			CLineItem * line = dynamic_cast<CLineItem *> (curitem);
			if(line == 0){
				//qDebug()<<"line cannot be converted..";
			}else{
				//qDebug()<<"converting is success..";
			}
			//QGraphicsLineItem * line = static_cast<QGraphicsLineItem *> (curitem);
			QList<QGraphicsItem *> startItems = scene->items(line->line().p1());
			if (startItems.count() && startItems.first() == line)
				startItems.removeFirst();
			QList<QGraphicsItem *> endItems = scene->items(line->line().p2());
			if (endItems.count() && endItems.first() == line)
				endItems.removeFirst();
			lineItemGroup->addToGroup(line);
			line->setFlag(QGraphicsItem::ItemIsMovable, true);
			scene->addItem(line);
			line->setComplete();
			line->setInitLine();
			//scene->findItems();
			//Object  저장
			UserObject obj;
			obj.chkObject = true;
			obj.obj_name = "Line_";
			obj.obj_name.append(QString::number(line->getId()));
			obj.shape = Line;
			obj.object = static_cast<void *>(curitem);
			obj.pen = line->getPen();
			obj.brush = line->getBrush();
			object_list.append(obj);
			break;
		}
		case Rect:
		case RoundedRect:
		{
			CRectItem * rect = static_cast<CRectItem *> (curitem);
			if(shape == Rect){
				rect->setShape(Rect);
			}else if(shape == RoundedRect){
				rect->setShape(RoundedRect);
			}
			QList<QGraphicsItem *> startItems = scene->items(rect->rect().topLeft());
			if (startItems.count() && startItems.first() == rect)
				startItems.removeFirst();
			QList<QGraphicsItem *> endItems = scene->items(rect->rect().bottomRight());
			if (endItems.count() && endItems.first() == rect)
				endItems.removeFirst();

			rect->setFlag(QGraphicsItem::ItemIsMovable, true);
			rect->setCompleteRect();
			rectItemGroup->addToGroup(rect);
			scene->addItem(rect);
			//scene->findItems();

			//Object  저장
			UserObject obj;
			obj.chkObject = true;
			obj.obj_name = "Rect_";
			obj.obj_name.append(QString::number(rect->getId()));
			obj.shape = Rect;
			obj.object = static_cast<void *>(curitem);
			obj.pen = rect->getPen();
			obj.brush = rect->getBrush();
			object_list.append(obj);
			break;
		}

		case Ellipse:
		{
			CEllipseItem * rect = static_cast<CEllipseItem *> (curitem);
			QList<QGraphicsItem *> startItems = scene->items(rect->rect().topLeft());
			if (startItems.count() && startItems.first() == rect)
				startItems.removeFirst();
			QList<QGraphicsItem *> endItems = scene->items(rect->rect().bottomRight());
			if (endItems.count() && endItems.first() == rect)
				endItems.removeFirst();
			rect->setFlag(QGraphicsItem::ItemIsMovable, true);
			scene->addItem(rect);
			rect->setComplete();
			//scene->findItems();

			//Object  저장
			UserObject obj;
			obj.chkObject = true;
			obj.obj_name = "Ellipse_";
			obj.obj_name.append(QString::number(rect->getId()));
			obj.shape = Ellipse;
			obj.object = static_cast<void *>(curitem);

			object_list.append(obj);
			break;
		}
		case Circle:
		{
			QGraphicsEllipseItem * rect = static_cast<QGraphicsEllipseItem *> (curitem);
			QList<QGraphicsItem *> startItems = scene->items(rect->rect().topLeft());
			if (startItems.count() && startItems.first() == rect)
				startItems.removeFirst();
			QList<QGraphicsItem *> endItems = scene->items(rect->rect().bottomRight());
			if (endItems.count() && endItems.first() == rect)
				endItems.removeFirst();
			rect->setFlag(QGraphicsItem::ItemIsMovable, true);
			scene->addItem(rect);
			scene->findItems();

			//Object  저장
			UserObject obj;
			obj.chkObject = true;
			obj.obj_name = "Circle_";
			//obj.obj_name.append(QString::number(rect->getId()));
			obj.shape = Circle;
			obj.object = static_cast<void *>(curitem);
			object_list.append(obj);
			break;
		}
		case Arc:
		{

			CArcItem * arc = static_cast<CArcItem *>(curitem);


			arc->setFlag(QGraphicsItem::ItemIsMovable);
			scene->addItem(arc);
			if(enableArcDrawing == true)
			{
				arc->setFinishArcDrawing(true);
				arc->update();
				//enableArcDrawing = false;
			}else{
				arc->setFixedPoint();					//반지름이 될 점을 찍는다.
			}
		}
		case Text:
		{
			CTextItem * text = static_cast<CTextItem *>(curitem);
			text->setFlag(QGraphicsItem::ItemIsMovable);
			scene->addItem(text);
			break;
		}
		case Symbol:
		{
			CPixMap * pixmap = static_cast<CPixMap *>(curitem);
			pixmap->setFlag(QGraphicsItem::ItemIsMovable);
			scene->addItem(pixmap);
			break;
		}
		default:
			curitem = new QGraphicsEllipseItem;
			break;
	}

	//object_list를 레퍼런스 변수로 지정하여, drawingWidget 테이블에서 삭제할때도 반영할 수 있도록 한다.
	scene->runUserObject(object_list);

}


/**
 * Polygon을 초기화 한다..
 */
void DrawingMng::createPolygon(QPointF point, QGraphicsItem ** curitem)
{
	* curitem = new CPolyGonItem(point);
}

/**
 * Polygon을 그린다.
 */
void DrawingMng::drawPolygon(QPointF point, QGraphicsItem * curitem)
{
	//qDebug()<<"[DrawingMng - drawpolygon] called..point : "<<point<<", item : "<<curitem;
	CPolyGonItem * polygonItem = dynamic_cast<CPolyGonItem *> (curitem);
	polygonItem->setCurrentPoint(point);
	polygonItem->update();

}

/**
 * Polygon을 위한 포인트를 고정 시킨다.
 */
void DrawingMng::fixPolygon(QPointF point, QGraphicsItem * curitem)
{
	//qDebug()<<"Line..";
	CPolyGonItem * polygonItem = dynamic_cast<CPolyGonItem *> (curitem);
	polygonItem->setFixedPoint(point);
	polygonItem->update();

}

/**
 * Polygon을 완성 시킨다.
 */
void DrawingMng::completedPolygon(QPointF point, QGraphicsItem * curitem, DrawingScene * scene)
{
	//qDebug()<<"Line..";
	CPolyGonItem * polygonItem = dynamic_cast<CPolyGonItem *> (curitem);
	polygonItem->completePoint(point);
	polygonItem->setFlag(QGraphicsItem::ItemIsMovable);
	polygonItem->setComplete();
	//scene->findItems();
	polygonItem->update();
	//Object  저장
	UserObject obj;
	obj.chkObject = true;
	obj.obj_name = "Polygon_";
	obj.obj_name.append(QString::number(polygonItem->getId()));
	obj.shape = Polygon;
	obj.object = static_cast<void *>(curitem);
	object_list.append(obj);
	scene->runUserObject(object_list);
}




/**
 * Polyline을 초기화 한다..
 */
void DrawingMng::createPolyline(QPointF point, QGraphicsItem ** curitem)
{
	* curitem = new CPolyLineItem(point);
}

/**
 * Polyline을 그린다.
 */
void DrawingMng::drawPolyline(QPointF point, QGraphicsItem * curitem)
{
	//qDebug()<<"[DrawingMng - drawpolygon] called..point : "<<point<<", item : "<<curitem;
	CPolyLineItem * polygonItem = dynamic_cast<CPolyLineItem *> (curitem);
	polygonItem->setCurrentPoint(point);
	polygonItem->update();

}

/**
 * Polyline을 위한 포인트를 고정 시킨다.
 */
void DrawingMng::fixPolyline(QPointF point, QGraphicsItem * curitem)
{
	//qDebug()<<"Line..";
	CPolyLineItem * polylineItem = dynamic_cast<CPolyLineItem *> (curitem);
	polylineItem->setFixedPoint(point);
	polylineItem->update();

}

/**
 * Polyline을 완성 시킨다.
 */
void DrawingMng::completedPolyline(QPointF point, QGraphicsItem * curitem,  DrawingScene * scene)
{
	//qDebug()<<"Line..";
	CPolyLineItem * polylineItem = dynamic_cast<CPolyLineItem *> (curitem);
	polylineItem->completePoint(point);
	polylineItem->setFlag(QGraphicsItem::ItemIsMovable);
	polylineItem->update();
	//Object  저장
	UserObject obj;
	obj.chkObject = true;
	obj.obj_name = "Polyline_";
	obj.obj_name.append(QString::number(polylineItem->getId()));
	obj.shape = Polyline;
	obj.object = static_cast<void *>(curitem);
	object_list.append(obj);
	scene->runUserObject(object_list);
}

/**
 * MapInfo를 그린다.
 */

QGraphicsItem * DrawingMng::drawMapInfo(LatLonMng latlonmng)
{

	if(latlonmng.getMapType() == Polygon){
		//qDebug()<<"[DrawingMng-drawMapInfo]Draw Polygon -- ID : "<<latlonmng.getId_name()<<", FillType :"<<latlonmng.layer_fille_pattern;
		QPolygonF polygonF(latlonmng.getConvertedLatLonList2QPointF());

		for(int i = 0 ; i < polygonF.size() ; i++){
			QPointF point = polygonF.at(i);
			qDebug()<<"point : "<<point.toPoint();
		}
		//qDebug()<<"polygon : "<<polygonF;
		latlonmng.layer_fill_color.setAlpha(40);
		QBrush brush(latlonmng.layer_fill_color, latlonmng.getBrushStyle());
		QPen pen(latlonmng.getPenStyle());
		pen.setColor(latlonmng.layer_line_color);
		pen.setWidth(latlonmng.layer_line_width);

		QGraphicsItem * item = drawMapInfo(static_cast<void *>(&polygonF), Polygon, pen, brush);		//Polygon을 그린다..


		//qDebug()<<"item : "<<item;

		return item;
	}else if(latlonmng.getMapType() == Polyline)
	{
		//폴리라인 그리기 - LatLonMng에서 LatLon 타입으로 리턴한 것을 이용하여 그린다.
		QVector<LatLon> latlon_list = latlonmng.getConvertedLatLonList();
		QVector<QPointF> polyline_list;
		//qDebug()<<"Draw PolyLine -- ID : "<<latlonmng.getId_name()<<", latlonsize : "<<latlon_list.size();
		for(int j = 0 ; j < latlon_list.size() ; j++){
			LatLon start = latlon_list.at(j);
			LatLon last;
			if(j < latlon_list.size()-1){
				last = latlon_list.at(j+1);
			}else{
				last = start;
			}
			qreal x =   start.lon;
			qreal y =   start.lat;
			qreal x1 =  last.lon;
			qreal y1 =  last.lat;

			//added
			QPointF p1(x, y);
			QPointF p2(x1, y1);

			polyline_list.append(p1);
			polyline_list.append(p2);
		}
		QPen pen(latlonmng.getPenStyle());
		pen.setColor(latlonmng.layer_line_color);
		pen.setWidth(latlonmng.layer_line_width);
		QGraphicsItem * item = drawMapInfo(static_cast<void *>(&polyline_list), Polyline, pen, QBrush());

		//qDebug()<<"item : "<<item;

		return item;
	}else if(latlonmng.getMapType() == Symbol)
	{
	//	qDebug()<<"Draw SYMBOL -- ID : "<<latlonmng.getId_name();
		QVector<LatLon> latlon_list = latlonmng.getConvertedLatLonList();

		QString filename = "/home/jiwon/images/";
		filename.append(latlonmng.layer_symbol);
		QPixmap * pixmap;
		if(latlonmng.layer_symbol == "REP_FIX_REQ.xpm1")
		{
	//		qDebug()<<"static const is called..";
			static const char * const start_xpm[] =
					{"15 15 2 1",
					". c None",
					"a c #ffffff",
					"...............",
					".......a.......",
					"......aaa......",
					"......aaa......",
					".....aaaaa.....",
					".....aaaaa.....",
					"....aaaaaaa....",
					"....aaaaaaa....",
					"...aaaaaaaaa...",
					"...aaaaaaaaa...",
					"..aaaaaaaaaaa..",
					"..aaaaaaaaaaa..",
					".aaaaaaaaaaaaa.",
					".aaaaaaaaaaaaa.",
					"..............."};
			pixmap = new QPixmap(start_xpm);

		}else{
	//		qDebug()<<"filename is called..";
			pixmap = new QPixmap(filename);
		}

	//	qDebug()<<"Pixmap size : "<<pixmap->size();
		//pixmap->scaled(100,100, Qt::IgnoreAspectRatio, Qt::FastTransformation);


		//Pixmap..
		QPointF * pixPos = new QPointF(latlon_list.at(0).lon, latlon_list.at(0).lat);

		QGraphicsItem * item = drawMapInfo(static_cast<void *>(pixmap), Symbol, QPen(), QBrush(), pixPos);

		return item;
	}
	return 0;
}

/**
 * MapInfo를 그린다.
 */

/*
QGraphicsItem * DrawingMng::drawMapInfo(QVector<QPointF> point_list, MapType type)
{


	QPolygonF polygonF(point_list);

	return 0;
}
*/

/**
 * MapInfo를 그린다.
 */

QGraphicsItem * DrawingMng::drawMapInfo(void * var1, Shape type, QPen pen, QBrush brush, QPointF *point)
{


	if(type == Polygon)
	{
		QPolygonF *polygon = static_cast<QPolygonF *>(var1);
		//qDebug()<<"PolygonF : "<<*polygon;
		return drawMapInfoPolygon(*polygon, pen, brush);
	}
	else if(type == Polyline)
	{
		QVector<QPointF> * point_list = static_cast<QVector<QPointF> * >(var1);
		return drawMapInfoPolyline(*point_list, pen);
	}else if(type == Symbol)
	{
		QPixmap * pixmap = static_cast<QPixmap *>(var1);
		//qDebug()<<"Pixmap : "<<pixmap;
		return drawMapInfoSymbol(pixmap, *point);
	}

	return 0;
}

/**
 * MapInfo를 그린다.
 */

/*
QGraphicsItem * DrawingMng::drawMapInfo(QPolygonF polygonF, MapType type)
{

	LineItem * item;
	if(type == POLYGON)
	{
		item = new LineItem(POLYGON);
		item->setPolygon(polygonF);
	}
	else if(type == POLYLINE)
	{
		item = new LineItem(POLYLINE);
		item->setPolyLineList(polygonF);
	}
	return item;
}
*/

/*
 * MapInfo Polygon을 그린다.
 */
QGraphicsItem * DrawingMng::drawMapInfoPolygon(QPolygonF polygonF, QPen pen, QBrush brush)
{
	LineItem * item = new LineItem(POLYGON);
	item->setBrush(brush);
	item->setPen(pen);
	item->setPolygon(polygonF);

	QGraphicsItem * qgitem = dynamic_cast<QGraphicsItem *>(item);
	if(qgitem == 0){
		//qDebug()<<"casting is failed to qgraphicsitem..";
	}else{
		//qDebug()<<"casting is success to qgraphicsitem..";
	}

	return qgitem;
}

/*
 * MapInfo
 */

QGraphicsItem * DrawingMng::drawMapInfoPolyline(QVector<QPointF> point_list, QPen pen)
{
	LineItem * item =  new LineItem(POLYLINE);
	item->setPolyLineList(point_list);
	item->setPen(pen);
	QGraphicsItem * qgitem = dynamic_cast<QGraphicsItem *>(item);
//	if(qgitem == 0){
//		qDebug()<<"casting is failed to qgraphicsitem..";
//	}else{
//		qDebug()<<"casting is success to qgraphicsitem..";
//	}
	return qgitem;
}

/*
 * MapInfo Pixmap
 */

QGraphicsItem * DrawingMng::drawMapInfoSymbol(QPixmap * pixmap, QPointF pos)
{
	//Pixmap
	LineItem * item =  new LineItem(POINTnSYMBOL);
	item->setPixmap(pixmap);
	item->setPixmapPosition(pos);

	QGraphicsItem * qgitem = dynamic_cast<QGraphicsItem *>(item);
//	if(qgitem == 0){
//		qDebug()<<"casting is failed to qgraphicsitem..";
//	}else{
//		qDebug()<<"casting is success to qgraphicsitem.."<<pos;
//	}
	return qgitem;
}


QGraphicsItem * DrawingMng::drawMapInfoCircle(QPointF pos, double dist, double bearing)
{
	qDebug()<<"drawMapInfoCircle..dist : "<<dist;

	QPointF topLeft;
	topLeft.setX(pos.x() - dist);
	topLeft.setY(pos.y() - dist);

	QPointF bottomRight;
	bottomRight.setX(pos.x() + dist);
	bottomRight.setY(pos.y() + dist);

	QRectF rectF(topLeft, bottomRight);

	QGraphicsEllipseItem * item = new QGraphicsEllipseItem(rectF);
	QGraphicsItem * qgitem = dynamic_cast<QGraphicsItem *>(item);
/*	if(qgitem == 0){
		qDebug()<<"casting is failed to qgraphicsitem..";
	}else{
		qDebug()<<"casting is success to qgraphicsitem.."<<pos;
	}*/
	return qgitem;
}

/*
 * UserObject의 체크 상태를 확인하여 재 드로잉 한다.
 */

void DrawingMng::reDrawUserObject()
{
	qDebug()<<"[DrawingMng-reDrawUserObject] called..";
	for(int i = 0 ; i < object_list.size() ; i++){
		UserObject object = object_list.at(i);
		QGraphicsItem * item = static_cast<QGraphicsItem *>(object.object);
		if(object.chkObject == false){
			item->setVisible(false);
		}else{
			item->setVisible(true);
		}
	}
}

/*
 * 유저 오브젝트를 파일로 변환한다..
 */
void DrawingMng::genUserObject2File(SaveMode mode, QString str)
{
	//UserObject는 하나의 레이어에 하나의 아이만 존재하는 구조이다..
	//0 : LAYER
	//1 : LAYER_ID
	//2 : Line Type
	//3 : Line Width
	//4 : Line Color
	//5 : Fill Pattern
	//6 : Fill Color
	//7 : Font Name
	//8 : Font Size
	//9 : Font Color
	//10 : Symbol

//	QStringList layer_list;


	for(int i = 0 ; i < object_list.size() ; i++){
		USER_OBJECT_LAYERINFO object_layer;
		QString layer = "LAYER:";
		QString id;
		QStringList coord_list;

		UserObject object = object_list.at(i);
		//LAYER_ID;
		layer.append(object.obj_name).append(":");
		//Line Type, Width, Color
		layer.append(this->findUserObjectLineInfo(object));
		//Fill Pattern, Fill Color;
		layer.append(this->findUserObjectFillInfo(object));
		//Font Name
		layer.append(":");
		//Font Size
		layer.append(":");
		//Font Color
		layer.append(":");
		//Symbol
		//layer.append(":");

		id = findUserObjectIdInfo(object, coord_list);

		object_layer.coord_list = coord_list;
		object_layer.id = id;
		object_layer.layer = layer;
		//qDebug()<<"Layer : "<<layer;
		object_layer_list.append(object_layer);
	}

	for(int i = 0 ; i < object_layer_list.size() ; i++){
		USER_OBJECT_LAYERINFO object = object_layer_list.at(i);
		qDebug()<<"Layer : "<<object.layer;
		qDebug()<<"ID : "<<object.id;
		qDebug()<<"COORD : "<<object.coord_list;
		qDebug()<<"===============================================";
	}

	//qDebug()<<layer_list;
	saveUserObjectInfo(mode, str);

}

/*
 * 현재 유저 오브젝트의 LineType과 Line Color를 반환한다.
 */

QString DrawingMng::findUserObjectLineInfo(UserObject object)
{
	//변환.. Object타입 .. Line, Rect, Circle, Ellipse, Polygon, Polyline
	//enum LineType {Blank = 0, Solid = 1, Dashed = 2, Dotted =3 };
	QString lineType;
	QString lineWidth;
	QString lineColor;

	//Linetype
	switch(object.pen.style()){
		case Qt::SolidLine :
		{
			lineType = "1";
			break;
		}
		case Qt::DashLine :
		{
			lineType = "2";
			break;
		}
		case Qt::DotLine :
		{
			lineType = "3";
			break;
		}
		default :
		{
			lineType = "0";
			break;
		}


	}
	lineType.append(":");
	lineWidth = QString::number(object.pen.width(), 10);
	lineWidth.append(":");

	int r, g, b, a;
	object.pen.color().getRgb(&r, &g, &b, &a);

	lineColor = QString(QString::number(r, 10)).append(",").append(QString::number(g, 10)).append(",").append(QString::number(b, 10)).append(":");

	QString resultLine;
	resultLine.append(lineType).append(lineWidth).append(lineColor);

	qDebug()<<"ResultLine : "<<resultLine<<", LineType : "<<lineType;

	return resultLine;

}


/*
 * 현재 유저 오브젝트의 Fill Fill Color를 반환한다.
 */

QString DrawingMng::findUserObjectFillInfo(UserObject object)
{
	//5 : Fill Pattern
	//6 : Fill Color
//	enum FillPattern{
//		BLANK					= 0,
//		SOLID_F 				= 1,
//		DOTTED_F				= 2,
//		HORIZONTALLINE 		= 3,
//		VERTICALLINE 		= 4,
//		CROSSLINE 			= 5,
//		SLASHED 				= 6,
//		REVERSESLASHED 		= 7,
//		CROSSSLASHED 		= 9,
//	};
	QString fillType;
	QString fillColor;

	//filltype
	switch(object.brush.style()){
		case Qt::SolidPattern :
		{
			fillType = "1";
			break;
		}
		case Qt::Dense1Pattern :
		{
			fillType = "2";
			break;
		}
		case Qt::HorPattern :
		{
			fillType = "3";
			break;
		}
		case Qt::VerPattern :
		{
			fillType = "4";
			break;
		}
		case Qt::CrossPattern :
		{
			fillType = "5";
			break;
		}
		case Qt::BDiagPattern :
		{
			fillType = "6";
			break;
		}
		case Qt::FDiagPattern :
		{
			fillType = "7";
			break;
		}
		case Qt::DiagCrossPattern :
		{
			fillType = "8";
			break;
		}
		default :
		{
			fillType = "0";
			break;
		}


	}
	fillType.append(":");
	int r, g, b, a;
	object.brush.color().getRgb(&r, &g, &b, &a);

	fillColor = QString(QString::number(r, 10)).append(",").append(QString::number(g, 10)).append(",").append(QString::number(b, 10)).append(":");

	QString resultFill;
	resultFill.append(fillType).append(fillColor);

	qDebug()<<"ResultFill : "<<resultFill;

	return resultFill;

}


/*
 * 현재 유저 오브젝트의 Fill Fill Color를 반환한다.
 */

QString DrawingMng::findUserObjectIdInfo(UserObject object, QStringList & strList)
{

	QString idInfo = "ID:";
	QStringList coord_list;
	//ID Name
	idInfo.append(object.obj_name).append(":");

	QGraphicsItem * grpItem = static_cast<QGraphicsItem *>(object.object);

	switch(object.shape){
		case Line :
		{
			//casting
			CLineItem * line = static_cast<CLineItem *>(grpItem);
			QString p1 = LatLonConvert::getInstance().screenToLatLon(line->line().p1().toPoint());
			QString p2 = LatLonConvert::getInstance().screenToLatLon(line->line().p2().toPoint());
			p1.prepend("G:");
			p2.prepend("G:");
			strList.append(p1);
			strList.append(p2);
			idInfo.append("2:P");
			//qDebug()<<"p1 : "<<p1<<", p2 : "<<p2;
			break;
		}
		case Rect :
		{
			CRectItem * rect = static_cast<CRectItem * >(grpItem);
			QString p1 = LatLonConvert::getInstance().screenToLatLon(rect->rect().topLeft().toPoint());
			QString p2 = LatLonConvert::getInstance().screenToLatLon(rect->rect().topRight().toPoint());
			QString p3 = LatLonConvert::getInstance().screenToLatLon(rect->rect().bottomLeft().toPoint());
			QString p4 = LatLonConvert::getInstance().screenToLatLon(rect->rect().bottomRight().toPoint());

			p1.prepend("G:");
			p2.prepend("G:");
			p3.prepend("G:");
			p4.prepend("G:");

			strList.append(p1);
			strList.append(p2);
			strList.append(p4);
			strList.append(p3);

			idInfo.append("4:G");

			break;

		}
		case Circle:
		{
			QGraphicsEllipseItem * circle = static_cast<QGraphicsEllipseItem * >(grpItem);
//			QString p1 = LatLonConvert::getInstance().screenToLatLon(circle->rect().topLeft().toPoint());
//			QString p2 = LatLonConvert::getInstance().screenToLatLon(circle->rect().bottomRight().toPoint());

			qreal x_dist = circle->rect().bottomRight().x() - circle->rect().topLeft().x();			//x축의 길이
			qreal y_dist = circle->rect().bottomRight().y() - circle->rect().topLeft().y();			//x축의 길이

			QPointF point_center = QPointF(circle->rect().x() + x_dist/2, circle->rect().y() + y_dist/2);
			QString str_center = LatLonConvert::getInstance().screenToLatLon(point_center.toPoint());

			//중심점 구하기
			str_center.prepend("C:");
			strList.append(str_center);

			idInfo.append("1:C");

			break;
		}
		case Ellipse:
		{
			break;
		}
		case Polyline:
		{
			break;
		}
		case Polygon:
		{
			break;

		}
		default :
		{
			break;
		}

	}


	return idInfo;
}

/*
 * 실제로 파일에 저장한다..
 */

void DrawingMng::saveUserObjectInfo(SaveMode mode, QString str)
{
	QFileDialog fileDialog;
	QString fileName = fileDialog.getSaveFileName(0, "Save file", "", ".map");

	QFile file(fileName);
	if(mode == All){
		QFile strFile(str);
		if(!strFile.copy(fileName)){
			qDebug()<<"dst : "<<file.fileName()<<", src : "<<str;
			qDebug()<<"Copy process is failed..";
			return;
		}

		if(!file.open(QIODevice::Append)){
			qDebug()<<"Cannot open file for writing !";
			return;
		}
	}else{
		if(!file.open(QIODevice::WriteOnly)){
			qDebug()<<"Cannot open file for writing !";

			return;
		}
	}

	QTextStream out(&file);
	for(int i = 0 ; i < object_layer_list.size() ; i++){
		USER_OBJECT_LAYERINFO object_layer = object_layer_list.at(i);

		out<<object_layer.layer<<endl;
		out<<object_layer.id<<endl;
		for(int j = 0 ; j < object_layer.coord_list.size() ; j++){
			QString coord = object_layer.coord_list.at(j);
			out<<coord<<endl;
		}
		out<<"ENDLAYER"<<endl;
	}

}

//DrawingText
QGraphicsTextItem * DrawingMng::drawText(QString id, QPointF point)
{
	QFont font("Time", 10);
	point.setX(point.x()-10);
	point.setY(point.y()-10);
	QGraphicsTextItem * txtItem = new QGraphicsTextItem(id);
	txtItem->setFont(font);
	txtItem->setPos(point);

	return txtItem;
}
