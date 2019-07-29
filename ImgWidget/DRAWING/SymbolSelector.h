/*
 * SymbolSelector.h
 *
 *  Created on: 2013. 7. 11.
 *      Author: jiwon
 */

#ifndef SYMBOLSELECTOR_H_
#define SYMBOLSELECTOR_H_

#include <QtGui>
#include <QDialog>
#include <QTableWidget>
#include <QObject>
#include "DrawingWidget.h"

class DrawingWidget;
class SymbolSelector : public QDialog
{
	Q_OBJECT;

public:
	SymbolSelector(DrawingWidget * drawingWidget, QDialog * parent = 0);
	virtual ~SymbolSelector();
	void genSymbolTable();
	void addRows();
	QPixmap genPixmap(QString name);

public slots:
	void runOk();
	void runCancel();
	void processTable(const QModelIndex & index);

private:
	QLabel * lblUrl;
	QPushButton * btnRefresh;
	QPushButton * btnOk;
	QPushButton * btnCancel;

	QTableWidget * tblWidget;

	QStringList file_list;
	QString dirPath;
	QString selectedName;

	DrawingWidget * drawingWidget;
};

#endif /* SYMBOLSELECTOR_H_ */
