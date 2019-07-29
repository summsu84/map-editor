/*
 * RaderItemInfo.h
 *
 *  Created on: 2013. 10. 22.
 *      Author: jiwon
 */

#ifndef RADERITEMINFO_H_
#define RADERITEMINFO_H_

#include <QWidget>
#include <QtGui>
#include "../lib/Function.h"
#include "RadarItem.h"

class RadarItem;

class RaderItemInfo : public QWidget
{
	Q_OBJECT
public:
	RaderItemInfo(QString type, QWidget * parent = 0);
	RaderItemInfo(RadarItem * item, QWidget * parent = 0);
	RaderItemInfo(QWidget * parent = 0);
	virtual ~RaderItemInfo();
	void initUi();
	void setItemInfo(int flag);

public slots:
	void runAdd();
	void runSet();

private:
	QLabel * lblAcid;
	QLabel * lblSrc;
	QLabel * lblDst;
	QLabel * lblCuAlt;
	QLabel * lblClAlt;
	QLabel * lblCuSpd;
	QLabel * lblClSpd;
	QLabel * lblClHeading;			//Clear Heading Info
	QLabel * lblCuHeading;

	//txt
	QLineEdit * txtAcid;
	QLineEdit * txtSrc;
	QLineEdit * txtDst;
	QLineEdit * txtCuAlt;
	QLineEdit * txtClAlt;
	QLineEdit * txtCuSpd;
	QLineEdit * txtClSpd;
	QLineEdit * txtClHeading;		//Clear Heading Info
	QLineEdit * txtCuHeading;

	//Button
	QPushButton * btnOk;
	QPushButton * btnAdd;

	QPushButton * btnSet;
	QPushButton * btnCancel;

	QString type;
	RadarItem * curRadarItem;
signals:
	void emitAddRadarItem(const RDITEM item);

};

#endif /* RADERITEMINFO_H_ */
