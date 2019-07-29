/*
 * LatLonToPixel.cpp
 *
 *  Created on: 2013. 5. 14.
 *      Author: jiwon
 */

#include "LatLonToPixel.h"
#include <QFileDialog>
#include <QDebug>
#include <QTextStream>

using namespace::DS;

LatLonToPixel::LatLonToPixel() {
	// TODO Auto-generated constructor stub

	//wgs_tm = new WGS84_TM;

}

LatLonToPixel::~LatLonToPixel() {
	// TODO Auto-generated destructor stub
}


/*
 * x, y coordinate로 변환한다..
 */
void LatLonToPixel::toPixel()
{
	qDebug()<<"toPixel is called.."<<latlonmng_list.size();

	// get x value
	double x = 0;
	double y = 0;
	int latRad;
	int mercN;

	for(int j = 0 ; j < latlonmng_list.size() ; j++){
		LatLonMng latlonmng = latlonmng_list.at(j);
		qDebug()<<"LatLonCount : "<<latlonmng.getLatlon_list().size();
		for(int i = 0 ; i < latlonmng.getLatlon_list().size(); i++){

			LatLon latlon = latlonmng.getLatlon_list().at(i);
			float latitude = latlon.lat;
			float longitude = latlon.lon;

			WGS84_TM::getInstance().LatLonConvert(x, y, (double)longitude, (double)latitude);

			//아래는 0514에 업데이트한 맵 변환 소스
			/*x = this->long2tilex(longitude, 12);
			y = this->lat2tiley(latitude, 12);*/

			//아래는 기존 컨버터 소스임.
			/*x= ((mapWidth*(180 + longitude)/360));
			x = x % mapWidth + (mapWidth/2);

			// convert from degrees to radians
			latRad = latitude*PI/180;

			// get y value
			mercN = log(tan((PI/4)+(latRad/2)));
			y     = (mapHeight/2)-(mapWidth*mercN/(2*PI));
	*/
			LatLon cLatLon;
			cLatLon.lat = y;
			cLatLon.lon = x;

			converted_latlon_list.append(cLatLon);
			//cout<<"x : "<<x<<", y "<<y<<endl;
			qDebug()<<"Lat : "<<latitude<<", Lon : "<<longitude<<", X : "<<x<<", Y : y";
		}
	}
}


/*
 * 파일을 읽는다.
 */
bool LatLonToPixel::readFile()
{
	count = 0;
	QFileDialog * fdialog = new QFileDialog;

	QString dir = QDir::currentPath();
	cfilename = fdialog->getOpenFileName(0,QString("Open the kml file"),
			dir, QString("dat file(*.map)"));

	if (!cfilename.isEmpty()) {
		qDebug() << "fileName : " << cfilename;
	}else{
		qDebug() <<"File is not selected..";
		return false;
	}
	openFile();

	QTextStream out(openedFile);
	LayerInfo layer_info;
	QVector<LatLon> latlon_list;

	int idIndex = 0;
	int layerIndex = 0;
	bool ok;

	while(!out.atEnd()){
		QString strTmp = out.readLine();
		//qDebug()<<"line : "<<strTmp;
		//ENDLAYER일 경우 continue 한다.
		if(strTmp == "ENDLAYER"){
			layerIndex += 1;
			//idIndex = 0;
			latlonmng_list[idIndex-1].setLatlon_list(latlon_list);
			continue;
		}

		//line을 파싱한다..
		QStringList info_list = strTmp.split(':');

		if(info_list.at(0) == "LAYER"){

			qDebug()<<"IDX : "<<layerIndex<<", Layer : "<<info_list<<", IdIndex : "<<idIndex;;
			//레이어 정보 파싱
			//0 : LAYER
			//1 : LAYER_ID
			//2 : Line Type
			//3 : Line Width
			//4 : Line Color
			//5 : Fill Pattern
			//6 : Fill Color
			//7 : Font Name
			//8 : Font Size
			//9 : Font Color
			//10 : Symbol


			//1 : LAYER_ID
			layer_info.layer_name = info_list.at(1);
			//2 : Line Type
			if(info_list.at(2) != 0){
				if(info_list.at(2) == "1"){
					layer_info.layer_line_type = Solid;
				}else if(info_list.at(2) == "2"){
					layer_info.layer_line_type = Dashed;
				}else{
					layer_info.layer_line_type = Dotted;
				}
			}
			//3 : Line Width
			if(info_list.at(3).length() != 0){
				layer_info.layer_line_width = info_list.at(3).toInt(&ok, 10);
			}

			//4 : Line Color
			if(info_list.at(4).length() != 0){
				parsingColor(info_list.at(4), &layer_info.layer_line_color);

			}
			//5 : FillPattern

			if(info_list.at(5).length() != 0){
				int fill_pattern = info_list.at(5).toInt(&ok, 10);
				if(fill_pattern == 1){
					layer_info.layer_fille_pattern = SOLID_F;
				}else if(fill_pattern == 2){
					layer_info.layer_fille_pattern = DOTTED_F;
				}else if(fill_pattern == 3){
					layer_info.layer_fille_pattern = HORIZONTALLINE;
				}else if(fill_pattern == 4){
					layer_info.layer_fille_pattern = VERTICALLINE;
				}else if(fill_pattern == 5){
					layer_info.layer_fille_pattern = CROSSLINE;
				}else if(fill_pattern == 6){
					layer_info.layer_fille_pattern = SLASHED;
				}else if(fill_pattern == 7){
					layer_info.layer_fille_pattern = REVERSESLASHED;
				}else if(fill_pattern == 4){
					layer_info.layer_fille_pattern = CROSSSLASHED;
				}
			}

			//6 : Fill Color
			if(info_list.at(6).length() != 0){
				parsingColor(info_list.at(6), &layer_info.layer_fill_color);

			}
			//7 : Font Name
			if(info_list.at(7).length() != 0){
				layer_info.layer_font_name = info_list.at(7);
			}

			//8 : Font Size
			if(info_list.at(8).length() != 0){
				layer_info.layer_font_size = info_list.at(8).toInt(&ok, 10);

			}

			//9 : Font Color
			if(info_list.at(9).length() != 0){
				parsingColor(info_list.at(9), &layer_info.layer_font_color);

			}

			//10 :  Symbol
			if(info_list.at(10).length() != 0){
				layer_info.layer_symbol = info_list.at(10);
			}

			//qDebug()<<"Layer : "<<layer_info.layer_name;
		}else if(info_list.at(0) == "ID"){
			//아이디 정보 파싱

			if(idIndex > 0){
				//Inserting latlon list to latlonmng
				latlonmng_list[idIndex-1].setLatlon_list(latlon_list);
			}
			LatLonMng mng(layer_info);

			// 0 : ID Tab
			// 1 : ID Name
			// 2 : Number of Coordinates
			// 3 : Map Type
			// 4 : Line Type (todo)

			if(info_list.at(1).length() != 0){
				// 1 : ID Name
				mng.setId_name(info_list.at(1));
			}

			if(info_list.at(2).length() != 0){
				// 2: Number of Coordinates
				mng.setCount(info_list.at(2).toInt(&ok, 10));
			}

			if(info_list.at(3).length() != 0){
				// 3: Map Type
				if(info_list.at(3) == "G"){
					mng.setMapType(Polygon);
				}else if(info_list.at(3) == "P"){
					mng.setMapType(Polyline);
				}else if(info_list.at(3) == "C"){
					mng.setMapType(Circle);
				}else if(info_list.at(3) == "E"){
					mng.setMapType(Ellipse);
				}else if(info_list.at(3) == "L"){
					mng.setMapType(Line);
				}else if(info_list.at(3) == "S"){
					mng.setMapType(Symbol);
				}
			}

			mng.setIndex(idIndex);
			latlonmng_list.append(mng);
			idIndex += 1;

			latlon_list.clear();
			//qDebug()<<"ID : "<<info_list.at(1);
		}else if(info_list.at(0) == "G" || info_list.at(0) == "S"){
			//좌표 정보 파싱
			LatLon latlon;
			QStringList str_list_latlon = info_list.at(1).split('E');
			QString str_lat = str_list_latlon[0].remove(0,1);
			QString str_lon = str_list_latlon[1];

			str_lat.insert(2, ".");
			str_lon.insert(3, ".");

			float float_lat = str_lat.toFloat(&ok);
			float float_lon = str_lon.toFloat(&ok);

			latlon.lat = float_lat;
			latlon.lon = float_lon;

			//qDebug()<<"Lat : "<<float_lat<<", Lon : "<<float_lon;

			//latlonmng_list[curIndex-1].
			latlon_list.append(latlon);
			//latlonmng_list[idIndex-1].getLatlon_list().append(latlon);

			}
		}

		count++;

		for(int i = 0 ; i < latlonmng_list.size() ;i++ )
		{
			LatLonMng latlonmng = latlonmng_list.at(i);
			qDebug()<<"LAYER : "<<latlonmng.layer_name<<", ID : "<<latlonmng.getId_name();
			QVector<LatLon> latlon_list = latlonmng.getLatlon_list();
			for(int j = 0 ; j < latlon_list.size() ; j ++){
				LatLon latlon = latlon_list.at(j);
				//qDebug()<<"Lat : "<<latlon.lat<<", Lon : "<<latlon.lon;
			}
		}

		qDebug()<<"[LatLonToPixel] End of Reading File..";

		return true;
}

void LatLonToPixel::openFile()
{
	openedFile = new QFile(cfilename);
	if(!openedFile->open(QIODevice::ReadWrite | QIODevice::Text)){
		qDebug()<<"[RightLayout] Cannot open the file";
		return;
	}
}


/*
 * 파일을 프로세싱 한다.
 */
void LatLonToPixel::processingFile(QString str)
{
	//process lat lon

	str = str.remove(0,3);
	QStringList strList = str.split('E');

	LatLon latlon;
	bool ok;
	latlon.lat = strList[0].toFloat(&ok);
	latlon.lon = strList[1].toFloat(&ok);

	//latlon_list.append(latlon);
}

void LatLonToPixel::test()
{
//	for(int i = 0 ; i < latlon_list.size() ; i++)
//	{
//		LatLon latlon = latlon_list.at(i);
//		qDebug()<<"lat : "<<latlon.lat<<", lon : "<<latlon.lon;
//	}
}

int LatLonToPixel::long2tilex(double lon, int z)
{
	return (int)(floor((lon + 180.0) / 360.0 * pow(2.0, z)));
}

int LatLonToPixel::lat2tiley(double lat, int z)
{
//	return (int)(floor((1.0 - log( tan(lat * PI/180.0) + 1.0 / cos(lat * PI/180.0)) / PI) / 2.0 * pow(2.0, z)));
}

//RGB 정보 파싱
void LatLonToPixel::parsingColor(QString org_rgb, QColor * color)
{
	QStringList rgb = org_rgb.split(',');
	bool ok;
	int r = rgb.at(0).toInt(&ok, 10);
	int g = rgb.at(1).toInt(&ok, 10);
	int b = rgb.at(2).toInt(&ok, 10);
	//qDebug()<<"Color : "<<rgb.at(0).toInt(&ok, 10)<< rgb.at(1).toInt(&ok, 10)<< rgb.at(2).toInt(&ok, 10);
	color->setRgb(r, g, b);
	//qDebug()<<"Color : "<<layer_info.layer_color;
}
