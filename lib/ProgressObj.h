/*
 * ProgressObj.h
 *
 *  Created on: 2013. 6. 13.
 *      Author: jiwon
 */

#ifndef PROGRESSOBJ_H_
#define PROGRESSOBJ_H_

#include <QObject>
#include <QTimer>
#include <QProgressDialog>

class ProgressObj : public QObject
{
	Q_OBJECT

public:
	ProgressObj(QObject * parent = 0);
	virtual ~ProgressObj();

	QTimer * timer;
	QProgressDialog * pd;
public slots:
	void perform();
	void cancel();

private:
	int step;


};

#endif /* PROGRESSOBJ_H_ */
