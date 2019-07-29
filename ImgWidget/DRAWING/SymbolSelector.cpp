/*
 * SymbolSelector.cpp
 *
 *  Created on: 2013. 7. 11.
 *      Author: jiwon
 */

#include "SymbolSelector.h"

SymbolSelector::SymbolSelector(DrawingWidget * drawingWidget, QDialog * parent)
: QDialog(parent)
{
	// TODO Auto-generated constructor stub

	this->drawingWidget = drawingWidget;
	QDir dir("/home/jiwon/workspace/0510_Test01/images");

	dirPath = dir.path();
	dirPath.append('/');

	file_list = dir.entryList(QDir::Files);

	tblWidget = new QTableWidget;
	qDebug()<<"Path : "<<dirPath<<"file_list : "<<file_list;


	genSymbolTable();


	//Layout

	QHBoxLayout * hbox = new QHBoxLayout;

	lblUrl = new QLabel(tr("Url"));
	btnRefresh = new QPushButton(tr("Refresh"));

	hbox->addWidget(lblUrl);
	hbox->addWidget(btnRefresh);

	QHBoxLayout * hbox2 = new QHBoxLayout;

	btnOk = new QPushButton(tr("Ok"));
	btnCancel = new QPushButton(tr("Cancel"));

	connect(btnOk, SIGNAL(clicked()), this, SLOT(runOk()));
	connect(btnCancel, SIGNAL(clicked()), this, SLOT(runCancel()));

	hbox2->addWidget(btnOk);
	hbox2->addWidget(btnCancel);

	QVBoxLayout * vbox = new QVBoxLayout;

	vbox->addLayout(hbox);
	vbox->addWidget(tblWidget);
	vbox->addLayout(hbox2);

	setLayout(vbox);

	show();

}

SymbolSelector::~SymbolSelector() {
	// TODO Auto-generated destructor stub
}

/*
 * 테이블 위젯을 생성한다.
 */
void SymbolSelector::genSymbolTable()
{
	qDebug()<<"display Blanking Area Info called...test";

	tblWidget->disconnect();
	tblWidget->setRowCount(0);

	connect(tblWidget, SIGNAL(clicked(const QModelIndex &)), this,	SLOT(processTable(const QModelIndex &)));

	QColor color(255,0,0,100);
	QBrush brush(color);

	tblWidget->setColumnCount(2);

	tblWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	//tblView->setSelectionMode(QAbstractItemView::ExtendedSelection);
	tblWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	tblWidget->resizeColumnsToContents();
	tblWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
//	tblWidget->setHorizontalHeaderLabels(QStringList()
//			<<tr("Symbol")<<tr("File Name"));

	for(int row = 0 ; row < file_list.size(); row++){
		addRows();
		QPixmap pixmap = genPixmap(file_list.at(row));
		tblWidget->item(row,0)->setIcon(QIcon(pixmap));
		tblWidget->item(row,1)->setText(file_list.at(row));
	}

	tblWidget->resizeColumnsToContents();
	tblWidget->setCurrentCell(0,0);
}

/**
 * Row 추가
 */

void SymbolSelector::addRows()
{
	int row = tblWidget->rowCount();
	tblWidget->insertRow(row);

		QTableWidgetItem * item[2];
		for(int i = 0 ; i < 2; i++){
			item[i] = new QTableWidgetItem;
			if(i == 0){
				item[i]->setBackgroundColor(Qt::black);
			}
			item[i]->setTextAlignment(Qt::AlignCenter | Qt::AlignCenter);
			item[i]->setFlags(item[i]->flags() ^ Qt::ItemIsEditable);

			tblWidget->setItem(row,i,item[i]);
		}
	//위의 소스코드에서 체크 박스 및 하나의 셀을 만드는 과정이다..

		tblWidget->setCurrentItem(item[0]);
}

/*
 * Pixmap 리턴
 */

QPixmap SymbolSelector::genPixmap(QString name)
{

	QPixmap pixmap(name.prepend(dirPath));

	return pixmap;
}

void SymbolSelector::runOk()
{
	qDebug()<<"[SymbolSelector - runOk] call..selectedName : "<<selectedName<<", dirPath : "<<dirPath<<", DW ; "<<drawingWidget;
	selectedName.prepend(dirPath);

	drawingWidget->getDrawing().strText = selectedName;

	qDebug()<<"[SymbolSelector - runOk] close..";
	accept();
}

void SymbolSelector::runCancel()
{

	close();
}


void SymbolSelector::processTable(const QModelIndex & index)
{

	int row = index.row();

	QTableWidgetItem * item = tblWidget->item(row, 1);

	qDebug()<<"Selected Text : "<<item->text();

	selectedName = item->text();

}
