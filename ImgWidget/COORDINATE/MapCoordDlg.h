/*
 * MapCoordDlg.h
 *
 *  Created on: 2013. 6. 3.
 *      Author: jiwon
 */

#ifndef MAPCOORDDLG_H_
#define MAPCOORDDLG_H_

#include <QDialog>
#include <QtGui>
#include "../lib/ConvertPoint.h"
#include "../lib/GlobalMath.h"
#include "../LATLON/LatLonConvert.h"
/*
 * 맵 위경도를 좌표 (도분초) 를 입력해서 해당 위치로 이동
 *
 * 맵 위경도를 X,Y 좌표로 변환한 값 표시
 * 한 지점(위경도 또는 X,Y), 기울기 그리고 거리를 알때 해당 ㄷ
 */
class MapCoordDlg : public QDialog
{
	Q_OBJECT
public:
	MapCoordDlg(QDialog * parent = 0);
	virtual ~MapCoordDlg();
	void init();
	void maskText();

public slots:
	void checkLat(const QString & str);
	void checkLon(const QString & str);
	void runOk();
	void runConvert();						//위경도를 도분초로 변경한다..
	void runDmsWgsConvert();				//도분초를 위경도 좌표로 변환한다..
	void runGetNewPoint();
private:
	ConvertPoint * cvtPoint;
	QPushButton * btnOk;
	QPushButton * btnCancel;
	QPushButton * btnConvert; 			//위경도를 도분초로 변경
	QPushButton * btnDmsWgsConvert;
	QCheckBox * chkSymbol;

	QLineEdit * txtLat;
	QLineEdit * txtLon;

	QLineEdit * txtWgLat;
	QLineEdit * txtWgLon;

	QLineEdit * txtDmsLat;
	QLineEdit * txtDmsLon;

	//도분초 변환 관련 위젯
	QLineEdit * txtAngle;
	QLineEdit * txtDist;
	QLineEdit * txtResult;

signals:
	void emitRunOk(QWidget * lat, QWidget * lon, int status);		//1: Checked, 0 : unChecked..
};

#endif /* MAPCOORDDLG_H_ */
