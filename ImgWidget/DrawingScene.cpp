/*
 * DrawingScene.cpp
 *
 *  Created on: 2013. 1. 21.
 *      Author: jiwon
 */

#include "DrawingScene.h"
#include <QGraphicsLineItem>
#include "DRAWING/CLineItem.h"
#include <math.h>

#define PI 3.14
#define NODE_RAD 20

using namespace::DS;

DrawingScene::DrawingScene(QObject * parent)
: QGraphicsScene(parent)
{
	// TODO Auto-generated constructor stub
	enableText = true;
	openNewMap = true;
	enableArcDrawing = false;
	enableArc = false;
	enablePolyline = false;
	enablePolygon = false;
	mppItem = 0;
	my = 0;
	latlonItem = 0;
	latlonDrawer = 0;
	angle = 0;
	scale = 1;
	drawingMng = new DrawingMng;
	//connect(drawingMng, SIGNAL(emitUserObject(QVector<UserObject>)), this, SLOT(runUserObject(QVector<UserObject>)));
	mode = -1;
	drawingMode = false;
	curitem = 0;
	colTimer = new QTimer;
	colTimer->setInterval(500);
	connect(colTimer, SIGNAL(timeout()), this, SLOT(findNode()));
//	this->setSceneRect(0, 0, 600, 600);
	setBackgroundBrush(QColor(47, 157, 39));

	drMode = Initial;


	qDebug()<<"[DrawingScene] constructor is called.";
}

DrawingScene::~DrawingScene() {
	// TODO Auto-generated destructor stub
}

void DrawingScene::initLine()
{

	qDebug()<<"pPoint : "<<pPoint<<", cPoint : "<<cPoint;
	QGraphicsLineItem * item = new QGraphicsLineItem(QLineF(pPoint, cPoint));
	pPoint = cPoint;

	addItem(item);


}

void DrawingScene::keyPressEvent(QKeyEvent * eve)
{
	//qDebug()<<"[DrawingScene] keyPressEvent is called..";

	/*Node * tmpNode = static_cast<Node*>(mouseGrabberItem());
	if(tmpNode == 0){
		qDebug()<<"Error!";
	}else{
		qDebug()<<tmpNode->getNodeNm();
	}*/

	Node * tmpNode = static_cast<Node*>(focusItem());
	//QMetaObject::invokeMethod(tmpNode, "createWP", Qt::QueuedConnection);
	if(tmpNode == 0){
		qDebug()<<"Error!";
		return;
	}
	qreal xPos = tmpNode->pos().x();
	qreal yPos = tmpNode->pos().y();

	float fx, fy;

	switch(eve->key()){

		case Qt::Key_Left :
			xPos -= 4.0;
			break;
		case Qt::Key_Right :
			xPos += 4.0;
			break;
		case Qt::Key_Up :
			yPos -= 4.0;
			break;
		case Qt::Key_Down :
			yPos += 4.0;
			break;
		case Qt::Key_Space :
			if(tmpNode == 0){
				qDebug()<<"Error!";
				break;
			}else{
				this->addItem(tmpNode->goWP(tmpNode->sceneBoundingRect().x(), tmpNode->sceneBoundingRect().y() + 30,
					tmpNode->sceneBoundingRect().x()+10, tmpNode->sceneBoundingRect().y()+30));
			}
			break;
	}

	fx = xPos;
	fy = yPos;
	tmpNode->setPos(fx, fy);
}

void DrawingScene::mousePressEvent(QGraphicsSceneMouseEvent *eve )
{

	qDebug()<<"[DrawingScene]mousepressEvent is clicked..";

	//qDebug()<<"Mouse Press Event called..";
	if (eve->button() != Qt::LeftButton){
		//qDebug()<<"Left Button is not clicked..";
		enableRightButton = true;
		if(eve->button() & Qt::RightButton && enablePolygon == true)
		{
			qDebug()<<"completePolygon..";
			//폴리곤을 완성 시킨다.
			//drawingMng->completePolygon();
			drawingMng->completedPolygon(eve->scenePos(), curitem, this);
			curitem = 0;
			drawingMode = false;
			enablePolygon = false;
		}else if(eve->button() & Qt::RightButton && enablePolyline == true)
		{
			qDebug()<<"completePolyline..";
			//폴리곤을 완성 시킨다.
			drawingMng->completedPolyline(eve->scenePos(), curitem, this);
			curitem = 0;
			drawingMode = false;
			enablePolyline = false;
		}else if(eve->button() & Qt::RightButton && enableArc == true && enableArcDrawing == true)
		{
			//아크를 드로잉하고 종료 한다.
			qDebug()<<"[DrawingScene-mousePressEvent] arc drawing will be finished..";
			drawingMng->completeItems(drawing, curitem, this);
			curitem = 0;
			drawingMode = false;
			enableArc = false;
			enableArcDrawing = false;
			drawingMng->setArcDrawing(false);
		}else{
			enableRightButton = true;
		}

		QGraphicsScene::mousePressEvent(eve);
		return;
	}

	if (eve->buttons() & Qt::LeftButton)
	{
		//qDebug()<<"Mouse Button Clicked..";

		pPoint = eve->scenePos();

		/*
		 * DrawingMode가 true인 경우에만 (DrawingObject Button을 클릭시에만) 실행된다..
		 * Polygon과 Polyline인 경우 따로 처리를 해준다.
		 */
		if(drawingMode == true){
			//this->drawCustomizedItems_mousePress(eve->scenePos(), eve->scenePos());
			//DrawingMng::getInstance().createItems(drawing, eve->scenePos(), curitem);


			if(drawing.shape == Polygon){
				if(enablePolygon == true && curitem != 0){
					//먼저 마우스를 클릭한 상태임.
					//qDebug()<<"H1";
					drawingMng->fixPolygon(pPoint, curitem);
				}else{
					enablePolygon = true;
					drawingMng->createPolygon(pPoint, &curitem);
					//qDebug()<<"H2";
					//qDebug()<<"curitem : "<<curitem;
				}
			}else if(drawing.shape == Polyline){
				if(enablePolyline == true && curitem != 0){
					//먼저 마우스를 클릭한 상태임.
					//qDebug()<<"H1";
					drawingMng->fixPolyline(pPoint, curitem);
				}else{
					enablePolyline = true;
					drawingMng->createPolyline(pPoint, &curitem);
					qDebug()<<"H2";
					qDebug()<<"curitem : "<<curitem;
				}
			}else{
				//Polygon과 Polyline이 아닌 경우 첫번째 Item을 생성한다.
				drawingMng->createItems(drawing, eve->scenePos(), &curitem, this);
				if(drawing.shape == Arc){
					enableArc = true;
				}
			}
			//qDebug()<<"CurItem : "<<curitem;
			addItem(curitem);
		}

		if(mode == 0){
			//colTimer->start();
			drawingChart();
		}else if(mode == 1){
			drawingNodes();
		}
		mode = -1;

	}
	QGraphicsScene::mousePressEvent(eve);

}

void DrawingScene::mouseMoveEvent(QGraphicsSceneMouseEvent *eve)
{

	//qDebug()<<"[DrawingScene] mouseMoveEvent is called.. curitem : "<<curitem;
	if(drawingMode == true && curitem != 0){
		//this->drawCustomizedItems_mouseMove(eve->scenePos());
		//DrawingMng::getInstance().drawItems(drawing, eve->scenePos(), curitem);
		if(enableArcDrawing == true){
			//Arc Drawing을 위해 drawingMng에 arcdrawing setting.
			//qDebug()<<"enableArcdrawing is true..";
			drawingMng->setArcDrawing(enableArcDrawing);
			drawingMng->drawItems(drawing, eve->scenePos(), curitem);
		}
		drawingMng->drawItems(drawing, eve->scenePos(), curitem);
	}

	if(enablePolygon && curitem != 0){
		//qDebug()<<"h1"<<", ScenePos : "<<eve->scenePos();
		drawingMng->drawPolygon(eve->scenePos(), curitem);
	}

	if(enablePolyline && curitem != 0){
		qDebug()<<"h1"<<", ScenePos : "<<eve->scenePos();
		drawingMng->drawPolyline(eve->scenePos(), curitem);
	}

	QPointF tmpPos = eve->scenePos();
	QString txtpos = "X:";
	txtpos.append(QString::number(tmpPos.x()));
	txtpos.append(", Y:");
	txtpos.append(QString::number(tmpPos.y()));

	double lon = 0;
	double lat = 0;

	QPoint point;
	point.setX((int)tmpPos.x());
	point.setY((int)tmpPos.y());

	QString strPos = LatLonConvert::getInstance().screenToLatLon(point);
	//qDebug()<<"point : "<<strPos;

/*
	WGS84_TM::getInstance().setScale(scale);
	WGS84_TM::getInstance().XYConvert(x, y, &lon, &lat, angle);
*/

	//qDebug()<<"lon : "<<lon<<", lat : "<<lat;

	QString txtlatlon = QString().setNum(lat, 'f', 4);
	txtlatlon.append('/');
	txtlatlon.append(QString().setNum(lon, 'f', 4));

	//qDebug()<<"Pos : "<<txtpos;

	emitPos(txtpos, strPos);
	//displayToCoordinate(tmpPos, 1);
	if(eve->buttons() & Qt::LeftButton){
		cPoint = eve->scenePos();
		//initLine();
	}
	QGraphicsScene::mouseMoveEvent(eve);
}

/**
 * 마우스 버튼을 띈다.
 */
void DrawingScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	if (curitem != 0 && drawingMode == true){
		//drawCustomizedItems_mouseRelease();

		if(enableArc == true){
			qDebug()<<"enableArc is true..";
			enableArcDrawing = true;
			drawingMng->completeItems(drawing, curitem, this);
			//drawingMng->setArcDrawing(true);
			return;
		}
		if(enablePolygon == false && enablePolyline == false){
			qDebug()<<"R1";
			drawingMng->completeItems(drawing, curitem, this);
			//여기서 드로잉 위젯으로 시그널을 전송한다..
			curitem = 0;
			drawingMode = false;
		}
		qDebug()<<"R2";
	}

		if(enableRightButton == true){
			//원점 변경하여 드로잉
			qDebug()<<"RightButton : "<<enableRightButton;
			QPointF p = mouseEvent->scenePos();
			p = LatLonConvert::getInstance().screenToDecimal(p.toPoint());
			LatLonConvert::getInstance().moveNorthPoint(p.x());
			LatLonConvert::getInstance().moveGreenichPoint(p.y());

			this->setAngle(0);

			enableRightButton = false;
		}
		qDebug()<<"RightButton2 : "<<enableRightButton;


    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}


void DrawingScene::drawingEllipse()
{
	//Draw Ellipse
	qreal x = pPoint.x() - 20;
	qreal y = pPoint.y() - 20;
	qreal width = 40;
	qreal height = 40;
	QGraphicsEllipseItem * item = new QGraphicsEllipseItem(x, y, width, height);
	item->setFlag(QGraphicsItem::ItemIsMovable, true);
	item->setFlag(QGraphicsItem::ItemIsSelectable, true);
	item->setBrush(Qt::blue);
	QGraphicsLineItem * lineItem = new QGraphicsLineItem(x + 20, y + 20, x + 40, y - 60, item);
	/*item->setFlag(QGraphicsItem::ItemIsMovable, true);
	item->setFlag(QGraphicsItem::ItemIsSelectable, true);*/
	addItem(item);
	setFocusItem(item);
	//addItem(lineItem);

}


void DrawingScene::drawingNodes()
{
	static int j = 0;

	for(int i = 0 ; i < 4 ; i++){
		Node * node = new Node(pPoint.x() -20, pPoint.y() - 20 + (i * 10), 2, 2, 1);
		node->setNodeNm("test_"+QString().setNum(j++, 10));
		node->setZValue(2);
		addItem(node);
		connect(node, SIGNAL(emitRemoveNode(Node * )), this, SLOT(removeNode(Node *)));
		connect(node, SIGNAL(emitFindNode()), this, SLOT(findNode()));
		node_list.append(node);
	}
}


void DrawingScene::drawingChart()
{
	qDebug()<<"[DrawingScene] drawingChart is called..";
	QPointF strPoint(500,500);



	/*for(int i = 0 ; i < 4 ; i++){
		Node * node = new Node(pPoint.x() -20, pPoint.y() - 20 + (i * 10), 2, 2, 1);
		node->setNodeNm("test_"+QString().setNum(j++, 10));
		node->setZValue(2);
		addItem(node);
		connect(node, SIGNAL(emitRemoveNode(Node * )), this, SLOT(removeNode(Node *)));
		connect(node, SIGNAL(emitFindNode()), this, SLOT(findNode()));
		node_list.append(node);
	}*/

	//Draw Enemy
/*	EMNode * enemy_node = new EMNode(800, 500, 40, 40);
	connect(enemy_node, SIGNAL(emitEnemyWP(QGraphicsItem *)), this, SLOT(addEnemyWP(QGraphicsItem *)));
	//connect(enemy_node, SIGNAL(emitFindNode()), this, SLOT(findNode()));
	enemy_node->setEMNodeNm("Enemy Node");
	addItem(enemy_node);*/
	//QMetaObject::invokeMethod(enemy_node, "createWP", Qt::QueuedConnection);


	/*qreal wx = 2500;
	qreal wy = 2500;
	qDebug()<<"[DrawingScene] drawing line is called..";
	for(int i = 0 ; i < latlonmng_list.size() ; i++){
		//qDebug()<<"loop start : "<<i;
		LatLonMng latlonmng = latlonmng_list.at(i);
		qDebug()<<"ID : "<<latlonmng.getId_name();

		//QVector<LatLon> converted_latlon = latlonmng.getConvertedLatLonList();

		//Polygon Item

		if(latlonmng.isEnable == true){
			QPolygonF polygonF(latlonmng.getConvertedLatLonList2QPointF());
			QGraphicsPolygonItem * item = new QGraphicsPolygonItem(polygonF);

			//item->setPen(latlonmng.layer_color);
			item->setBrush(Qt::green);
			addItem(item);

		}*/ //Ommited 20130522


		/*for(int j = 0 ; j < converted_latlon.size() ; j++){

			LatLon start = converted_latlon.at(j);
			LatLon last;
			if(j < converted_latlon.size()-1){
				last = converted_latlon.at(j+1);
			}else{
				last = start;
			}
			qreal x = wx + start.lon;
			qreal y = wy + start.lat;
			qreal x1 = wx + last.lon;
			qreal y1 = wy + last.lat;

			qDebug()<<"Idx : "<<j<<", line start..x : "<<x<<", y : "<<y<<", x1 "<<x1<<", y1 "<<y1;
			//QGraphicsLineItem * item = new QGraphicsLineItem(x, y, x1, y1);
			QGraphicsPolygonItem * item = new QGraphics

			item->setPen(latlonmng.layer_color);
			addItem(item);
		}*/
	//}

	this->drawMapInfo();

}

void DrawingScene::addEnemyWP(QGraphicsItem * item)
{
	addItem(item);
	//this->findNode();
}

QString DrawingScene::displayToCoordinate(const QPointF& point, int zoom)
{
    // longitude
	zoom = 1;
    double longitude = (point.x()*(360/(pow(2,zoom)*256)))-180;
    // latitude
    double latitude = point.y()*(2/(pow(2,zoom)*256));
    latitude = 1-latitude;
    latitude = latitude*PI;
    latitude = (atan(sinh(latitude))) * 180 / PI;

    //Coordinate coord = Coordinate(longitude, latitude);
    //return coord;
    qDebug()<<"Lat : "<<QString().setNum(latitude)<<", Lon : "<<QString().setNum(longitude);
    return "";
}

//자식 노드들을 그린다..

void DrawingScene::drawingChildNode(QVector<QGraphicsEllipseItem *> child_list)
{
	qDebug()<<"[DrawingScene] drawingChildNode is called..";

	for(int i = 0 ; i < child_list.count() ; i++){
		addItem(child_list[i]);
	}
}

//테스트
void DrawingScene::deleteChildNode(QGraphicsEllipseItem ** child)
{
	qDebug()<<"deleteChildNode is called..";


	for(int i = 0 ; i < 3 ; i++){
		if(!child[i])
		{
			qDebug()<<"remove process..";
			removeItem(child[i]);
		}

	}

}

/**
 * Node를 제거 한다.
 */
void DrawingScene::removeNode(Node * node)
{
	qDebug()<<"removeNode is called..";

	removeItem(node);
}

bool DrawingScene::findNode()
{
	//qDebug()<<"Find Node is called..";

	QList<QGraphicsItem * > item_list = this->items();
	EMNode * enemy_node;
	//Enemy Detection
	for(int i = 0 ; i < item_list.count() ; i++){
		qDebug()<<"Type : "<<item_list.at(i)->type();
	}


	//Collide test
	for(int i = 0 ; i < item_list.count() ; i++){
		if(item_list.at(i)->type() == 4){
			Node * item = static_cast<Node *>(item_list.at(i));
			qDebug()<<"Nm : "<<item->getNodeNm();
			for(int j = 0 ; j < item_list.count() ; j++){
				if(item_list.at(j)->type() == 6){
					CommonWP * cwp = (CommonWP *)item_list.at(j);
					bool chk = item->collidesWithItem(cwp);
					if(chk == true){
						qDebug()<<"Collision Detection..";
						/*if(item->getNodeNm() != ""){
							qDebug()<<item->getNodeNm()<<" with "<<cwp->getWp_name();
						}*/
						cwp->~CommonWP();
		//				item->updateTimer->stop();
		//				target_item->updateTimer->stop();

				}
			}
		}
	}



	}
	//qDebug()<<"Find Node is close..";
	return true;
}


/*
 * 해당 함수는 맵 인포에서 uncheck 된 항목을 체크 한다.
 * 맵 레이어 인포에서 체크한 레이어에 대해서 그리그를 다시 한다..
 */
void DrawingScene::checkLayerInfo(QStringList unchecked_layer_list, QStringList checked_layer_list, DrawingMode dm)
{
	qDebug()<<"[DrawingScene] checkLayerInfo is called.. Mode : "<<dm;



	if(dm == SMSMap){
		for(int i = 0 ; i < unchecked_layer_list.size() ; i++){
			QString layer_name = unchecked_layer_list.at(i);
			for(int j = 0 ; j < latlonmng_list.size() ; j++){
				LatLonMng latlonmng = latlonmng_list.at(j);
				if(layer_name == latlonmng.getId_name()){
					latlonmng.isEnable = false;
					latlonmng_list.replace(j, latlonmng);
				}/*else {
					if(latlonmng.isEnable == false){
						latlonmng.isEnable = true;
						latlonmng_list.replace(j, latlonmng);
					}

				}*/
			}
		}

		for(int i = 0 ; i < checked_layer_list.size() ; i++){
			QString layer_name = checked_layer_list.at(i);
			for(int j = 0 ; j < latlonmng_list.size() ; j++){
				LatLonMng latlonmng = latlonmng_list.at(j);
				if(layer_name == latlonmng.getId_name()){
					latlonmng.isEnable = true;
					latlonmng_list.replace(j, latlonmng);
				}
			}
		}

		//this->clearItems();
		drawMapInfo();
	}else if(dm == UserMap){
		//UserMap ReDrawing
		QVector<UserObject> &object_list = drawingMng->getUserObjectList();
		for(int i = 0 ; i < unchecked_layer_list.size() ; i++){
			QString layer_name = unchecked_layer_list.at(i);
			for(int j = 0 ; j < object_list.size() ; j++){
				UserObject object = object_list.at(j);
				qDebug()<<"LayerName : "<<layer_name<<", ObjectName : "<<object.obj_name;
				if(layer_name == object.obj_name){
					object.chkObject = false;
					object_list.replace(j, object);
				}
			}
		}

		for(int i = 0 ; i < checked_layer_list.size() ; i++){
			QString layer_name = checked_layer_list.at(i);
			for(int j = 0 ; j < object_list.size() ; j++){
				UserObject object = object_list.at(j);
				qDebug()<<"LayerName : "<<layer_name<<", ObjectName : "<<object.obj_name;
				if(layer_name == object.obj_name){
					object.chkObject = true;
					object_list.replace(j, object);
				}
			}
		}

		drawUserMapInfo();

	}

}

void DrawingScene::setEnable2AllLayer()
{
	for(int i = 0 ; i < latlonmng_list.size() ; i++){
		latlonmng_list[i].isEnable = true;
	}
}

/*
 * 실제로 읽은 맵파일을 이용하여 화면에 현시하는 기능을 한다.
 */
void DrawingScene::drawMapInfo()
{

//	qDebug()<<"=======================================";
//	qDebug()<<"[DrawingScene] drawMapInfo is called.. Angle"<<angle;

	/*
	 * 여기서 latlonmng_list에 모든 맵 정보가 저장되어 있다. 만약 해당 리스트의 값이 0이면 그릴수 있는 맵이 존재 하지 않는다.
	 * Angle 값이 주어졌을 경우 latlonmng_list를 새롭게 받아 와야 한다.
	 */
	//qDebug()<<"Scale : "<<scale;


	WGS84_TM::getInstance().setScale(scale);

	if(openNewMap == true || drMode == ReDrawing){
		//qDebug()<<"[DrawingScene - drawMapInfo] openNewMap is true..";
		if(openNewMap == true){
			for(int i = 0 ; i < latlonmng_list.size() ; i++){

				LatLonMng latlonmng = latlonmng_list.at(i);
				//Polygon Item
				QGraphicsItem * qgitem = drawingMng->drawMapInfo(latlonmng);
				//qDebug()<<"MapItem : "<<qgitem;
				//LineItem * item = dynamic_cast<LineItem *>(qgitem);
				//text item
				QGraphicsTextItem * txtItem = drawingMng->drawText(latlonmng.getId_name(), latlonmng.drawMapId());
				latlonmng.setTextItem(txtItem);
				latlonmng.setItem(qgitem);
				latlonmng_list.replace(i, latlonmng);
				addItem(qgitem);
				addItem(txtItem);
//				if(enableText == false){
//					txtItem->setVisible(false);
//				}else{
//					txtItem->setVisible(true);
//				}
				//enableText = false;


				openNewMap = false;

			}
		}
	}

	//레이어 체크 상태를 반영하여, 체크가 되지 않으면, 해당 레이어 및 텍스트를 보이지 않게 하며, 그렇치 않은 경우 보이도록 한다..

	for(int i = 0 ; i < latlonmng_list.size() ; i++){
		LatLonMng latlonmng = latlonmng_list.at(i);
		//qDebug()<<"LatLonItem : "<<latlonmng.getItem();
		if(latlonmng.isEnable == true){
			//qDebug()<<"Enable ..";
			//LineItem * item = dynamic_cast<LineItem *>(latlonmng.getItem());
			latlonmng.getItem()->setVisible(true);
			//latlonmng.getTextItem()->setVisible(true);
			if(enableText == false){
				latlonmng.getTextItem()->setVisible(false);
			}else{
				latlonmng.getTextItem()->setVisible(true);
			}

		}else{
			//qDebug()<<"Disable..";
			latlonmng.getItem()->setVisible(false);
			latlonmng.getTextItem()->setVisible(false);
		}
		//qDebug()<<"loop..";

	}




/*

	WGS84_TM::getInstance().setScale(scale);

	for(int i = 0 ; i < latlonmng_list.size() ; i++){
		LatLonMng latlonmng = latlonmng_list.at(i);
		//Polygon Item
		if(latlonmng.isEnable == true){
			//폴리곤 타입 그리기 - LatLonMng에 관리하는 QPointF 타입의 좌표를 가져온다.

			//처음 파일을 오픈 했는 경우
		//	if(openNewMap == true){
			QGraphicsItem * qgitem = drawingMng->drawMapInfo(latlonmng);

//				LineItem * item = dynamic_cast<LineItem *>(qgitem);
//				if(item == 0){
////				qDebug()<<"Casting is failed..";
////				}else{
////					qDebug()<<"Casting is success..";
////				}
				//qDebug()<<"item : "<<item;
			addItem(qgitem);
				////item->update();
		}

	}
*/



	//qDebug()<<"===========end==========";
}

/*
 *  아이디를 드로잉한다.
 *  1) enableText 값이 true이면 모든 아이디 텍스트를 비현시한다.
 *  2) enableText 값이 false 이면, 모든 아이디에 대해서 체크가 되어 있는 경우에만 아이디 텍스트를 현시하고, 그 외에는 현시 하지 않는다.
 */
void DrawingScene::drawText()
{
	//qDebug()<<"[DrawingScene - drawText] called..";


	if(enableText == true){
		for(int i = 0 ; i < latlonmng_list.size() ; i++){
			LatLonMng latlonmng = latlonmng_list.at(i);
			if(enableText == true){
				//qDebug()<<"enable true..";
				latlonmng.getTextItem()->setVisible(false);
			}
		}
		enableText = false;
	}else{
		for(int i = 0 ; i < latlonmng_list.size() ; i++){
			LatLonMng latlonmng = latlonmng_list.at(i);
			if(latlonmng.isEnable == true){
				latlonmng.getTextItem()->setVisible(true);
			}else{
				latlonmng.getTextItem()->setVisible(false);
			}
		}
		enableText = true;
	}

}

/*
 *  위경도 그리드
 */
void DrawingScene::displayLatLon()
{

	//qDebug()<<"[DrawingScene] displayLatLon";

	if(latlonMode == true){
		if(latlonItem == 0){
			qDebug()<<"latlon is 0";
			latlonItem = new LatLonItem;
			//latlonItem->setScreenConvertClass(vp);
			latlonItem->setVisible(true);
			this->addItem(latlonItem);
			latlonItem->update();
		}else{
			if(latlonItem->getVisible() == true){
				latlonItem->setVisible(false);
				latlonItem->update();
			}else{
				latlonItem->setVisible(true);
				latlonItem->update();
			}
		}
	}else{
		if(latlonItem != 0){
			removeItem(latlonItem);
			latlonItem = 0;
		}
	}

}

/**
 * 맵 좌표 입력 다이얼로그에서 입력한 좌표로 이동한다..
 */

void DrawingScene::goToCoordinate(QWidget * lat, QWidget * lon, int status)
{

	qDebug()<<"[DrawingScene] goToCoordinate is called..";
	QLineEdit *edit_lat = qobject_cast<QLineEdit*>(lat);
	QLineEdit *edit_lon = qobject_cast<QLineEdit*>(lon);
	QString strLat = edit_lat->text();
	QString strLon = edit_lon->text();

	strLat = strLat.remove(0, 1);
	strLat.replace(":", "");
	strLat.replace(".", "");

	strLat.insert(2, '.');

	strLon = strLon.remove(0, 1);
	strLon.replace(':', "");
	strLon.replace('.', "");

	strLon.insert(3, '.');

	bool ok;

	double d_lon = strLon.toDouble(&ok);
	double d_lat = strLat.toDouble(&ok);


	QPointF latlonDecimal;
	latlonDecimal.setY(WGS84_TM::getInstance().MinSecond2Degree(d_lon));
	latlonDecimal.setX(WGS84_TM::getInstance().MinSecond2Degree(d_lat));

	QPointF point = LatLonConvert::getInstance().latlonToScreen2(latlonDecimal);

	qDebug()<<"point : "<<point;

	if(status == 1){
		Node * node = new Node(point.x(), point.y(), 2, 2, 1);
		node->updateTimer->stop();
		node->setZValue(2);
		addItem(node);
		connect(node, SIGNAL(emitRemoveNode(Node * )), this, SLOT(removeNode(Node *)));
		connect(node, SIGNAL(emitFindNode()), this, SLOT(findNode()));
	}
	emit emitCoordPos(point);





//	qDebug()<<"After..";
//	qDebug()<<"Lat : "<<strLat<<", Lon : "<<strLon;



	//임시
	/*qDebug()<<"[DrawingScene] goToCoordinate is called..";
	QLineEdit *edit_lat = qobject_cast<QLineEdit*>(lat);
	QLineEdit *edit_lon = qobject_cast<QLineEdit*>(lon);
	QString strLat = edit_lat->text();
	QString strLon = edit_lon->text();

	qDebug()<<"Lat : "<<strLat<<", Lon : "<<strLon;

	//입력한 Lat, Lon 정보를 도분초형태를 위경도로 변환하기 위한 형식으로 변경한다. '00.000000'
	strLat = strLat.remove(0, 1);
	strLat.replace(":", "");
	strLat.replace(".", "");

	strLat.insert(2, '.');

	strLon = strLon.remove(0, 1);
	strLon.replace(':', "");
	strLon.replace('.', "");

	strLon.insert(3, '.');

//	qDebug()<<"After..";
//	qDebug()<<"Lat : "<<strLat<<", Lon : "<<strLon;

	bool ok;

	double x = 0;
	double y = 0;

	double wx = 2500;
	double wy = 2500;


	//위경도를 X, Y 좌표로 변환한다..
	WGS84_TM::getInstance().LatLonConvert(x, y, strLon.toDouble(&ok), strLat.toDouble(&ok));
	qDebug()<<"x : "<<wx  + x<<", y : "<<wy + y;

	//변환한 좌표를 Rotate 시킨다..



	QPointF point = WGS84_TM::getInstance().rotateLatLon(QPointF(x, y), angle);
	point.setX(point.x() + wx);
	point.setY(point.y() + wy);

	qDebug()<<"point : "<<point;

	if(status == 1){
		Node * node = new Node(point.x(), point.y(), 2, 2, 1);
		node->updateTimer->stop();
		node->setZValue(2);
		addItem(node);
		connect(node, SIGNAL(emitRemoveNode(Node * )), this, SLOT(removeNode(Node *)));
		connect(node, SIGNAL(emitFindNode()), this, SLOT(findNode()));
	}
	emit emitCoordPos(point);*/
}

/*
 * 사용자 그리기 도구를 활성화 시킨다.
 */
void DrawingScene::runDrawing(DRAWING drawing)
{
	//qDebug()<<"[DrawingScene] run Drawing is called..";

	this->drawing = drawing;

	drawingMode = true;
	//qDebug()<<"[DrawingScene] run Drawing close..";
}



/*
 * 드로잉 모드에서 마우스 이벤트 처리 함수들.
 */
void DrawingScene::drawCustomizedItems_mouseMove(QPointF p1)
{

	Shape shape = drawing.shape;
	switch(shape)
	{
		case Line:
		{
			//qDebug()<<"Line..";
			QGraphicsLineItem * line = static_cast<QGraphicsLineItem *> (curitem);
			QLineF newLine(line->line().p1(), p1);
			line->setLine(newLine);
			qDebug()<<"Line : "<<line->line();
			break;
		}
		case Rect:
		{
			//qDebug()<<"Line..";

			QGraphicsRectItem * rect = static_cast<QGraphicsRectItem *> (curitem);
			QRectF newRect(rect->rect().topLeft(), p1);
			rect->setRect(newRect);
			break;
		}
		default:
			curitem = new QGraphicsEllipseItem;
			break;
	}


}

void DrawingScene::drawCustomizedItems_mousePress(QPointF p1, QPointF p2)
{
	qDebug()<<"P1 : "<<p1<<", P2 : "<<p2;
	Shape shape = drawing.shape;
	switch(shape)
	{
		case Line:
			qDebug()<<"Line..";
			curitem = new CLineItem(QLineF(p1, p2));
			break;
		case Rect:
			curitem = new QGraphicsRectItem(QRectF(p1, p2));
			break;
		case Ellipse:
			curitem = new QGraphicsEllipseItem(QRectF(p1, p2));
			break;
		case Arc:
			curitem = new QGraphicsEllipseItem(QRectF(p1, p2));
			break;
		default:
			curitem = new QGraphicsEllipseItem;
			break;
	}

	//curitem->setPen((QPen(Qt::blue, 2)));

	addItem(curitem);
}



void DrawingScene::drawCustomizedItems_mouseRelease()
{
	Shape shape = drawing.shape;

	switch(shape)
	{
		case Line:
		{
			qDebug()<<"Line..";
			CLineItem * line = dynamic_cast<CLineItem *> (curitem);
			if(line == 0){
				qDebug()<<"line cannot be converted..";
			}else{
				qDebug()<<"converting is success..";
			}
			//QGraphicsLineItem * line = static_cast<QGraphicsLineItem *> (curitem);
			QList<QGraphicsItem *> startItems = items(line->line().p1());
			if (startItems.count() && startItems.first() == line)
				startItems.removeFirst();
			QList<QGraphicsItem *> endItems = items(line->line().p2());
			if (endItems.count() && endItems.first() == line)
				endItems.removeFirst();
			addItem(line);
			line->setFlag(QGraphicsItem::ItemIsMovable, true);
			line->setInitLine();
			//line->getLine();
			//static_cast<CLineItem*>(line)->getLine();

			//test
/*			for(int i = 0 ; i < items().size() ; i++){
				QGraphicsItem * item = items().at(i);
				qDebug()<<"type : "<<item->type();
			}*/


			findItems();
			break;
		}
		case Rect:
		{
			QGraphicsRectItem * rect = static_cast<QGraphicsRectItem *> (curitem);
			QList<QGraphicsItem *> startItems = items(rect->rect().topLeft());
			if (startItems.count() && startItems.first() == rect)
				startItems.removeFirst();
			QList<QGraphicsItem *> endItems = items(rect->rect().bottomRight());
			if (endItems.count() && endItems.first() == rect)
				endItems.removeFirst();
			rect->setFlag(QGraphicsItem::ItemIsMovable, true);
			addItem(rect);
			findItems();
			break;
		}
		case Ellipse:
		{
			QGraphicsEllipseItem * rect = static_cast<QGraphicsEllipseItem *> (curitem);
			QList<QGraphicsItem *> startItems = items(rect->rect().topLeft());
			if (startItems.count() && startItems.first() == rect)
				startItems.removeFirst();
			QList<QGraphicsItem *> endItems = items(rect->rect().bottomRight());
			if (endItems.count() && endItems.first() == rect)
				endItems.removeFirst();
			rect->setFlag(QGraphicsItem::ItemIsMovable, true);
			addItem(rect);
			findItems();
			break;
		}
		case Arc:
		{
			QGraphicsEllipseItem * arc = static_cast<QGraphicsEllipseItem *>(curitem);
			QList<QGraphicsItem *> startItems = items(arc->rect().topLeft());
			if (startItems.count() && startItems.first() == arc)
				startItems.removeFirst();
			QList<QGraphicsItem *> endItems = items(arc->rect().bottomRight());
			if (endItems.count() && endItems.first() == arc)
				endItems.removeFirst();
			arc->setFlag(QGraphicsItem::ItemIsMovable, true);
			addItem(arc);
			findItems();
			break;
		}
		default:
			curitem = new QGraphicsEllipseItem;
			break;
	}

	curitem = 0;
	drawingMode = false;

}

//angle
void DrawingScene::setAngle(int angle)
{
	//qDebug()<<"[DrawingScene] setAngle is called..<<sceneRect : "<<sceneRect();

	if(drMode == Initial){
		drMode = ReDrawing;
	}
	this->angle = angle;


	if(drMode == ReDrawing){
		//rectItemGroup = drawingMng->getRectItemGroup();
		//사용자 오브젝트를 리드로잉 한다..
		//qDebug()<<"[DrawingScene] reDrawing is called..";
		QList<QGraphicsItem *> items_list = items();
		for(int i = 0 ; i < items_list.size() ; i++){
			QGraphicsItem * item = items_list[i];
			if(item->type() == 3 || item->type() == 6 || item->type() == 4 || item->type() == 65537 || item->type() == 65540){
				if(item->type() == 65540){
					qDebug()<<"DrawMpp Item..";
					MppItem * mppItem = dynamic_cast<MppItem *>(item);
					if(mppItem){
						mppItem->setStrMpp(LatLonConvert::getInstance().wonjum());
					}
				}
				item->update();
			}else{
				removeItem(item);
			}
		}
	}

	openNewMap = true;




//	this->clearItems();
	//drawMpp();
	this->drawMapInfo();
	//qDebug()<<"[DrawingScene] setAngle is close..";
}

/*
 * 텍스트 아이템을 추가한다..
 */

void DrawingScene::addTextItem(QGraphicsItem * txtItem)
{
	qDebug()<<"[DrawingScene] addTextItem is called..";
	addItem(txtItem);
}

/*
 * 뷰로부터 받은 마우스 포인트
 */

void DrawingScene::movedfromView(const QPointF point)
{
	qDebug()<<"[DrawingScene] movedFromView is called..";
	/*if(drawingMode == true && curitem != 0){
			//this->drawCustomizedItems_mouseMove(eve->scenePos());
			//DrawingMng::getInstance().drawItems(drawing, eve->scenePos(), curitem);
			drawingMng->drawItems(drawing, eve->scenePos(), curitem);
		}

		QPointF tmpPos = eve->scenePos();
		QString txtpos = "X : ";
		txtpos.append(QString::number(tmpPos.x()));
		txtpos.append(", Y : ");
		txtpos.append(QString::number(tmpPos.y()));

		double x = tmpPos.x();
		double y = tmpPos.y();
		double lon = 0;
		double lat = 0;
	//	if(angle != 0)
			WGS84_TM::getInstance().XYConvert(x, y, &lon, &lat, angle);

		//qDebug()<<"lon : "<<lon<<", lat : "<<lat;

		QString txtlatlon = QString().setNum(lat, 'f', 4);
		txtlatlon.append('/');
		txtlatlon.append(QString().setNum(lon, 'f', 4));

		//qDebug()<<"Pos : "<<txtpos;

		emitPos(txtpos, txtlatlon);
		//displayToCoordinate(tmpPos, 1);
		if(eve->buttons() & Qt::LeftButton){
			cPoint = eve->scenePos();
			//initLine();
		}
		QGraphicsScene::mouseMoveEvent(eve);*/
}

void DrawingScene::setScale(int value)
{
	qDebug()<<"[DrawingScene] setScale is called..";
	scale = value;


	this->clear();



	this->drawMapInfo();
}


void DrawingScene::setLatLonCovert(LatLonConvert * vp)
{
	qDebug()<<"setlatLonConvert..";
	/*if(latlonItem != 0)
	latlonItem->setScreenConvertClass(vp);*/
	//this->vp = vp;
}

void DrawingScene::updateLatLon()
{
	//위경도 그리드를 그린다.
	qDebug()<<"updateLatLon..";
	if(latlonItem != 0){
		this->removeItem(latlonItem);
		delete latlonItem;
		latlonItem = 0;
		//atlonItem->update();
		this->displayLatLon();
	}else{
		this->displayLatLon();
	}
}

/*
 * MPP 정보를 그린다.
 */

void DrawingScene::drawMpp(QPointF point)
{
	//qDebug()<<"=================drawMpp start ================= mppItem : "<<mppItem;
	QString strMpp = QString::number(LatLonConvert::getInstance().mpp(), 'f', 2);
	strMpp.prepend("mpp : ");

	//qDebug()<<"strMpp : "<<strMpp;

	QPointF wonjum = LatLonConvert::getInstance().wonjum();
	QString lat = "N";
	lat.append(QString::number((int)wonjum.x(), 10));
	QString lon = "E";
	lon.append(QString::number((int)wonjum.y(), 10));

	strMpp.prepend(lon);
	strMpp.prepend(lat);
	strMpp.prepend("wonjum : ");
	//strMpp.prepend("wonjum : N35 E125 \n");
	point.setY(point.y() + 20);
	point.setX(point.x() + 20);

	if(mppItem != 0){
		removeItem(mppItem);
		delete mppItem;
		mppItem = 0;
	}

	mppItem = new MppItem(point, strMpp);
	addItem(mppItem);
	//mppItem->setFlag(QGraphicsItem::ItemIgnoresTransformations);
	mppItem->update();
	//qDebug()<<"=================drawMpp End =================";
}

/*
 * 특정 아이템들을 제외하고 클리어 한다..
 */
void DrawingScene::clearItems()
{
	qDebug()<<"====clearItems====";
	MppItem *tmp = new MppItem;

	if(latlonItem != 0){
		removeItem(latlonItem);
		latlonItem = 0;
	}
	if(mppItem != 0){
		memcpy(tmp, mppItem, sizeof(MppItem));
		removeItem(mppItem);
		//delete mppItem;
		mppItem = 0;


	}


	clear();

	//addRect(0, 0, 600, 600, QPen(), QBrush(QColor(Qt::green)));
/*	for(int i = 0 ; i < drawingItem_list.size() ; i++){
		CLineItem * tmpItem = static_cast<CLineItem*>(drawingItem_list.at(i));
		//qDebug()<<"Item : "<<tmpItem->;

		addItem(tmpItem);
	}*/
	this->addItem(tmp);
	drawUserComponents();
	mppItem = tmp;
	qDebug()<<"====clearItems close====";
}

// Scene에 있는 모든 아이템들을 검출한다..
void DrawingScene::findItems()
{

	qDebug()<<"==[DrawingScene - findItems] called..";
	QList<QGraphicsItem *> item_list = items();
	//QList<QGraphicsItem *> item_list = items(pPoint, Qt::ContainsItemBoundingRect, Qt::AscendingOrder);
	line_list.clear();
	rect_list.clear();
	ellipse_list.clear();
	polygonitem_list.clear();
	polylineitem_list.clear();



	for(int i = 0 ; i < item_list.size() ; i++){
		QGraphicsItem * item = item_list.at(i);

		qDebug()<<"item = : "<<item->type();
		if(item->type() == 6){
			//line
			findLines(item);
		}else if(item->type() == 3){
			//rect
			findRects(item);
		}else if(item->type() == 4){
			findEllipses(item);
		}else if(item->type() == 65537){
			findPolygons(item);
		}
	}
}

//사용자가 그린 Line을 검색하고, 벡터에 저장함

void DrawingScene::findLines(QGraphicsItem * item)
{
	qDebug()<<"[DrawingScene - findLines] called..";
	CLineItem * tmpcline = dynamic_cast<CLineItem * >(item);
	if(tmpcline == 0){
		qDebug()<<"casting fail..";
	}else{
		qDebug()<<"casting success..";
	}

	QPointF latlon_1 = LatLonConvert::getInstance().screenToDecimal(tmpcline->line().p1().toPoint());
	QPointF latlon_2 = LatLonConvert::getInstance().screenToDecimal(tmpcline->line().p2().toPoint());

	QLineF line(latlon_1, latlon_2);


	line_list.append(line);
}


void DrawingScene::findRects(QGraphicsItem * item)
{
	qDebug()<<"[DrawingScene - findRects] called..";
	QGraphicsRectItem * tmpcline = dynamic_cast<QGraphicsRectItem * >(item);
	if(tmpcline == 0){
		qDebug()<<"casting fail..";
	}else{
		qDebug()<<"casting success..";
	}

	//좌표를 위겨도 좌표로 변환한다.
	QPointF latlon_1 = LatLonConvert::getInstance().screenToDecimal(tmpcline->rect().topLeft().toPoint());
	QPointF latlon_2 = LatLonConvert::getInstance().screenToDecimal(tmpcline->rect().bottomRight().toPoint());

	QRectF rect(latlon_1, latlon_2);

	rect_list.append(rect);
}


void DrawingScene::findEllipses(QGraphicsItem * item)
{

	QGraphicsEllipseItem * tmpcline = dynamic_cast<QGraphicsEllipseItem * >(item);
	if(tmpcline == 0){
		qDebug()<<"casting fail..";
	}else{
		qDebug()<<"casting success..";
	}

	//좌표를 위겨도 좌표로 변환한다.
	QPointF latlon_1 = LatLonConvert::getInstance().screenToDecimal(tmpcline->rect().topLeft().toPoint());
	QPointF latlon_2 = LatLonConvert::getInstance().screenToDecimal(tmpcline->rect().bottomRight().toPoint());


	QRectF rect(latlon_1, latlon_2);

	ellipse_list.append(rect);
}

void DrawingScene::findPolygons(QGraphicsItem * item)
{

	CPolyGonItem * polygon = dynamic_cast<CPolyGonItem * >(item);
	if(polygon == 0){
		qDebug()<<"casting fail..";
	}else{
		qDebug()<<"casting success..";
	}

	//좌표를 위겨도 좌표로 변환한다.
	QPolygonF polygon_list = polygon->getPolygonNR();

	for(int i = 0 ; i < polygon_list.size() ; i++){
		QPoint point = polygon_list.at(i).toPoint();
		QPointF newPoint = LatLonConvert::getInstance().screenToDecimal(point);
		polygon_list.replace(i, newPoint);
	}

	polygon->setPolygon(polygon_list);

	CPolyGonItem * newPolygon = new CPolyGonItem;
	memcpy(newPolygon, polygon, sizeof(CPolyGonItem));
	//newPolygon->setPolygon(polygon_list);

	qDebug()<<"newPolygon initPoint : "<<newPolygon->getInitPoint()<<", old Initpoint : "<<polygon->getInitPoint();
	qDebug()<<"newPolygon list : "<<newPolygon->getPolygonNR();
	//test
	polygonitem_list.append(newPolygon);

//	qDebug()<<"PolygonList : "<<polygonitem_list.at(0)->getPolygon();
}


/*
 * 사용자 정의 오브젝트를 mpp에 따라서 재 드로잉 한다. 즉, 휠 이벤트 발생시 재드로잉
 */

void DrawingScene::drawUserComponents()
{
	qDebug()<<"[DrawingScene - drawuserComponents] called..";

	//qDebug()<<"PolygonList : "<<polygonitem_list.at(0)->getPolygonNR();

	for(int i = 0 ; i < line_list.size() ; i++){
		QLineF line = line_list.at(i);
		QPointF p1 = LatLonConvert::getInstance().latlonToScreen2(line.p1());
		QPointF p2 = LatLonConvert::getInstance().latlonToScreen2(line.p2());
		line.setP1(p1);
		line.setP2(p2);

		qDebug()<<"lien : "<<line;
		CLineItem * cline = new CLineItem(line);
		cline->setFlag(QGraphicsItem::ItemIsMovable);
		/*cline->setInitLine();
		cline->genLatLonPos();*/

		addItem(cline);
	}

	for(int i = 0 ; i < rect_list.size() ; i++){
		QRectF rect = rect_list.at(i);

		QPointF p1 = LatLonConvert::getInstance().latlonToScreen2(rect.topLeft());
		QPointF p2 = LatLonConvert::getInstance().latlonToScreen2(rect.bottomRight());

		QGraphicsRectItem * rectItem = new QGraphicsRectItem(QRectF(p1, p2));
		rectItem->setFlag(QGraphicsItem::ItemIsMovable);
		addItem(rectItem);
	}

	for(int i = 0 ; i < ellipse_list.size() ; i++){
		QRectF rect = ellipse_list.at(i);

		QPointF p1 = LatLonConvert::getInstance().latlonToScreen2(rect.topLeft());
		QPointF p2 = LatLonConvert::getInstance().latlonToScreen2(rect.bottomRight());

		QGraphicsEllipseItem * rectItem = new QGraphicsEllipseItem(QRectF(p1, p2));
		rectItem->setFlag(QGraphicsItem::ItemIsMovable);
		addItem(rectItem);
	}

	for(int i = 0 ; i <  polygonitem_list.size() ; i++){
		//qDebug()<<"count : "<<polygonitem_list.size();
		CPolyGonItem * polygon_item = polygonitem_list.at(i);

		qDebug()<<"polygon address : "<<polygon_item;
		//QPolygonF polygonF = polygon_item->getPolygonNR();

		qDebug()<<"initpoint : "<<polygon_item->getInitPoint()<<", polygon : "<<polygon_item->getPolygonNR();


		/*for(int j = 0 ;  j < polygonF.size() ; j++){
			qDebug()<<"polygon size : "<<polygonF.size();
			QPointF point = polygonF.at(j);
			QPointF newPoint = LatLonConvert::getInstance().latlonToScreen2(point);
			polygonF.replace(j, newPoint);
		}

		polygon_item->setPolygon(polygonF);

		addItem(polygon_item);
		polygon_item->update();*/
	}

	qDebug()<<"[DrawingScene - drawuserComponents] close..";
}

/*
 * 화면에 클릭 했을때 사용자가 그린 도형이 있는지 판단한다..
 */
bool DrawingScene::checkUserItems(QPointF point)
{

	qDebug()<<"[DrawingScene - checkUserItem] called.. point : "<<point;
	QList<QGraphicsItem *> item_list = items(point);

	//QPointF tmp(point.x() )
	//QList<QGraphicsItem *> item_list = items(point, Qt::ContainsItemShape, Qt::AscendingOrder);

	for(int i = 0 ; i < item_list.size() ; i++){
		QGraphicsItem * item = item_list.at(i);

		qDebug()<<"[DrawingScene - checkUserItems] item type : "<<item->type();
		if(item->type() == 3 || item->type() == 4 || item->type() == 6 ||
				item->type() == 65537 || item->type() == 65538 || item->type() == 65539)
		{
			qDebug()<<"detected..";
			return false;
		}
	}

	return true;
}

/**
 * Manual Drawing 의 Done 클릭시 호출되는 함수이다..
 * DrawiingMode (dm)의 값에 따라서 다르게 액션 (Initial -> Object table insert, ReDrawing -> Clear)
 *
 */

void DrawingScene::runManualDrawing(QVector<COORDINATE> coord_list, DrawingMode dm, QGraphicsItem * item)
{
	qDebug()<<"[DrawingScene] - runManualDrawing..";

	//VIA가 G인 경우에만 해당..
	//1. LatLon Point를 파싱하여, XY좌표로 변환한다.


	if(dm == ReDrawing)
	{
		qDebug()<<"DrawingMode is 'ReDrawing'.. Shape : "<<coord_list.at(0).shape;
		if(coord_list.at(0).shape == 0){
			coord_list[0].shape = Polyline;
		}
		this->removeItem(item);
	}

	QVector<QPointF> point_list;
	UserObject object;			//object table에 등록시키기 위한 변수
	Shape shape = coord_list.at(0).shape;

	if(shape == Polygon || shape == Polyline){

		QPainterPath path;

		for(int i = 0 ; i < coord_list.size() ;i++){
			COORDINATE cn = coord_list.at(i);
			QPointF point;
			point = getXYManualPointList(cn);
			//첫번째 좌표에 대해서는 포인트로 이동한다.
			if(i == 0){
				//XY 좌표로 변환한다..
				path.moveTo(point);
			}else{
				if(cn.Via == GREATECIRCLE){
				//직선
					path.lineTo(point);
				}else if(cn.Via == COUNTERCLOCKWISEARC){
					QPointF centerPoint = this->getXYManualPointList(cn.centerLat, cn.centerLon);
					QPointF nextPoint;				//해당 지점의 다음 지점 좌표
					//만약 다음 지점이 존재하면, nextPoint를 다음 지점으로 설정한다. 만약 다음 지점이 존재 하지 않으면
					//첫번째 포인트의 좌표를 다음 지점으로 설정한다.
					if(i == coord_list.size()){
						nextPoint = getXYManualPointList(coord_list.at(0));
					}else{
						nextPoint = getXYManualPointList(coord_list.at(i+1));
					}

					path.lineTo(point);
					QRectF rectF = this->getCircleRect(point, centerPoint);		//정사각형 생성
					qDebug()<<"rect : "<<rectF<<", point : "<<point<<", centerPoint : "<<centerPoint;

					double startAngle = getAngle(centerPoint, point);
					double endAngle = getAngle(centerPoint, nextPoint);

					double roundAngle = fmod((720 + endAngle - startAngle), 360);
					path.arcTo(rectF, startAngle, roundAngle);
					//path.arcTo(rect, startAngle, (-1)*(360-roundAngle));		// Right wise
				}
				else if(cn.Via == CLOCKWISEARC)
				{
					QPointF centerPoint = this->getXYManualPointList(cn.centerLat, cn.centerLon);
					QPointF nextPoint;				//해당 지점의 다음 지점 좌표
					//만약 다음 지점이 존재하면, nextPoint를 다음 지점으로 설정한다. 만약 다음 지점이 존재 하지 않으면
					//첫번째 포인트의 좌표를 다음 지점으로 설정한다.
					if(i == coord_list.size()){
						nextPoint = getXYManualPointList(coord_list.at(0));
					}else{
						nextPoint = getXYManualPointList(coord_list.at(i+1));
					}

					path.lineTo(point);
					QRectF rectF = this->getCircleRect(point, centerPoint);		//정사각형 생성
					qDebug()<<"rect : "<<rectF<<", point : "<<point<<", centerPoint : "<<centerPoint;

					double startAngle = getAngle(centerPoint, point);
					double endAngle = getAngle(centerPoint, nextPoint);

					double roundAngle = fmod((720 + endAngle - startAngle), 360);
					//path.arcTo(rectF, startAngle, roundAngle);
					path.arcTo(rectF, startAngle, (-1)*(360-roundAngle));		// Right wise
				}
			}
		}
		if(shape == Polygon)
			path.closeSubpath();

		QGraphicsPathItem * tmpitem = new QGraphicsPathItem(path);
		addItem(tmpitem);

		//UserObject..
		if(dm == Initial){
			object.chkObject = true;
			if(shape == Polygon){
				object.obj_name ="Test_Polygon";
				object.shape = ManualPolygon;
			}else {
				object.obj_name = "Test_Polyline";
				object.shape = ManualPolyline;
			}
			object.object = static_cast<void *>(tmpitem);
			drawingMng->getUserObjectList().append(object);
			this->runUserObject(drawingMng->getUserObjectList());

		}
	}/*else if(coord_list.at(0).shape == Polyline)
	{
		//폴리라인 그리기 - LatLonMng에서 LatLon 타입으로 리턴한 것을 이용하여 그린다.

		point_list = this->getXYManualPointList(coord_list);

		QVector<QPointF> polyline_list;

		for(int j = 0 ; j < point_list.size() ; j++){
			QPointF start = point_list.at(j);
			QPointF last;
			if(j < point_list.size()-1){
				last = point_list.at(j+1);
			}else{
				last = start;
			}
			qreal x =   start.x();
			qreal y =   start.y();
			qreal x1 =  last.x();
			qreal y1 =  last.y();

			//added
			QPointF p1(x, y);
			QPointF p2(x1, y1);

			polyline_list.append(p1);
			polyline_list.append(p2);

		}

		QGraphicsItem * tmpItem = drawingMng->drawMapInfoPolyline(polyline_list, QPen(Qt::white));

		LineItem * lineItem = dynamic_cast<LineItem *>(tmpItem);
		if(lineItem == 0)
		{
			qDebug()<<"casting is failed..";
		}else{
			qDebug()<<"casting is success..";
		}

//		LineItem * lineItem = new LineItem(POLYLINE);
//		lineItem->setPolyLineList(polyline_list);
//		lineItem->setPen(QPen(Qt::white));
		//lineItem->setPen(latlonmng.layer_line_color);
		addItem(lineItem);
		lineItem->update();

		//UserObject..
		if(dm == Initial){
			object.chkObject = true;
			object.obj_name ="Test_Polyline";
			object.object = static_cast<void *>(lineItem);
			object.shape = ManualPolyline;

			drawingMng->getUserObjectList().append(object);

			this->runUserObject(drawingMng->getUserObjectList());

		}
	}*/
	else if(coord_list.at(0).shape == Circle)
	{
		//Circle..서클은 단 하나의 좌표점만을 가져온다. 0번째 인덱스 값..
		point_list = this->getXYManualPointList(coord_list);
		//QGraphicsItem * tmpItem = drawingMng->drawMapInfoPolyline(point_list, coord_list.at(0).dist, coord_list.at(0).bearing);
		QGraphicsItem * tmpItem = drawingMng->drawMapInfoCircle(point_list.at(0), coord_list.at(0).dist, coord_list.at(0).bearing);
		tmpItem->setFlags(QGraphicsItem::ItemIsMovable);
		addItem(tmpItem);


		//UserObject..
		if(dm == Initial){
			object.chkObject = true;
			object.obj_name ="Test_Circle";
			object.object = static_cast<void *>(tmpItem);
			object.shape = Circle;

			drawingMng->getUserObjectList().append(object);

			this->runUserObject(drawingMng->getUserObjectList());

		}
	}

}

/**
 * XY 좌표로 변환된 메뉴얼 포인트 리스트를 반환한다..
 */
QVector<QPointF> DrawingScene::getXYManualPointList(QVector<COORDINATE> coord_list)
{
	QVector<QPointF> point_list;

	bool ok;

	for(int i = 0 ; i < coord_list.size() ; i++){
		COORDINATE cn = coord_list.at(i);

		QPointF newpoint = getXYManualPointList(cn);

		point_list.append(newpoint);
	}

	return point_list;
}

QPointF DrawingScene::getXYManualPointList(COORDINATE cn)
{
//	double x;
//	double y;


	QPointF point;

	if(cn.shape == Circle){

		point = this->getXYManualPointList(cn.centerLat, cn.centerLon);
//		x = convertStringLat(cn.centerLat);
//		y = convertStringLon(cn.centerLon);
	}else{
		point = this->getXYManualPointList(cn.Lat, cn.Lon);
//		x = convertStringLat(cn.Lat);
//		y = convertStringLon(cn.Lon);
	}

	/*cn.Lat.replace(".", "");
	cn.Lat.replace(":", "");
	cn.Lat.remove(0, 1);
	cn.Lat.insert(2, ".");
	cn.Lon.replace(".", "");
	cn.Lon.replace(":", "");
	cn.Lon.remove(0, 1);
	cn.Lon.insert(3, ".");
	qDebug()<<"Shape "<<cn.shape<<", Idx : "<<cn.idx<<", lat : "<<cn.Lat<<", lon : "<<cn.Lon;*/


//	point.setX(x);
//	point.setY(y);

	//QPointF newpoint = LatLonConvert::getInstance().latlonToScreen2(point);

	//qDebug()<<"point : "<<point<<", newPoint : "<<newpoint;

	return point;

}

/**
 * Lat, Lon을 이용하여 ,X, Y 좌표로 변환한다.
 */
QPointF DrawingScene::getXYManualPointList(QString lat, QString lon)
{

	QPointF point(convertStringLat(lat), convertStringLon(lon));
	QPointF newpoint = LatLonConvert::getInstance().latlonToScreen2(point);

	qDebug()<<"point : "<<point<<", newPoint : "<<newpoint;
	return newpoint;
}
/**
 * 스트링 형식의 위경도를 숫자로변환한다..
 */

double DrawingScene::convertStringLat(QString lat)
{
	double dLat;
	bool ok;

	lat.replace(".", "");
	lat.replace(":", "");
	lat.remove(0, 1);
	lat.insert(2, ".");

	dLat = lat.toDouble(&ok);

	return dLat;
}
/**
 * 스트링 형식의 위경도를 숫자로변환한다..
 */
double DrawingScene::convertStringLon(QString lon)
{
	double dLon;
	bool ok;

	lon.replace(".", "");
	lon.replace(":", "");
	lon.remove(0, 1);
	lon.insert(3, ".");

	dLon = lon.toDouble(&ok);

	return dLon;
}

/**
 * 드로잉 위젯에서 슬라이더를 변경하는 경우 발생되는 슬롯함수
 */

void DrawingScene::runSlderReleased(int value)
{
	//qDebug()<<"[DrawingScene-runSlderReleased] called..";

	double mpp = value;

	LatLonConvert::getInstance().setMeterPerPixel(mpp);

	//qDebug()<<"Mpp : "<<LatLonConvert::getInstance().mpp();
	setAngle(0);
	emit emitDrawMpp();
}

/**
 * p2가 중심일때, p1과의 반지름을 구하여 정사각형 Rect를 반환한다..
 */
QRectF DrawingScene::getCircleRect(QPointF p1, QPointF p2)
{
	double dx = p2.x() - p1.x();
	double dy = p2.y() - p1.y();

	dy = 0 - dy;
	//double r = sqrt((p2.x() - p1.x()) * (p2.x() - p1.x()) + (p2.y() - p1.y()) * (p2.y() - p1.y()));

	double r= sqrt(dx*dx + dy*dy);

	qDebug()<<"r : "<<r;

	return getCircleRect(p2, r);

}

QRectF DrawingScene::getCircleRect(QPointF centerPoint, double r)
{
	QPointF topLeft;
	topLeft = QPointF((centerPoint.x() - r), (centerPoint.y() -r));

	QPointF bottomRight(QPointF((centerPoint.x() + r), (centerPoint.y() +r)));

	return QRectF(topLeft, bottomRight);
}

/*
 *  두 지점을 이용하여 각도를 구한다.
 */
double DrawingScene::getAngle(QPointF p1, QPointF p2)
{
	double dx = p2.x() - p1.x();
	double dy = p2.y() - p1.y();

	dy = 0 - dy;

	return getAngle(dx, dy);
}
/*
 * 두 거리를 이용하여 각도를 구한다.
 */
double DrawingScene::getAngle(double dx, double dy){

	if(dx == 0) dx = 0.00000001;

	double angle = atan(dy/dx) * rad2deg;

	if(angle < 0) angle += 180;

	return angle;
}


/*
 * DrawingMng 객체에서 유저 오브젝트의 드로잉이 완료 되었을때 호출된다.
 * 해당 파라미터는 DrawingWidget으로 넘어간다.
 * call flows
 * - DrawingMng -> DrawingScene -> Window04 -> MapWindow -> DrawingWidget
 */

void DrawingScene::runUserObject(QVector<UserObject>  object_list)
{

	qDebug()<<"[DrawingScene-runUserObject] called..";

	emit emitUserObject(object_list);
}

/*
 * Item을 제거한다.
 */

void DrawingScene::runRemoveItem(QGraphicsItem * item, int idx)
{
	qDebug()<<"[DrawignScene-runRemoveItem] caled..idx"<<idx;
	removeItem(item);
	drawingMng->getUserObjectList().remove(idx);

}



/*
 * UserMap을 다시 현시 한다.
 */

void DrawingScene::drawUserMapInfo()
{

	qDebug()<<"=======================================";
	qDebug()<<"[DrawingScene] drawUserMapInfo is called..";

	/*
	 * 여기서 latlonmng_list에 모든 맵 정보가 저장되어 있다. 만약 해당 리스트의 값이 0이면 그릴수 있는 맵이 존재 하지 않는다.
	 * Angle 값이 주어졌을 경우 latlonmng_list를 새롭게 받아 와야 한다.
	 */

	drawingMng->reDrawUserObject();




	/*for(int i = 0 ; i < latlonmng_list.size() ; i++){

		LatLonMng latlonmng = latlonmng_list.at(i);
		//Polygon Item
		if(latlonmng.isEnable == true){
			//폴리곤 타입 그리기 - LatLonMng에 관리하는 QPointF 타입의 좌표를 가져온다.
			QGraphicsItem * qgitem = drawingMng->drawMapInfo(latlonmng);

			LineItem * item = dynamic_cast<LineItem *>(qgitem);
			if(item == 0){
				qDebug()<<"Casting is failed..";
			}else{
				qDebug()<<"Casting is success..";
			}
			//qDebug()<<"item : "<<item;
			addItem(item);
			item->update();

		}

	}*/



	qDebug()<<"===========end==========";
}


void DrawingScene::runTrack()
{
	Airplane * ap1 = new Airplane("a1", 50, 5, 100, 30000, "bogus1", 200, 200, 200, 10);
	//Airplane * ap2 = new Airplane("a2", 50, 5, 100, 10000, "bogus2", 200, 300, 250, 10);

	connect(ap1, SIGNAL(emitTrailComponents(TrailComponent **)), this, SLOT(updateTrack(TrailComponent **)));

	ap1->emitTrailComponent();
	ap1->SetClearAlt(1000);
	ap1->SetClearHeading(160);
	//ap1->SetClearSpeed(75);


	this->addItem(ap1);
	this->addItem(ap1->apLabel);
	//this->addItem(ap2);
	//this->addItem(ap2->apLabel);

	planeList.append(ap1);
	//planeList.append(ap2);

	//updateTrack();
}

void DrawingScene::updateTrack(TrailComponent ** trail_list)
{
	/*for(int i = 0 ; i < planeList.size() ; i++){
		Airplane * ap = planeList.at(i);
		ap->PlaneProcess();
	}*/

	qDebug()<<"UpdateTrack is called.";

	addItem(trail_list[0]);
	addItem(trail_list[1]);
	addItem(trail_list[2]);
	addItem(trail_list[3]);
}
