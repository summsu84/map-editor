/*
 * Node.h
 *
 *  Created on: 2013. 1. 21.
 *      Author: jiwon
 */

#ifndef EMNODE_H_
#define EMNODE_H_

#define CHILD_MAX 3

#include <QGraphicsItem>
#include <QString>
#include <QPainter>
#include <QTimer>
#include <QMenu>
#include <QThread>
#include <QGraphicsSceneContextMenuEvent>
#include "../Weapon/CommonWP.h"
#include "../Weapon/WP_1.h"
#include "../Weapon/WP_2.h"
#include "../BaseNode.h"


#define WP1 1
#define WP2 2
#define WP3 3

/**
 * Create Enemy Node
 */

class EMNode : public QObject, public QGraphicsEllipseItem, public BaseNode
{
	Q_OBJECT
public:
	EMNode(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = 0);
	virtual ~EMNode();
	void setEMNodeNm(QString nm){ this->node_nm = nm;}
	QString getEMNodeNm(){return this->node_nm;}
	QTimer * updateTimer;
	QTimer * weaponTimer;
	QGraphicsItem  *goWP(qreal x, qreal y, qreal x1, qreal y1);
public slots:
	void move();
	void removeEMNode();
	void infoEMNode();
	void changeWP();
	void callFindEMNode();
	void createWP();
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
private:
	QString node_nm;
	qreal node_x;
	qreal node_y;
	int count;
	bool isUp;
	bool isDown;
	bool isLeft;
	bool isRight;
	int type;
	CommonWP * wp;
	//Layer Option
	int wp_type;
	QAction * wp_1;
	QAction * wp_2;
	QAction * wp_3;
	QThread * mThread;
	bool checkThread;
signals:
	void emitChildNode(QVector<QGraphicsEllipseItem *> child_list);
	void emitDeleteChild(QGraphicsEllipseItem ** child);
	void emitRemoveNode(EMNode * node);
	void emitFindNode();
	void emitEnemyWP(QGraphicsItem * wp);
};

#endif /* NODE_H_ */
