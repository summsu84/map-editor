#include "test01.h"
#include "MapWindow.h"
#include <QtGui>
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MapWindow w;
    w.show();



    return a.exec();
}
