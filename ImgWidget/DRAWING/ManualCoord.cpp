/*
 * ManualCoord.cpp
 *
 *  Created on: 2013. 7. 10.
 *      Author: jiwon
 */

#include "ManualCoord.h"
#include <QSqlQueryModel>
using namespace::DS;

ManualCoord::ManualCoord(DrawingWidget * drawingWidget) : drawingWidget(drawingWidget){
	// TODO Auto-generated constructor stub

	dm = Initial;
	init();
	this->processMCDB();

}

ManualCoord::ManualCoord(DrawingWidget * drawingWidget, QVector<COORDINATE> cn_list, QGraphicsItem * item)
{
	dm = ReDrawing;
	coord_list = cn_list;
	grpItem = item;
	init();
	this->processMCDB();

}

ManualCoord::~ManualCoord() {
	// TODO Auto-generated destructor stub
}


void ManualCoord::init()
{
	index = 0;

	QVBoxLayout * mainLayout = new QVBoxLayout;

	QHBoxLayout * hboxLayout = new QHBoxLayout;

	hboxLayout->addWidget(initDrawType());
	hboxLayout->addWidget(initBondaryVia());

	QHBoxLayout * hboxLayout2 = new QHBoxLayout;

	hboxLayout2->addWidget(initLatLon());
	hboxLayout2->addWidget(initCenterLatLon());

	QHBoxLayout * hboxLayout3 = new QHBoxLayout;
	hboxLayout3->addWidget(initPoint());
	hboxLayout3->addWidget(initArcCircle());

	mainLayout->addLayout(hboxLayout);
	mainLayout->addLayout(hboxLayout2);
	mainLayout->addLayout(hboxLayout3);
	mainLayout->addLayout(initButtons());

	QGroupBox * mainGroup = new QGroupBox("Coordinate Info");
	mainGroup->setLayout(mainLayout);

	vboxMain = new QVBoxLayout;

	vboxMain->addWidget(dynamic_cast<QWidget *>(mainGroup));


	this->setLayout(vboxMain);

	grpLatLon->setEnabled(false);
	grpCenterLatLon->setEnabled(false);
	grpPoint->setEnabled(false);
	grpArcCircle->setEnabled(false);

	tblWidget = new QTableWidget;


	vboxMain->addWidget(tblWidget);

	genTable();

}

QWidget * ManualCoord::initDrawType()
{

	QGroupBox * grpBox = new QGroupBox("Draw Type");

	rdoPolyline = new QRadioButton(tr("Polyline"));
	rdoPolygon = new QRadioButton(tr("Polygon"));
	rdoCircle = new QRadioButton(tr("Circle"));
	rdoSymbol = new QRadioButton(tr("Symbol"));

	connect(rdoPolyline, SIGNAL(clicked()), this, SLOT(rdo_click()));
	connect(rdoPolygon, SIGNAL(clicked()), this, SLOT(rdo_click()));
	connect(rdoCircle, SIGNAL(clicked()), this, SLOT(rdo_click()));
	connect(rdoSymbol, SIGNAL(clicked()), this, SLOT(rdo_click()));


	QHBoxLayout * hbox = new QHBoxLayout;
	hbox->addWidget(rdoPolyline);
	hbox->addWidget(rdoPolygon);
	hbox->addWidget(rdoCircle);
	hbox->addWidget(rdoSymbol);

	hbox->addStretch(1);

	grpBox->setLayout(hbox);


	QWidget * widget = dynamic_cast<QWidget * >(grpBox);

	return widget;
}


QWidget * ManualCoord::initBondaryVia()
{

	QGroupBox * grpBox = new QGroupBox("Bondary Via");

	cboBndryVia = new QComboBox;

	cboBndryVia->addItem(tr("select via type.."), NONE);
	cboBndryVia->addItem(tr("Greate Circle"), GREATECIRCLE);
	cboBndryVia->addItem(tr("Rhumb Line"), RHUMBLINE);
	cboBndryVia->addItem(tr("Counter clockwise Arc"), COUNTERCLOCKWISEARC);
	cboBndryVia->addItem(tr("Clockwise Arc"), CLOCKWISEARC);
	cboBndryVia->addItem(tr("Circle"), BNCIRCLE);
	cboBndryVia->addItem(tr("Symbol"), BNSYMBOL);


	connect(cboBndryVia, SIGNAL(currentIndexChanged(int)), this, SLOT(runBndryChanged(int)));
	txtBndryVia = new QLineEdit;


	QHBoxLayout * hbox = new QHBoxLayout;
	hbox->addWidget(cboBndryVia);
	hbox->addWidget(txtBndryVia);

	hbox->addStretch(1);

	grpBox->setLayout(hbox);


	QWidget * widget = dynamic_cast<QWidget * >(grpBox);

	return widget;
}


QWidget * ManualCoord::initLatLon()
{
	QGroupBox * grpBox = new QGroupBox("Reference for Lat/Lon");

	grpLatLon = grpBox;

	QGridLayout * grid = new QGridLayout;

	QLabel * lblAirport = new QLabel(tr("Airport : "));
	QLabel * lblFix = new QLabel(tr("Fix : "));
	QLabel * lblNavaid = new QLabel(tr("Navaid :"));

	QLabel * lblRho = new QLabel(tr("Rho(NM"));
	QLabel * lblTheta = new QLabel(tr("Theta(o)"));

	cboAirport = new QComboBox;
	cboFix = new QComboBox;
	cboNavaid = new QComboBox;


	txtRhoAirport = new QLineEdit;
	txtRhoFix = new QLineEdit;
	txtRhoNavaid = new QLineEdit;

	txtThetaAirport = new QLineEdit;
	txtThetaFix = new QLineEdit;
	txtThetaNavaid = new QLineEdit;

	grid->addWidget(lblRho, 0, 2);
	grid->addWidget(lblTheta, 0, 3);

	grid->addWidget(lblAirport, 1, 0);
	grid->addWidget(cboAirport, 1, 1);
	grid->addWidget(txtRhoAirport, 1, 2);
	grid->addWidget(txtThetaAirport, 1, 3);

	grid->addWidget(lblFix, 2, 0);
	grid->addWidget(cboFix, 2, 1);
	grid->addWidget(txtRhoFix, 2, 2);
	grid->addWidget(txtThetaFix, 2, 3);

	grid->addWidget(lblNavaid, 3, 0);
	grid->addWidget(cboNavaid, 3, 1);
	grid->addWidget(txtRhoNavaid, 3, 2);
	grid->addWidget(txtThetaNavaid, 3, 3);

	btnApply = new QPushButton(tr("Apply"));
	grid->addWidget(btnApply, 4, 2);
	grpBox->setLayout(grid);

	connect(btnApply, SIGNAL(clicked()), this, SLOT(runApply()));

	QWidget * widget = dynamic_cast<QWidget * >(grpBox);

	return widget;

}


QWidget * ManualCoord::initCenterLatLon()
{
	QGroupBox * grpBox = new QGroupBox("Reference for Lat/Lon");

	grpCenterLatLon = grpBox;

	QGridLayout * grid = new QGridLayout;

	QLabel * lblAirport = new QLabel(tr("Airport : "));
	QLabel * lblFix = new QLabel(tr("Fix : "));
	QLabel * lblNavaid = new QLabel(tr("Navaid :"));

	QLabel * lblRho = new QLabel(tr("Rho(NM"));
	QLabel * lblTheta = new QLabel(tr("Theta(o)"));

	cboCenterAirport = new QComboBox;
	cboCenterFix = new QComboBox;
	cboCenterNavaid = new QComboBox;

	txtCenterRhoAirport = new QLineEdit;
	txtCenterRhoFix = new QLineEdit;
	txtCenterRhoNavaid = new QLineEdit;

	txtCenterThetaAirport = new QLineEdit;
	txtCenterThetaFix = new QLineEdit;
	txtCenterThetaNavaid = new QLineEdit;

	grid->addWidget(lblRho, 0, 2);
	grid->addWidget(lblTheta, 0, 3);

	grid->addWidget(lblAirport, 1, 0);
	grid->addWidget(cboCenterAirport, 1, 1);
	grid->addWidget(txtCenterRhoAirport, 1, 2);
	grid->addWidget(txtCenterThetaAirport, 1, 3);

	grid->addWidget(lblFix, 2, 0);
	grid->addWidget(cboCenterFix, 2, 1);
	grid->addWidget(txtCenterRhoFix, 2, 2);
	grid->addWidget(txtCenterThetaFix, 2, 3);

	grid->addWidget(lblNavaid, 3, 0);
	grid->addWidget(cboCenterNavaid, 3, 1);
	grid->addWidget(txtCenterRhoNavaid, 3, 2);
	grid->addWidget(txtCenterThetaNavaid, 3, 3);

	btnCenterApply = new QPushButton(tr("Apply"));
	grid->addWidget(btnCenterApply, 4, 2);
	grpBox->setLayout(grid);

	connect(btnCenterApply, SIGNAL(clicked()), this, SLOT(runCenterApply()));

	QWidget * widget = dynamic_cast<QWidget * >(grpBox);

	return widget;

}


QWidget * ManualCoord::initPoint()
{
	QGroupBox * grpBox = new QGroupBox("Point");

	grpPoint = grpBox;

	QLabel * lblLat = new QLabel(tr("Latitude:"));
	QLabel * lblLon = new QLabel(tr("Longitude:"));

	txtLat = new QLineEdit;
	txtLon = new QLineEdit;

	txtLat->setInputMask("A00:00:00.00;_");
	txtLon->setInputMask("A000:00:00.00;_");

	txtLat->setText("N");
	txtLon->setText("E");

	QGridLayout * grid = new QGridLayout;

	grid->addWidget(lblLat, 0, 0);
	grid->addWidget(txtLat, 0, 1);
	grid->addWidget(lblLon, 1, 0);
	grid->addWidget(txtLon, 1, 1);

	grpBox->setLayout(grid);

	QWidget * widget = dynamic_cast<QWidget * >(grpBox);

	return widget;
}

QWidget * ManualCoord::initArcCircle()
{
	QGroupBox * grpBox = new QGroupBox("Arc/Circle");

	grpArcCircle = grpBox;

	QLabel * lblLat = new QLabel(tr("Center Latitude:"));
	QLabel * lblLon = new QLabel(tr("Center Longitude:"));

	txtCenterLat = new QLineEdit;
	txtCenterLon = new QLineEdit;

	txtCenterLat->setInputMask("A00:00:00.00;_");
	txtCenterLon->setInputMask("A000:00:00.00;_");

	txtCenterLat->setText("N");
	txtCenterLon->setText("E");

	QGridLayout * grid = new QGridLayout;

	txtDist = new QLineEdit;
	txtBearing = new QLineEdit;

	txtDist->setInputMask("000.0;_");
	txtBearing->setInputMask("000.0;_");

	grid->addWidget(lblLat, 0, 0);
	grid->addWidget(txtCenterLat, 0, 1);
	grid->addWidget(txtDist, 0, 2);
	grid->addWidget(lblLon, 1, 0);
	grid->addWidget(txtCenterLon, 1, 1);
	grid->addWidget(txtBearing, 1, 2);


	grpBox->setLayout(grid);

	QWidget * widget = dynamic_cast<QWidget * >(grpBox);

	return widget;
}


QLayout * ManualCoord::initButtons()
{
	//initButtons

	QHBoxLayout * layout = new QHBoxLayout;

	int mWidth = 100;
	btnInsert = new QPushButton(tr("Insert"));
	btnInsert->setMaximumWidth(mWidth);
	btnUpdate = new QPushButton(tr("Update"));
	btnUpdate->setMaximumWidth(mWidth);
	btnDelete = new QPushButton(tr("Delete"));
	btnDelete->setMaximumWidth(mWidth);
	btnClear = new QPushButton(tr("Clear"));
	btnClear->setMaximumWidth(mWidth);
	btnDone = new QPushButton(tr("Done"));
	btnDone->setMaximumWidth(mWidth);
	btnPreview = new QPushButton(tr("Preview"));
	btnPreview->setMaximumWidth(mWidth);
	btnCancel = new QPushButton(tr("Cancel"));
	btnCancel->setMaximumWidth(mWidth);

	connect(btnInsert, SIGNAL(clicked()), this, SLOT(runInsert()));
	connect(btnUpdate, SIGNAL(clicked()), this, SLOT(runUpdate()));
	connect(btnDelete, SIGNAL(clicked()), this, SLOT(runDelete()));
	connect(btnClear, SIGNAL(clicked()), this, SLOT(runClear()));
	connect(btnDone, SIGNAL(clicked()), this, SLOT(runDone()));
	connect(btnPreview, SIGNAL(clicked()), this, SLOT(runPreview()));
	connect(btnCancel, SIGNAL(clicked()), this, SLOT(runCancel()));



	layout->addWidget(btnInsert);
	layout->addWidget(btnUpdate);
	layout->addWidget(btnDelete);
	layout->addWidget(btnClear);
	layout->addWidget(btnDone);
	layout->addWidget(btnPreview);
	layout->addWidget(btnCancel);

	layout->insertSpacing(0, 90);
	layout->insertSpacing(-1, 90);


	QLayout * mLayout = dynamic_cast<QLayout *>(layout);

	return mLayout;

}


void ManualCoord::rdo_click()
{
	if(rdoPolyline->isChecked() == true || rdoPolygon->isChecked() == true)
	{
		grpLatLon->setEnabled(true);
		grpCenterLatLon->setEnabled(false);
		grpPoint->setEnabled(true);
		grpArcCircle->setEnabled(false);

		txtLat->setFocus();
		txtLat->setCursorPosition(1);
		cboBndryVia->setCurrentIndex(cboBndryVia->findData(GREATECIRCLE));
	}else if(rdoCircle->isChecked() == true)
	{
		grpLatLon->setEnabled(false);
		grpCenterLatLon->setEnabled(true);
		grpPoint->setEnabled(false);
		grpArcCircle->setEnabled(true);
		txtCenterLat->setFocus();
		txtCenterLat->setCursorPosition(1);

		txtDist->setText("010.0");
		txtBearing->setText("000.0");
		cboBndryVia->setCurrentIndex(cboBndryVia->findData(BNCIRCLE));
	}else if(rdoSymbol->isChecked() == true)
	{
		grpLatLon->setEnabled(false);
		grpCenterLatLon->setEnabled(true);
		grpPoint->setEnabled(false);
		grpArcCircle->setEnabled(true);

		SymbolSelector * symbol = new SymbolSelector(drawingWidget);
		symbol->setModal(true);
		if(symbol->exec()){
			delete symbol;
		}else{
			delete symbol;
		}
	}

	//cboBndryVia->setCurrentIndex(cboBndryVia->itemData())

	//qDebug()<<"CBO Index : "<<cboBndryVia->findData(BNCIRCLE);
}


/*
 * DB의 자료를 가져온다.
 */

void ManualCoord::processMCDB()
{
	mcdb = new ManualCoordDbProcess;

	//Airport
	cboAirport->setModel(mcdb->getAirPortList());
	cboAirport->insertItem(-1, "");
	cboAirport->setCurrentIndex(-1);

	cboCenterAirport->setModel(mcdb->getAirPortList());
	cboCenterAirport->setCurrentIndex(-1);

	connect(cboAirport, SIGNAL(currentIndexChanged (int)), this, SLOT(runCurrentIndexChanged(int)));
	connect(cboCenterAirport, SIGNAL(currentIndexChanged (int)), this, SLOT(runCurrentIndexChanged(int)));

	//Fix

	cboFix->setModel(mcdb->getFixList());
	cboFix->setCurrentIndex(-1);
	cboCenterFix->setModel(mcdb->getFixList());
	cboCenterFix->setCurrentIndex(-1);
	connect(cboFix, SIGNAL(currentIndexChanged (int)), this, SLOT(runCurrentIndexChanged(int)));
	connect(cboCenterFix, SIGNAL(currentIndexChanged (int)), this, SLOT(runCurrentIndexChanged(int)));
	//connect(cboNavaid, SIGNAL(currentIndexChanged (int)), this, SLOT(runCurrentIndexChanged(int)));

	//Navaid

/*	cboFix->setModel(mcdb->getFixList());
	cboFix->setCurrentIndex(-1);
	cboCenterFix->setModel(mcdb->getFixList());
	cboCenterFix->setCurrentIndex(-1);*/
}

/*
 * 테이블 위젯을 생성한다.
 */
void ManualCoord::genTable()
{
	//qDebug()<<"display Blanking Area Info called...test";

	tblWidget->disconnect();
	tblWidget->setRowCount(0);


	//connect(tblWidget, SIGNAL(itemChanged(QTableWidgetItem *)), this,	SLOT(processItems(QTableWidgetItem *)));

	//connect(tblWidget, SIGNAL(clicked(const QModelIndex &)), this,	SLOT(processTable(const QModelIndex &)));
	connect(tblWidget, SIGNAL(clicked(const QModelIndex &)), this, SLOT(runTblClicked(const QModelIndex &)));

	QColor color(255,0,0,100);
	QBrush brush(color);

	tblWidget->setColumnCount(8);

	tblWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	//tblView->setSelectionMode(QAbstractItemView::ExtendedSelection);
	tblWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	tblWidget->resizeColumnsToContents();
	tblWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

	tblWidget->setHorizontalHeaderLabels(QStringList()
			<<tr("Via")<<tr("LAT")<<tr("LON")<<tr("Center LAT")<<tr("Center LON")<<tr("Dist.")<<tr("Bearing")<<tr("Symbol"));

	if(dm == Initial){
		if(coord_list.size() > 0){
			deleteRows();
		}
	}

	for(int row = 0 ; row < coord_list.size(); row++){
		COORDINATE cn = coord_list.at(row);
		addRows();
		//QPixmap pixmap = genPixmap(file_list.at(row));
		//tblWidget->item(row,0)->setIcon(QIcon(pixmap));
		QString via;
		if(cn.Via == GREATECIRCLE){
			via = "G";
		}else if(cn.Via == RHUMBLINE){
			via = "U";
		}else if(cn.Via == COUNTERCLOCKWISEARC){
			via = "L";
		}else if(cn.Via == CLOCKWISEARC){
			via = "R";
		}else if(cn.Via == BNCIRCLE){
			via = "C";
		}else if(cn.Via == BNSYMBOL){
			via = "S";
		}
		tblWidget->item(row, 0)->setText(via);
		tblWidget->item(row,1)->setText(cn.Lat);
		tblWidget->item(row,2)->setText(cn.Lon);
		tblWidget->item(row,3)->setText(cn.centerLat);
		tblWidget->item(row,4)->setText(cn.centerLon);
		tblWidget->item(row,5)->setText(QString::number(cn.dist, 'f', 1));
		tblWidget->item(row,6)->setText(QString::number(cn.bearing, 'f', 1));
	}

	tblWidget->resizeColumnsToContents();
	tblWidget->setCurrentCell(0,0);

	qDebug()<<"displayBAInfo closed...";
}

/**
 * Row 추가
 */

void ManualCoord::addRows()
{
	int row = tblWidget->rowCount();
	tblWidget->insertRow(row);

		QTableWidgetItem * item[8];
		for(int i = 0 ; i < 8; i++){
			item[i] = new QTableWidgetItem;
			/*if(i == 0){
				item[i]->setBackgroundColor(Qt::black);
			}*/
			item[i]->setTextAlignment(Qt::AlignCenter | Qt::AlignCenter);
			item[i]->setFlags(item[i]->flags() ^ Qt::ItemIsEditable);

			tblWidget->setItem(row,i,item[i]);
		}
	//위의 소스코드에서 체크 박스 및 하나의 셀을 만드는 과정이다..

		tblWidget->setCurrentItem(item[0]);
}

/**
 * Row delete
 */

void ManualCoord::deleteRows()
{
	for(int row = 0 ; row < coord_list.size() ; row ++){
		tblWidget->removeRow(row);
	}
}

/**
 * Clear
 */

void ManualCoord::clear()
{
	qDebug()<<"[ManualCoord-Clear] called..";
	rdoPolygon->setChecked(false);
	rdoPolyline->setChecked(false);
	rdoCircle->setChecked(false);
	rdoSymbol->setChecked(false);

	cboBndryVia->setCurrentIndex(cboBndryVia->findData(NONE));

//	qDebug()<<"h1";
	txtRhoAirport->setText("");
	txtThetaAirport->setText("");

	txtRhoFix->setText("");
	txtThetaFix->setText("");

	txtRhoNavaid->setText("");
	txtThetaNavaid->setText("");

	txtCenterRhoAirport->setText("");
	txtCenterThetaAirport->setText("");

	txtCenterRhoFix->setText("");
	txtCenterThetaFix->setText("");

	txtCenterRhoNavaid->setText("");
	txtCenterThetaNavaid->setText("");

	txtLat->setText("");
	txtLon->setText("");

	txtCenterLat->setText("");
	txtCenterLon->setText("");
//	txtDist->setText("");
//	txtBearing->setText("");
//	qDebug()<<"h2";
	grpLatLon->setEnabled(false);
	grpCenterLatLon->setEnabled(false);
	grpPoint->setEnabled(false);
	grpArcCircle->setEnabled(false);


	qDebug()<<"[ManualCoord-Clear] closed..";
}

/**
 * Insert
 */

void ManualCoord::runInsert()
{

	COORDINATE cn;

	//BoundaryVia 적용은 나중에

	BndryVia via = BndryVia(cboBndryVia->itemData(cboBndryVia->currentIndex(), Qt::UserRole).toInt());
	qDebug()<<"shape : "<<via;
	if(rdoPolyline->isChecked() == true || rdoPolygon->isChecked() == true)
	{
		if(rdoPolyline->isChecked() == true)
			cn.shape = Polyline;
		else
			cn.shape = Polygon;
		cn.Via = via;
		cn.Lat = txtLat->text();
		cn.Lon = txtLon->text();
		if(via == COUNTERCLOCKWISEARC || via == CLOCKWISEARC){
			cn.centerLat = txtCenterLat->text();
			cn.centerLon = txtCenterLon->text();
		}
	}
	else if(rdoSymbol->isChecked() == true)
	{
		cn.shape = Symbol;
		cn.Via = via;
		cn.centerLat = txtCenterLat->text();
		cn.centerLon = txtCenterLon->text();
	}

	else if(rdoCircle->isChecked() == true)
	{
		if(tblWidget->rowCount() > 0){
			QMessageBox::warning(this,tr("Error"), tr("already exist"));
			return;
		}
		bool ok;
		cn.shape = Circle;
		cn.Via = via;
		cn.centerLat = txtCenterLat->text();
		cn.centerLon = txtCenterLon->text();
		cn.dist = txtDist->text().toDouble(&ok);
		cn.bearing = txtBearing->text().toDouble(&ok);
	}

	cn.idx = index++;
	coord_list.append(cn);

	genTable();

}

/**
 * Update
 */

void ManualCoord::runUpdate()
{
	int row = tblWidget->currentRow();
	if(row < 0){
		QMessageBox::warning(this, tr("Error"), tr("Select row"));
		return;
	}

	COORDINATE cn;
	BndryVia via = BndryVia(cboBndryVia->itemData(cboBndryVia->currentIndex(), Qt::UserRole).toInt());
	qDebug()<<"shape : "<<via;
	if(rdoPolyline->isChecked() == true || rdoPolygon->isChecked() == true)
	{
		if(rdoPolyline->isChecked() == true)
			cn.shape = Polyline;
		else
			cn.shape = Polygon;
		cn.Via = via;
		cn.Lat = txtLat->text();
		cn.Lon = txtLon->text();
		if(via == COUNTERCLOCKWISEARC || via == CLOCKWISEARC){
			cn.centerLat = txtCenterLat->text();
			cn.centerLon = txtCenterLon->text();
		}
	}
	else if(rdoSymbol->isChecked() == true)
	{
		cn.shape = Symbol;
		cn.Via = via;
		cn.centerLat = txtCenterLat->text();
		cn.centerLon = txtCenterLon->text();
	}

	else if(rdoCircle->isChecked() == true)
	{
		/*if(tblWidget->rowCount() < 0){
			QMessageBox::warning(this,tr("Error"), tr("already exist"));
			return;
		}*/
		bool ok;
		cn.shape = Circle;
		cn.Via = via;
		cn.centerLat = txtCenterLat->text();
		cn.centerLon = txtCenterLon->text();
		cn.dist = txtDist->text().toDouble(&ok);
		cn.bearing = txtBearing->text().toDouble(&ok);
	}else{
		QMessageBox::warning(this, tr("Error"), tr("Select Shape Type"));
		return;
	}

	//Replace
	coord_list.replace(row, cn);

	genTable();


}

/**
 * Delete
 */

void ManualCoord::runDelete()
{
	int row = tblWidget->currentRow();
	if(row < 0){
		QMessageBox::warning(this, tr("Error"), tr("Select row"));
		return;
	}

	coord_list.remove(row);
	genTable();
}

/**
 * Clear
 */
void ManualCoord::runClear()
{
	clear();
}

/**
 * Done
 */

void ManualCoord::runDone()
{

	if(dm == Initial){
		emit emitDone(coord_list, dm);
	}else{
		emit emitDone(coord_list, dm, grpItem);
	}
	close();

}


/**
 * Preview
 */

void ManualCoord::runPreview()
{

}

/**
 * Cance
 */
void ManualCoord::runCancel()
{
	close();
}

/**
 *
 */
void ManualCoord::runBndryChanged(int index)
{

	BndryVia type = BndryVia(cboBndryVia->itemData(index, Qt::UserRole).toInt());

	if(type == COUNTERCLOCKWISEARC || type == CLOCKWISEARC){
		grpArcCircle->setEnabled(true);
		grpPoint->setEnabled(true);
	}else if(type == GREATECIRCLE || type == RHUMBLINE){
		grpArcCircle->setEnabled(false);
		grpPoint->setEnabled(true);
	}else if(type == BNCIRCLE){
		grpArcCircle->setEnabled(true);
		grpPoint->setEnabled(false);
	}
}

/**
 * table widget 클릭시 발생되는 함수
 */
void ManualCoord::runTblClicked(const QModelIndex & index)
{
	int row = index.row();

	QString via;
	for(int i = 0 ; i < 8 ; i++){
		QTableWidgetItem * item = tblWidget->item(row, i);
		QString tmp = item->text();
		//0번째 컬럼 -> via
		if(i == 0){
			via = tmp;
			if(tmp == "G"){
				cboBndryVia->setCurrentIndex(cboBndryVia->findData(GREATECIRCLE));
			}else if(tmp == "C"){
				cboBndryVia->setCurrentIndex(cboBndryVia->findData(BNCIRCLE));
			}else if(tmp == "L"){
				cboBndryVia->setCurrentIndex(cboBndryVia->findData(COUNTERCLOCKWISEARC));
			}else if(tmp == "R"){
				cboBndryVia->setCurrentIndex(cboBndryVia->findData(CLOCKWISEARC));
			}
			continue;
		}

		//Polyline, Polygon 인 경우 lat, lon point만 읽는다
		if(rdoPolyline->isChecked() == true || rdoPolygon->isChecked() == true)
		{
			if(i == 1)
			{
				txtLat->setText(tmp);
			}else if(i == 2)
			{
				txtLon->setText(tmp);
			}

			if(via == "R" || via == "L")
			{
				if(i == 3)
				{
					txtCenterLat->setText(tmp);
				}else if(i == 4)
				{
					txtCenterLon->setText(tmp);
				}else if(i == 5)
				{
					txtDist->setText(tmp);
				}else if(i == 6)
				{
					txtBearing->setText(tmp);
				}
			}
		}else if(rdoCircle->isChecked() ==  true)
		{
			if(i == 3)
			{
				txtCenterLat->setText(tmp);
			}else if(i == 4)
			{
				txtCenterLon->setText(tmp);
			}else if(i == 5)
			{
				txtDist->setText(tmp);
			}else if(i == 6)
			{
				txtBearing->setText(tmp);
			}
		}
	}
}

/**
 * 콤보 박스의 인덱스 변경시 호출됨
 */
void ManualCoord::runCurrentIndexChanged(int index)
{

	qDebug()<<"[ManualCoord - runCurrentIndexChanged] index : "<<index;

	QComboBox * cboWidget = static_cast<QComboBox *>(sender());

	QSqlQueryModel * model = dynamic_cast<QSqlQueryModel *>(cboWidget->model());
	if(model == 0)
	{
		qDebug()<<"Casting to QsqlQueryModel is failed..";
	}else{
		qDebug()<<"Casting is succes..";
	}

	tmpLat = model->record(index).value("LAT").toString();
	tmpLon = model->record(index).value("LON").toString();
	//qDebug()<<"ICAO_CD : "<<model->record(index).value(0).toString();

	qDebug()<<"ID:"<<model->record(index).value(0).toString()<<", tmpLat : "<<tmpLat<<", tmpLon : "<<tmpLon;

}

void ManualCoord::runApply()
{
	if(cboAirport->currentIndex() < 0 && cboFix->currentIndex() <0 && cboNavaid->currentIndex() < 0){
		QMessageBox::warning(this, tr("Error"), tr("Select Combobox"));

		return;
	}

	if(cboAirport->currentIndex() >= 0){
		if(cboFix->currentIndex() >= 0 || cboNavaid->currentIndex() >= 0){
			QMessageBox::warning(this, tr("Error"), tr("Select a combobox among three comboboxes.."));

			return;
		}
	}

	if(cboFix->currentIndex() >= 0){
		if(cboAirport->currentIndex() >= 0 || cboNavaid->currentIndex() >= 0){
			QMessageBox::warning(this, tr("Error"), tr("Select a combobox among three comboboxes.."));

			return;
		}
	}

	if(cboNavaid->currentIndex() >= 0){
		if(cboAirport->currentIndex() >= 0 || cboFix->currentIndex() >= 0){
			QMessageBox::warning(this, tr("Error"), tr("Select a combobox among three comboboxes.."));

			return;
		}
	}

	txtLat->setText(tmpLat);
	txtLon->setText(tmpLon);
}



void ManualCoord::runCenterApply()
{
	if(cboCenterAirport->currentIndex() < 0 && cboCenterFix->currentIndex() <0 && cboCenterNavaid->currentIndex() < 0){
		QMessageBox::warning(this, tr("Error"), tr("Select Center Combobox"));

		return;
	}

	if(cboCenterAirport->currentIndex() >= 0){
		if(cboCenterFix->currentIndex() >= 0 || cboCenterNavaid->currentIndex() >= 0){
			QMessageBox::warning(this, tr("Error"), tr("Select a combobox among three comboboxes.."));

			return;
		}
	}

	if(cboCenterFix->currentIndex() >= 0){
		if(cboCenterAirport->currentIndex() >= 0 || cboCenterNavaid->currentIndex() >= 0){
			QMessageBox::warning(this, tr("Error"), tr("Select a combobox among three comboboxes.."));

			return;
		}
	}

	if(cboCenterNavaid->currentIndex() >= 0){
		if(cboCenterAirport->currentIndex() >= 0 || cboCenterFix->currentIndex() >= 0){
			QMessageBox::warning(this, tr("Error"), tr("Select a combobox among three comboboxes.."));

			return;
		}
	}

	txtCenterLat->setText(tmpLat);
	txtCenterLon->setText(tmpLon);
}
