/*
 * DatLatLon.cpp
 *
 *  Created on: 2014. 2. 10.
 *      Author: jiwon
 */

#include "DatLatLon.h"
#include "math.h"
DatLatLon::DatLatLon() {
	// TODO Auto-generated constructor stub

}

DatLatLon::DatLatLon(QString lat, QString lon)
{
	dat_lat = lat;
	dat_lon = lon;
}

DatLatLon::~DatLatLon() {
	// TODO Auto-generated destructor stub
}

//도분초 변환 작업 실시
bool DatLatLon::process()
{
	bool ok;
	double double_lat = dat_lat.toDouble(&ok);
	double double_lon = dat_lon.toDouble(&ok);

	con_lat = this->LatDecimalToDMS(double_lat);
	con_lon = this->LonDecimalToDMS(double_lon);

//	qDebug()<<"Org Lat : "<<dat_lat<<", Org Lon : "<<dat_lon;
//	qDebug()<<"Conv Lat : "<<con_lat<<", Conv Lon : "<<con_lon;
}

QString DatLatLon::getDMSLat()
{
	return con_lat;
}

QString DatLatLon::getDMSLon()
{
	return con_lon;
}


// 35.12345 => N35001234
// 위경도를 도분초로 변환 (위도)
QString DatLatLon::LatDecimalToDMS(double latdecimal)
{
	qDebug()<<"LatDecimalToDMS - lat : "<<latdecimal;
	double d = fabs(latdecimal);
	int deg = (int)floor(d);
	int min = (int)floor((d - deg) * 60);

	int sec = (int)floor((((d - deg) * 60 - min) * 100/ 60) * 3600);
	QChar sign = QChar('N');
	if (latdecimal < 0) {
		sign = QChar('S');
	}

	return QString("%1%2%3%4").arg(sign).arg(deg, 2, 'f', 0, QChar('0')).arg(min, 2, 'f', 0, '0').arg(sec, 4, 'f', 0, '0');
}
// 위경도를 도분초로 변환 (경도)
QString DatLatLon::LonDecimalToDMS(double londecimal)
{
	qDebug()<<"LonDecimalToDMS lon : "<<londecimal;
	double d = fabs(londecimal);
	int deg = (int)floor(d);
	int min = (int)floor((d - deg) * 60);
	int sec = (int)floor((((d - deg)*60 - min)*100/60)*3600);
	QChar sign = QChar('E');
	if (londecimal < 0) {
		sign = QChar('W');
	}

	return QString("%1%2%3%4").arg(sign).arg(deg, 3, 'f', 0, QChar('0')).arg(min, 2, 'f', 0, '0').arg(sec, 4, 'f', 0, '0');
}
