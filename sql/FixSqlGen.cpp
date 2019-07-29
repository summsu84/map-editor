/*
 * FixSqlGen.cpp
 *
 *  Created on: 2013. 7. 22.
 *      Author: jiwon
 */

#include "FixSqlGen.h"

FixSqlGen::FixSqlGen(QString name) : SqlGen(name)
{
	// TODO Auto-generated constructor stub

}

FixSqlGen::~FixSqlGen() {
	// TODO Auto-generated destructor stub
}



QString FixSqlGen::insertMainTableSql()
{
	QString sql;


	return sql;
}

/**
 * SIDSTARMAP은 테이블을 하나만 작업하기 때문에 아래 subTableSql만을 이용한다
 */
QString FixSqlGen::insertSubTableSql()
{
	QString sql = "";


	return sql;
}

QString FixSqlGen::getCountMainTableSql()
{
	QString sql;

	//sql  = " SELECT COUNT(*) FROM "+tb_name+" WHERE COAST_ID = '"+data.getId()+"'";

	return sql;
}

QString FixSqlGen::getCountSubTableSql()
{

	QString sql = "";

	return sql;
}

/*
 * 특정 조건에 대한 레코드들을 가져온다.
 */

QString  FixSqlGen::getMainTableSql()
{

	QString sql;

	sql = "SELECT FIX_ID, ICAO_CD, LAT, LON FROM V_FIX WHERE ICAO_CD = 'RK'";

	return sql;

}
