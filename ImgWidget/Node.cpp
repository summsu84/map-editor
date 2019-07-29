/*
 * Node.cpp
 *
 *  Created on: 2013. 1. 21.
 *      Author: jiwon
 */

#include "Node.h"
#include <QDebug>
Node::Node(qreal x, qreal y, qreal width, qreal height, int type, QGraphicsItem * parent)
:QGraphicsEllipseItem(x, y, width, height, parent)
{
	// TODO Auto-generated constructor stub
	info = 0;
	menu = new QMenu;
	menu->addAction("test1");
	node_nm = "";
	setFlag(QGraphicsItem::ItemIsMovable);
	setFlag(QGraphicsItem::ItemIsFocusable);
	node_type = BlueNode;
	this->type = type;
	if(type == 1){
		setBrush(Qt::blue);
	}else if(type == 0){
		setBrush(Qt::red);
	}

	updateTimer = new QTimer();
	updateTimer->setInterval(2000);
	QObject::connect(updateTimer, SIGNAL(timeout()), this, SLOT(move()));
	//if(this->type == 0)
		updateTimer->start();

	wp_type = WP1;
}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

void Node::move()
{
	//qDebug()<<"Move is called..";
	qreal xPos = pos().x();
	qreal yPos = pos().y();
	//qDebug()<<"SceneBounding Rect : "<<sceneBoundingRect()<<", X : "<<QString().setNum(sceneBoundingRect().center().x())<<", Y : "<<QString().setNum(sceneBoundingRect().center().y());
	float fx, fy;

	if(count < 50){
		xPos -= 1.0;
		isLeft = true;
		isRight = false;
		isUp = false;
		isDown = false;
	}
	else if (count < 100 ){
		yPos += 1.0;
		isDown = true;
		isRight = false;
		isUp = false;
		isLeft = false;
	}
	else if (count < 150 )
	{
		xPos += 1.0;
		isRight = true;
		isLeft = false;
		isUp = false;
		isDown = false;
	}
	else if (count < 200 )
	{
		yPos -= 1.0;
		isUp = true;
		isRight = false;
		isLeft = false;
		isDown = false;
	}
	else if (count < 250 )
	{
		yPos += 1.0;
		xPos -= 1.0;
	}
	else if (count < 300 )
	{
		yPos -= 1.0;
		xPos += 1.0;
	}else{
		count = 0;
		return;
	}

	count+=1;
	fx = xPos;
	fy = yPos;
	setPos(fx, fy);
	//setChildPos(fx, fy);
	if(info != 0){
		node_x = sceneBoundingRect().center().x();
		node_y = sceneBoundingRect().center().y();
		info->setPos(node_x, node_y);
	}

	node_x = sceneBoundingRect().center().x();
	node_y = sceneBoundingRect().center().y();
	qDebug()<<"X : "<<node_x<<", Y : "<<node_y;
	QGraphicsItem * temp = goWP(node_x, node_y + 40, node_x - 30, node_y + 40);
	emitEnemyWP(temp);
	//emitFindNode();


}

void Node::setChildPos(qreal x, qreal y)
{
	x = 0;
	y = 0;
	//자식 노드의 위치를 변경 시킨다..
	QGraphicsEllipseItem * item = child_node_list[0];
	if(isLeft && leftCnt == 0){
		qDebug()<<"X Pos : "<<QString().setNum(x)<<", Y Pos : "<<QString().setNum(y);
		item->setPos(x+16, y);
		leftCnt++;
	}
	if(isRight && rightCnt == 0){
		qDebug()<<"X Pos : "<<QString().setNum(x)<<", Y Pos : "<<QString().setNum(y);
		item->setPos(x-16, y);
		rightCnt++;
	}
	if(isUp && upCnt == 0){
		qDebug()<<"X Pos : "<<QString().setNum(x)<<", Y Pos : "<<QString().setNum(y);
		item->setPos(x, y + 16);
		upCnt++;
	}
	if(isDown && downCnt == 0){
		qDebug()<<"X Pos : "<<QString().setNum(x)<<", Y Pos : "<<QString().setNum(y);
		item->setPos(x, y - 16);
		downCnt++;
	}
}

//자식 노드를 그린다.
QVector<QGraphicsEllipseItem *> Node::drawingChild()
{
	qDebug()<<"DrawingChildNode is called.";
	/*for(int i = 0 ; i < CHILD_MAX ; i++){
		qreal x = sceneBoundingRect().center().x();
		qreal y = sceneBoundingRect().center().y();
		//qDebug()<<"X : "<<QString().setNum(x)<<", Y : "<<QString().setNum(y);
		//QGraphicsEllipseItem * child = new QGraphicsEllipseItem(x+40+(i * 2), y+40+(i * 2), (10/i), (10/i), this);
		QGraphicsEllipseItem * child = new QGraphicsEllipseItem(x+40+(i*2), y+40+(i*2), 10, 10, this);
		qreal xPos = pos().x();
		qreal yPos = pos().y();
		setPos(xPos, yPos);
		child_node_list.append(child);
	}*/

	qreal x = sceneBoundingRect().center().x();
	qreal y = sceneBoundingRect().center().y();
	//qDebug()<<"X : "<<QString().setNum(x)<<", Y : "<<QString().setNum(y);
	//QGraphicsEllipseItem * child = new QGraphicsEllipseItem(x+40+(i * 2), y+40+(i * 2), (10/i), (10/i), this);
	QGraphicsEllipseItem * child = new QGraphicsEllipseItem(x, y, 10, 10, this);
	child_node_list.append(child);

	qDebug()<<"DrawingChildNode is closed..";

	return child_node_list;
}

/**
 * KeyPressEvent
 */

/*void Node::keyPressEvent(QKeyEvent *event)
{
	qDebug()<<"[Node] KeyPressEvent is called..";
	//QGraphicsItem::keyPressEvent(event);
}*/


void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	qDebug()<<"[Node] mouse press event is called..";
	drawDesc();
	if (event->buttons() & Qt::LeftButton)
	{
		//menu->popup(event->pos());
		qDebug()<<"Item : "<<node_nm<<" is clicked..";
		//event->
	}

	//menu->popup(QPoint(500,500));
	QGraphicsItem::mousePressEvent(event);



}
/*
void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}*/

void Node::drawDesc()
{
	qDebug()<<"[Node]drawDesc is called..";
	qDebug()<<"name : "<<node_nm;
}


void Node::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
 {
     QMenu menu;
     QAction *removeAction = menu.addAction("Remove");
     connect(removeAction, SIGNAL(triggered()), this, SLOT(removeNode()));
     QAction *markAction = menu.addAction("Info");
     connect(markAction, SIGNAL(triggered()), this, SLOT(infoNode()));

     //Weapon 선택
     wp_1 = menu.addAction("WP1");
     wp_1->setCheckable(true);
	  wp_2 = menu.addAction("WP2");
	  wp_3 = menu.addAction("WP3");

	  wp_2->setCheckable(true);
	  wp_3->setCheckable(true);

	  connect(wp_1, SIGNAL(triggered()), this, SLOT(changeWP()));
	  connect(wp_2, SIGNAL(triggered()), this, SLOT(changeWP()));
	  connect(wp_3, SIGNAL(triggered()), this, SLOT(changeWP()));

     QAction *selectedAction = menu.exec(event->screenPos());

 }

void Node::removeNode()
{
	qDebug()<<"remove Node...";
	emitRemoveNode(this);

}

void Node::callFindNode()
{
	emitFindNode();
}

void Node::infoNode()
{
	qDebug()<<"Information of Node is called..";
	node_x = sceneBoundingRect().center().x();
	node_y = sceneBoundingRect().center().y();
	info = new NodeInfo;
	info->setInfo(node_nm, node_x, node_y);
	if (info->exec()) {
		delete info;
		info = 0;
	}else {
		delete info;
		info = 0;
	}

}


QGraphicsItem * Node::goWP(qreal x, qreal y, qreal x1, qreal y1)
{
	if(wp_type == WP1){
		wp = new WP_1(x, y, x1, y1, type);
	}else if(wp_type == WP2){
		wp = new WP_2(x, y, x1, y1-10, type);
	}else if(wp_type == WP3)
	{
	}

	//connect(wp, SIGNAL(emitColDetection()), this, SLOT(callFindNode()));
	wp->attack();
	return wp;
}

void Node::changeWP()
{
	QAction * action = (QAction *)sender();
	//qDebug()<<"action name "<<action->text();
	QString actionName = action->text();
	qDebug()<<"ActionName : "<<actionName;
	if(actionName == "WP1"){
		qDebug()<<"WP1 is selected";
		//layer_level = LAYER_LEVEL_1;
		wp_1->setChecked(true);
		wp_2->setChecked(false);
		wp_3->setChecked(false);
		wp_type = WP1;
	}else if(actionName == "WP2"){
		qDebug()<<"WP2 is selected";
		wp_1->setChecked(false);
		wp_2->setChecked(true);
		wp_3->setChecked(false);
		wp_type = WP2;
	}else{
		qDebug()<<"WP3 is selected";
		wp_1->setChecked(false);
		wp_2->setChecked(false);
		wp_3->setChecked(true);
		wp_type=WP3;
	}
}


//History 영역을 관리한다..
