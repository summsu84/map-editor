/*
 * DatToMapUtil.cpp
 *
 *  Created on: 2014. 2. 10.
 *      Author: jiwon
 */

#include "DatToMapUtil.h"
#include <QDebug>

DatToMapUtil::DatToMapUtil() {
	// TODO Auto-generated constructor stub

}

DatToMapUtil::~DatToMapUtil() {
	// TODO Auto-generated destructor stub
}

//File을 오픈하여 파일을 읽어 들인다..
void DatToMapUtil::openFile()
{
	QString dir = QDir::currentPath();

	file_dlg = new QFileDialog();
	filename = file_dlg->getOpenFileName(0, QString("Open the dat file"), dir, QString("dat file(*.dat)"));

	if(!filename.isEmpty())
	{
		file = new QFile(filename);
		if(!file->open((QIODevice::ReadOnly))){
			qDebug()<<"Cannot open the file..";
			return;
		}

		//Read Line
		QTextStream out(file);
		int map_dat_idx = 0;
		while(!out.atEnd()){
			parsingLine(out.readLine(), map_dat_idx);

		}

		file->close();
	}

	this->decimalToDMS();

	writeFile();

}

void DatToMapUtil::parsingLine(QString line, int & idx)
{
	qDebug()<<"parsingLine.. line : "<<line<<", idx : "<<idx;
	if(line == ">")
	{
		//맵 정보 생성
		DatMapInfo datMapInfo;
		idx++;
		mapinfo_list.append(datMapInfo);
	}else{
		QString lat, lon;
		parsingLatLon(line, lat, lon);
		DatLatLon datLatLon(lat, lon);
		mapinfo_list[idx -1].addDatLatLon(datLatLon);
	}
}

/**
 * 위경도를 파싱한다.
 */
void DatToMapUtil::parsingLatLon(QString latlon, QString &lat, QString &lon)
{
	qDebug()<<"parsingLatLon called..";
	QStringList latlon_list = latlon.split('\t');

	lat = latlon_list.at(1);
	lon = latlon_list.at(0);

	//qDebug()<<"Lat : "<<lat<<", Lon : "<<lon;
}


/**
 * 위경도를 도분초로 변환하는 작업을 수행한다..
 */
void DatToMapUtil::decimalToDMS()
{
	for(int i = 0 ; i < mapinfo_list.size() ; i++){
		DatMapInfo datMapInfo = mapinfo_list.at(i);

		datMapInfo.process();

		/*for(int j = 0 ; j < datMapInfo.getDatLatLonList().size() ; j++)
		{
			DatLatLon datLatLon = datMapInfo.getDatLatLonList().at(j);
			datLatLon.process();

			datMapInfo.getDatLatLonList().replace(j, datLatLon);
//			qDebug()<<"Dat Lat : "<<datMapInfo.getDatLatLonList()[j].getDatLat()<<", Dat Lon : "<<datMapInfo.getDatLatLonList()[j].getDatLon();
//			qDebug()<<"DMS Lat : "<<datMapInfo.getDatLatLonList()[j].getDMSLat()<<", DMS Lon : "<<datMapInfo.getDatLatLonList()[j].getDMSLon();
		}*/
		mapinfo_list.replace(i, datMapInfo);
		//qDebug()<<"=================================================";
	}

	//Test
	for(int i = 0 ; i <mapinfo_list.size(); i++){
		DatMapInfo datMapInfo = mapinfo_list.at(i);
		datMapInfo.debug();
	}
}

void DatToMapUtil::writeFile()
{
	QString home = "/home/jiwon/";
	newfilename = home.append("new_korea.map");

	QFile * file = new QFile(newfilename);
	if(!file->open(QIODevice::WriteOnly)){
		qDebug()<<"Cannot open file for writing!"<<newfilename;
		return;
	}

	QTextStream out(file);
	for(int i = 0 ; i < mapinfo_list.size() ; i++)
	{
		DatMapInfo mapInfo = mapinfo_list.at(i);
		out<<"ID:"<<QString().setNum(i, 10)<<":"<<mapInfo.getListSize()<<":P"<<endl;
		for(int j = 0 ; j < mapInfo.getListSize() ; j++){
			DatLatLon latlon = mapInfo.getDatLatLonList().at(j);
			out<<"G:"<<latlon.getDMSLat()<<latlon.getDMSLon()<<endl;
		}
	}
	file->close();

}
