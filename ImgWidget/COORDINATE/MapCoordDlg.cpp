/*
 * MapCoordDlg.cpp
 *
 *  Created on: 2013. 6. 3.
 *      Author: jiwon
 */

#include "MapCoordDlg.h"
#include "../lib/DataValidator.h"
#include "../lib/WGS84_TM.h"

MapCoordDlg::MapCoordDlg(QDialog * parent)
: QDialog(parent)
{
	// TODO Auto-generated constructor stub


	init();
	maskText();
}

void MapCoordDlg::init()
{
	cvtPoint = new ConvertPoint;
	btnOk = new QPushButton(tr("Ok"));
	btnCancel = new QPushButton(tr("Cancel"));
	btnConvert = new QPushButton(tr("WGS To DMS"));
	btnDmsWgsConvert = new QPushButton(tr("DMS To WGS"));
	txtLat = new QLineEdit;
	txtLon = new QLineEdit;
	chkSymbol = new QCheckBox;

	txtWgLat = new QLineEdit;
	txtWgLon = new QLineEdit;
	txtDmsLat = new QLineEdit;
	txtDmsLon = new QLineEdit;

	//test
	txtAngle = new QLineEdit;
	txtDist = new QLineEdit;
	txtResult = new QLineEdit;

	connect(txtLat, SIGNAL(textChanged(const QString &)), this,SLOT(checkLat(const QString &)));
	connect(txtLon, SIGNAL(textChanged(const QString &)), this,SLOT(checkLon(const QString &)));
	connect(btnOk, SIGNAL(clicked()), this, SLOT(runGetNewPoint()));
	connect(btnCancel, SIGNAL(clicked()), this, SLOT(close()));
	connect(btnConvert, SIGNAL(clicked()), this, SLOT(runConvert()));
	connect(btnDmsWgsConvert, SIGNAL(clicked()), this, SLOT(runDmsWgsConvert()));

	QLabel * lblLat = new QLabel(tr("<h4>LAT : "));
	QLabel * lblLon = new QLabel(tr("<h4>LON : "));
	QLabel * lblHead = new QLabel(tr("<h2>MAP COORDINATES"));
	QLabel * lblSymbol = new QLabel(tr("Mark"));

	QLabel * lblCHead = new QLabel(tr("<h2>CONVERT"));
	QLabel * lblWLat = new QLabel(tr("<h4>WGS LAT : "));
	QLabel * lblWLon = new QLabel(tr("<h4>WGS LON : "));

	QLabel * lblDLat = new QLabel(tr("<h4>DMS LAT : "));
	QLabel * lblDLon = new QLabel(tr("<h4>DMS LON : "));

	//new
	QLabel * lblAngle = new QLabel("Angle : ");
	QLabel * lblDist = new QLabel("Dist : ");

	QHBoxLayout * hbox = new QHBoxLayout;
	QHBoxLayout * hbox2 = new QHBoxLayout;
	QHBoxLayout * hbox3 = new QHBoxLayout;
	QHBoxLayout * hbox4 = new QHBoxLayout;
	QVBoxLayout * vbox = new QVBoxLayout;

	QHBoxLayout * hbox5 = new QHBoxLayout;

	hbox->addWidget(lblLat);
	hbox->addWidget(txtLat);
	hbox->addWidget(lblLon);
	hbox->addWidget(txtLon);
	hbox->addWidget(lblSymbol, 10);
	hbox->addWidget(chkSymbol);

	hbox5->addWidget(lblAngle);
	hbox5->addWidget(txtAngle);
	hbox5->addWidget(lblDist);
	hbox5->addWidget(txtDist);
	hbox5->addWidget(txtResult);


	hbox3->addWidget(lblWLat);
	hbox3->addWidget(txtWgLat);
	hbox3->addWidget(lblWLon);
	hbox3->addWidget(txtWgLon);

	hbox4->addWidget(lblDLat);
	hbox4->addWidget(txtDmsLat);
	hbox4->addWidget(lblDLon);
	hbox4->addWidget(txtDmsLon);



	hbox2->addWidget(btnOk);
	hbox2->addWidget(btnCancel);
	hbox2->addWidget(btnConvert);
	hbox2->addWidget(btnDmsWgsConvert);

	vbox->addWidget(lblHead);
	vbox->addLayout(hbox);
	vbox->addLayout(hbox5);
	vbox->addWidget(lblCHead);
	vbox->addLayout(hbox3);
	vbox->addLayout(hbox4);
	vbox->addLayout(hbox2);



	this->setLayout(vbox);
	qDebug()<<"init end..";
}

MapCoordDlg::~MapCoordDlg() {
	// TODO Auto-generated destructor stub
}


void MapCoordDlg::maskText()
{
	txtLat->setInputMask("A00:00:00.00;_");
	txtLon->setInputMask("A000:00:00.00;_");

	txtWgLat->setInputMask("A00:00:00.00;_");
	txtWgLon->setInputMask("A000:00:00.00;_");

	txtDmsLat->setInputMask("A00:00:00.00;_");
	txtDmsLon->setInputMask("A000:00:00.00;_");
	qDebug()<<"mask end..";
}


void MapCoordDlg::checkLat(const QString & str)
{
	qDebug()<<"checkLat is called..str : "<<str;

	//DataValidator::getInstance().IsLatitude(str);
	cvtPoint->validatorLatitude(txtLat);

}

void MapCoordDlg::checkLon(const QString & str)
{
	qDebug()<<"checkLon is called..str : "<<str;
	cvtPoint->validatorLongitude(txtLon);
}

void MapCoordDlg::runOk()
{
	//좌표 입력 한뒤 close 한다..
	if(!DataValidator::getInstance().IsLatitude(txtLat->text())){
		return;
	}

	if(!DataValidator::getInstance().IsLongitude(txtLon->text())){
		return;
	}

	if(chkSymbol->checkState() == Qt::Checked){
		emit emitRunOk(txtLat, txtLon, 1);
	}else{
		emit emitRunOk(txtLat, txtLon, 0);
	}

	qDebug()<<"Dialog will be closed..";
	close();
}

void MapCoordDlg::runConvert()
{
	bool ok;

	QString wgslat = txtWgLat->text();
	QString wgslon = txtWgLon->text();

	wgslat = wgslat.remove(0,1);
	wgslon = wgslon.remove(0, 1);

	wgslat.replace(":","");
	wgslat.replace(".", "");

	wgslon.replace(":","");
	wgslon.replace(".", "");

	wgslat.insert(2, ".");
	wgslon.insert(3, ".");


	double dlat = wgslat.toDouble(&ok);
	double dlon = wgslon.toDouble(&ok);

	dlat = WGS84_TM::getInstance().LatLon2DMS(&dlat);
	dlon = WGS84_TM::getInstance().LatLon2DMS(&dlon);

	qDebug()<<"CLat : "<<QString::number(dlat, 'f', 6)<<", CLON : "<<QString::number(dlon, 'f', 6);

	txtDmsLat->setText(QString::number(dlat, 'f', 6).prepend("N").replace(".", ""));
	txtDmsLon->setText(QString::number(dlon, 'f', 6).prepend("E").replace(".", ""));

}

void MapCoordDlg::runDmsWgsConvert()
{
	bool ok;

	QString dmslat = txtDmsLat->text();
	QString dmslon = txtDmsLon->text();

	dmslat = dmslat.remove(0,1);
	dmslon = dmslon.remove(0, 1);

	dmslat.replace(":","");
	dmslat.replace(".", "");

	dmslon.replace(":","");
	dmslon.replace(".", "");

	dmslat.insert(2, ".");
	dmslon.insert(3, ".");


	double dlat = dmslat.toDouble(&ok);
	double dlon = dmslon.toDouble(&ok);

	dlat = WGS84_TM::getInstance().MinSecond2Degree(dlat);
	dlon = WGS84_TM::getInstance().MinSecond2Degree(dlon);

	qDebug()<<"CLat : "<<QString::number(dlat, 'f', 6)<<", CLON : "<<QString::number(dlon, 'f', 6);

	txtWgLat->setText(QString::number(dlat, 'f', 6).prepend("N").replace(".", ""));
	txtWgLon->setText(QString::number(dlon, 'f', 6).prepend("E").replace(".", ""));
}


//활주로의 연장선을 드로잉 한다..
void MapCoordDlg::runGetNewPoint()
{
	GlobalMath * gmath = new GlobalMath;
	bool ok;
	QString lat = txtLat->text();
	QString lon = txtLon->text();

	lat = lat.remove(0,1);
	lon = lon.remove(0, 1);

	lat.replace(":","");
	lat.replace(".", "");

	lon.replace(":","");
	lon.replace(".", "");

	lat.insert(2, ".");
	lon.insert(3, ".");

	double dlat = lat.toDouble(&ok);
	double dlon = lon.toDouble(&ok);

	QPointF latlonDecimal;
	latlonDecimal.setY(WGS84_TM::getInstance().MinSecond2Degree(dlon));
	latlonDecimal.setX(WGS84_TM::getInstance().MinSecond2Degree(dlat));

	//도분초 지점값을 xy 좌표로 변환
	QPoint npoint = LatLonConvert::getInstance().latlonToScreen(latlonDecimal);

	qDebug()<<"New Point : "<<npoint;
	//angle 값과 dist 값을


	int angle = txtAngle->text().toInt(&ok, 10);
	int dist = txtDist->text().toInt(&ok, 10);

	qDebug()<<"angle : "<<angle<<", dist : "<<dist;
	QVector<QPointF> point_list = gmath->getPoint(npoint, 0, dist);

	qDebug()<<"p1 : "<<point_list.at(0)<<", p2 : "<<point_list.at(1);

	//Angle 값만큼 회전 시킨다.

	QPointF rotated_point = gmath->rotateLatLon(npoint, point_list.at(0), angle);		//회전된 최종 포인트

	QString res_latlon = LatLonConvert::getInstance().screenToLatLon(rotated_point.toPoint());
	//QString res_latlon2 = LatLonConvert::getInstance().screenToLatLon(point_list.at(1).toPoint());
	QString orgin_latlon = LatLonConvert::getInstance().screenToLatLon(npoint);


	txtResult->setText(res_latlon.append(", ").append(orgin_latlon));

	//qDebug()<<"30 rotated.. : "<<gmath->rotateLatLon(npoint, point_list.at(0), 30);



	//2킬로 마다 거리가 1킬로미터인 수직인 선을 긋는다..

	int nline_angle = 90 - angle;

	QVector<QPointF> nline_point_list = gmath->getPoint(rotated_point, 0, 100);

	QPointF rotated_point_1 = gmath->rotateLatLon(rotated_point, nline_point_list.at(0), 150);
	QPointF rotated_point_2 = gmath->rotateLatLon(rotated_point, nline_point_list.at(0), 330);

	qDebug()<<"exline_1: "<<LatLonConvert::getInstance().screenToLatLon(rotated_point_1.toPoint());
	qDebug()<<"exline_2: "<<LatLonConvert::getInstance().screenToLatLon(rotated_point_2.toPoint());

}
