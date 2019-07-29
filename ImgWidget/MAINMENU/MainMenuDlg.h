/*
 * MainMenuDlg.h
 *
 *  Created on: 2013. 6. 12.
 *      Author: jiwon
 */

#ifndef MAINMENUDLG_H_
#define MAINMENUDLG_H_

#include <QtGui>


class MainMenuDlg : public QWidget
{
public:
	MainMenuDlg(QWidget * parent = 0);
	virtual ~MainMenuDlg();
	void init();
	void btnInit();
private:
	QPushButton * btnFpl;
	QPushButton * btnList;
	QPushButton * btnSn;
	QPushButton * btnCom;
	QPushButton * btnSup;
	QPushButton * btnRole;
	QPushButton * btnInOut;
	QPushButton * btnConsole;

	QLineEdit * txtDate;
	QLineEdit * txtFeedBack;
	QPushButton * btnCount;
	QPushButton * btnClear;

	QPixmap * pixLogo;

};

#endif /* MAINMENUDLG_H_ */

