/*
 * AirportSqlGen.h
 *
 *  Created on: 2013. 7. 22.
 *      Author: jiwon
 */

#ifndef AIRPORTSQLGEN_H_
#define AIRPORTSQLGEN_H_

#include "SqlGen.h"

class AirportSqlGen : public SqlGen
{
public:
	AirportSqlGen(QString name);
	~AirportSqlGen();
	QString insertMainTableSql();
	QString insertSubTableSql();
	QString getCountMainTableSql();
	QString getCountSubTableSql();
	QString getMainTableSql();
};

#endif /* AIRPORTSQLGEN_H_ */
