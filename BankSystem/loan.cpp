#include "loan.h"
#include "Psql.h"
#include "login.h"
#include "logup.h"
#include "osd.h"
#include <QtWidgets\qgridlayout.h>
#pragma execution_character_set("utf-8")
using namespace std;

LoanForm::LoanForm(QDialog* parent) :QDialog(parent) {
    this->setWindowTitle(tr("贷款"));
    this->resize(300, 200);
    this->setObjectName("Dia");
    this->setStyleSheet("#Dia{background-color:#f1feff;}");

    loanRateLbl = new QLabel(tr("本银行贷款月利率：0.1%（不满一月按一月）"));

    loanMoneyLbl = new QLabel(tr("贷款金额"));
    loanMoneyLEd = new QLineEdit;
    loanMoneyLEd->setText(tr(""));

    loanBtn = new QPushButton(tr("确定"));
    exitBtn = new QPushButton(tr("退出"));

    QGridLayout* grid_layout = new QGridLayout(this);
    grid_layout->addWidget(loanRateLbl,0,0,1,2);
    grid_layout->addWidget(loanMoneyLbl, 1, 0);
    grid_layout->addWidget(loanMoneyLEd, 1, 1);
    grid_layout->addWidget(exitBtn, 2, 0);
    grid_layout->addWidget(loanBtn, 2, 1);
    loanBtn->setObjectName("right");
    loanBtn->setStyleSheet("#right{background-color: #bcffb9;font-weight:bold;}#right:hover{background-color: #dbffd9;font-weight:bold;}");
    exitBtn->setObjectName("exit");
    exitBtn->setStyleSheet("#exit{background-color: #ff5d5d;font-weight:bold;color:#e8e8e8;}#exit:hover{background-color: #ff8989;font-weight:bold;color:#e8e8e8;}");

    connect(loanBtn, SIGNAL(clicked()), this, SLOT(loanMoney()));
    connect(exitBtn, SIGNAL(clicked()), this, SLOT(close()));

}

void LoanForm::loanMoney() {
    if (loanMoneyLEd->text().isEmpty()) {
        QMessageBox::warning(this, tr("错误！"), tr("输入不完整"), QMessageBox::Yes);
        return;
    }

    string tmp = "select loan,pass,priority,id from bankaccount.account where name = '" + UserName.toStdString() + "'";
    ExecSQL(tmp.c_str());

    if (SqlRes[0].toDouble() > Total) {
        QMessageBox::warning(this, tr("抱歉！"), tr("您的账户已经处于负债，不支持贷款操作"), QMessageBox::Yes);
        return;
    }

    string strM = loanMoneyLEd->text().toStdString();
    SYSTEMTIME ATN;
    GetLocalTime(&ATN);
    string currentTime = WORDToString(ATN.wYear) + "-" + FormatTwo(WORDToString(ATN.wMonth)) + "-" + FormatTwo(WORDToString(ATN.wDay)) + " " + FormatTwo(WORDToString(ATN.wHour)) + ":" + FormatTwo(WORDToString(ATN.wMinute)) + ":" + FormatTwo(WORDToString(ATN.wSecond));
    tmp = "INSERT INTO bankaccount.account(balance, pass, priority, time, name, id, income, expenditure) VALUES(" +
        strM + ", '" + SqlRes[1].toStdString() + "', " + SqlRes[2].toStdString() + ", '" + currentTime +
        "', '" + UserName.toStdString() + "', " + SqlRes[3].toStdString() + ", 1, 0)";
    ExecSQL(tmp.c_str());
    tmp = "UPDATE bankaccount.account set loan = " +
        strM + " where name = '" + UserName.toStdString() + "'";
    ExecSQL(tmp.c_str());
    QMessageBox::warning(this, tr("成功！"), tr("您已成功贷款，请按期还贷"), QMessageBox::Yes);

    accept();   //
}