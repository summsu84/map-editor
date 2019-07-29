/*
 * CommonWP.h
 *
 *  Created on: 2013. 5. 9.
 *      Author: jiwon
 */

#ifndef COMMONWP_H_
#define COMMONWP_H_

#include <QString>
#include <QDebug>
#include <QGraphicsLineItem>
#include <QGraphicsItem>
class CommonWP : public QObject, public QGraphicsLineItem
{
	Q_OBJECT
public:
	CommonWP(qreal x, qreal y, qreal x1, qreal y1, QGraphicsItem * parent = 0);
	virtual ~CommonWP();
    QString getDescr() const
    {
        return descr;
    }

    QString getWp_name() const
    {
        return wp_name;
    }

    void setDescr(QString descr)
    {
        this->descr = descr;
    }

    void setWp_name(QString wp_name)
    {
        this->wp_name = wp_name;
    }
    int getDamage() const
    {
        return damage;
    }
    void setDamage(int damage)
    {
        this->damage = damage;
    }
    void setWPBrush(QColor color);
    int nodetype;									//ENEMY - 0, NODE - 1

    virtual QGraphicsLineItem * attack4Node() = 0;
public slots:
	virtual QGraphicsLineItem * attack() = 0;
private :
	QString wp_name;
	QString descr;
	int damage;


};

#endif /* COMMONWP_H_ */
