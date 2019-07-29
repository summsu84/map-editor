/*
 * LeftLayout.h
 *
 *  Created on: 2013. 5. 22.
 *      Author: jiwon
 */

#ifndef LEFTLAYOUT_H_
#define LEFTLAYOUT_H_

#include <QTreeWidget>
#include <QVector>
#include "../../lib/Function.h"
#include "../../lib/LatLonMng.h"

class LeftLayout : public QTreeWidget
{
	Q_OBJECT
public:
	LeftLayout(DrawingMode mode, QWidget * parent = 0);
	virtual ~LeftLayout();
	void init();
	void removeItems();
	void genTreeMenu(QVector<LAYER_MAP> layer_map);
	int checkParentItem(QTreeWidgetItem * item);
	void checkParentItemBottomToUpper();
	void callTreeItemList(QTreeWidgetItem * item);
public slots:
	void runCheckState(QTreeWidgetItem * item , int column);
	void runSelectAll();
	void runSelectAll(int index);
	void runDeSelectAll();
	void runDeSelectAll(int index);

private:
	QVector<QTreeWidgetItem *> map_controller_list;
	QVector<LatLonMng> * latlonmng_list;
	QStringList unchecked_layer_list;
	QStringList checked_layer_list;
	DrawingMode mode;
signals:
	void emitTreeItemList(QTreeWidget * treeWidget, QTreeWidgetItem * item);
	void emitDisableMenu();
	void emitEnableMenu();
};

#endif /* LEFTLAYOUT_H_ */
