/*
 * AirportSqlGen.cpp
 *
 *  Created on: 2013. 7. 22.
 *      Author: jiwon
 */

#include "AirportSqlGen.h"

AirportSqlGen::AirportSqlGen(QString name) : SqlGen(name)
{
	// TODO Auto-generated constructor stub

}

AirportSqlGen::~AirportSqlGen() {
	// TODO Auto-generated destructor stub
}



QString AirportSqlGen::insertMainTableSql()
{
	QString sql;


	return sql;
}

/**
 * SIDSTARMAP은 테이블을 하나만 작업하기 때문에 아래 subTableSql만을 이용한다
 */
QString AirportSqlGen::insertSubTableSql()
{
	QString sql = "";


	return sql;
}

QString AirportSqlGen::getCountMainTableSql()
{
	QString sql;

	//sql  = " SELECT COUNT(*) FROM "+tb_name+" WHERE COAST_ID = '"+data.getId()+"'";

	return sql;
}

QString AirportSqlGen::getCountSubTableSql()
{

	QString sql = "";

	return sql;
}

/*
 * 특정 조건에 대한 레코드들을 가져온다.
 */

QString  AirportSqlGen::getMainTableSql()
{

	QString sql;

	sql = "SELECT AD_ID, AD_NM, LAT, LON, ICAO_CD FROM TB_AD WHERE ICAO_CD = 'RK'";

	return sql;

}
