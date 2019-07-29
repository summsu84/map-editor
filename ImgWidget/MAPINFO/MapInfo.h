/*******************************************************************************
 * Class Name  : DAFIF_PARSER
 * File Name   : DAFIF_PARSER.h
 * Short Desc  : DAFIF 정보중 FIR 관련된 정보를 파
 * Description : DAFIF 정보 중에 FIR과 관련된 정보를 파싱한다.
 * Write date  : 2013.04.01
 * Author      : JJW
 *******************************************************************************/
#ifndef MapInfo_H
#define MapInfo_H

#include <QtGui>
#include <QMap>
#include <QVector>
#include <QGridLayout>
#include "MyLineEdit.h"
#include "../../lib/LatLonMng.h"
#include "../../lib/Function.h"
#include "LeftLayout.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QBoxLayout>
#include <QMap>


class MapInfo : public QWidget
{
    Q_OBJECT

public:
   // MapInfo(QWidget * parent = 0);
    MapInfo(QVector<LatLonMng> & latlonmng_list, DrawingMode dm, QWidget *parent = 0);
    ~MapInfo();
    void parsing(const QString& line);
    void init();
    void initLayout();
    void initBtn();
    QStringList parsingHeader(const QString header);
    int getHeader(const QString headername);
    QStringList openFile();
    QVBoxLayout * setCheckBox(QStringList listHeader);
    QGridLayout * initTableParam();
    void clear();
    QStringList chckHeaderList();
    QMap<QString, QString> parsingParam2(QStringList param2);
    void genTree();
    void initComboBox();
    void initColorComboBox(QComboBox * cboColor);
    void initTreeWidget();
    void addColor2ComboBox(QComboBox * combo, QColor color, QString color_name);
    void setLatLonMngList(QVector<LatLonMng> & _latlonmng_list) { this->latlonmng_list = _latlonmng_list; init();}
    void setUserObjectList(QVector<UserObject> object_list) { this->object_list = object_list; genTree();}

public slots:
	void runParsing();
	void runSelectAll();
	void runDeSelectAll();
	void runClear();
	void setHelpLabel(bool hasFocus);
	void runCheckState(QTreeWidgetItem * item, int column);
	void runTreeItemList(QTreeWidget * treeWidget, QTreeWidgetItem * org_item);
	void processMapInfo(int index);
	void disableMenu();
	void enableMenu();
protected :
	//void resizeEvent(QResizeEvent * e);

private:

	LeftLayout * leftLayout;
	QString fileName;
	int cnt;

	QLineEdit ** txtHeader;
	QCheckBox ** chkHeader;
	QLabel	** lblHeader;

	//맵 상세 정보 관련
	QLabel	* lblLayerName;
	QLabel	* lblIdName;
	QLabel	* lblColor;
	QLabel	* lblLineType;			//LineType
	QLabel	* lblFillType;
	QLabel	* lblFillColor;			//FillColor

	QLineEdit * txtLayerName;
	QLineEdit * txtIdName;
	QComboBox * cboLineType;			//Line Type
	QComboBox * cboFillType;			//Fill Type
	QComboBox * cboColor;
	QComboBox * cboFillColor;		//FillColor

	QLineEdit * txtTableName;
	MyLineEdit * txtParam1;
	MyLineEdit * txtParam2;
	QLabel * lblHelp;

	QPushButton * btnSelectAll;
	QPushButton * btnDeselectAll;
	QPushButton * btnStart;
	QPushButton * btnDb;
	QPushButton * btnClear;

	QMap<QString, int> headerList;			//맵 자료형의 HeaderList
	QStringList	headerNameList;				//헤더 이름 목록
	QStringList  paramList;

	int lineNo;
	QString errorMessage;

	QStackedLayout * stackedLayout;

	QVector<LatLonMng> & latlonmng_list;	//SMS Map 데이터 리스트
	QVector<UserObject> object_list;		//User Object 리스트

	QStringList unchecked_layer_list;
	QStringList checked_layer_list;
	QVector<QTreeWidgetItem*> map_controller_list;	//맵 트리를 관리한다..

	LatLonMng * c_latlon_mng;		//latlonmng 관리 (현재 클릭한 latlonmng)

	bool colorInit;				//하위 트리 메뉴를 클릭시 상세 정보에 컬러가 없을 경우 콤보 박스에 컬러를 등록 시킨다.
									// 0이면 noInit, 1이면 init을 의미하며, 1일 경우 콤보박스가 변해도 슬롯 함수를 처리 하지 않는다.

	DrawingMode mode;			//SMS Map인지 UserObject인지 판단한다..
signals:
	void emitLayerInfo(QStringList unchecked_layer_list, QStringList checked_layer_list, DrawingMode mode);
};

#endif // MapInfo_H
