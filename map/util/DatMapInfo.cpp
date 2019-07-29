/*
 * DatMapInfo.cpp
 *
 *  Created on: 2014. 2. 10.
 *      Author: jiwon
 */

#include "DatMapInfo.h"

int DatMapInfo::id = 0;

DatMapInfo::DatMapInfo() {
	// TODO Auto-generated constructor stub
	id++;
}

DatMapInfo::~DatMapInfo() {
	// TODO Auto-generated destructor stub
}

void DatMapInfo::addDatLatLon(DatLatLon datLatLon)
{
	dat_latlon_list.append(datLatLon);
}

void DatMapInfo::debug()
{
	qDebug()<<"=====================";
	qDebug()<<"ID : "<<id;
	for(int i = 0 ; i < dat_latlon_list.size() ; i++)
	{
		DatLatLon datLatLon = dat_latlon_list.at(i);
		qDebug()<<"Org Lat : "<<datLatLon.getDatLat()<<", Org Lon : "<<datLatLon.getDatLon();
		qDebug()<<"Conv Lat : "<<datLatLon.getDMSLat()<<", Conv Lon : "<<datLatLon.getDMSLon();
	}
}

void DatMapInfo::process()
{
	list_size = dat_latlon_list.size();

	for(int i = 0 ; i < list_size ; i++)
		dat_latlon_list[i].process();
}
