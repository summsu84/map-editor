/*
 * CPixMap.h
 *
 *  Created on: 2013. 6. 10.
 *      Author: jiwon
 */

#ifndef CPIXMAP_H_
#define CPIXMAP_H_

#include <QtGui>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class CPixMap : public QGraphicsPixmapItem
{
public:
	CPixMap(QPixmap pixmap, QPointF point);
	CPixMap(QString name, QPointF point);
	virtual ~CPixMap();
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
	QRectF boundingRect() const;
	//void setShape(Shape shape) { this->shape = shape;}
	void setCurrentPoint(QPointF point) { this->currentPoint = point; enableMoving = true;}
	void setPen(QPen pen) { this->pen = pen; }
	void setFont(QFont font) { this->font = font; }
	void setBrush(QBrush brush) { this->brush = brush; }
	void setText(QString text) { this->strText = text; }

private:
	QPointF initPoint;
	QPointF currentPoint;
	QPen pen;
	QBrush brush;
	QFont font;

	bool enableMoving;				//마우스 커서가 움직이기 시작한것을 표시
	QString strText;

	QPixmap pixmap;
};

#endif /* CPIXMAP_H_ */
