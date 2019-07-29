/*
 * RadarView.h
 *
 *  Created on: 2013. 10. 14.
 *      Author: jiwon
 */

#ifndef RADARVIEW_H_
#define RADARVIEW_H_

#include <QGraphicsView>
#include <QGraphicsScene>
#include "Radar.h"
#include "MovingLine.h"
#include "RadarItem.h"

class RadarView : public QGraphicsView
{
	Q_OBJECT
public:
	RadarView(QWidget * parent = 0);
	virtual ~RadarView();

	QGraphicsScene * getGraphcisScene() { return scene; }
	void setGraphicsSceneRect(QRect rect);
	void drawRadar();
	void addRadarItem(RadarItem * item, int direction);
	void testRadarItem();		//여러개의 아이템을 생성한다..
public slots:
	void runAddRadarItem(const RDITEM item);
	void updateTrack(TrailComponent ** trail_list);
	void runAlignment(Qt::Alignment alignment);
protected:
	void mousePressEvent(QMouseEvent * event);
private :
	QGraphicsScene * scene;
};

#endif /* RADARVIEW_H_ */
