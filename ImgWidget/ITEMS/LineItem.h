/*
 * LineItem.h
 *
 *  Created on: 2013. 7. 2.
 *      Author: jiwon
 */

#ifndef LINEITEM_H_
#define LINEITEM_H_

#include <QtGui>
#include <QGraphicsItem>
#include <QVector>
#include "../LATLON/LatLonConvert.h"
#include "../../lib/Function.h"


class LineItem : public QGraphicsItem
{
public:
	LineItem(MapType type);
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
	QRectF boundingRect() const;
	void setPolyLineList(QVector<QPointF> polyline_list) { this->polyline_list = polyline_list; }
	void setPen(QPen pen) { this->pen = pen; }
	void setBrush(QBrush brush) { this->brush = brush; }
	QVector<QPointF> getPolyLineList(){ return polyline_list;}
	void setPolygon(QPolygonF polygon) { this->polygon = polygon; }
	void setPixmap(QPixmap * pixmap){ this->pixmap = pixmap; }
	void setPixmapPosition(QPointF pixmapPoint) { this->pixmapPoint = pixmapPoint;}
	virtual ~LineItem();

private:
	MapType type;
	QPen pen;
	QBrush brush;
	QVector<QPointF> polyline_list;
	QPolygonF polygon;
	QPixmap * pixmap;
	QPointF pixmapPoint;

	void drawPolyLines(QPainter * painter);
	void drawPolyGons(QPainter * painter);
	void drawPixmaps(QPainter * painter);
};

#endif /* LINEITEM_H_ */
