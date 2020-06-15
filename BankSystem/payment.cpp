#include "payment.h"
#include "loan.h"
#include "Psql.h"
#include "login.h"
#include "logup.h"
#include <QtWidgets\qgridlayout.h>
#pragma execution_character_set("utf-8")
using namespace std;

double loanM = 0.0;
string currentTime;

PaymentForm::PaymentForm(QDialog* parent) :QDialog(parent) {
    this->setWindowTitle(tr("还款"));
    this->resize(300, 300);
    this->setObjectName("Dia");
    this->setStyleSheet("#Dia{background-color:#f1feff;}");

    SYSTEMTIME ATN;
    GetLocalTime(&ATN);
    currentTime = WORDToString(ATN.wYear) + "-" + FormatTwo(WORDToString(ATN.wMonth)) + "-" + FormatTwo(WORDToString(ATN.wDay)) + " " + FormatTwo(WORDToString(ATN.wHour)) + ":" + FormatTwo(WORDToString(ATN.wMinute)) + ":" + FormatTwo(WORDToString(ATN.wSecond));
    string tmp = "select loan,time from bankaccount.account where name = '" + UserName.toStdString() + "'";
    ExecSQL(tmp.c_str());

    loanM = SqlRes[0].toDouble();
    string tm = SqlRes[1].toStdString();
    int T = atoi(tm.substr(5, 2).c_str());                  //月份抓出来
    T = atoi(WORDToString(ATN.wMonth).c_str()) - T;         //计算借了多长时间了，不满一个月按一个月算
    if (atoi(tm.substr(8, 2).c_str()) < atoi(WORDToString(ATN.wDay).c_str())) T++;
    for (int i = 0;i < T;i++) loanM = loanM * (1.0 + rate);

    loanLbl = new QLabel(tr("当前负债"));
    loanLEd = new QLineEdit;
    loanLEd->setReadOnly(1);
    loanLEd->setText(QString::number(loanM, 10, 4));
    paymentLbl = new QLabel(tr("还款金额"));
    paymentLEd = new QLineEdit;
    paymentLEd->setText(tr(""));

    payBtn = new QPushButton(tr("确定"));
    exitBtn = new QPushButton(tr("退出"));

    QGridLayout* grid_layout = new QGridLayout(this);
    grid_layout->addWidget(loanLbl, 0, 0);
    grid_layout->addWidget(loanLEd, 0, 1);
    grid_layout->addWidget(paymentLbl, 1, 0);
    grid_layout->addWidget(paymentLEd, 1, 1);
    grid_layout->addWidget(exitBtn, 2, 0);
    grid_layout->addWidget(payBtn, 2, 1);
    payBtn->setObjectName("right");
    payBtn->setStyleSheet("#right{background-color: #bcffb9;font-weight:bold;}#right:hover{background-color: #dbffd9;font-weight:bold;}");
    exitBtn->setObjectName("exit");
    exitBtn->setStyleSheet("#exit{background-color: #ff5d5d;font-weight:bold;color:#e8e8e8;}#exit:hover{background-color: #ff8989;font-weight:bold;color:#e8e8e8;}");

    connect(payBtn, SIGNAL(clicked()), this, SLOT(payment()));
    connect(exitBtn, SIGNAL(clicked()), this, SLOT(close()));

}

void PaymentForm::payment() {
    if (paymentLEd->text().isEmpty()) {
        QMessageBox::warning(this, tr("错误！"), tr("输入不完整"), QMessageBox::Yes);
        return;
    }

    if (loanM <= 0) {
        QMessageBox::warning(this, tr("抱歉！"), tr("您的账户不是负债状态，不支持还款操作"), QMessageBox::Yes);
        return;
    }

    double payM = paymentLEd->text().toDouble();       //还款金额

    string tmp = "select total from bankaccount.account where name = '" + UserName.toStdString() + "'";
    ExecSQL(tmp.c_str());
    double tot = SqlRes[0].toDouble();
    if (tot < payM) {
        QMessageBox::warning(this, tr("抱歉！"), tr("您的账户余额无法支付还款金额"), QMessageBox::Yes);
        return;
    }

    QString strM;
    if (payM >= loanM) payM = loanM;
    strM = QString::number(loanM - payM, 10, 6);
    QString strP = QString::number(payM, 10, 6);
    tmp = "UPDATE bankaccount.account SET loan =" + strM.toStdString() + " where name = '" + UserName.toStdString() + "'";
    ExecSQL(tmp.c_str());
    tmp = "select pass,id,priority from bankaccount.account where name = '" + UserName.toStdString() + "'";
    ExecSQL(tmp.c_str());
    tmp = "INSERT INTO bankaccount.account (balance,pass,priority,time,name,id,income,expenditure) VALUES (" + strP.toStdString() + ", '" + SqlRes[0].toStdString() + "'," + SqlRes[2].toStdString() + ", '" + currentTime + "', '" + UserName.toStdString() + "'," + SqlRes[1].toStdString() + ",0,1)";
    ExecSQL(tmp.c_str());

    if (payM < loanM) {           //还款金额小于贷款金额
        QMessageBox::warning(this, tr("成功！"), tr("您已成功还款"), QMessageBox::Yes);
    }
    else {                        //还款金额大于等于贷款金额
        QMessageBox::warning(this, tr("成功！"), tr("您已成功还款！当前负债为0.00，账户已支持贷款操作"), QMessageBox::Yes);
    }

    accept();     //贷款成功后立刻退出
}