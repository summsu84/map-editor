/*
 * DbManager.cpp
 *
 *  Created on: 2013. 1. 29.
 *      Author: jiwon
 */

#include "DbManager.h"
#include <QMessageBox>

DbManager::DbManager() {
	// TODO Auto-generated constructor stub


	init();
}

DbManager::~DbManager() {
	// TODO Auto-generated destructor stub
	qDebug()<<"[DbManager] db close..";
}

void DbManager::init()
{
	UserInfo::getInstance().setDbname("smsd");
	UserInfo::getInstance().setId("adapt");
	UserInfo::getInstance().setPass("adapt");
}

bool DbManager::dbOpen()
{
	qDebug()<<"[DbManager] dbOpen is called..";
	QSqlDatabase::removeDatabase("smsd");
	{
		QSqlDatabase db = QSqlDatabase::addDatabase("QOCI", "smsd");
		db.setHostName("sms02");
		db.setDatabaseName("smsd");
		db.setUserName("adapt");
		db.setPassword("adapt");
		//QMessageBox::warning(this, tr("DataBase Open Error"), tr("%1  %2  %3  %4 Driver %5").arg(parser->getDatabase()).arg(parser->getDbUser()).arg(parser->getDbPass()).arg(parser->getHost()).arg(parser->getDriver()));
		bool chk = db.open();
		qDebug()<<"Chk : "<<chk;
		if (chk == false) {
			qDebug()<<"Database Open Error!";
			return false;
		}else{
			qDebug()<<"Database Open Success!.";
			return true;
		}
	}
}
