/*
 * UserMapInfo.cpp
 *
 *  Created on: 2013. 7. 24.
 *      Author: jiwon
 */

#include "UserMapInfo.h"

UserMapInfo::UserMapInfo() {
	// TODO Auto-generated constructor stub

	init();
}

UserMapInfo::~UserMapInfo() {
	// TODO Auto-generated destructor stub
}

void UserMapInfo::init()
{

	btnSelect = new QPushButton(tr("Select All"));
	btnDeselect = new QPushButton(tr("Unselect All"));

	//treeWidget = new LeftLayout(mode);

	QHBoxLayout * hbox = new QHBoxLayout;

	hbox->addWidget(btnSelect);
	hbox->addWidget(btnDeselect);

	QVBoxLayout * vbox = new QVBoxLayout;

	vbox->addWidget(treeWidget);
	vbox->addLayout(hbox);

	this->setLayout(vbox);

}
