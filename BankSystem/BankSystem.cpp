#include <Windows.h>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QProcess>
#include <QDebug>
#include <QAction>
#include <QTextEdit>
#include <QIcon>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QTextDocument>
#include <QTextCursor>
#include <QToolBar>
#include <QPushButton>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QtPrintSupport/QPageSetupDialog>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include "BankSystem.h"
#include "login.h"
#include "logup.h"
#include "OSD.h"
#include "developers.h"
#pragma execution_character_set("utf-8")
BankSystem::BankSystem(QWidget* parent) :  QMainWindow(parent){
    this->resize(QSize(1000, 600));
    this->setMaximumSize(1010,606);
    this->setMinimumSize(1000, 600);
    tipLbl = new QLabel(this);
    QString  st = "<h2>欢迎登录110100银行</h2>";
    
    this->setObjectName("AppMain");
    this->setStyleSheet("#AppMain{border-image:url(bg14.jpg);}");

    tipLbl->setText(st.toStdString().data());
    tipLbl->move(210, 30);
    
    tipLbl->setStyleSheet("color:#DEFEE4");
    QFont font1,font2;
    font1.setPointSize(24);
    font1.setBold(1);
    font2.setPointSize(18);
    tipLbl->setFont(font1);
    tipLbl->adjustSize();


    logupBtnM = new QPushButton(this);
    logupBtnM->setText("注册");
    logupBtnM->move(150, 500);
    logupBtnM->setFont(font2);
    logupBtnM->adjustSize();
    logupBtnM->setObjectName("logup");
    logupBtnM->setStyleSheet("#logup{background-color:#33CC33;border-color:#33CC33;color:white;}");

    loginBtnM = new QPushButton(this);
    loginBtnM->setText("登录");
    loginBtnM->move(740, 500);
    loginBtnM->setFont(font2);
    loginBtnM->adjustSize();
    loginBtnM->setObjectName("login");
    loginBtnM->setStyleSheet("#login{background-color:#33CC33;border-color:#33CC33;color:white;}");


    QPushButton* developerWE = new QPushButton(this);
    developerWE->setText("关于");
    developerWE->move(450, 450);
    developerWE->setFont(font2);
    developerWE->adjustSize();
    developerWE->setObjectName("des");
    developerWE->setStyleSheet("#des{background-color:#FAFAE2;border-color:#FAFAE2;color:grey;}");


    connect(loginBtnM, SIGNAL(clicked()), this, SLOT(loginMain()));
    connect(logupBtnM, SIGNAL(clicked()), this, SLOT(logupMain()));
    connect(developerWE, SIGNAL(clicked()), this, SLOT(DeveloperAct()));
}

void BankSystem::OSD_A(){
    OSDM* osd;
ATM:
    osd = new OSDM;
    if (osd->exec() == QDialog::Accepted)goto ATM;
}

void BankSystem::loginMain() {
    LoginForm inlog;
    if (inlog.exec() == QDialog::Accepted) {
        OSD_A();
    }
}

void BankSystem::DeveloperAct() {
    Developers des;
    des.exec();
}
void BankSystem::logupMain() {
    LogupForm uplog;
    if (uplog.exec() == QDialog::Accepted) {
        QMessageBox::warning(this, tr("提示"), tr("请重新登录"), QMessageBox::Yes);
    }
}