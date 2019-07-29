/*
 * DatToMapUtil.h
 *
 *  Created on: 2014. 2. 10.
 *      Author: jiwon
 *      Descr : Dat 파일을 SMS 맵데이터 형식으로 변환한다..
 */

#ifndef DATTOMAPUTIL_H_
#define DATTOMAPUTIL_H_

#include <QString>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QObject>

#include "DatMapInfo.h"

class DatToMapUtil {
public:
	DatToMapUtil();
	virtual ~DatToMapUtil();
	void openFile();
	void parsingLine(QString line , int & idx);
	void parsingLatLon(QString latlon, QString &lat, QString &lon);
	void decimalToDMS();
	void writeFile();
private:
	QFileDialog * file_dlg;
	QString filename;				//opened filed
	QString newfilename;
	QFile * file;

	QVector<DatMapInfo> mapinfo_list;
};

#endif /* DATTOMAPUTIL_H_ */
