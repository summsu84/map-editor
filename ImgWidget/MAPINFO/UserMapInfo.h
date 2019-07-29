/*
 * UserMapInfo.h
 *
 *  Created on: 2013. 7. 24.
 *      Author: jiwon
 */

#ifndef USERMAPINFO_H_
#define USERMAPINFO_H_

#include <QtGui>
#include "LeftLayout.h"
class UserMapInfo : public QWidget
{
public:
	UserMapInfo();
	virtual ~UserMapInfo();
	void init();

private:

	QPushButton * btnSelect;
	QPushButton * btnDeselect;

	QScrollArea * scrollArea;
	LeftLayout * treeWidget;
};

#endif /* USERMAPINFO_H_ */
