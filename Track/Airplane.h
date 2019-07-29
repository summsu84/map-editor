/*
 * Airplane.h
 *
 *  Created on: 2013. 9. 23.
 *      Author: jiwon
 */

#ifndef AIRPLANE_H_
#define AIRPLANE_H_

/**
 * Airplane
 */
#include <QString>
#include <QGraphicsItem>
#include <QTimer>
#include "LabelComponent.h"
#include "TrailComponent.h"
#include <QObject>

class LabelComponent;
class Airplane : public QObject, public QGraphicsRectItem
{
	Q_OBJECT
public:
	Airplane();
	Airplane(QString call_sign, int climb_rate, int turn_rate, int heading, int alt, QString direct, int speed, int posx, int posy, int accel_rate);
	virtual ~Airplane();

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
public slots:
	void move();
	void PlaneProcess();
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
signals :

	void emitTrailComponents(TrailComponent ** tr_list);
};

#endif /* AIRPLANE_H_ */
