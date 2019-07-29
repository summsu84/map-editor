#include "test01.h"
#include "lib/WGS84_TM.h"

Test01::Test01(QWidget *parent)
    : QWidget(parent)
{
	//ui.setupUi(this);


	QVBoxLayout * mainLayout = new QVBoxLayout;
	mainLayout->addWidget(&window);

	this->setLayout(mainLayout);
	//this->show();

}

Test01::~Test01()
{

}
