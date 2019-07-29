#ifndef TEST01_H
#define TEST01_H

#include <QtGui/QWidget>
#include <ImgWidget/Window04.h>

//#include "ui_test01.h"

class Test01 : public QWidget
{
    Q_OBJECT

public:
    Test01(QWidget *parent = 0);
    ~Test01();

private:
    //Ui::Test01Class ui;
    Window04 window;
};

#endif // TEST01_H
