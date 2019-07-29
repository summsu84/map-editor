/*
 * CTextItem.h
 *
 *  Created on: 2013. 7. 10.
 *      Author: jiwon
 */

#ifndef CTEXTITEM_H_
#define CTEXTITEM_H_

#include <QtGui>
#include <QGraphicsTextItem>

class CTextItem : public QGraphicsTextItem
{
public:
	CTextItem(QPointF initPoint, QString strText, QFont font);
	virtual ~CTextItem();
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
};

#endif /* CTEXTITEM_H_ */
