/*
 * Node.h
 *
 *  Created on: 2013. 1. 21.
 *      Author: jiwon
 */

#ifndef NODE_H_
#define NODE_H_

#define CHILD_MAX 3

#include <QGraphicsItem>
#include <QString>
#include <QPainter>
#include <QTimer>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include "NodeInfo.h"
#include "BaseNode.h"
#include "Weapon/CommonWP.h"
#include "Weapon/WP_1.h"
#include "Weapon/WP_2.h"


#define WP1 1
#define WP2 2
#define WP3 3


class Node : public QObject, public QGraphicsEllipseItem, public BaseNode
{
	Q_OBJECT
public:
	Node(qreal x, qreal y, qreal width, qreal height, int type, QGraphicsItem * parent = 0);
	virtual ~Node();
	 //QPainterPath shape() const;
	void setNodeNm(QString nm){ this->node_nm = nm;}
	QString getNodeNm(){return this->node_nm;}
	void drawDesc();
	void setChildPos(qreal x, qreal y);
	QVector<QGraphicsEllipseItem *> drawingChild();
	QTimer * updateTimer;
	QGraphicsItem  *goWP(qreal x, qreal y, qreal x1, qreal y1);
	QVector<QPointF> getHistoryPoint();
	void setHistoryPoint(QPointF point);
public slots:
	void move();
	void removeNode();
	void infoNode();
	void changeWP();
	void callFindNode();
protected:
	//void keyPressEvent(QKeyEvent * event);
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
	//void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
	QVector<QGraphicsEllipseItem *> child_node_list;
	NodeInfo * info;						//Node Info
	QVector<QPointF> point_list;
	QString node_nm;

	int count;
	bool isUp;
	bool isDown;
	bool isLeft;
	bool isRight;
	QMenu * menu;
	qreal node_x;
	qreal node_y;
	int leftCnt;
	int rightCnt;
	int upCnt;
	int downCnt;

	int type;

	CommonWP * wp;

	//Layer Option
	int wp_type;
	QAction * wp_1;
	QAction * wp_2;
	QAction * wp_3;

	//History Info
	QVector<QPointF> historyPoint;
signals:
	void emitChildNode(QVector<QGraphicsEllipseItem *> child_list);
	void emitDeleteChild(QGraphicsEllipseItem ** child);
	void emitRemoveNode(Node * node);
	void emitFindNode();
	void emitEnemyWP(QGraphicsItem * wp);
};

#endif /* NODE_H_ */
