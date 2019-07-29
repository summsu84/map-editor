/*
 * FixSqlGen.h
 *
 *  Created on: 2013. 7. 22.
 *      Author: jiwon
 */

#ifndef FIXSQLGEN_H_
#define FIXSQLGEN_H_

#include "SqlGen.h"

class FixSqlGen : public SqlGen
{
public:
	FixSqlGen(QString name);
	virtual ~FixSqlGen();
	QString insertMainTableSql();
	QString insertSubTableSql();
	QString getCountMainTableSql();
	QString getCountSubTableSql();
	QString getMainTableSql();
};

#endif /* FIXSQLGEN_H_ */
