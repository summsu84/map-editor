/*
 * DrawingExample_04.h
 *
 *  Created on: 2013. 1. 17.
 *      Author: jiwon
 */

#ifndef DRAWINGEXAMPLE_04_H_
#define DRAWINGEXAMPLE_04_H_

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QMouseEvent>
#include "DrawingScene.h"

class DrawingScene;
class DrawingExample_04 : public QGraphicsView
{
	Q_OBJECT
public:
	DrawingExample_04(QWidget *parent = 0);
	virtual ~DrawingExample_04();
	//void initLine();

	QPointF GetCenter() { return CurrentCenterPoint; }
	bool isPress;
	void setDrawingScene(DrawingScene * drawingscene) { this->drawingscene = drawingscene;}

	void setDrawingMode(bool mode) { drawingMode = mode; }
	bool getDrawingMode() { return drawingMode; }
	QPointF getViewCenter();
public slots:
	void printPos(const QString & prt);
	void SetCenter(const QPointF& centerPoint);
	void drawMpp();
protected:
	//void resizeEvent(QResizeEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void wheelEvent(QWheelEvent* event);
private:
	//DrawingScene * scene;
	QPolygonF polygonF;
	QPointF pointF;
    //Holds the current centerpoint for the view, used for panning and zooming
    QPointF CurrentCenterPoint;

    //From panning the view
    QPoint LastPanPoint;

    QPointF pPoint;
    QPointF cPoint;

    DrawingScene * drawingscene;
    bool drawingMode;									// true: drawingMode,  false : non drawing mode;
signals:
	//void emitDebug(const QString & prt);
	void emitPos(const QString & prt);
	void moved(const QPointF point);
	void emitZoomIn(const double scale);
	void emitZoomOut(const double scale);

};

#endif /* DRAWINGEXAMPLE_04_H_ */
