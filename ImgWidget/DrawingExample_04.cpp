/*
 * DrawingExample_04.cpp
 *
 *  Created on: 2013. 1. 17.
 *      Author: jiwon
 */

#include "DrawingExample_04.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsPolygonItem>
#include <QPainter>
#include "OPENGL/glwidget.h"

DrawingExample_04::DrawingExample_04(QWidget *parent)
: QGraphicsView(parent)
{
	qDebug()<<"DrawingExample_04 is called..";
	// TODO Auto-generated constructor stub

	//setGeometry(QRect(0, 0, 250, 250));

	/*scene = new QGraphicsScene();
	scene->setSceneRect(0,0,250,250);
	setScene(scene);*/
	this->setMouseTracking(true);

	setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);


	//Set-up the view
	//setSceneRect(0, 0, 5000, 5000);

	//SetCenter(QPointF(2500.0, 2500.0)); //A modified version of centerOn(), handles special cases
	setInteractive(true);

	/*GLWidget * glWidget = new GLWidget(QGLFormat(QGL::SampleBuffers));
	glWidget->makeCurrent();*/
	//setViewport(new QGLWidget(new QGLContext(QGLFormat(QGL::SampleBuffers))));
	//setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
	setViewportUpdateMode(BoundingRectViewportUpdate);

	//setCursor(Qt::OpenHandCursor);
	//show();
	isPress = false;
	qDebug()<<"DrawingExample_04 constructor is close..scene rect : "<<this->sceneRect();
	//setBackgroundBrush(QColor(255, 0, 0));
	//this->setForegroundBrush(QColor(255,0,0));
}

DrawingExample_04::~DrawingExample_04() {
	// TODO Auto-generated destructor stub
}


void DrawingExample_04::SetCenter(const QPointF& centerPoint) {
    //Get the rectangle of the visible area in scene coords
//	qDebug()<<"=================================================";
//	qDebug()<<"[DrawingArea] SetCener is called.. pos : "<<centerPoint;
    QRectF visibleArea = mapToScene(rect()).boundingRect();

    //Get the scene area
    QRectF sceneBounds = sceneRect();

    double boundX = visibleArea.width() / 2.0;
    double boundY = visibleArea.height() / 2.0;
    double boundWidth = sceneBounds.width() - 2.0 * boundX;
    double boundHeight = sceneBounds.height() - 2.0 * boundY;

    //The max boundary that the centerPoint can be to
    QRectF bounds(boundX, boundY, boundWidth, boundHeight);

    if(bounds.contains(centerPoint)) {
        //We are within the bounds
        CurrentCenterPoint = centerPoint;
    } else {
        //We need to clamp or use the center of the screen
        if(visibleArea.contains(sceneBounds)) {
            //Use the center of scene ie. we can see the whole scene
            CurrentCenterPoint = sceneBounds.center();
        } else {

            CurrentCenterPoint = centerPoint;

            //We need to clamp the center. The centerPoint is too large
            if(centerPoint.x() > bounds.x() + bounds.width()) {
                CurrentCenterPoint.setX(bounds.x() + bounds.width());
            } else if(centerPoint.x() < bounds.x()) {
                CurrentCenterPoint.setX(bounds.x());
            }

            if(centerPoint.y() > bounds.y() + bounds.height()) {
                CurrentCenterPoint.setY(bounds.y() + bounds.height());
            } else if(centerPoint.y() < bounds.y()) {
                CurrentCenterPoint.setY(bounds.y());
            }

        }
    }

    //Update the scrollbars
    centerOn(CurrentCenterPoint);
}


/* 20130618 원본 소
 * void DrawingExample_04::mousePressEvent(QMouseEvent* event) {
	//For panning the view
	//qDebug()<<"[DrawingExample_04]Mouse Press Event called..";
	if (event->button() != Qt::RightButton){
		//qDebug()<<"Right Button is not clicked..";
		setCursor(Qt::ArrowCursor);
		QGraphicsView::mousePressEvent(event);
		 return;
	}
	if (event->buttons() & Qt::RightButton)
	{
		//qDebug()<<"Right Button is clicked..";
		LastPanPoint = event->pos();
		setCursor(Qt::ClosedHandCursor);
		if(isPress == true){
			isPress = false;
		}else{
			isPress = true;
		}
	}
}*/

void DrawingExample_04::mousePressEvent(QMouseEvent* event) {
	//For panning the view


	drawingMode = drawingscene->getDrawingMode();
	qDebug()<<"[DrawingExample_04]Mouse Press Event called.. drawmingMode : "<<drawingMode;
	if(drawingMode == false){
		//qDebug()<<"drawingMode false..";
		if (event->button() != Qt::RightButton){
			//qDebug()<<"Right Button is not clicked..";
			LastPanPoint = event->pos();

			//아이템이 존재하는 확인한다.
			QPointF point = mapToScene(LastPanPoint);

			qDebug()<<"point : "<<point;
			if(drawingscene->checkUserItems(point) == false){
				QGraphicsView::mousePressEvent(event);
				return;
			}


			if(isPress == true){
				isPress = false;
			}else{
				isPress = true;
			}
			//setCursor(Qt::ArrowCursor);
//			QGraphicsView::mousePressEvent(event);
			//return;
		}
		QGraphicsView::mousePressEvent(event);
	}else{
		qDebug()<<"non drawingMode..";
		if (event->button() == Qt::LeftButton){
			qDebug()<<"Left Button";
			isPress = false;
			QGraphicsView::mousePressEvent(event);
		}else if(event->button() == Qt::RightButton){
			qDebug()<<"RightButton";
			QGraphicsView::mousePressEvent(event);
		}
	}
	//QGraphicsView::mousePressEvent(event);
}

/**
 * Handles when the mouse button is released
 */
 void DrawingExample_04::mouseReleaseEvent(QMouseEvent* event) {
	if(isPress == true){
		 setCursor(Qt::ArrowCursor);
		 LastPanPoint = QPoint();

		 QGraphicsView::mouseReleaseEvent(event);
		 isPress = false;
	}else{
		// qDebug()<<"[DrawingExample_04] mouseMove event is called..";
		 QGraphicsView::mouseReleaseEvent(event);
	 }
 }

 /**
 *Handles the mouse move event
 */
 void DrawingExample_04::mouseMoveEvent(QMouseEvent* event) {
	 //qDebug()<<"IsPress : "<<isPress;
	 if(isPress == true){
		 if(!LastPanPoint.isNull()) {
			 setCursor(Qt::ClosedHandCursor);
			 //Get how much we panned
			 QPointF delta = mapToScene(LastPanPoint) - mapToScene(event->pos());
			 //qDebug()<<"The Wheel Delta value:"<< delta;
			 LastPanPoint = event->pos();

			 //Update the center ie. do the pan
			 if(delta.x() < 0 )
			 {
				 SetCenter(GetCenter() + delta);
			 } else
				 SetCenter(GetCenter() + delta);
			 QGraphicsView::mouseMoveEvent(event);

			 drawMpp();
		 }
	 }else{
		 //qDebug()<<"[DrawingExample_04] mouseMove event is called..";
		 QGraphicsView::mouseMoveEvent(event);
	 }
 }


/*void DrawingExample_04::mousePressEvent(QMouseEvent* event) {
	//For panning the view
	LastPanPoint = event->pos();
	setCursor(Qt::ClosedHandCursor);
 }*/

 /**
 * Handles when the mouse button is released
 */
 /*void DrawingExample_04::mouseReleaseEvent(QMouseEvent* event) {
	 setCursor(Qt::OpenHandCursor);
	 LastPanPoint = QPoint();
 }*/

 /**
 *Handles the mouse move event
 */
 /*void DrawingExample_04::mouseMoveEvent(QMouseEvent* event) {
	 if(!LastPanPoint.isNull()) {
		 //Get how much we panned
		 QPointF delta = mapToScene(LastPanPoint) - mapToScene(event->pos());
		 qDebug()<<"The Wheel Delta value:"<< delta;
		 LastPanPoint = event->pos();

 //Update the center ie. do the pan
		 if(delta.x() < 0 )
		 {
			 qDebug()<<"-"<<", Center : "<<GetCenter();
			 SetCenter(GetCenter() + delta);
		 } else{
			 qDebug()<<"+"<<", Center : "<<GetCenter();;
			 SetCenter(GetCenter() + delta);
		 }
	 }
 }*/


/**
  * Zoom the view in and out.
  */
/*void DrawingExample_04::wheelEvent(QWheelEvent* event) {

    //Get the position of the mouse before scaling, in scene coords
    QPointF pointBeforeScale(mapToScene(event->pos()));

    //Get the original screen centerpoint
    QPointF screenCenter = GetCenter(); //CurrentCenterPoint; //(visRect.center());

    //Scale the view ie. do the zoom
    double scaleFactor = 1.10; //How fast we zoom
    if(event->delta() > 0) {
        //Zoom in
        scale(scaleFactor, scaleFactor);
        emit emitZoomIn(scaleFactor);
        qDebug()<<"Zoom in..";
    } else {
        //Zooming out
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        emit emitZoomOut(1.0 / scaleFactor);
    }




    //Get the position after scaling, in scene coords
    QPointF pointAfterScale(mapToScene(event->pos()));

    //Get the offset of how the screen moved
    QPointF offset = pointBeforeScale - pointAfterScale;

    //Adjust to the new center for correct zooming
    QPointF newCenter = screenCenter + offset;
    SetCenter(newCenter);

    drawMpp();
}*/


 void DrawingExample_04::wheelEvent(QWheelEvent* event) {

     //Get the position of the mouse before scaling, in scene coords
	 //qDebug()<<"DrawingArea size : "<<this->size();
     QPointF pointBeforeScale(mapToScene(event->pos()));

     //Get the original screen centerpoint
     QPointF screenCenter = GetCenter(); //CurrentCenterPoint; //(visRect.center());

     //Scale the view ie. do the zoom
     double scaleFactor = 1.10; //How fast we zoom
     if(event->delta() > 0) {
         //Zoom in
         //scale(scaleFactor, scaleFactor);
         emit emitZoomIn(scaleFactor);
        // qDebug()<<"Zoom in..";
     } else {
         //Zooming out
         //scale(1.0 / scaleFactor, 1.0 / scaleFactor);
         emit emitZoomOut(1.0 / scaleFactor);
     }




     //Get the position after scaling, in scene coords
     QPointF pointAfterScale(mapToScene(event->pos()));

     //Get the offset of how the screen moved
     QPointF offset = pointBeforeScale - pointAfterScale;

     //Adjust to the new center for correct zooming
     QPointF newCenter = screenCenter + offset;
     SetCenter(newCenter);

     drawMpp();
 }

void DrawingExample_04::printPos(const QString & prt)
{
	qDebug()<<"[DrawingExample_04] printPos called..";
	emitPos(prt);
}


/**
  * Need to update the center so there is no jolt in the
  * interaction after resizing the widget.
  */
/*
void DrawingExample_04::resizeEvent(QResizeEvent* event) {
    //Get the rectangle of the visible area in scene coords
	qDebug()<<"Resize Event is called..";
    QRectF visibleArea = mapToScene(rect()).boundingRect();
    SetCenter(visibleArea.center());

    //Call the subclass resize so the scrollbars are updated correctly
    QGraphicsView::resizeEvent(event);

    qDebug()<<"[DrawingExample_04] Resize Event close..sceneRect : "<<sceneRect()<<", visibleArea : "<<visibleArea;
}
*/

/*
 * MPP를 적용하기 위한 함수
 */
void DrawingExample_04::drawMpp()
{
    //Test
	QPointF txtInfo = mapToScene(rect().topLeft());
//	qDebug()<<"txtInfo : "<<txtInfo;
	drawingscene->drawMpp(txtInfo);
//	qDebug()<<"drawMpp close..";
}

/*
 * 뷰의 중간 좌표를 반환한다. 뷰의 중간 좌표는 (2500, 2500)이다. 단 5000 * 5000 인 경우에만 해당.
 *
 */

QPointF DrawingExample_04::getViewCenter()
{
	return QPointF(2500, 2500);
}
