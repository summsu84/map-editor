/*
 * PosMng.h
 *
 *  Created on: 2013. 7. 23.
 *      Author: jiwon
 */

#ifndef POSMNG_H_
#define POSMNG_H_

#include <QPointF>

class PosMng {
public:
	PosMng();
	virtual ~PosMng();

	QPointF xyPos;
	QPointF latlonPos;

};

#endif /* POSMNG_H_ */
