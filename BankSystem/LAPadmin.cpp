#include "LAPadmin.h"
#include "OSDadmin.h"
#include "Psql.h"
#include "login.h"
#include "logup.h"
#include "loan.h"
#include <QtWidgets\qgridlayout.h>
#pragma execution_character_set("utf-8")
using namespace std;

double loanM = 0.0;
string currentTime;
QString getTotal(QString UserN) {
    QString tmp = "select time,balance,income,expenditure from bankaccount.account where name = '" + UserN + "' order by time";
    ExecSQL(tmp.toStdString().data());
    double tot = 0.0;

    for (int i = 0; i < SqlRes.size() / 4; ++i) {
        int Jd = SqlRes[2 + i * 4].toInt() + SqlRes[3 + i * 4].toInt();
        if (Jd == 0) tot = SqlRes[1].toDouble();
        else if (SqlRes[2 + i * 4].toInt() == 1) {
            tot = tot + SqlRes[1 + i * 4].toDouble();
        }
        else {
            tot = tot - SqlRes[1 + i * 4].toDouble();
        }
    }
    tmp = "UPDATE bankaccount.account set total = " + QString::number(tot, 10, 6) + "where name = '" + UserN + "'";
    ExecSQL(tmp.toStdString().data());
    return QString::number(tot, 10, 6);
}

LAPADMIN::LAPADMIN(QDialog* parent) :QDialog(parent) {
    this->setWindowTitle(tr("用户贷款状况查询"));
    this->resize(300, 300);
    this->setObjectName("Dia");
    this->setStyleSheet("#Dia{background-color:#f1feff;}");

    clientLbl = new QLabel(tr("用户名"));
    clientLEd = new QLineEdit;
    clientLEd->setText(tr(""));
    loanLbl = new QLabel(tr("当前负债"));
    loanLEd = new QLineEdit;
    loanLEd->setReadOnly(1);
    loanLEd->setText(tr(""));

    checkBtn = new QPushButton(tr("确定"));
    exitBtn = new QPushButton(tr("退出"));

    QGridLayout* grid_layout = new QGridLayout(this);
    grid_layout->addWidget(clientLbl, 0, 0);
    grid_layout->addWidget(clientLEd, 0, 1);
    grid_layout->addWidget(loanLbl, 1, 0);
    grid_layout->addWidget(loanLEd, 1, 1);
    grid_layout->addWidget(checkBtn, 2, 0);
    grid_layout->addWidget(exitBtn, 2, 1);
    checkBtn->setObjectName("right");
    checkBtn->setStyleSheet("#right{background-color: #bcffb9;font-weight:bold;}#right:hover{background-color: #dbffd9;font-weight:bold;}");
    exitBtn->setObjectName("exit");
    exitBtn->setStyleSheet("#exit{background-color: #ff5d5d;font-weight:bold;color:#e8e8e8;}#exit:hover{background-color: #ff8989;font-weight:bold;color:#e8e8e8;}");

    connect(checkBtn, SIGNAL(clicked()), this, SLOT(checkLoan()));
    connect(exitBtn, SIGNAL(clicked()), this, SLOT(close()));
}

void LAPADMIN::checkLoan() {
    if (clientLEd->text().isEmpty()) {
        QMessageBox::warning(this, tr("错误！"), tr("输入不完整"), QMessageBox::Yes);
        return;
    }
    string tmp;
    Client = clientLEd->text();
    if(clientLEd->text()!=UserName)
         tmp = "select loan,time from bankaccount.account where name = '" + Client.toStdString() + "' AND proority <" + QString::number(priRight).toStdString();
    else 
        tmp = "select loan,time from bankaccount.account where name = '" + Client.toStdString() + "'";
    ExecSQL(tmp.c_str());
    if (SqlRes.isEmpty()) {
        QMessageBox::warning(this, tr("错误！"), tr("该用户不存在"), QMessageBox::Yes);
        return;
    }

    SYSTEMTIME ATN;
    GetLocalTime(&ATN);
    currentTime = WORDToString(ATN.wYear) + "-" + FormatTwo(WORDToString(ATN.wMonth)) + "-" + FormatTwo(WORDToString(ATN.wDay)) + " " + FormatTwo(WORDToString(ATN.wHour)) + ":" + FormatTwo(WORDToString(ATN.wMinute)) + ":" + FormatTwo(WORDToString(ATN.wSecond));

    loanM = SqlRes[0].toDouble();
    string tm = SqlRes[1].toStdString();
    int T = atoi(tm.substr(5, 2).c_str());                  //月份抓出来
    T = atoi(WORDToString(ATN.wMonth).c_str()) - T;         //计算借了多长时间了，不满一个月按一个月算
    if (atoi(tm.substr(8, 2).c_str()) < atoi(WORDToString(ATN.wDay).c_str())) T++;
    for (int i = 0;i < T;i++) loanM = loanM * (1.0 + rate);
    loanLEd->setText(QString::number(loanM, 10, 4));

    getTotal(clientLEd->text());
    accept();
}