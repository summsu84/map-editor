/********************************************************************************
** Form generated from reading UI file 'NodeInfo.ui'
**
** Created: Wed Jul 9 17:25:42 2014
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NODEINFO_H
#define UI_NODEINFO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_NodeInfoClass
{
public:
    QPushButton *btnClose;
    QLineEdit *txtName;
    QLineEdit *lineEdit_2;
    QLabel *label;
    QLabel *label_2;
    QGroupBox *groupBox;
    QLineEdit *txtX;
    QLabel *label_3;
    QLineEdit *txtY;
    QLabel *label_4;

    void setupUi(QDialog *NodeInfoClass)
    {
        if (NodeInfoClass->objectName().isEmpty())
            NodeInfoClass->setObjectName(QString::fromUtf8("NodeInfoClass"));
        NodeInfoClass->resize(525, 264);
        btnClose = new QPushButton(NodeInfoClass);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setGeometry(QRect(210, 220, 88, 27));
        txtName = new QLineEdit(NodeInfoClass);
        txtName->setObjectName(QString::fromUtf8("txtName"));
        txtName->setGeometry(QRect(130, 44, 113, 27));
        lineEdit_2 = new QLineEdit(NodeInfoClass);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(130, 110, 113, 27));
        label = new QLabel(NodeInfoClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 50, 100, 17));
        label_2 = new QLabel(NodeInfoClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 110, 60, 17));
        groupBox = new QGroupBox(NodeInfoClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(290, 40, 211, 111));
        txtX = new QLineEdit(groupBox);
        txtX->setObjectName(QString::fromUtf8("txtX"));
        txtX->setGeometry(QRect(100, 30, 70, 27));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 40, 40, 17));
        txtY = new QLineEdit(groupBox);
        txtY->setObjectName(QString::fromUtf8("txtY"));
        txtY->setGeometry(QRect(100, 80, 70, 27));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 80, 40, 17));

        retranslateUi(NodeInfoClass);

        QMetaObject::connectSlotsByName(NodeInfoClass);
    } // setupUi

    void retranslateUi(QDialog *NodeInfoClass)
    {
        NodeInfoClass->setWindowTitle(QApplication::translate("NodeInfoClass", "NodeInfo", 0, QApplication::UnicodeUTF8));
        btnClose->setText(QApplication::translate("NodeInfoClass", "Close", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("NodeInfoClass", "Node Name :", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("NodeInfoClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("NodeInfoClass", "Pos", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("NodeInfoClass", "X :", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("NodeInfoClass", "Y :", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NodeInfoClass: public Ui_NodeInfoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NODEINFO_H
