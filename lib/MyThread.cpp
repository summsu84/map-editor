/*
 * MyThread.cpp
 *
 *  Created on: 2013. 1. 22.
 *      Author: jiwon
 */

#include "MyThread.h"
#include <QDebug>
#include <iostream>


using namespace std;


MyThread::MyThread()
{
	qDebug()<<"[MyThread] constructor is called..";
	pd = new QProgressDialog("Loading...", "cancel", 0, 100);
	pd->show();
	connect(this, SIGNAL(emitValue(int)), this, SLOT(test(int)));
   stopped = false;

   start(QThread::HighestPriority);
}

MyThread::~MyThread() {
	// TODO Auto-generated destructor stub
}

void MyThread::setMessage(const QString &message)
{
    mutex.lock();
    messageStr = message;
    mutex.unlock();
}

void MyThread::run()
{
	int i = 0;
	QString msg;


    while (!stopped){
    	msg = QString().setNum(i);
    	//qDebug()<<"msg : "<<msg;
    	i++;
    	//rightLayout->setPlainText(msg);
    	//emitMsg(msg);
    	emitValue(i*2);
    	msleep(300);
    }

    stopped = false;
    cerr << endl;
}

void MyThread::stop()
{
    mutex.lock();
    pd->setValue(100);
    stopped = true;
    mutex.unlock();
}
void MyThread::test(int value)
{
	qDebug()<<"test value : "<<value;
	pd->setValue(value);
}
