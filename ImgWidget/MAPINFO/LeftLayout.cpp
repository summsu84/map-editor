/*
 * LeftLayout.cpp
 *
 *  Created on: 2013. 5. 22.
 *      Author: jiwon
 */

#include "LeftLayout.h"
#include <QComboBox>
#include <QDebug>
#include <QStringList>
LeftLayout::LeftLayout(DrawingMode mode, QWidget * parent)
: QTreeWidget(parent)
{
	// TODO Auto-generated constructor stub
	this->mode = mode;
	init();
}

LeftLayout::~LeftLayout() {
	// TODO Auto-generated destructor stub
}

void LeftLayout::init()
{
	qDebug()<<"init..";

	//Set QtreeWidget Column Header (FileName, Layer_name)
	QTreeWidgetItem * headerItem = new QTreeWidgetItem();
	if(mode == SMSMap){
		headerItem->setText(0, QString("LAYER_NAME"));
	}else{
		headerItem->setText(0, QString("OBJECT_NAME"));
	}
	this->setHeaderItem(headerItem);
}

void LeftLayout::removeItems()
{
	QTreeWidgetItem * item = this->currentItem();
	int i = this->indexOfTopLevelItem(item);
	this->takeTopLevelItem(i);
	delete item;
}


/**
 * MapInfo로부터 받아온 레이어 및 맵 정보를 바탕으로 트리를 생성한다..
 */
void LeftLayout::genTreeMenu(QVector<LAYER_MAP> layer_map_list)
{
	//qDebug()<<"Layers name :"<<layers;

	this->clear();

	for(int i = 0 ; i < layer_map_list.size() ; i++){
		LAYER_MAP layer_map = layer_map_list.at(i);
		QTreeWidgetItem * item = new QTreeWidgetItem();
		item->setText(0, layer_map.layer_id);	//Root
		item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
		item->setCheckState(0, Qt::Checked);
		for(int j = 0 ; j < layer_map.map_id_list.size() ; j++){
			QString map_id = layer_map.map_id_list.at(j);
			QTreeWidgetItem * layer = new QTreeWidgetItem();
			QComboBox * cboColor = new QComboBox;
			cboColor->addItem("test1");

			layer->setText(0, map_id);
			layer->setFlags(layer->flags() | Qt::ItemIsUserCheckable);
			if(layer_map.isEnable[j] == true)
				layer->setCheckState(0,Qt::Checked);
			else
				layer->setCheckState(0,Qt::Unchecked);
			//connect(chkHeader[i], SIGNAL(stateChanged(int)), this, SLOT(runCheckState()));
			this->setItemWidget(layer, 1, cboColor);

			item->addChild(layer);
			map_controller_list.append(layer);
		}
		this->addTopLevelItem(item);
	}

	checkParentItemBottomToUpper();
	connect(this, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(runCheckState(QTreeWidgetItem * , int)));
	//
	qDebug()<<"[LeftLayout] genTreeMenu close..";
}

/**
 * 아이템을 클릭시 호출됨..
 */
void LeftLayout::runCheckState(QTreeWidgetItem * item , int column)
{
	qDebug()<<"[LeftLayout] runCheckState.. "<<item->text(0);

	//루트 아이템인지 체크 한다. 루트 아이템을 클릭햇을 시 만약 체크일 경우 아래 하위 아이템들을 모두 체크 한다.
	if(checkParentItem(item) == 0){

		return;
	}

	//루트 아이템인 경우 위의 소스코드에 의해서 return 되며, 루트가 아닌 경우 아래 소스 코드를 실행 한다.
	//만약 하위 아이템 중 언체크가 발견 되었을 경우 루트 아이템도 언체크로 만든다.
	qDebug()<<"after..";
	if(item->checkState(0) == Qt::Unchecked){
		item->parent()->setCheckState(0, Qt::PartiallyChecked);
	}

	emitTreeItemList(this, item);
}

/**
 * 루트 아이템을 클릭했을 때, 하위 아이템을 모두 선택 또는 모두 해제 한다..
 */
int LeftLayout::checkParentItem(QTreeWidgetItem * item)
{
	QList<QTreeWidgetItem*> top_item_list;

	for(int i = 0 ; i < this->topLevelItemCount() ; i++){
		top_item_list.append(this->topLevelItem(i));
	}

	for(int i = 0 ; i < top_item_list.size() ; i++){
		if(item == top_item_list.at(i)){
			qDebug()<<"Root item is clicked..";
			//루트를 클릭시 레이어 인포의 버튼 및 텍스트 위젯을 disable 시킨다.
			emit emitDisableMenu();
			if(item->checkState(0) == Qt::Checked)
			{
				qDebug()<<"Checked..";
				runSelectAll(i);
				return 0;
			}else{
				qDebug()<<"UnChecked..";
				runDeSelectAll(i);
				return 0;
			}
		}else{
			emit emitEnableMenu();
		}
	}

	return 1;
}

//하위 아이템들을 검사하여 하위 아이템 중에 모두 체크 되어 있는 경우 루트 아이템을 Checked 하게 만든다..
void LeftLayout::checkParentItemBottomToUpper()
{
	qDebug()<<"CheckParentItemBottomToUpper is called..";
	QList<QTreeWidgetItem*> top_item_list;

	for(int i = 0 ; i < this->topLevelItemCount() ; i++){
		top_item_list.append(this->topLevelItem(i));
	}

	for(int i = 0 ; i < top_item_list.size() ; i++){
		QTreeWidgetItem * top_item = top_item_list.at(i);
		bool checked = true;
		for(int j = 0 ; j < top_item->childCount() ; j++){
			QTreeWidgetItem * item = top_item->child(j);
			if(item->checkState(0) == Qt::Unchecked){
				checked = false;
				break;
			}
		}
		if(checked == true){
			top_item->setCheckState(0, Qt::Checked);
		}else{
			top_item->setCheckState(0, Qt::Unchecked);
		}
	}
	qDebug()<<"CheckParentItemBottomToUpper close..";
}

void LeftLayout::runSelectAll()
{
	qDebug()<<"[Leftlayout] runSelectAll is called..";
	QList<QTreeWidgetItem*> top_item_list;
	for(int i = 0 ; i < this->topLevelItemCount() ; i++){
		top_item_list.append(this->topLevelItem(i));
	}

	for(int i = 0 ; i < top_item_list.size() ; i++){
		QTreeWidgetItem * top_item = top_item_list.at(i);
		for(int j = 0 ; j < top_item->childCount() ; j++){
			QTreeWidgetItem * item = top_item->child(j);
			if(item->checkState(0) == Qt::Unchecked){
				item->setCheckState(0, Qt::Checked);
			}
		}
	}

	emitTreeItemList(this, 0);
}

void LeftLayout::runSelectAll(int index)
{
	qDebug()<<"[Leftlayout] runSelectAll is called..";
	QTreeWidgetItem * top_item = this->topLevelItem(index);
	for(int j = 0 ; j < top_item->childCount() ; j++){
		QTreeWidgetItem * item = top_item->child(j);
		if(item->checkState(0) == Qt::Unchecked){
			item->setCheckState(0, Qt::Checked);
		}
	}


	emitTreeItemList(this, 0);
}


void LeftLayout::runDeSelectAll()
{
	qDebug()<<"[Leftlayout] runDeSelectAll is called..";
	QList<QTreeWidgetItem*> top_item_list;
	for(int i = 0 ; i < this->topLevelItemCount() ; i++){
		top_item_list.append(this->topLevelItem(i));
	}

	for(int i = 0 ; i < top_item_list.size() ; i++){
		QTreeWidgetItem * top_item = top_item_list.at(i);
		for(int j = 0 ; j < top_item->childCount() ; j++){
			QTreeWidgetItem * item = top_item->child(j);
			if(item->checkState(0) == Qt::Checked){
				item->setCheckState(0, Qt::Unchecked);
			}
		}
	}

	this->checkParentItemBottomToUpper();
	emitTreeItemList(this, 0);
}


void LeftLayout::runDeSelectAll(int index)
{
	qDebug()<<"[Leftlayout] runDeSelectAll is called..";
	QTreeWidgetItem * top_item = this->topLevelItem(index);
	for(int j = 0 ; j < top_item->childCount() ; j++){
		QTreeWidgetItem * item = top_item->child(j);
		if(item->checkState(0) == Qt::Checked){
			item->setCheckState(0, Qt::Unchecked);
		}
	}


	emitTreeItemList(this, 0);
}

void LeftLayout::callTreeItemList(QTreeWidgetItem * item)
{
	emitTreeItemList(this, item);
}
