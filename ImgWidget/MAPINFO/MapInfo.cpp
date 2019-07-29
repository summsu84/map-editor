#include "MapInfo.h"

MapInfo::MapInfo(QVector<LatLonMng> & latlonmng_list, DrawingMode dm, QWidget *parent )
: latlonmng_list(latlonmng_list), QWidget(parent)
{
	qDebug()<<"MapInfo is called..";
	leftLayout = 0;
	this->mode = dm;
	init();
	setWindowTitle(tr("MAP INFO"));
	disableMenu();

	qDebug()<<"[MapInfo] constructure close..";
}

void MapInfo::initLayout()
{
	qDebug()<<"initLayout is called..";
	QVBoxLayout * mainLayout = new QVBoxLayout;

	QVBoxLayout * gridLayout = setCheckBox(QStringList());
	QBoxLayout * box = new QBoxLayout(QBoxLayout::LeftToRight);
	box->addWidget(btnSelectAll);
	box->addWidget(btnDeselectAll);

	QGridLayout * centerLayout = new QGridLayout();

	centerLayout->addLayout(box, 0, 0);
	centerLayout->addLayout(gridLayout,1,0);

	mainLayout->addWidget(leftLayout);
	mainLayout->addLayout(centerLayout);

	this->setLayout(mainLayout);

}

void MapInfo::initBtn()
{
	qDebug()<<"initBtn is called..";
	btnStart = new QPushButton(tr("Close"));
	btnDb = new QPushButton(tr("Gen"));
	btnSelectAll = new QPushButton(tr("Select All"));
	btnDeselectAll = new QPushButton(tr("DeSelect All"));
	btnClear = new QPushButton(tr("Clear"));

	btnStart->setMaximumWidth(60);
	btnSelectAll->setMaximumWidth(100);
	btnDeselectAll->setMaximumWidth(100);

	connect(btnSelectAll, SIGNAL(clicked()), this, SLOT(runSelectAll()));
	connect(btnDb, SIGNAL(clicked()), this, SLOT(runParsing()));
	connect(btnDeselectAll, SIGNAL(clicked()), this, SLOT(runDeSelectAll()));
	connect(btnClear, SIGNAL(clicked()), this, SLOT(runClear()));
	connect(btnStart, SIGNAL(clicked()), this, SLOT(close()));
}

/*
 * TreeWidget을 초기화한다..
 */
void MapInfo::initTreeWidget()
{
	if(leftLayout == 0){
		leftLayout = new LeftLayout(mode);
		//connect(leftLayout, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(runCheckState(QTreeWidgetItem * , int)));
		connect(leftLayout, SIGNAL(emitTreeItemList(QTreeWidget *, QTreeWidgetItem * )), this, SLOT(runTreeItemList(QTreeWidget *, QTreeWidgetItem*)));
		connect(leftLayout, SIGNAL(emitDisableMenu()), this, SLOT(disableMenu()));
		connect(leftLayout, SIGNAL(emitEnableMenu()), this, SLOT(enableMenu()));
	}

}


void MapInfo::clear()
{
	qDebug()<<"Clear is called..";

	fileName = "";
	cnt = 0;

	if(leftLayout != 0){
		delete leftLayout;
		leftLayout = 0;
	}

	txtTableName = 0;
	txtParam1 = 0;
	txtParam2 = 0;

	btnSelectAll = 0;
	btnDeselectAll = 0;
	btnStart = 0;
	btnDb = 0;
	btnClear = 0;

	headerList.clear();			//맵 자료형의 HeaderList
	headerNameList.clear();				//헤더 이름 목록
	paramList.clear();
	c_latlon_mng = 0;
	colorInit = false;

	lineNo = 0;
	errorMessage = "";

}

MapInfo::~MapInfo()
{
	qDebug()<<"Desconstruction..";

/*	for(int i = 0 ; i < cnt ; i++){
		delete [] * txtHeader;
		delete [] * chkHeader;
		delete [] * lblHeader;
	}
	delete [] txtHeader;
	delete [] chkHeader;
	delete [] lblHeader;*/
}

void MapInfo::init()
{
	qDebug()<<"latlon size : "<<latlonmng_list.size();
	clear();

	initBtn();
	initTreeWidget();
	initLayout();
	genTree();				//tree generation

	qDebug()<<"[MapInfo] init close..";
}

//파일을 열고 헤더를 읽어온다..
QStringList MapInfo::openFile()
{
	qDebug()<<"Open File is called..";
	QString dir = QDir::currentPath();
	QFileDialog fdialog(this);
	QStringList tmp;
	//fdialog.setFileMode(QFileDialog::ExistingFiles);


	qDebug()<<"h1";
	fileName = fdialog.getOpenFileName(0, tr("Open the dat file"),
			dir, tr("dat file(*.TXT)"));

	QFile file(fileName);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
		errorMessage = QString(QObject::tr("Cannot read file %1:\n%2")
									.arg(file.fileName())
									.arg(file.errorString()));
		qDebug()<<"h2";
		return tmp;
	}

	qDebug()<<"h3";
	lineNo = 0;
	QTextStream in(&file);

	//파일을 읽어 들인다..
	QString line = in.readLine();
	qDebug() << "Read Line : " << line;
	lineNo++;


	tmp = parsingHeader(line);
	qDebug()<<"HeaderList : "<<tmp;

	//QMessageBox::warning(this, "Information", "Parsing is completed");
	qDebug() << "File end read....";
	file.close();

	return tmp;
}

void MapInfo::runParsing()
{
	qDebug()<<"Run Parsing is called..";

	//TB_CHECK
	if(txtTableName->text().length() == 0){
		QMessageBox::warning(this, tr("Input Data Error"), tr("Input Table Name"));
		return;
	}
	//PARAMETER CHECK
	if(txtParam1->text().length() == 0){
		QMessageBox::warning(this, tr("Input Data Error"), tr("Input Parameter 1"));
		return;
	}

	//PARAMETER PARSING
	paramList = txtParam1->text().split('/');
	qDebug()<<"Param1 : "<<paramList;


	QFile file(fileName);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
		errorMessage = QString(QObject::tr("Cannot read file %1:\n%2")
									.arg(file.fileName())
									.arg(file.errorString()));
		return;
	}

	lineNo = 0;
	QTextStream in(&file);
	//파일을 읽어 들인다..

	while(!in.atEnd()){
		QString line = in.readLine();
		qDebug() << "Read Line : " << line;
		lineNo++;

		parsing(line);
	}
	//QMessageBox::warning(this, "Information", "Parsing is completed");
	qDebug() << "File end read....";
	file.close();
}


/**
 * 컬럼 이름을 검출 한다..
 * @param header
 * @return
 */
QStringList MapInfo::parsingHeader(const QString header)
{
	qDebug()<<"Parsing Header.... data : "<<header;
	QStringList headername = header.split('\t');

	headerList.clear();
	for(int i = 0 ; i < headername.count() ; i++)
	{
		//qDebug()<<"headername : "<<headername.at(i)<<", value :"<<i;
		headerList.insert(headername.at(i), i);
		//qDebug()<<"Header :"<<headerList;
	}
	qDebug()<<"Header : "<<headerList;
	return headername;
}

/**
 * 컬럼의 이름으로 컬럼의 인덱스를 검출 한다..
 * @param headername
 * @return
 */
int MapInfo::getHeader(const QString headername)
{
	int num = headerList.value(headername);

	return num;
}


void MapInfo::parsing(const QString& line)
{
	qDebug() << "parsing .........";
	QStringList listStrList = line.split('\t');
	qDebug()<<"ListStrList : "<<listStrList;
	QStringList param;
	//체크 부분에 해당하는 정보 얻기
	for(int i = 0 ; i < cnt; i++){
		if(chkHeader[i]->isChecked() == true){
			QString pr = listStrList.at(this->getHeader(txtHeader[i]->text()));
			param.append(pr);
		}
	}

/*
	idx = listStrList.at(1);

	idx = idx.remove(idx.length()-1, 1);
	for(int i = idx.length() ; i < 3 ; i++){
		idx.prepend('0');
	}
	idx.append('0');
*/

	//Param2 parsing
	QMap<QString, QString> param2Map;
	if(txtParam2->text().length() != 0){
	 param2Map= this->parsingParam2(txtParam2->text().split("/"));
	}

	QString sql;

	sql = "INSERT INTO "+txtTableName->text()+ " ( ";
	for(int i = 0 ;i < paramList.count() ; i++){
		sql.append(paramList.at(i));
		if(i < paramList.count() - 1){
			sql.append(", ");
		}
	}
	if(txtParam2->text().length() != 0){
		QList<QString> param2Keys = param2Map.keys();
		sql.append(", ");
		for(int i = 0 ; i < param2Keys.count() ; i++){
			sql.append(param2Keys.at(i));
			if(i < param2Keys.count() - 1){
				sql.append(", ");
			}
		}
	}

	sql.append(") VALUES(");
	for(int i = 0 ; i < param.count() ; i++){
		sql.append("'"+param.at(i)+"'");
		if(i < param.count() - 1){
			sql.append(", ");
		}
	}
	if(txtParam2->text().length() != 0){
		QList<QString> param2Values = param2Map.values();
		sql.append(", ");
		for(int i = 0 ; i < param2Values.count() ; i++){
			sql.append("'"+param2Values.at(i)+"'");
			if(i < param2Values.count() - 1){
				sql.append(", ");
			}
		}
	}

	sql.append(") ");

	qDebug()<<"sql : "<<sql;

	/*QSqlQuery * query = new QSqlQuery(QSqlDatabase::database(UserInfo::getInstance().getDbname()));

	QString sql;

	sql = "INSERT INTO TB_FIRBNDRY (FIR_ID, FIR_ADDR, BNDRY_IDX, BNDRY_VIA, LAT, LON)";
	sql += " VALUES('XXXX', 'XXXX', '"+idx+"', 'G', '"+lat+"', '"+lon+"')";
	qDebug()<<"sql : "<<sql;
	query->prepare(sql);*/
	/*query->exec();
	if (query->lastError().type() != QSqlError::NoError) {
		QMessageBox::critical(this, "SQL Error", query->lastError().text());
	}else {
		//QMessageBox::information(this, tr("Success message"), tr("Success"));
	}*/
	//delete query;
}


/**
 * 헤더 리스트를 파싱하여 헤더의 순서와 이름을 표시한다.
 */
QVBoxLayout * MapInfo::setCheckBox(QStringList listHeader)
{


	cnt = latlonmng_list.count();
	qDebug()<<"setCheckBox is called.."<<cnt;
	int numColumn = 3;

	QLabel * headerName = new QLabel(tr(""));
	//QCheckBox * chkHeader[cnt];
	chkHeader = new QCheckBox*[cnt];
	txtHeader = new QLineEdit*[cnt];
	lblHeader = new QLabel * [cnt];
	//QLabel * lblHeader[cnt];

	QVBoxLayout * boxLayout = new QVBoxLayout;
	boxLayout->addWidget(headerName);

	QGridLayout * chkLayout = new QGridLayout;
	boxLayout->addLayout(chkLayout);
	//chkLayout->addWidget(headerName, 0, 0);
	/*int row = 1;
	int col = 0;
	for(int i = 0 ; i < cnt ; i++){
		LatLonMng latlonmng = latlonmng_list->at(i);
		if(i > 0){
			if(i%8 == 0){
				row++;
				col = 0;
			}
		}

		if(row - 1 == 0){
			chkLayout->addWidget(new QLabel(tr("<h4>No.</h4>")),row-1,col * numColumn,Qt::AlignCenter);
			chkLayout->addWidget(new QLabel(tr("<h4>Name</h4>")),row-1,col * numColumn + 1, Qt::AlignCenter);
		}
		lblHeader[i] = new QLabel(QString().setNum(i, 10));
		txtHeader[i] = new QLineEdit(latlonmng.getId_name());
		//txtHeader[i]->resize(60,20);
		txtHeader[i]->setMaximumWidth(70);
		chkHeader[i] = new QCheckBox;
		connect(chkHeader[i], SIGNAL(stateChanged(int)), this, SLOT(runCheckState()));
		chkLayout->addWidget(lblHeader[i],row,col * numColumn);
		chkLayout->addWidget(txtHeader[i],row,col * numColumn + 1);
		chkLayout->addWidget(chkHeader[i],row,col * numColumn + 2);
		qDebug()<<"HeaderName : "<<txtHeader[i]->text();

		col++;
	}

	this->runSelectAll();*/

	lblLayerName = new QLabel(tr("LAYER NAME : "));
	lblIdName = new QLabel(tr("MAP ID NAME : "));
	lblColor = new QLabel(tr("LINE COLOR : "));
	lblLineType = new QLabel(tr("LINE TYPE : "));
	lblFillType = new QLabel(tr("FILL TYPE : "));
	lblFillColor = new QLabel(tr("FILL COLOR : "));

	txtLayerName = new QLineEdit;
	txtIdName = new QLineEdit;

	txtLayerName->setMaximumWidth(120);
	txtIdName->setMaximumWidth(120);

	cboColor = new QComboBox;
	cboFillColor = new QComboBox;
	cboLineType = new QComboBox;
	cboFillType = new QComboBox;

	connect(cboColor, SIGNAL(currentIndexChanged(int)), this, SLOT(processMapInfo(int)));
	connect(cboFillColor, SIGNAL(currentIndexChanged(int)), this, SLOT(processMapInfo(int)));
	connect(cboLineType, SIGNAL(currentIndexChanged(int)), this, SLOT(processMapInfo(int)));
	connect(cboFillType, SIGNAL(currentIndexChanged(int)), this, SLOT(processMapInfo(int)));

/*	QStringList colorNames = QColor::colorNames();
	int index = 0;
	foreach(QString colorName, colorNames){
		QColor color(colorName);
		cboColor->addItem(colorName, color);
		QModelIndex idx = cboColor->model()->index(index++, 0);
		cboColor->model()->setData(idx, color, Qt::BackgroundColorRole);

	}*/

	chkLayout->addWidget(lblLayerName, 0, 0);
	chkLayout->addWidget(txtLayerName, 0, 1);
	chkLayout->addWidget(lblIdName, 1, 0);
	chkLayout->addWidget(txtIdName, 1, 1);
	chkLayout->addWidget(lblLineType, 2, 0);
	chkLayout->addWidget(cboLineType, 2, 1);
	chkLayout->addWidget(lblColor, 3, 0);
	chkLayout->addWidget(cboColor, 3, 1);
	chkLayout->addWidget(lblFillType, 4, 0);
	chkLayout->addWidget(cboFillType, 4, 1);
	chkLayout->addWidget(lblFillColor, 5, 0);
	chkLayout->addWidget(cboFillColor, 5, 1);


	initComboBox();
	return boxLayout;
}

/**
 * 콤보 박스 초기화
 */
void MapInfo::initComboBox()
{
	QString lineType[3] = {"SOLID", "DASHED", "DOTTED"};
	QString fillType[8] = {"SOLID", "DOTTED", "HORIZONTAL LINE", "VERTICAL LINE", "CROSS LINE",
								"SLASHED", "REVERSE SLASHED", "CROSS SLASHED"};

	cboLineType->addItem(lineType[0], Solid);
	cboLineType->addItem(lineType[1], Dashed);
	cboLineType->addItem(lineType[2], Dotted);

	//cboFillType->addItems(fillTypeList);
	cboFillType->addItem(fillType[0], SOLID_F);
	cboFillType->addItem(fillType[1], DOTTED_F);
	cboFillType->addItem(fillType[2], HORIZONTALLINE);
	cboFillType->addItem(fillType[3], VERTICALLINE);
	cboFillType->addItem(fillType[4], CROSSLINE);
	cboFillType->addItem(fillType[5], SLASHED);
	cboFillType->addItem(fillType[6], REVERSESLASHED);
	cboFillType->addItem(fillType[7], CROSSSLASHED);

	cboLineType->setMaximumWidth(120);
	cboFillType->setMaximumWidth(120);
	cboColor->setMaximumWidth(120);
	cboFillColor->setMaximumWidth(120);
	initColorComboBox(cboColor);
	initColorComboBox(cboFillColor);
}

/*
 * 컬러 콤보 박스 초기화
 */
void MapInfo::initColorComboBox(QComboBox * cboColor)
{
	QStringList colorNames = QColor::colorNames();
	int index = 0;
	foreach(QString colorName, colorNames){
		QColor color(colorName);
		cboColor->addItem(colorName, color);
		QModelIndex idx = cboColor->model()->index(index++, 0);
		cboColor->model()->setData(idx, color, Qt::BackgroundColorRole);

	}
	qDebug()<<"Result of Index : "<<index;
}

/*
 * 컬러 콤보 박스에 컬러 추가
 */
void MapInfo::addColor2ComboBox(QComboBox * combo, QColor color, QString color_name)
{

	QStringList colorNames = QColor::colorNames();
	//qDebug()<<"color names : "<<colorNames;
	combo->addItem(color_name, color);
	int index = combo->model()->rowCount() - 1;
	qDebug()<<"Index : "<<index;
	QModelIndex idx = combo->model()->index(index++, 0);
	combo->model()->setData(idx, color, Qt::BackgroundColorRole);
}

QGridLayout * MapInfo::initTableParam()
{
	qDebug()<<"initTableParam is called..";
	//테이블과 파라미터에 관련된 레이아웃 설정
	QGridLayout * tableLayout = new QGridLayout;

	QLabel * lblTable = new QLabel(tr("<h3>Table Name</h3>"));
	QLabel * lblParam1 = new QLabel(tr("Param1 : "));
	QLabel * lblParam2 = new QLabel(tr("Param2 : "));
	QLabel * lblTableName = new QLabel(tr("Table Name : "));
	lblHelp = new QLabel;
	txtTableName = new QLineEdit;
	txtParam1 = new MyLineEdit;
	txtParam2 = new MyLineEdit;
	tableLayout->addWidget(lblTable, 0, 0);
	tableLayout->addWidget(lblTableName,1,0);
	tableLayout->addWidget(txtTableName, 1, 1);
	tableLayout->addWidget(lblParam1, 2, 0);
	tableLayout->addWidget(txtParam1, 2, 1);
	tableLayout->addWidget(lblParam2, 3, 0);
	tableLayout->addWidget(txtParam2, 3, 1);
	tableLayout->addWidget(lblHelp, 4, 1);

	txtParam1->setObjectName("txtParam1");
	txtParam2->setObjectName("txtParam2");
	connect(txtParam1, SIGNAL(focussed(bool )), this, SLOT(setHelpLabel(bool )));
	connect(txtParam2, SIGNAL(focussed(bool )), this, SLOT(setHelpLabel(bool )));


	return tableLayout;

}

void MapInfo::runSelectAll()
{
	qDebug()<<"runSelectAll is called..";

/*
	for(int i = 0 ; i < cnt; i++){
		chkHeader[i]->setChecked(true);
	}
*/
	leftLayout->runSelectAll();

}

void MapInfo::runDeSelectAll()
{

	/*for(int i = 0 ; i < cnt; i++){
		chkHeader[i]->setChecked(false);
	}*/

	leftLayout->runDeSelectAll();
}

void MapInfo::runClear()
{
	init();
	repaint();
}


/*
void MapInfo::resizeEvent(QResizeEvent * e)
{
	qDebug()<<"Resize Event is called..";
	this->adjustSize();
}
*/

QMap<QString, QString> MapInfo::parsingParam2(QStringList param2)
{
	QMap<QString, QString> paramMap;
	qDebug()<<"ParsingParam2 .. "<<param2;
	for(int j = 0 ; j < param2.count() ; j++){
		QStringList paramList = param2.at(j).split('=');
		paramMap.insert(paramList.at(0), paramList.at(1));
	}

	qDebug()<<"ParamMap : "<<paramMap;

	return paramMap;
}


void MapInfo::setHelpLabel(bool hasFocus)
{
	qDebug()<<"[MapInfo] setHelpLabel is called..";
	MyLineEdit * temp = (MyLineEdit *)sender();
	qDebug()<<temp->objectName();
	QString str = "";
	if(temp->objectName() == "txtParam1"){
		str = "usage : column name/column name/column name...../column name";
	}else if(temp->objectName() == "txtParam2"){
		str = "usage : column name=value/column name=value...";
	}
	if(hasFocus ==  true)
	{
		lblHelp->setText(str);
	}else{
		//temp->setCursorPosition(0);
		lblHelp->setText("");
	}

}

/**
 * 체크 여부에 따라, 맵 데이터를 그릴지 판단한다..
 */
void MapInfo::runCheckState(QTreeWidgetItem * item, int column)
{
	qDebug()<<"[MapInfo] runCheckState.. "<<item->text(0)<<column;


	//체크된 레이어 정보를 저장한다.
	unchecked_layer_list.clear();
	checked_layer_list.clear();
	for(int i = 0 ; i < map_controller_list.size() ; i++)
	{
		if(chkHeader[i]->checkState() == Qt::Unchecked){
			unchecked_layer_list.append(txtHeader[i]->text());
		}else{
			checked_layer_list.append(txtHeader[i]->text());
		}
	}

	qDebug()<<"unchecked_layer_list : "<<unchecked_layer_list<<", checked_layer_list : "<<checked_layer_list;

	emitLayerInfo(unchecked_layer_list, checked_layer_list, mode);



}

/*
 * 레이어 리스트를 파싱하여, 레이어와 그에 해당하는 맵 아이디를 검출 한다.
 */
void MapInfo::genTree()
{
	qDebug()<<"[MapInfo] genTree start..userObjeect count : "<<object_list.count();

	/*for(int i = 0 ; i < latlonmng_list->size() ; i++){
		LatLonMng latlonmng = latlonmng_list->at(i);
		qDebug()<<"Layer : "<<latlonmng.layer_name<<", ID : "<<latlonmng.getId_name();
	}*/

	QVector<LAYER_MAP> layer_map_list;
	QString layer_id;
	QString map_id;

	if(mode == SMSMap){
		for(int i = 0 ; i < latlonmng_list.size() ; i++){
			LatLonMng latlonmng = latlonmng_list.at(i);
			LAYER_MAP layer_map;
			int n = 0;
			layer_id = latlonmng.layer_name;
			layer_map.layer_id = layer_id;
			for(int j = i ; j < latlonmng_list.size() ; j++){
				if(layer_id == latlonmng_list.at(j).layer_name){
					layer_map.map_id_list.append(latlonmng_list.at(j).getId_name());
					if(latlonmng_list.at(j).isEnable == true){
						layer_map.isEnable[n] = true;
					}else{
						layer_map.isEnable[n] = false;
					}
					n++;
				}else{
					//layer_id = "";
					i = j - 1;
					qDebug()<<"i : "<<i;
					break;
				}
				i = j;
			}
			layer_map_list.append(layer_map);
		}

		for(int i = 0 ; i < layer_map_list.size() ; i++){
			LAYER_MAP layer_map = layer_map_list.at(i);
			qDebug()<<"LAYER : "<<layer_map.layer_id<<", IDs : "<<layer_map.map_id_list;
		}

		leftLayout->genTreeMenu(layer_map_list);
	}else if(mode == UserMap)
	{
		for(int i = 0 ; i < object_list.size() ; i++){
			UserObject object = object_list.at(i);
			LAYER_MAP layer_map;
			int n = 0;
			layer_id = object.obj_name;
			layer_map.layer_id = object.obj_name;
			for(int j = i ; j < object_list.size() ; j++){
				//Layer이름이 같으며 아래 ID들은 같은 레이어에 속한다.
				if(layer_id == object_list.at(j).obj_name){
					layer_map.map_id_list.append(object_list.at(j).obj_name);
//					if(latlonmng_list.at(j).isEnable == true){
//						layer_map.isEnable[n] = true;
//					}else{
//						layer_map.isEnable[n] = false;
//					}
					layer_map.isEnable[n] = true;
					n++;
				}else{
					//layer_id = "";
					i = j - 1;
					qDebug()<<"i : "<<i;
					break;
				}
				i = j;
			}
			layer_map_list.append(layer_map);
		}

		/*for(int i = 0 ; i < layer_map_list.size() ; i++){
			LAYER_MAP layer_map = layer_map_list.at(i);
			qDebug()<<"LAYER : "<<layer_map.layer_id<<", IDs : "<<layer_map.map_id_list;
		}*/

		leftLayout->genTreeMenu(layer_map_list);
	}

	qDebug()<<"[MapInfo] genTree close.. layer_map_list count : "<<layer_map_list.count();
}

/**
 * 트리 메뉴를 클릭했을때 (LeftLayout 클래스) 호출되는 함수
 */

void MapInfo::runTreeItemList(QTreeWidget * treeWidget, QTreeWidgetItem * org_item)
{
	qDebug()<<"[MapInfo] runTreeItemList is called.. toLevelItemCount : "<<treeWidget->topLevelItemCount();

	unchecked_layer_list.clear();
	checked_layer_list.clear();

	QList<QTreeWidgetItem*> top_item_list;
	for(int i = 0 ; i < treeWidget->topLevelItemCount() ; i++){
		top_item_list.append(treeWidget->topLevelItem(i));
	}

	for(int i = 0 ; i < top_item_list.size() ; i++){
		QTreeWidgetItem * top_item = top_item_list.at(i);
		for(int j = 0 ; j < top_item->childCount() ; j++){
			QTreeWidgetItem * item = top_item->child(j);

			if(item->checkState(0) == Qt::Checked){
				qDebug()<<"[Checked] : "<<item->text(0);
				checked_layer_list.append(item->text(0));
			}else{
				qDebug()<<"[Unchecked] : "<<item->text(0);
				unchecked_layer_list.append(item->text(0));
			}
		}
	}


	qDebug()<<"unchecked_layer_list : "<<unchecked_layer_list<<", checked_layer_list : "<<checked_layer_list<<", mode : "<<mode;

	emitLayerInfo(unchecked_layer_list, checked_layer_list, mode);

	//오른쪽 화면에 선택한 아이템에 대한 정보를 제공
	//만약 top level인경우 리턴한다.

	/*for(int i = 0 ; i < treeWidget->topLevelItemCount() ; i++){
		qDebug()<<"Selected Item : "<<org_item<<", Top Level Item : "<<treeWidget->topLevelItem(i);
		if(org_item == treeWidget->topLevelItem(i)){
			qDebug()<<"Top level is selected..";
			return;
		}

	}*/

	if(org_item == 0){
		qDebug()<<"Top Level is selected..";
		return;
	}
	qDebug()<<"Top Level is not slected..";

	if(mode == SMSMap){


		//하위 맵 정보(트리 메뉴) 를 클릭시 핸들러를 지정 한다. 이때, c_latlon_mng는 현재 클릭한 하위 맵 정보를 핸들링 하게 된다..
		for(int i = 0 ; i < latlonmng_list.size() ; i++){
			LatLonMng * latlonmng = &latlonmng_list[i];
			if(latlonmng->getId_name() == org_item->text(0)){
				c_latlon_mng = latlonmng;
				qDebug()<<"[MapInfo] c_latlon_mng : "<<c_latlon_mng<<", latlonmng : "<<latlonmng<<", latlonmng_list.value : "<<&(latlonmng_list[i]);
			}
		}

		qDebug()<<"test1";
		//c_latlon_mng 핸들러를 통해서 상세 뷰를 작성한다.
		txtLayerName->setText(c_latlon_mng->layer_name);
		txtIdName->setText(c_latlon_mng->getId_name());
		LineType lineType;
		//qDebug()<<"Find Data : "<<cboLineType->findData(c_latlon_mng->layer_line_type, Qt::UserRole);
	//	cboLineType->setCurrentIndex(cboLineType->findData(c_latlon_mng->layer_line_type, Qt::UserRole));
	//	cboFillType->setCurrentIndex(cboLineType->findData(c_latlon_mng->layer_fille_pattern, Qt::UserRole));


		QModelIndex idx = cboColor->model()->index(cboColor->currentIndex(), 0);
		QModelIndex idx2 = cboFillColor->model()->index(cboFillColor->currentIndex(), 0);



		/*QModelIndex idx = cboColor->model()->index(index++, 0);
		cboColor->model()->setData(idx, color, Qt::BackgroundColorRole);


		//qDebug()<<"LineColor : "<<cboColor->model()->itemData(idx);
		QColor lineColor = cboColor->model()->data(idx, Qt::BackgroundColorRole).value<QColor>();
		QColor fillColor = cboFillColor->model()->data(idx2, Qt::BackgroundColorRole).value<QColor>();*/
		qDebug()<<"test2";

	//	QColor red(255,0,0);
		qDebug()<<"Find Data : "<<cboColor->findData(c_latlon_mng->layer_line_color, Qt::BackgroundColorRole);

		colorInit = true;

		if(cboColor->findData(c_latlon_mng->layer_line_color, Qt::BackgroundColorRole) == -1){
			//컬러를 추가한다..
			qDebug()<<"[MapInfo] color is added..";
			this->addColor2ComboBox(cboColor, c_latlon_mng->layer_line_color, c_latlon_mng->layer_name);
		}

		if(cboFillColor->findData(c_latlon_mng->layer_fill_color, Qt::BackgroundColorRole) == -1){
			//컬러를 추가한다..
			qDebug()<<"[MapInfo] color is added..";
			this->addColor2ComboBox(cboFillColor, c_latlon_mng->layer_fill_color, c_latlon_mng->layer_name);
		}

		qDebug()<<"===================Detail view=============";
		qDebug()<<"ID : "<<c_latlon_mng->getId_name()<<", Line Color : "<<c_latlon_mng->layer_line_color.name()
				<<", Fill color : "<<c_latlon_mng->layer_fill_color.name();
		cboColor->setCurrentIndex(cboColor->findData(c_latlon_mng->layer_line_color, Qt::BackgroundColorRole) );
		cboFillColor->setCurrentIndex(cboFillColor->findData(c_latlon_mng->layer_fill_color, Qt::BackgroundColorRole));
		cboLineType->setCurrentIndex(cboLineType->findData(c_latlon_mng->layer_line_type, Qt::UserRole));
		cboFillType->setCurrentIndex(cboLineType->findData(c_latlon_mng->layer_fille_pattern, Qt::UserRole));

		colorInit = false;

		if(c_latlon_mng->getMapType() == POLYLINE){
			cboFillType->setEnabled(false);
			cboFillColor->setEnabled(false);
		}else{
			cboFillType->setEnabled(true);
			cboFillColor->setEnabled(true);
		}
	}else if(mode == UserMap)
	{
		//하위 맵 정보(트리 메뉴) 를 클릭시 핸들러를 지정 한다. 이때, c_latlon_mng는 현재 클릭한 하위 맵 정보를 핸들링 하게 된다..
		for(int i = 0 ; i < object_list.size() ; i++){
			LatLonMng * latlonmng = &latlonmng_list[i];
			if(latlonmng->getId_name() == org_item->text(0)){
				c_latlon_mng = latlonmng;
				qDebug()<<"[MapInfo] c_latlon_mng : "<<c_latlon_mng<<", latlonmng : "<<latlonmng<<", latlonmng_list.value : "<<&(latlonmng_list[i]);
			}
		}

		qDebug()<<"test1";
		//c_latlon_mng 핸들러를 통해서 상세 뷰를 작성한다.
		txtLayerName->setText(c_latlon_mng->layer_name);
		txtIdName->setText(c_latlon_mng->getId_name());
		LineType lineType;
		//qDebug()<<"Find Data : "<<cboLineType->findData(c_latlon_mng->layer_line_type, Qt::UserRole);
	//	cboLineType->setCurrentIndex(cboLineType->findData(c_latlon_mng->layer_line_type, Qt::UserRole));
	//	cboFillType->setCurrentIndex(cboLineType->findData(c_latlon_mng->layer_fille_pattern, Qt::UserRole));


		QModelIndex idx = cboColor->model()->index(cboColor->currentIndex(), 0);
		QModelIndex idx2 = cboFillColor->model()->index(cboFillColor->currentIndex(), 0);



		/*QModelIndex idx = cboColor->model()->index(index++, 0);
		cboColor->model()->setData(idx, color, Qt::BackgroundColorRole);


		//qDebug()<<"LineColor : "<<cboColor->model()->itemData(idx);
		QColor lineColor = cboColor->model()->data(idx, Qt::BackgroundColorRole).value<QColor>();
		QColor fillColor = cboFillColor->model()->data(idx2, Qt::BackgroundColorRole).value<QColor>();*/
		qDebug()<<"test2";

	//	QColor red(255,0,0);
		qDebug()<<"Find Data : "<<cboColor->findData(c_latlon_mng->layer_line_color, Qt::BackgroundColorRole);

		colorInit = true;

		if(cboColor->findData(c_latlon_mng->layer_line_color, Qt::BackgroundColorRole) == -1){
			//컬러를 추가한다..
			qDebug()<<"[MapInfo] color is added..";
			this->addColor2ComboBox(cboColor, c_latlon_mng->layer_line_color, c_latlon_mng->layer_name);
		}

		if(cboFillColor->findData(c_latlon_mng->layer_fill_color, Qt::BackgroundColorRole) == -1){
			//컬러를 추가한다..
			qDebug()<<"[MapInfo] color is added..";
			this->addColor2ComboBox(cboFillColor, c_latlon_mng->layer_fill_color, c_latlon_mng->layer_name);
		}

		qDebug()<<"===================Detail view=============";
		qDebug()<<"ID : "<<c_latlon_mng->getId_name()<<", Line Color : "<<c_latlon_mng->layer_line_color.name()
				<<", Fill color : "<<c_latlon_mng->layer_fill_color.name();
		cboColor->setCurrentIndex(cboColor->findData(c_latlon_mng->layer_line_color, Qt::BackgroundColorRole) );
		cboFillColor->setCurrentIndex(cboFillColor->findData(c_latlon_mng->layer_fill_color, Qt::BackgroundColorRole));
		cboLineType->setCurrentIndex(cboLineType->findData(c_latlon_mng->layer_line_type, Qt::UserRole));
		cboFillType->setCurrentIndex(cboLineType->findData(c_latlon_mng->layer_fille_pattern, Qt::UserRole));

		colorInit = false;

		if(c_latlon_mng->getMapType() == POLYLINE){
			cboFillType->setEnabled(false);
			cboFillColor->setEnabled(false);
		}else{
			cboFillType->setEnabled(true);
			cboFillColor->setEnabled(true);
		}
	}


}

/**
 * 맵 상세 정보를 처리한다..
 */
void MapInfo::processMapInfo(int index)
{
	qDebug()<<"----------------------ProcessMapInfo is called..-------------------------";
	if(colorInit == true) {
		qDebug()<<"Color init is set..";
		return;
	}

	qDebug()<<"Color init is not set..";
	const int IdRole = Qt::UserRole;

	//라인 타입 결정
	LineType lineType = LineType(cboLineType->itemData(cboLineType->currentIndex(), IdRole).toInt());
	//필 패턴 결정
	FillPattern fillType = FillPattern(cboFillType->itemData(cboFillType->currentIndex(), IdRole).toInt());

	//라인 색깔 결정
	QModelIndex idx = cboColor->model()->index(cboColor->currentIndex(), 0);
	//필 패턴 색깔 결정
	QModelIndex idx2 = cboFillColor->model()->index(cboFillColor->currentIndex(), 0);

	//qDebug()<<"LineColor : "<<cboColor->model()->itemData(idx);
	QColor lineColor = cboColor->model()->data(idx, Qt::BackgroundColorRole).value<QColor>();
	QColor fillColor = cboFillColor->model()->data(idx2, Qt::BackgroundColorRole).value<QColor>();

	qDebug()<<"---------------------ProcessMapInfo-------------------"<<c_latlon_mng;
	qDebug()<<"LineType : "<<lineType<<" Line Color : "<<lineColor.name()
			<<"FillType : "<<fillType<<", Fill Color : "<<fillColor.name();

	if(c_latlon_mng != 0){
		c_latlon_mng->layer_line_type = lineType;
		c_latlon_mng->layer_line_color = lineColor;
		c_latlon_mng->layer_fill_color = fillColor;
		c_latlon_mng->layer_fille_pattern = fillType;

		emitLayerInfo(unchecked_layer_list, checked_layer_list, mode);
	}
}


/*
 * 루트 아이템을 클릭시 메뉴를 디스에이블 시킨다.
 */
void MapInfo::disableMenu()
{
	txtLayerName->setEnabled(false);
	txtIdName->setEnabled(false);
	cboLineType->setEnabled(false);
	cboFillType->setEnabled(false);
	cboColor->setEnabled(false);
	cboFillColor->setEnabled(false);
}

void MapInfo::enableMenu()
{
	txtLayerName->setEnabled(false);
	txtIdName->setEnabled(false);
	cboLineType->setEnabled(true);
	cboFillType->setEnabled(true);
	cboColor->setEnabled(true);
	cboFillColor->setEnabled(true);
}

