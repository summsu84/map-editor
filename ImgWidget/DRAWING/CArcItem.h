/*
 * CArcItem.h
 *
 *  Created on: 2013. 7. 9.
 *      Author: jiwon
 */

#ifndef CARCITEM_H_
#define CARCITEM_H_

#include <QtGui>
#include <QObject>
#include <QGraphicsItem>

class CArcItem : public QObject, public QGraphicsItem
{
	Q_OBJECT
	enum { Type = UserType + 3 };
public:
	CArcItem(QPointF initPoint);
	virtual ~CArcItem();
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
	QRectF boundingRect() const;

	void setPolygon(QPolygonF polygon) { this->polygon = polygon; }
	QPolygonF& getPolygon(){ return this->polygon; }
	void genPointList(QPointF point);
	int& getPointCnt() { return pointCnt; }
	void setInitPoint(QPointF initPoint) { this->initPoint = initPoint; }
	//마우스를 이동할 때 마다 현재의 마우스 커서 위치 정보를 저장한다. 마우스를 릴리즈 하지 않으면 isFixed는 false이다.
	void setCurrentPoint(QPointF currentPoint) { this->currentPoint = currentPoint; isFixed = false;}
	void setFixedPoint(QPointF fixedPoint);
	void setFixedPoint() { fixedPoint = currentPoint;}								//마우스 버튼을 놓앗을 때 마지막으로 이동한 포인트가 fix 포인트가 된다.
	void completePoint(QPointF curPoint);

	//LINE 을 그리기 위한 함수
	QPointF getInitPoint() { return initPoint; }
	void setLineF(QLineF lineF) { this->lineF = lineF; }
	QLineF getLineF() { return this->lineF; }
	void setRectF(QRectF rectF) { this->rectF = rectF; }
	QRectF getRectF();

	void setArcDrawing(bool mode) { this->arcDrawing = mode; }
	void setFinishArcDrawing(bool mode) {this->finishArcDrawing = mode; }
	double getAngle(QPointF p1, QPointF p2, bool isClockWise);
	double getAngle(QPointF p1, QPointF p2);
	double getAngle(double dx, double dy, int mode);
	QRectF getCircleRect(QPointF p1, QPointF p2);
	QRectF getCircleRect(QPointF p1, double r);

	bool checkClockWise(QPointF p1, QPointF p2);

	void setPen(QPen pen) { this->pen = pen; }
	void setBrush(QBrush brush) { this->brush = brush; }
	int type() const
	{
		return Type;
	}
public slots:
	QGraphicsItem * getBearing();

protected:
	void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
private:
	QPen pen;
	QBrush brush;

	QPolygonF polygon;
	QVector<QPointF> point_list;
	QVector<QPointF> org_point_list;

	QPointF initPoint;				//최초 포인트 지점
	QPointF currentPoint;			//마우스 무빙시 현재 지점
	QPointF fixedPoint;			//마우스 클릭시 결정된 지점
	bool isFixed;

	int pointCnt;
	QLineF lineF;
	QRectF rectF;
	bool arcDrawing;
	bool finishArcDrawing;		//포물선 그리기를 종료 한다.
	QPainterPath path;

	double over180Degree;			//180도를 넘어가기 위한 변수
	double over270Degree;			//270도를 넘어가기 위한 변수
	bool over180;
	bool over270;
	bool isEndAngle;				//EndAngle을 처리하기 위한 변수

	bool clockWise;
	bool flag;

	double prevAngle;
	double currentAngle;
	bool isDown;
	bool isUp;
	double bearing;

	double radius;
	QRectF arcBoundingRect;
	static int id;


signals:
	void emitAddTextItem(QGraphicsItem * txtItem);
};

#endif /* CARCITEM_H_ */

