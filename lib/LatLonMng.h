/*
 * LatLonMng.h
 *
 *  Created on: 2013. 5. 15.
 *      Author: jiwon
 *      Descr : SMS 맵 형식을 읽어서 아이디 별로 좌표와 레이어 정보를 저장한다.
 */

#ifndef LATLONMNG_H_
#define LATLONMNG_H_

#include "LayerInfo.h"
#include <QVector>
#include <QPointF>
#include "Function.h"
#include "../ImgWidget/LATLON/LatLonConvert.h"
#include <QGraphicsItem>

class LatLonMng : public LayerInfo
{
public:
	LatLonMng();
	LatLonMng(LayerInfo info);
	virtual ~LatLonMng();
    int getIndex() const
    {
        return index;
    }

    void setIndex(int index)
    {
        this->index = index;
    }

    int getCount() const
    {
        return count;
    }

    QString getId_name() const
    {
        return id_name;
    }

    QVector<LatLon> getLatlon_list() const
    {
        return latlon_list;
    }



    void setCount(int count)
    {
        this->count = count;
    }

    void setId_name(QString id_name)
    {
        this->id_name = id_name;
    }

    void setLatlon_list(QVector<LatLon> latlon_list)
    {
        this->latlon_list = latlon_list;
    }

    void setMapType(DS::Shape mapType)
    {
    	this->mapType = mapType;
    }
    DS::Shape getMapType()
    {
    	return this->mapType;
    }

    void print();
    QVector<QPointF> rotateLatLon(QVector<QPointF> point_list, int angle);
    QVector<LatLon> rotateLatLon(QVector<LatLon> point_list, int angle);
    QVector<LatLon> getConvertedLatLonList();
    QVector<QPointF> getConvertedLatLonList2QPointF();
    QPointF drawMapId();
    void setAngle(int angle);
    bool			isEnable;			//true : enable, false : disable;

    void setItem(QGraphicsItem * item) { this->item = item; }
    QGraphicsItem * getItem() { return item; }
    void setTextItem(QGraphicsTextItem * item) { this->txtItem = item; }
    QGraphicsTextItem * getTextItem() { return txtItem; }
private :

	QString			id_name;
	DS::Shape				mapType;
	int				index;
	int				count;
	QVector<LatLon>	latlon_list; //위경도 좌표
	QVector<QPointF> latlon_point_list;	//X, Y 좌표
	int angle;

	QGraphicsItem * item;			//아이템
	QGraphicsTextItem * txtItem;	//아이디 아이템

};

#endif /* LATLONMNG_H_ */
