/*
 * ManualCoordDbProcess.h
 *
 *  Created on: 2013. 7. 22.
 *      Author: jiwon
 */

#ifndef MANUALCOORDDBPROCESS_H_
#define MANUALCOORDDBPROCESS_H_

#include "../../sql/SqlGen.h"
#include "../../sql/AirportSqlGen.h"
#include "../../sql/FixSqlGen.h"
#include "../../lib/UserInfo.h"
#include <QVector>
#include <QSqlQuery>
/**
 * Manual Coord 중 디비와 관련된 작업을 수행한다..
 */

class ManualCoordDbProcess {
public:
	ManualCoordDbProcess();
	virtual ~ManualCoordDbProcess();
	//void getAirPortList();				//메뉴얼에서 요구한
	QSqlQueryModel * processAirPortList(QString sql);
	QSqlQueryModel * getAirPortList();

	//Fix info
	QSqlQueryModel * processFixList(QString sql);
	QSqlQueryModel * getFixList();

private:
	QVector<TB_AD> ad_list;
	QVector<V_FIX> fix_list;
	AirportSqlGen * airportSqlGen;
	FixSqlGen * fixSqlGen;
};

#endif /* MANUALCOORDDBPROCESS_H_ */
