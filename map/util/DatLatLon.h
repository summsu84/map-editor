/*
 * DatLatLon.h
 *
 *  Created on: 2014. 2. 10.
 *      Author: jiwon
 *      Descr : Dat파일로 부터 읽어온 위경도 정
 */

#ifndef DATLATLON_H_
#define DATLATLON_H_

#include <QString>
#include <QDebug>
class DatLatLon {
public:
	DatLatLon();
	DatLatLon(QString lat, QString lon);
	virtual ~DatLatLon();

	QString getDatLat() { return dat_lat;}
	QString getDatLon() { return dat_lon;}
	QString getDMSLat();
	QString getDMSLon();
	bool process();
	QString LatDecimalToDMS(double latdecimal);
	QString LonDecimalToDMS(double londecimal);
private:
	QString dat_latlon;			//dat 파일에서의 위경도 정
	QString dat_lat;				//dat 파일에서 위도만 추출한 정보
	QString dat_lon;				//dat 파일에서 경도만 추출한 정보

	QString con_lat;				//도본초 형식의 위도 정보
	QString con_lon;				//도분초 형식의 경도 정보

};

#endif /* DATLATLON_H_ */
