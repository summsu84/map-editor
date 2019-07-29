/*
 * ManualCoordDbProcess.cpp
 *
 *  Created on: 2013. 7. 22.
 *      Author: jiwon
 */

#include "ManualCoordDbProcess.h"

ManualCoordDbProcess::ManualCoordDbProcess() {
	// TODO Auto-generated constructor stub

	airportSqlGen = new AirportSqlGen("TB_AD");
	fixSqlGen = new FixSqlGen("V_FIX");

}

ManualCoordDbProcess::~ManualCoordDbProcess() {
	// TODO Auto-generated destructor stub
}



QSqlQueryModel * ManualCoordDbProcess::getAirPortList()
{
	QString sql;

	sql = airportSqlGen->getMainTableSql();

	return processAirPortList(sql);

	//return ad_list;


}



QSqlQueryModel * ManualCoordDbProcess::processAirPortList(QString sql)
{
	/*QSqlQuery * query = new QSqlQuery(QSqlDatabase::database(UserInfo::getInstance().getDbname()));

	query->prepare(sql);
	query->exec();

	int idx = 0;
	while(query->next())
	{
		TB_AD ad;
		ad.ad_id = query->value(0).toString();
		ad.ad_nm = query->value(1).toString();
		ad.lat = query->value(2).toString();
		ad.lon = query->value(3).toString();
		ad.icao_cd = query->value(4).toString();
		ad.idx = idx++;

		ad_list.append(ad);
	}
*/

	QSqlQueryModel * model = new QSqlQueryModel;

	model->setQuery(sql, QSqlDatabase::database(UserInfo::getInstance().getDbname()));

	return model;
}





QSqlQueryModel * ManualCoordDbProcess::getFixList()
{
	QString sql;

	sql = fixSqlGen->getMainTableSql();

	return processFixList(sql);

	//return ad_list;


}



QSqlQueryModel * ManualCoordDbProcess::processFixList(QString sql)
{

	QSqlQueryModel * model = new QSqlQueryModel;

	model->setQuery(sql, QSqlDatabase::database(UserInfo::getInstance().getDbname()));

	return model;
}






