/*
 * Radar.h
 *
 *  Created on: 2013. 10. 14.
 *      Author: jiwon
 */

#ifndef RADAR_H_
#define RADAR_H_

/**
 * Circle을 그린다.
 */
#include <QGraphicsItem>
#include "RadarView.h"

class RadarView;
class Radar : public QGraphicsItem
{
public:
	Radar();
	Radar(RadarView * view);
	virtual ~Radar();
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
	void drawRadarCircle(QPainter * painter, int gap);
	void drawLine(QPainter * painter);
	void drawBearing(QPainter * painter);
	QRectF boundingRect() const;

private:
	RadarView * view;
};

#endif /* RADAR_H_ */
