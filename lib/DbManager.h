/*
 * DbManager.h
 *
 *  Created on: 2013. 1. 29.
 *      Author: jiwon
 */

#ifndef DBMANAGER_H_
#define DBMANAGER_H_

#include "UserInfo.h"
/*
#include "ConvertDataInfo.h"
#include "Sql/SqlGen.h"
#include "Sql/CoastSqlGen.h"
#include "Sql/SidStarSqlGen.h"
#include "Sql/AirspaceSqlGen.h"
*/
#include <QtSql>


class DbManager {
public:
	DbManager();
	bool dbOpen();
	void init();
	virtual ~DbManager();

	/*bool insertProcess(QChar & prefix);
	QString retriveTableName(QString layer);
	bool getCount4Insert(QString sql, QSqlQuery * query);*/
	QString errorMessage;
	int mainCnt;
	int subCnt;
private:
	/*QVector<ConvertDataInfo> convertDataInfo;
	SqlGen * sqlgen;*/

/*signals:
	emitDuplication(QString error);*/

};

#endif /* DBMANAGER_H_ */
