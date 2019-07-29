/*
 * AngleInfo.h
 *
 *  Created on: 2013. 6. 5.
 *      Author: jiwon
 */

#ifndef ANGLEINFO_H_
#define ANGLEINFO_H_
/*
 * 회전값 입력과 관련된 다이얼로그
 */
#include <QDialog>
#include <QLineEdit>
#include <QtGui>

class AngleInfo : public QDialog
{
	Q_OBJECT

public:
	AngleInfo(int angle, int scale, QDialog * parent=0);
	virtual ~AngleInfo();
	void init(int angle, int scale);
public slots:
	void runOk();
	void runValueChanged(int value);
	void runSliderReleased();
private:
	QPushButton * btnOk;
	QPushButton * btnCancel;
	QLineEdit * txtAngle;

	QSlider * sldScale;
	QLineEdit * txtScale;
signals:
	void emitRunOk(int angle);
	void emitSetScale(int value);
};

#endif /* ANGLEINFO_H_ */
