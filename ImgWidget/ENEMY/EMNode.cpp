/*
 * Node.cpp
 *
 *  Created on: 2013. 1. 21.
 *      Author: jiwon
 */

#include "EMNode.h"
#include <QDebug>
EMNode::EMNode(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent)
:QGraphicsEllipseItem(x, y, width, height, parent)
{
	// TODO Auto-generated constructor stub
	node_nm = "Enemy_Node";
	count = 0;
	node_type = BlueNode;
	setFlag(QGraphicsItem::ItemIsMovable);
	setFlag(QGraphicsItem::ItemIsFocusable);
	setBrush(Qt::red);
	updateTimer = new QTimer();
	updateTimer->setInterval(500);
	QObject::connect(updateTimer, SIGNAL(timeout()), this, SLOT(move()));
	updateTimer->start();

	weaponTimer = new QTimer();
	weaponTimer->setInterval(1000);
	connect(weaponTimer, SIGNAL(timeout()), this, SLOT(createWP()));
	weaponTimer->start();
	wp_type = WP1;
/*	mThread = new QThread;
	mThread->start();
	this->moveToThread(mThread);
	checkThread = true;*/
}

EMNode::~EMNode() {
	// TODO Auto-generated destructor stub
	mThread->exit(0);
	mThread->wait();
	delete mThread;
}

void EMNode::move()
{
	//qDebug()<<"Move is called..count : "<<count;
	qreal xPos = pos().x();
	qreal yPos = pos().y();
	//qDebug()<<"SceneBounding Rect : "<<sceneBoundingRect()<<", X : "<<QString().setNum(sceneBoundingRect().center().x())<<", Y : "<<QString().setNum(sceneBoundingRect().center().y());
	float fx, fy;

	if(count < 50){
		xPos -= 10.0;
		isLeft = true;
		isRight = false;
		isUp = false;
		isDown = false;
	}
	else if (count < 100 ){
		yPos += 10.0;
		isDown = true;
		isRight = false;
		isUp = false;
		isLeft = false;
	}
	else if (count < 150 )
	{
		xPos += 10.0;
		isRight = true;
		isLeft = false;
		isUp = false;
		isDown = false;
	}
	else if (count < 200 )
	{
		yPos -= 10.0;
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

	count+=5;
	fx = xPos;
	fy = yPos;
	setPos(fx, fy);

	//emitFindEMNode();


}

void EMNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	qDebug()<<"[EMNode] mouse press event is called..";
	if (event->buttons() & Qt::LeftButton)
	{
		//menu->popup(event->pos());
		qDebug()<<"Item : "<<node_nm<<" is clicked..";
		//event->
	}

	//menu->popup(QPoint(500,500));
	QGraphicsItem::mousePressEvent(event);



}


void EMNode::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
 {
     QMenu menu;
     QAction *removeAction = menu.addAction("Remove");
    // connect(removeAction, SIGNAL(triggered()), this, SLOT(removeEMNode()));
     QAction *markAction = menu.addAction("Info");
    // connect(markAction, SIGNAL(triggered()), this, SLOT(infoEMNode()));

     //Weapon 선택
     wp_1 = menu.addAction("WP1");
     wp_1->setCheckable(true);
	  wp_2 = menu.addAction("WP2");
	  wp_3 = menu.addAction("WP3");

	  wp_2->setCheckable(true);
	  wp_3->setCheckable(true);

//	  connect(wp_1, SIGNAL(triggered()), this, SLOT(changeWP()));
//	  connect(wp_2, SIGNAL(triggered()), this, SLOT(changeWP()));
//	  connect(wp_3, SIGNAL(triggered()), this, SLOT(changeWP()));


 }

void EMNode::removeEMNode()
{
	qDebug()<<"remove EMNode...";
//	emitRemoveEMNode(this);

}

void EMNode::callFindEMNode()
{
//	emitFindEMNode();
}

void EMNode::infoEMNode()
{
	qDebug()<<"Information of EMNode is called..";
/*
	node_x = sceneBoundingRect().center().x();
	node_y = sceneBoundingRect().center().y();
	info = new EMNodeInfo;
	info->setInfo(node_nm, node_x, node_y);
	if (info->exec()) {
		delete info;
		info = 0;
	}else {
		delete info;
		info = 0;
	}
*/

}


QGraphicsItem * EMNode::goWP(qreal x, qreal y, qreal x1, qreal y1)
{
	if(wp_type == WP1){
		wp = new WP_1(x, y, x1, y1, type);
	}else if(wp_type == WP2){
		//wp = new WP_2(x, y, x1, y1-10, type);
	}else if(wp_type == WP3)
	{
	}
	//connect(wp, SIGNAL(emitColDetection()), this, SLOT(callFindEMNode()));
	//wp->attack();
	return wp;
}

void EMNode::changeWP()
{
	/*//QAction * action = (QAction *)sender();
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
	}*/
}

void EMNode::createWP()
{
	/*while(checkThread != true){
		qDebug()<<"createWP is called..";
		qDebug()<<"ID : "<<QThread::currentThreadId();
		node_x = sceneBoundingRect().center().x();
		node_y = sceneBoundingRect().center().y();
		qDebug()<<"X : "<<node_x<<", Y : "<<node_y;

		CommonWP *wp1 = new WP_1(node_x, node_y + 40, node_x - 10, node_y + 40, 0);
		QMetaObject::invokeMethod(wp1, "attack", Qt::QueuedConnection);
		emitEnemyWP(wp1);

//		/*QGraphicsItem * temp = goWP(node_x, node_y + 40, node_x - 30, node_y + 40);
//		emitEnemyWP(temp);
		sleep(3);
	}*/

	//qDebug()<<"createWP is called..";

	node_x = sceneBoundingRect().center().x();
	node_y = sceneBoundingRect().center().y();
	//qDebug()<<"X : "<<node_x<<", Y : "<<node_y;

	wp = new WP_1(node_x, node_y + 40, node_x - 10, node_y + 40, 0);
	wp->attack();
	emitEnemyWP(wp);


}
