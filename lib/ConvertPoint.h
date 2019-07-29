/*
 * ConvertPoint.h
 *
 *  Created on: 2009. 11. 2.
 *      Author: root
 */

#ifndef CONVERTPOINT_H_
#define CONVERTPOINT_H_

#include <QtCore>
#include <QObject>
#include <QtGui>
class ConvertPoint : public QObject
{
    Q_OBJECT

public:
	ConvertPoint();
	virtual ~ConvertPoint();

public slots:
	void validatorLatLon(QWidget* obj);
	void validatorLatitude(QWidget* obj);
	void validatorLongitude(QWidget* obj);
	void validatorBearing(QWidget* obj);
	void validatorBearingTrue(QWidget* obj);
	void validatorBearingEnd(QWidget* obj);
	void validatorBearingTrueEnd(QWidget* obj);
	void validatorGradient(QWidget* obj);
	void validatorGradientEnd(QWidget *obj);
	void validatorEllipsoid(QWidget* obj);
	void validatorEllipsoidEnd(QWidget *obj);
	void validatorDotEnd(QWidget *obj);
	void validatorDate(QWidget *obj);
	void validatorFacility(QWidget *obj);
private:
	int validatorLatitudeCheck(QWidget *obj, int currentIndex);
	void setBearingFormat(QWidget *obj, int index, QChar format);
	void setBearingTrueFormat(QWidget *obj, int index, QChar format);
	void setGradientFormat(QWidget *obj, int index, QChar format);
};

#endif /* CONVERTPOINT_H_ */
