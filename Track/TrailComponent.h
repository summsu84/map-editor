/*
 * TrailComponent.h
 *
 *  Created on: 2013. 9. 25.
 *      Author: jiwon
 */

#ifndef TRAILCOMPONENT_H_
#define TRAILCOMPONENT_H_


#include <QGraphicsItem>

class TrailComponent : public QGraphicsRectItem
{
public:
	TrailComponent(int posx, int posy, QGraphicsItem * parent = 0);
	virtual ~TrailComponent();
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
	QRectF boundingRect() const;

	int getPosX() { return posx; }
	int getPosY() { return posy; }

	void setPosX(int posx) { this->posx = posx;	}
	void setPosY(int posy){ this->posy = posy;	}

	void updatePos();
private :
	int posx;
	int posy;

};

#endif /* TRAILCOMPONENT_H_ */
