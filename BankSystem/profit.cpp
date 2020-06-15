#include"profit.h"
#include"login.h"
#include"OSD.h"
#include <QtWidgets\qgridlayout.h>
#pragma execution_character_set("utf-8")
using namespace std;

Profit::Profit(QDialog* parent):QDialog(parent) {
    this->setWindowTitle(tr("利润预估"));
    this->resize(400, 300);
    this->setObjectName("Dia");
    this->setStyleSheet("#Dia{background-color:#f1feff;}");

  /*  userNameLbl = new QLabel(tr("用户名"));
    userNameLEd = new QLineEdit;
    userNameLEd->setText(tr(""));*/
    yearlyRateLbl = new QLabel(tr("预计年利率"));
    yearlyRateLEd = new QLineEdit;
    yearlyRateLEd->setText("");
    tmLbl = new QLabel(tr("存款时长"));
    tmLEd = new QLineEdit;
    tmLEd->setText("");
    profitLbl = new QLabel(tr("预期收益"));
    profitLEd = new QLineEdit;
    profitLEd->setReadOnly(1);                 //只读

    checkBtn = new QPushButton(tr("确定"));
    exitBtn = new QPushButton(tr("退出"));

    QGridLayout* grid_layout = new QGridLayout(this);
//    grid_layout->addWidget(userNameLbl, 0, 0);
//    grid_layout->addWidget(userNameLEd, 0, 1);
    grid_layout->addWidget(yearlyRateLbl, 0, 0);
    grid_layout->addWidget(yearlyRateLEd, 0, 1);
    grid_layout->addWidget(tmLbl, 1, 0);
    grid_layout->addWidget(tmLEd, 1, 1);
    grid_layout->addWidget(profitLbl, 2, 0);
    grid_layout->addWidget(profitLEd, 2, 1);
    grid_layout->addWidget(checkBtn, 0, 2);
    grid_layout->addWidget(exitBtn, 1, 2);
    checkBtn->setObjectName("right");
    checkBtn->setStyleSheet("#right{background-color: #bcffb9;font-weight:bold;}#right:hover{background-color: #dbffd9;font-weight:bold;}");
    exitBtn->setObjectName("exit");
    exitBtn->setStyleSheet("#exit{background-color: #ff5d5d;font-weight:bold;color:#e8e8e8;}#exit:hover{background-color: #ff8989;font-weight:bold;color:#e8e8e8;}");

    connect(checkBtn, SIGNAL(clicked()), this, SLOT(CheckProfit()));
    connect(exitBtn, SIGNAL(clicked()), this, SLOT(close()));
    
}

void Profit::CheckProfit() {
    if (/*userNameLEd->text().isEmpty() ||*/ yearlyRateLEd->text().isEmpty() || tmLEd->text().isEmpty()) {
        QMessageBox::warning(this, tr("错误！"), tr("输入不完整"), QMessageBox::Yes);
        return;
    }
    QString p0 = yearlyRateLEd->text();        //利率
    QString t0 = tmLEd->text();                //存款时长
    double p = p0.toDouble();
    double b = Total;        //balance
    int t = t0.toInt();
    double ans = b;
    for (int i = 0; i < t; i++)
        ans = ans * (1.0 + p), qDebug() << ans<<p;
    ans -= b;
    profitLEd->setText(QString::number(ans, 10, 4));
   // accept();
}
