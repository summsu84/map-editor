/*
 * RadarItem.h
 *
 *  Created on: 2013. 10. 17.
 *      Author: jiwon
 */

#ifndef RADARITEM_H_
#define RADARITEM_H_
#include <QString>
#include <QGraphicsItem>
#include <QGraphicsSceneContextMenuEvent>
#include <QTimer>
#include "../Track/LabelComponent.h"
#include "../Track/TrailComponent.h"
#include <QObject>
#include "RaderItemInfo.h"

class LabelComponent;
class RaderItemInfo;
class RadarItem : public QObject, public QGraphicsItem{
	Q_OBJECT

public:
	RadarItem();
	RadarItem(QString call_sign, int climb_rate, int turn_rate, int heading, int alt, QString direct, int speed, int posx, int posy, int accel_rate, QGraphicsItem * parent = 0);
	virtual ~RadarItem();

	void SetClearHeading(int heading) { cl_heading = heading; }
	void SetClearAlt(int alt) { cl_alt = alt; }
	void SetClearDirect(QString fix) { cl_direct = fix; }
	void SetClearSpeed(int speed) { cl_speed = speed; }

	void PrintPlane();

	int getPosX() { return posx; }
	int getPosY() { return posy; }
	QString getCallSign() { return callsign; }
	int getCuHeading() { return cu_heading; }
	int getClHeading() { return cl_heading; }
	int getCuAlt() { return cu_alt;}
	int getClAlt() { return cl_alt;}
	int getCuSpeed() { return cu_speed; }
	int getClSpeed() { return cl_speed; }

	qint64 toMsec();
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
	QRectF boundingRect() const;
	LabelComponent * apLabel;
	TrailComponent * trail_list[4];
	void emitTrailComponent();
	void deleteInfo();
protected :
	void mousePressEvent(QGraphicsSceneMouseEvent * event);
	void contextMenuEvent(QGraphicsSceneContextMenuEvent * event);
public slots:
	void move();
	void PlaneProcess();
	void runInfo();
private:
	QString callsign;
	int climbrate;		//feet per second
	int turnrate;		//degree per second;

	/*clearance */
	int cl_heading;		//degree
	int cl_alt;			//feet
	QString cl_direct;	//
	int cl_speed;

	/*current */
	int cu_heading;		//degree
	int cu_alt;			//feet;
	int cu_speed;		//knots
	double cu_speed_pix;	//speed in pixel
	int posx;
	int posy;
	int accel;			//knots per second
	int deccel;			//knots per second

	qint64 IterTimeStamp;		//time stamp of last iteration in second



	QTimer * updateTimer;

	RaderItemInfo * info;
signals :

	void emitTrailComponents(TrailComponent ** tr_list);
};
#endif /* RADARITEM_H_ */
