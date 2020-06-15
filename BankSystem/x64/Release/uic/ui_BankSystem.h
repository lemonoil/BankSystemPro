/********************************************************************************
** Form generated from reading UI file 'BankSystem.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BANKSYSTEM_H
#define UI_BANKSYSTEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BankSystemClass
{
public:
    QWidget *centralWidget;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BankSystemClass)
    {
        if (BankSystemClass->objectName().isEmpty())
            BankSystemClass->setObjectName(QString::fromUtf8("BankSystemClass"));
        BankSystemClass->resize(924, 453);
        centralWidget = new QWidget(BankSystemClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        BankSystemClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(BankSystemClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        BankSystemClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(BankSystemClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        BankSystemClass->setStatusBar(statusBar);

        retranslateUi(BankSystemClass);

        QMetaObject::connectSlotsByName(BankSystemClass);
    } // setupUi

    void retranslateUi(QMainWindow *BankSystemClass)
    {
        BankSystemClass->setWindowTitle(QCoreApplication::translate("BankSystemClass", "BankSystem", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BankSystemClass: public Ui_BankSystemClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BANKSYSTEM_H
