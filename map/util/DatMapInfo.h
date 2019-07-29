/*
 * DatMapInfo.h
 *
 *  Created on: 2014. 2. 10.
 *      Author: jiwon
 */

#ifndef DATMAPINFO_H_
#define DATMAPINFO_H_

#include <QVector>
#include "DatLatLon.h"
#include <QDebug>
class DatMapInfo {
public:
	DatMapInfo();
	virtual ~DatMapInfo();
	void addDatLatLon(DatLatLon datLatLon);
	QVector<DatLatLon> getDatLatLonList() { return dat_latlon_list; }
	void process();
	void debug();
	int getListSize() { return list_size; }
	int getId() { return id; }
private:
	static int id;
	int list_size;
	QString dat_mapinfo;					//읽어 들인 맵정보
	QString con_mapinfo;					//변환된 맵정보
	QVector<DatLatLon>	dat_latlon_list;
};

#endif /* DATMAPINFO_H_ */
