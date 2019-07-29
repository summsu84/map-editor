/*
 * WGS84_TM.cpp
 *
 *  Created on: 2013. 5. 15.
 *      Author: jiwon
 */

#include "WGS84_TM.h"
#include <QDebug>
WGS84_TM * WGS84_TM::pinstance = NULL;
WGS84_TM::WGS84_TM() {
	// TODO Auto-generated constructor stub
	scale = 1;
}

WGS84_TM::~WGS84_TM() {
	// TODO Auto-generated destructor stub
}


//도를 라디안으로 변환
double WGS84_TM::Deg2Rad(double Degree)
{
	return Degree*M_PI/180.;
}

//라디안을 도로 변환
double WGS84_TM::Rad2Deg(double Radian)
{
	return Radian*180./M_PI;
}


void WGS84_TM::_TM2Bessel(double tm_x, double tm_y, double lonOrg, double latOrg, double *lon, double *lat)
{
	// TM -> Bessel

	double x = tm_x;
	double y = tm_y;

	// phi_prime을 계산하기 위한 초기치 산정....
	double for_calcult_phi1 = x / (a*(1.-e_squre)*A);
	double phi1 = Deg2Rad(latOrg) + for_calcult_phi1;
	// phi1 값을 이용해서 iteration 수행.....
	double phi0 = Deg2Rad(latOrg);

	while(1) {
		double B1 = a*(1-e_squre)*(A*(phi1-phi0)
			- 1./2. *B*(sin(2. *phi1) - sin(2.*phi0))
			+ 1./4. *C*(sin(4. *phi1) - sin(4.*phi0))
			- 1./6. *D*(sin(6. *phi1) - sin(6.*phi0))
			+ 1./8. *E*(sin(8. *phi1) - sin(8.*phi0))
			- 1./10.*F*(sin(10.*phi1) - sin(10.*phi0)));

		double phi2 = phi1 + (x - B1) / (a*(1.-e_squre)*A);

		if(fabs(x - B1) < 0.00000001) break;
		else phi1 = phi2;
	}

	double W1 = sqrt(1.-e_squre*pow(sin(phi1),2.));
	double N1 = a / W1;
	double M1 = a * (1.- e_squre) / pow(W1,3.);
	M1 = 635604.152;
	double eta1_squre = e_prime_squre*pow(cos(phi1),2.);
	double t1 = tan(phi1);

	double t1_squre = t1*t1;

	double phi_b1 = t1/(2. *pow(N1,2.))*(1.+eta1_squre);
	double phi_b2 = t1/(24. *pow(N1,4.))*(5. + 3. *t1_squre +6.*eta1_squre -6*t1_squre*eta1_squre-3.*pow(eta1_squre,2.)-9.*t1_squre*pow(eta1_squre,2.));
	double phi_b3 = t1/(720. *pow(N1,6.))*(61. + 90. *t1_squre +45.*pow(eta1_squre,2.)+107.*eta1_squre-162.*t1_squre*eta1_squre-45.*pow(t1_squre,2.)*eta1_squre);
	double phi_b4 = t1/(40320.*pow(N1,8.))*(1385.+3633.*t1_squre +4095.*pow(eta1_squre,2.) +1575*pow(eta1_squre,3.));

	double lambda_b1 = 1./(N1*cos(phi1));
	double lambda_b2 = 1. /6. * 1./(pow(N1,3.)*cos(phi1))*(1.+2.*pow(t1,2.)+eta1_squre);
	double lambda_b3 = 1./120 * 1./(pow(N1,5.)*cos(phi1))*(5.+28.*t1_squre+24.*pow(t1_squre,2.)+6.*eta1_squre+8.*t1_squre*eta1_squre);
	double lambda_b4 = 1./5040.* 1./(pow(N1,7.)*cos(phi1))*(61.+662.*t1_squre+1320.*pow(t1_squre,2.) + 720.*pow(t1_squre,3.));

	double phi = phi1
		- phi_b1*pow(y,2.)
		+ phi_b2*pow(y,4.)
		- phi_b3*pow(y,6.)
		+ phi_b4*pow(y,8.);


	double lambda = lambda_b1*y
		- lambda_b2*pow(y,3.)
		+ lambda_b3*pow(y,5.)
		- lambda_b4*pow(y,7.);

	// 계산된 라디안 값을 백분 Degree로 바꾸어줌....
	*lat = Rad2Deg(phi);
	*lon = Rad2Deg(lambda)+lonOrg;
}


void WGS84_TM::_Bessel2TM(double lon, double lat, double lonOrg, double latOrg, double *tm_x, double *tm_y)
{
	// Bessel -> TM

	double phi = Deg2Rad(lat);
	double lambda= Deg2Rad(lon);

	double phi_0 = Deg2Rad(latOrg); // 원점.

	double for_B = a*(1-e_squre)*(A*(phi-phi_0)
		- 1./2. *B*(sin(2. *phi) - sin(2. *phi_0))
		+ 1./4. *C*(sin(4. *phi) - sin(4. *phi_0))
		- 1./6. *D*(sin(6. *phi) - sin(6. *phi_0))
		+ 1./8. *E*(sin(8. *phi) - sin(8. *phi_0))
		- 1./10.*F*(sin(10.*phi) - sin(10.*phi_0)));

	//계산을 위한 값들....
	double t = tan(phi);
	double eta = sqrt(e_prime_squre)*cos(phi); // eta_squre(eta^2 = e_prime_squre* cos^2 phi
	double N = a / sqrt(1 - e_squre * pow(sin(phi),2.));

	//Gauss-Kruger Projection 식.....
	double Delta_lambda = lambda - Deg2Rad(lonOrg);

	double x = for_B + pow(Delta_lambda,2.) / 2. * N * sin(phi) * pow(cos(phi),1.)
		+ pow(Delta_lambda,4.) / 24. * N * sin(phi) * pow(cos(phi),3.)*(5.- pow(t,2.) + 9.*pow(eta,2.) + 4.*pow(eta,4.))
		+ pow(Delta_lambda,6.) / 720. * N * sin(phi) * pow(cos(phi),5.)*(61. - 58.*pow(t,2) + pow(t,2.) + 270. * pow(eta,2) - 330 * pow(t,2) * pow(eta,2))
		+ pow(Delta_lambda,8.) / 40320.* N * sin(phi) * pow(cos(phi),7.)*(1385. - 3111.*pow(t,2.) + 543. * pow(t,4.) - pow(t,6.));


	double y = Delta_lambda * N * cos(phi)
		+ pow(Delta_lambda,3.) / 6. * N * pow(cos(phi),3.)*(1-pow(t,2.) + pow(eta,2.))
		+ pow(Delta_lambda,5.) / 120. * N * pow(cos(phi),5.)*(5.- 18.*pow(t,2.) + pow(t,4.) + 14.* pow(eta,2.) - 58.*pow(t,2.)*pow(eta,2))
		+ pow(Delta_lambda,7.) / 5040. * N * pow(cos(phi),7.)*(61. - 479.*pow(t,2) + 179.*pow(t,4.) - pow(t,6.));

	*tm_x = nTMScaleFacter*x;
	*tm_y = nTMScaleFacter*y;
}

//Test original
/*void WGS84_TM::_Bessel2TM(double lon, double lat, double lonOrg, double latOrg, double *tm_x, double *tm_y)
{
	// Bessel -> TM

	double phi = Deg2Rad(lat);
	double lambda= Deg2Rad(lon);

	double phi_0 = Deg2Rad(latOrg); // 원점.

	double for_B = a*(1-e_squre)*(A*(phi-phi_0)
		- 1./2. *B*(sin(2. *phi) - sin(2. *phi_0))
		+ 1./4. *C*(sin(4. *phi) - sin(4. *phi_0))
		- 1./6. *D*(sin(6. *phi) - sin(6. *phi_0))
		+ 1./8. *E*(sin(8. *phi) - sin(8. *phi_0))
		- 1./10.*F*(sin(10.*phi) - sin(10.*phi_0)));

	//계산을 위한 값들....
	double t = tan(phi);
	double eta = sqrt(e_prime_squre)*cos(phi); // eta_squre(eta^2 = e_prime_squre* cos^2 phi
	double N = a / sqrt(1 - e_squre * pow(sin(phi),2.));

	//Gauss-Kruger Projection 식.....
	double Delta_lambda = lambda - Deg2Rad(lonOrg);

	double x = for_B + pow(Delta_lambda,2.) / 2. * N * sin(phi) * pow(cos(phi),1.)
		+ pow(Delta_lambda,4.) / 24. * N * sin(phi) * pow(cos(phi),3.)*(5.- pow(t,2.) + 9.*pow(eta,2.) + 4.*pow(eta,4.))
		+ pow(Delta_lambda,6.) / 720. * N * sin(phi) * pow(cos(phi),5.)*(61. - 58.*pow(t,2) + pow(t,2.) + 270. * pow(eta,2) - 330 * pow(t,2) * pow(eta,2))
		+ pow(Delta_lambda,8.) / 40320.* N * sin(phi) * pow(cos(phi),7.)*(1385. - 3111.*pow(t,2.) + 543. * pow(t,4.) - pow(t,6.));


	double y = Delta_lambda * N * cos(phi)
		+ pow(Delta_lambda,3.) / 6. * N * pow(cos(phi),3.)*(1-pow(t,2.) + pow(eta,2.))
		+ pow(Delta_lambda,5.) / 120. * N * pow(cos(phi),5.)*(5.- 18.*pow(t,2.) + pow(t,4.) + 14.* pow(eta,2.) - 58.*pow(t,2.)*pow(eta,2))
		+ pow(Delta_lambda,7.) / 5040. * N * pow(cos(phi),7.)*(61. - 479.*pow(t,2) + 179.*pow(t,4.) - pow(t,6.));

	*tm_x = nTMScaleFacter*x;
	*tm_y = nTMScaleFacter*y;
}*/

void WGS84_TM::Bessel2TM(double alt, double lon, double lat, double lonOrg, double latOrg, double *tm_x, double *tm_y)
{
	//lat과 lon을 변경함..
	double R0 = 6378137.0;	// 지구 장축 길이
	double e = 0.081819191;	// 이심률

	double phi = Deg2Rad(lon);
	cout<<"PHI : "<<phi<<endl;
	double den = sqrt(1 - e*e*sin(phi)*sin(phi));
	double RN = R0*(1 - e*e)/(den*den*den);
	double RE = R0/den;

	// 우리나라 TM(Transverse Mercator) 좌표계 원점들의 경위도 값
	// x-축 : 남북 방향, 북쪽이 +
	// y-축 : 동서 방향, 동쪽이 +
	*tm_x = (RN + alt)*Deg2Rad(lon - lonOrg);
	*tm_y = (RE + alt)*Deg2Rad(lat - latOrg)*cos(phi);
}

/**
 *  X, Y 좌표를 위경도 좌표로 변환
 */

void WGS84_TM::TM2Bessel(double alt, double * lon, double  * lat, double lonOrg, double latOrg, double tm_x, double tm_y)
{
	//lat과 lon을 변경함..
	double R0 = 6378137.0;	// 지구 장축 길이
	double e = 0.081819191;	// 이심률

	double phi = Deg2Rad(*lon);
	double den = sqrt(1 - e*e*sin(phi)*sin(phi));
	double RN = R0*(1 - e*e)/(den*den*den);
	double RE = R0/den;

	// 우리나라 TM(Transverse Mercator) 좌표계 원점들의 경위도 값
	// x-축 : 남북 방향, 북쪽이 +
	// y-축 : 동서 방향, 동쪽이 +


	//*tm_x = (RN + alt)*Deg2Rad(lon - lonOrg);

	*lon = ((tm_x / (RN + alt)) * 180/M_PI) + lonOrg;

	phi = Deg2Rad(*lon);
	den = sqrt(1 - e*e*sin(phi)*sin(phi));
	RN = R0*(1 - e*e)/(den*den*den);
	RE = R0/den;

	//*tm_y = (RE + alt)*Deg2Rad(lat - latOrg)*cos(phi);

	*lat = ((tm_y / (RE + alt)) * 180/M_PI) /cos(phi) + latOrg;

}



/*
 * Added
 * 도분초를 위경도 형식으로 변환
 */
double WGS84_TM::MinSecond2Degree(double num)
{
	int a1 = (int)num;			//정수 부분

	double a2 = (num - a1) * 100;
	//qDebug()<<"a2 ; "<<a2<<", (int)a2 : "<<(int)a2;
	int inta2 = (int)a2;
	a2 = (double)inta2 / 60;
	//qDebug()<<"(int)a2 / 60 : "<<a2;
	//qDebug()<<"Num - a1 : "<<num - a1<<", Num : "<<num;

	//소수점처리

	double a3 =  ((num * 100) - (a1 * 100 + inta2)) * 100;
	a3 = a3 / 3600;
			//((num - (num * 100)) * 100) / 3600;

	//qDebug()<<"a1 : "<<a1<<", a2 : "<<a2<<", a3 :"<<a3;

	double rest = a1 + a2 + a3;
	//cout<<"real number : "<<left_num<<", min : "<<r1<<", seconds : "<<r2<<", rest : "<<(float)rest<<endl;

	//qDebug()<<"Orginal Number : "<<QString::number(num, 'f', 6)<<", Converted Number : "<<QString::number(rest, 'f', 6);

	return rest;
}

/*
double WGS84_TM::MinSecond2Degree(double num)
{
	int left_num = (int)num;			//정수 부분
	double right_num = num - (double)left_num;

	double r1 = floor(100.*(right_num))/100;		//분
	double r2 = right_num - r1;
	r2 = floor(10000.*(r2))/10000;		//초
	r1 = (r1 * 100) / 60;
	r2 = (r2 * 10000) / 3600;

	double rest = (double)left_num + r1 + r2;
	//cout<<"real number : "<<left_num<<", min : "<<r1<<", seconds : "<<r2<<", rest : "<<(float)rest<<endl;

	return rest;
}
*/



/*
 * Added
 * 위경도를 도분초로 변환
 */
double WGS84_TM::LatLon2DMS(double * num)
{

	double degree = (int) *num;

	double min = (int)((*num - degree) * 60);

	double sec = ((*num - degree) - min/60) * 3600;



	double rest = degree + (min/100) + (sec/10000);

	*num = rest;

	//cout<<"Degree : "<<degree<<", Min : "<<min<<", Sec : "<<sec<<", Result : "<<*num<<endl;

	return rest;
}


void WGS84_TM::test()
{
	double alt = 1;
	//분초를 위경도 degree로 변환
	//도 + 분/60 + 초/3600
	/*double test = 35.1813;
	this->MinSecond2Degree(test);*/
	double lon = this->MinSecond2Degree(127.0100);
	double lat = 38.0000;
	double lonOrg = 127.0000;
	double latOrg = 38.0000;
	double x = 0;
	double y = 0;

	this->Bessel2TM(alt, lon, lat, lonOrg, latOrg, &x, &y);

	//cout<<"X : "<<y<<", Y : "<<x<<endl;
}

/*
 * 위경도를 XY 좌표로 변환
 */
void WGS84_TM::LatLonConvert(double & x, double & y, double lon, double lat)
{
	double alt = 1;

	double tmplon = lon;
	double tmplat = lat;

	lon = MinSecond2Degree(lon);
	lat = MinSecond2Degree(lat);
	//중부 원점
	double lonOrg = 127.0000;
	double latOrg = 38.0000;

	_Bessel2TM(lon, lat, lonOrg, latOrg, &x, &y);
	//_Bessel2TM(lat, lon, latOrg, lonOrg, &x, &y);
	//km로 표시
	x = (x / 1000) * scale;
	y = (y / 1000) * scale;

	//cout<<"OrgLat : "<<tmplat<<", ConLat : "<<lat<<", OrgLon : "<<tmplon<<", ConLon : "<<lon<<endl;
}

/*
 * XY 좌표를 위경도로 변환
 */

void WGS84_TM::XYConvert(double tm_x, double tm_y, double *lon, double *lat, int angle)
{

//	qDebug()<<"[Before] X : "<<tm_x<<", Y : "<<tm_y;
	double lonOrg = 127.0000;
	double latOrg = 38.0000;
	double alt = 1;

	//X, Y의 원래 좌표로 변환한다. original

	/*tm_x = (tm_x - 2500) * 1000 ;
	tm_y = (tm_y - 2500)  * 1000;*/

	tm_x = ((tm_x - 2500) / scale);
	tm_y = ((tm_y - 2500) / scale);

	//qDebug()<<"[After] X : "<<tm_x<<", Y : "<<tm_y;

	if(angle != 0){
		QPointF tmp = this->rotateLatLon(QPointF(tm_x, tm_y), angle);

		tm_x = tmp.x();
		tm_y = tmp.y();

		tm_x = tm_x * 1000 * -1;
		tm_y = tm_y * 1000 * -1;
	}else{
		tm_x *= 1000 * scale;
		tm_y *= 1000 * scale;
	}

/*
	tm_x = tm_x * 1000;
	tm_y = tm_y * 1000;
*/

	//qDebug()<<"[Roated After] X : "<<tm_x<<", Y : "<<tm_y;

	_TM2Bessel(tm_x,  tm_y,  lonOrg,  latOrg,  lon, lat);
	//TM2Bessel(alt, lon, lat, lonOrg, latOrg, tm_x, tm_y);
	double tmplon = *lon;
	double tmplat = *lat;
	LatLon2DMS(lat);
	LatLon2DMS(lon);

	//cout<<"OrgLat : "<<tmplat<<", ConLat : "<<*lat<<", OrgLon : "<<tmplon<<", ConLon : "<<*lon<<endl;
}


void WGS84_TM::getDistanceFromOneDegree(double &x, double &y)
{
	double alt = 1;

	double lon = 127.0000;
	double lat = 37.5900;

	lon = MinSecond2Degree(lon);
	lat = MinSecond2Degree(lat);

	//qDebug()<<"[WGS84_TM]"<<"lon : "<<lon <<", lat : "<<lat;

	//중부 원점
	double lonOrg = 127.0000;
	double latOrg = 38.0000;

	//_Bessel2TM(lon, lat, lonOrg, latOrg, &x, &y);
	_Bessel2TM(lat, lon, latOrg, lonOrg, &x, &y);
	//km로 표시
	x = x / 1000;
	y = y / 1000;

}



/**
 * 지도상의 두 좌표 사이의 거리를 구한다.
 * 이때 위경도를 반영하여 구한다. 왜냐 하면 위도에 따라서 경도의 길이가 달라지기 때문이다..
 */
void WGS84_TM::getDistance(double x1, double y1, double x2, double y2)
{
	//1. 우선 위경도 값으로 변환한다.
	double lat1 = 0;
	double lon1 = 0;
	double lat2 = 0;
	double lon2 = 0;

	this->XYConvert(x1, y1, &lon1, &lat1);
	this->XYConvert(x2, y2, &lon2, &lat2);

	//qDebug()<<"Converted... Lat1 : "<<lat1<<", Lon1 : "<<lon1<<", Lat2 : "<<lat2<<", Lon2 : "<<lon2;

	double dlon = fabs((lon2 - lon1) * M_PI/180);
	double dlat = fabs((lat2 - lat1) * M_PI/180);

	double s = fabs((pow(sin(dlat/2), 2) + cos(lat1 * M_PI/180) * cos(lat2 * M_PI/180) * pow(sin(dlon/2), 2)));

	double dis = 2 * a * asin(sqrt(s));

	qDebug()<<"Dis : "<<dis;

}

void WGS84_TM::getDistance(QPointF p1, QPointF p2)
{
	getDistance(p1.x(), p1.y(), p2.x(), p2.y());
}


/*
 * ANGLE 값만 큼 회전한다..
 */
QPointF WGS84_TM::rotateLatLon(QPointF cur_point, int angle)
{
	//qDebug()<<"[LatLonMng] rotateLatLon is called..";
	double u = 0;
	double v = 0;

	QPointF new_point;

	double x = cur_point.x();
	double y = cur_point.y();

	new_point.setX((((x - u) * cos(M_PI/180*angle) + (y - v)*sin(M_PI/180*angle)) + u ) );
	new_point.setY((((x - u) * -sin(M_PI/180*angle) + (y - v)*cos(M_PI/180*angle)) + v ));

	//qDebug()<<"ox : "<<x<<", oy : "<<y;
	//qDebug()<<"nx : "<<new_point.x()<<", yx : "<<new_point.y();
	//qDebug()<<"[LatLonMng] rotateLatLon is close..";

//	latlon_list = tmp;
	if(angle == 180){
		new_point.setX(new_point.x() * -1);
		new_point.setY(new_point.y() * -1);
	}
	return new_point;
}
