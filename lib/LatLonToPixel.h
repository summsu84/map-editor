/*
 * LatLonToPixel.h
 *
 *  Created on: 2013. 5. 14.
 *      Author: jiwon
 */

#ifndef LATLONTOPIXEL_H_
#define LATLONTOPIXEL_H_

#include <iostream>
#include <QString>
#include <QFile>
#include <QVector>
#include <math.h>
#include "lib/WGS84_TM.h"
#include "LatLonMng.h"

using namespace std;


class LatLonToPixel {
public:
	LatLonToPixel();
	virtual ~LatLonToPixel();
	void toPixel();
	void openFile();
	bool readFile();
	void processingFile(QString str);
	void test();
	int long2tilex(double lon, int z);
	int lat2tiley(double lat, int z);

	void parsingColor(QString org_rgb, QColor * color);

	QVector<LatLonMng> getLatLonMngList(){ return this->latlonmng_list;}
	QVector<LatLon> getConvertedLatLonList(){ return this->converted_latlon_list;}

	QString getFileName() { return cfilename; }

private:
	int lat;
	int lon;
	int count;
	QString cfilename;
	QFile * openedFile;
	QVector<LatLonMng> latlonmng_list;				//파일을 읽어서 레이어 및 맵 정보를 저장
	//QVector<LatLon> latlon_list;
	QVector<LatLon> converted_latlon_list;
};

#endif /* LATLONTOPIXEL_H_ */
