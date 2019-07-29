/*
 * LatLonMng.cpp
 *
 *  Created on: 2013. 5. 15.
 *      Author: jiwon
 */

#include "LatLonMng.h"
#include "WGS84_TM.h"
#include <QDebug>

LatLonMng::LatLonMng()
{
	// TODO Auto-generated constructor stub
	isEnable = true;
	angle = 0;
}

LatLonMng::LatLonMng(LayerInfo info)
: LayerInfo(info)
{
	// TODO Auto-generated constructor stub

	isEnable = true;
}
LatLonMng::~LatLonMng() {
	// TODO Auto-generated destructor stub
}

/*
 * 위경도 좌표를 x, y 좌표로 변환한다..
 */

/*QVector<LatLon> LatLonMng::getConvertedLatLonList()
{
	QVector<LatLon> tmp;

	QVector<QPointF> converted_latlon_point_list;

	for(int i = 0 ; i < this->latlon_list.size() ; i++){
		LatLon cur_latlon = latlon_list.at(i);
		double x = 0;
		double y = 0;
		WGS84_TM::getInstance().LatLonConvert(x, y, (double)cur_latlon.lon, (double)cur_latlon.lat);
		LatLon new_latlon;
		new_latlon.lat = y;
		new_latlon.lon = x;

		QPointF converted_latlon_point;

		converted_latlon_point.setX(x);
		converted_latlon_point.setY(y);

		converted_latlon_point_list.append(converted_latlon_point);


		tmp.append(new_latlon);
		//qDebug()<<"Lat : "<<cur_latlon.lat<<", Lon : "<<cur_latlon.lon<<", X : "<<x<<", Y : "<<y;
	}

	//latlon_list = tmp;
	latlon_point_list = converted_latlon_point_list;	//X, Y 좌표로 변환됨

	//tmp = rotateLatLon();
	return tmp;
}*/

// TEST
QVector<LatLon> LatLonMng::getConvertedLatLonList()
{
	//리턴하는것은 LatLon 타입이며, 포인트로 저장하는 것은 QPointF 타입이다.
	QVector<LatLon> tmp;

	QVector<QPointF> converted_latlon_point_list;

	for(int i = 0 ; i < this->latlon_list.size() ; i++){
		LatLon cur_latlon = latlon_list.at(i);

		//도분추 -> 위경도
		QPointF latlonDecimal;
		latlonDecimal.setY(WGS84_TM::getInstance().MinSecond2Degree(cur_latlon.lon));
		latlonDecimal.setX(WGS84_TM::getInstance().MinSecond2Degree(cur_latlon.lat));

		//qDebug()<<"lonDD : "<<latlonDecimal.x()<<", lat : " <<latlonDecimal.y();

		QPointF pointLatLon = LatLonConvert::getInstance().latlonToScreen(latlonDecimal);

		//qDebug()<<"prePoint : "<<latlonDecimal<<", newPoint : "<<pointLatLon;

		LatLon new_latlon;
		new_latlon.lat = pointLatLon.y();
		new_latlon.lon = pointLatLon.x();

		//qDebug()<<"[LatLonMng - getConvertedlatLonList] lat : "<<new_latlon.lat<<", lon : "<<new_latlon.lon;

		QPointF converted_latlon_point;

		converted_latlon_point.setX(new_latlon.lon);
		converted_latlon_point.setY(new_latlon.lat);

		converted_latlon_point_list.append(converted_latlon_point);

		tmp.append(new_latlon);

	}

	//latlon_list = tmp;
	latlon_point_list = converted_latlon_point_list;	//X, Y 좌표로 변환됨

	//tmp = rotateLatLon();
	return tmp;
}



/*
 * angle 만큼 회전 한다.
 */
QVector<QPointF> LatLonMng::rotateLatLon(QVector<QPointF> point_list, int angle)
{
	//qDebug()<<"[LatLonMng] rotateLatLon is called..";
	double u = 0;
	double v = 0;
	qreal wx = 2500;
	qreal wy = 2500;
	QVector<QPointF> new_point_list;

	for(int i = 0 ; i < point_list.size() ; i++){
		QPointF cur_point = point_list.at(i);
		double x = cur_point.x();
		double y = cur_point.y();
		QPointF new_point;

		new_point.setX((((x - u) * cos(M_PI/180*angle) + (y - v)*sin(M_PI/180*angle)) + u ) + wx);
		new_point.setY((((x - u) * -sin(M_PI/180*angle) + (y - v)*cos(M_PI/180*angle)) + v ) + wy);
		//qDebug()<<"ox : "<<x<<", oy : "<<y;
		//qDebug()<<"nx : "<<new_point.x()<<", yx : "<<new_point.y();
		new_point_list.append(new_point);
	}

	//qDebug()<<"[LatLonMng] rotateLatLon is close..";

//	latlon_list = tmp;
	return new_point_list;
}


/*
 * angle 만큼 회전 한다.
 */
QVector<LatLon> LatLonMng::rotateLatLon(QVector<LatLon> point_list, int angle)
{
	//qDebug()<<"[LatLonMng] rotateLatLon is called.. ID : "<<this->id_name;
	double u = 0;
	double v = 0;
	qreal wx = 0;
	qreal wy = 0;
	QVector<LatLon> new_point_list;

	for(int i = 0 ; i < point_list.size() ; i++){
		LatLon cur_point = point_list.at(i);
		double x = cur_point.lon;
		double y = cur_point.lat;
		LatLon new_point;

		new_point.lon = (((x - u) * cos(M_PI/180*angle) + (y - v)*sin(M_PI/180*angle)) + u ) + wx;
		new_point.lat = (((x - u) * -sin(M_PI/180*angle) + (y - v)*cos(M_PI/180*angle)) + v ) + wy;

	//	qDebug()<<"ox : "<<x<<", oy : "<<y;
	//	qDebug()<<"nx : "<<new_point.lon<<", yx : "<<new_point.lat;
		new_point_list.append(new_point);
	}

//	qDebug()<<"[LatLonMng] rotateLatLon is close..";

//	latlon_list = tmp;
	return new_point_list;
}



/**
 * 변경된 위경도 좌표를 QPointF 타입으로 반환..
 */
QVector<QPointF> LatLonMng::getConvertedLatLonList2QPointF()
{
	QVector<LatLon> tmp = getConvertedLatLonList();

	//wonjum
	qreal wx = 0;
	qreal wy = 0;

	//Angle 값이 0일 경우 기존데로 수행한다..
	QVector<QPointF> qpoint_latlon_list;
	for(int i = 0 ; i < tmp.size() ; i++)
	{
		LatLon latlon = tmp.at(i);
		QPointF qpoint_latlon;

		qpoint_latlon.setX(wx + (qreal)latlon.lon);
		qpoint_latlon.setY(wy + (qreal)latlon.lat);
		//qDebug()<<"Point : "<<qpoint_latlon;
	//	qDebug()<<"ID : "<<this->id_name<<"Lon : "<<latlon.lon<<", Lat : "<<latlon.lat;
		qpoint_latlon_list.append(qpoint_latlon);
	}

	return qpoint_latlon_list;

}


void LatLonMng::print()
{
	qDebug()<<"[LatLonMng] Layer : "<<layer_name<<", ID : "<<getId_name()<<", LineType : "<<layer_line_type
			<<", Line Color : "<<layer_line_color;
}

/*
 * POLYGON일 경우 맵 아이디를 그린다.
 */
QPointF LatLonMng::drawMapId()
{
	getConvertedLatLonList();
	//qDebug()<<"drawMapId is called.. point list size : "<<latlon_point_list.size();

	//Polygon일 경우,  x 좌표 좌끝점과 y 좌표 위아래 끝점을 구한 중간 값을 리턴한다..
	QPointF left;
	QPointF upper;
	QPointF bottom;
	QPointF right;

	QPointF tmpPoint;
	tmpPoint.setX(0);
	tmpPoint.setY(0);
	//좌측 좌표 구하기
	for(int i = 0 ; i < this->latlon_point_list.size() ; i++){
		QPointF cPoint = latlon_point_list.at(i);
		//WGS84_TM::getInstance().LatLonConvert(cPoint.rx(), cPoint.ry(), latlon.lon, latlon.lat);

		if(i == 0){
			tmpPoint = cPoint;
		}else{

			if(tmpPoint.x() > cPoint.x()){
				tmpPoint = cPoint;
			}
		}
	}
	left.setX(tmpPoint.x());
	left.setY(tmpPoint.y());



	//우측 좌표 구하
	tmpPoint.setX(0);
	tmpPoint.setY(0);
	for(int i = 0 ; i < this->latlon_point_list.size() ; i++){
		QPointF cPoint = latlon_point_list.at(i);

		//WGS84_TM::getInstance().LatLonConvert(cPoint.rx(), cPoint.ry(), latlon.lon, latlon.lat);


		if(tmpPoint.x() < cPoint.x()){
			tmpPoint = cPoint;
		}

	}

	right.setX(tmpPoint.x());
	right.setY(tmpPoint.y());

	//윜 좌표 구하
	tmpPoint.setX(0);
	tmpPoint.setY(0);
	for(int i = 0 ; i < this->latlon_point_list.size() ; i++){
		QPointF cPoint = latlon_point_list.at(i);


		//WGS84_TM::getInstance().LatLonConvert(cPoint.rx(), cPoint.ry(), latlon.lon, latlon.lat);

		if(i == 0){
			tmpPoint = cPoint;
		}else{

			if(tmpPoint.y() > cPoint.y()){
				tmpPoint = cPoint;
			}
		}
	}

	upper.setX(tmpPoint.x());
	upper.setY(tmpPoint.y());


	//아래쪽 좌표 구하쪽
	tmpPoint.setX(0);
	tmpPoint.setY(0);
	for(int i = 0 ; i < this->latlon_point_list.size() ; i++){
		QPointF cPoint = latlon_point_list.at(i);

//		WGS84_TM::getInstance().LatLonConvert(cPoint.rx(), cPoint.ry(), latlon.lon, latlon.lat);



		if(tmpPoint.y() < cPoint.y()){
			tmpPoint = cPoint;
		}
	}

	bottom.setX(tmpPoint.x());
	bottom.setY(tmpPoint.y());

	QPointF centerPoint;

	centerPoint.setX((right.x() - left.x())/2 + left.x());
	centerPoint.setY((bottom.y() - upper.y())/2 + upper.y());


	//qDebug()<<"ID : "<<this->id_name<<", Left : "<<left<<", Right : "<<right<<", Upper : "<<upper<<", Bottom : "<<bottom;
	//qDebug()<<"Center : "<<centerPoint;


	return centerPoint;

}

void LatLonMng::setAngle(int angle)
{
	this->angle = angle;
}
