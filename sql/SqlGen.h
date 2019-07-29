/*
 * SqlGen.h
 *
 *  Created on: 2013. 1. 30.
 *      Author: jiwon
 */

#ifndef SQLGEN_H_
#define SQLGEN_H_

#include <iostream>
#include <QString>

typedef struct _TB_AD
{
	int idx;
	QString ad_id;
	QString ad_nm;
	QString lat;
	QString lon;
	QString icao_cd;
} TB_AD;

typedef struct _V_FIX
{
	int idx;
	QString fix_id;
	QString lat;
	QString lon;
}V_FIX;
class SqlGen {
public:
	SqlGen(QString tb_name);
	virtual ~SqlGen();
	virtual QString insertMainTableSql();
	virtual QString insertSubTableSql();
	virtual QString getCountMainTableSql() = 0;
	virtual QString getMainTableSql() = 0;

protected:
	QString tb_name;			//테이블 이름
};

#endif /* SQLGEN_H_ */
