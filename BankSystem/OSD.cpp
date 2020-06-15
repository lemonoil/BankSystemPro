#include "OSD.h"
#include "Psql.h"
#include "login.h"
#include "logup.h"
#include "profit.h"
#include "LAP.h"
#include "Transition.h"
#include "developers.h"
#pragma execution_character_set("utf-8")
OSDM::OSDM(QDialog* parent) :QDialog(parent){
	this->setWindowTitle(tr("账户信息"));
    InfoOSD();
    this->resize(1000, 500);
    this->setObjectName("Dia");
    this->setStyleSheet("#Dia{background-color:#f1feff;}");

}

void OSDM::InfoOSD() {

    mainLayout = new QGridLayout;
    mainLayout->setSpacing(10);  
    mainLayout->setMargin(10);   
    QPushButton*  refreshDialog = new QPushButton(tr("刷新"));
    
    addIn = new QPushButton("加入记录");
    changPass = new QPushButton("修改密码");
    QPushButton* exitBtn = new QPushButton("退出");
    profitBtn = new QPushButton("利润预估");
    //添加QTableView代码
    tableView = new QTableView;
    QStandardItemModel * standItemModel = new QStandardItemModel();

    //添加表头
    standItemModel->setColumnCount(5);
    standItemModel->setHorizontalHeaderLabels({ "User Name", "Time", "Money", "In/Out","Balance" });

    Total = 0.0;
    QString tmp;
    tmp = "select count(time) from bankaccount.account where name = '" + UserName + "'";
    ExecSQL(tmp.toStdString().data());
    int Cnt = SqlRes[0].toInt();
    tmp = "select time,balance,income,expenditure from bankaccount.account where name = '" + UserName + "' order by time";
    ExecSQL(tmp.toStdString().data());
    
    //standItemModel->setItem(0, 0, new QStandardItem("状态"));
    qDebug() << Cnt;
    for (int i = 0; i < Cnt; ++i) {
        if (i == 0)standItemModel->setItem(i, 0, new QStandardItem(UserName));
        else standItemModel->setItem(i, 0, new QStandardItem("---"));
        standItemModel->setItem(i, 1, new QStandardItem(SqlRes[0 + i * 4]));
        standItemModel->setItem(i, 2, new QStandardItem(SqlRes[1 + i * 4]));
        int Jd = SqlRes[2 + i * 4].toInt() + SqlRes[3 + i * 4].toInt();
        if (Jd == 0) Total = SqlRes[1].toDouble(), standItemModel->setItem(i, 3, new QStandardItem("NULL"));
        else if (SqlRes[2 + i * 4].toInt() == 1) {
            Total = Total + SqlRes[1 + i * 4].toDouble();
            standItemModel->setItem(i, 3, new QStandardItem("+"));
        }
        else {
            Total = Total - SqlRes[1 + i * 4].toDouble();
            standItemModel->setItem(i, 3, new QStandardItem("-"));
        }
        standItemModel->setItem(i, 4, new QStandardItem(QString::number(Total, 10, 6)));
    }
    tableView->setModel(standItemModel);
    
    tmp = "UPDATE bankaccount.account set total = "+ QString::number(Total, 10, 6) + "where name = '"+UserName + "'";
    ExecSQL(tmp.toStdString().data());
    //设置表格属性
    tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);   
    tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
    tableView->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Fixed);

    tableView->setColumnWidth(0, 150);
    tableView->setColumnWidth(1, 270);
    tableView->setColumnWidth(2, 200);
    tableView->setColumnWidth(3, 100);
    tableView->setColumnWidth(4, 200);

    
    tableView->verticalHeader()->hide();   
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows); 
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); 

    tableView->setMinimumSize(950, 500);
    tableView->setShowGrid(false);
    QPushButton* tmpA = refreshDialog;
    QPushButton* tmpB = addIn;
    QPushButton* tmpC = changPass;
    QPushButton* tmpD = profitBtn;
    QPushButton* tmpE = new QPushButton("贷款服务");
    QPushButton* tmpF = exitBtn;
    QPushButton* tmpG = new QPushButton("转账");
    QPushButton* tmpH = new QPushButton("开发人员");
    mainLayout->addWidget(tableView,0,1,7,1);  
    mainLayout->addWidget(tmpA,0, 0);
    mainLayout->addWidget(tmpB,2, 0);
    mainLayout->addWidget(tmpE,4, 0);
    mainLayout->addWidget(tmpC,0, 2);
    mainLayout->addWidget(tmpD,2, 2);
    mainLayout->addWidget(tmpG,4, 2);
    mainLayout->addWidget(tmpF, 6, 2);
    mainLayout->addWidget(tmpH, 6, 0);
    tmpA->setObjectName("A");
    tmpA->setStyleSheet("#A{background-color: #f8fbaf;font-weight:bold;}#A:hover{background-color: #fdfedf;font-weight:bold;}");
    tmpB->setObjectName("B");
    tmpB->setStyleSheet("#B{background-color: #f8fbaf;}#B:hover{background-color: #fdfedf;}");
    tmpC->setObjectName("C");
    tmpC->setStyleSheet("#C{background-color: #f8fbaf;}#C:hover{background-color: #fdfedf;}");
    tmpD->setObjectName("D");
    tmpD->setStyleSheet("#D{background-color: #f8fbaf;}#D:hover{background-color: #fdfedf;}");
    tmpE->setObjectName("E");
    tmpE->setStyleSheet("#E{background-color: #f8fbaf;}#E:hover{background-color: #fdfedf;}");
    tmpG->setObjectName("G");
    tmpG->setStyleSheet("#G{background-color: #f8fbaf;}#G:hover{background-color: #fdfedf;}");
    tmpH->setObjectName("H");
    tmpH->setStyleSheet("#H{background-color: #f8fbaf;}#H:hover{background-color: #fdfedf;}");
    tmpF->setObjectName("exit");
    tmpF->setStyleSheet("#exit{background-color: #ff5d5d;font-weight:bold;color:#e8e8e8;}#exit:hover{background-color: #ff8989;font-weight:bold;color:#e8e8e8;}");

    mainLayout->setColumnMinimumWidth(1, 500);
    this->setLayout(mainLayout);    
    connect(addIn, SIGNAL(clicked()), this, SLOT(addInfo()));
    connect(refreshDialog, SIGNAL(clicked()), this, SLOT(accept()));
    connect(changPass, SIGNAL(clicked()), this, SLOT(chgPass()));
    connect(exitBtn, SIGNAL(clicked()), this, SLOT(close()));
    connect(profitBtn, SIGNAL(clicked()), this, SLOT(profitP()));
    connect(tmpE, SIGNAL(clicked()), this, SLOT(LoAn()));
    connect(tmpG, SIGNAL(clicked()), this, SLOT(TAS()));
    connect(tmpH, SIGNAL(clicked()), this, SLOT(developers()));
}

void OSDM::addInfo() {
    ADDMoney *Add_part;
    Add_part = new ADDMoney;
    Add_part->exec();
}
void OSDM::chgPass() {
    ChangePass* Ch_part;
    Ch_part = new ChangePass;
    Ch_part->exec();
}

void OSDM::LoAn() {
    LAPM* LAP_part;
    LAP_part = new LAPM;
    LAP_part->exec();
}
void OSDM::profitP() {
    Profit* Bk;
    Bk = new Profit;
    Bk->exec();
}
void OSDM::TAS()
{
    Transition* Bk;
    Bk = new Transition;
    Bk->exec();
}
void OSDM::developers()
{
    Developers* De;
    De = new Developers;
    De->exec();
}
ADDMoney::ADDMoney(QDialog* parent) :QDialog(parent) {
    this->setWindowTitle(tr("收入/支出"));
    this->resize(325,100);
    this->setObjectName("Dia");
    this->setStyleSheet("#Dia{background-color:#f1feff;}");
    MoneyIn = new QLabel(tr("金额"));
    InLab = new QLabel(tr("收入"));
    OutLab = new QLabel(tr("支出"));
    RightBtn = new QPushButton(tr("确定"));
    ActionM = new QLineEdit;
    ActionM->setText(tr(""));
    InComeBtn = new QRadioButton;
    OutComeBtn = new QRadioButton;
    QGridLayout* grid_layout = new QGridLayout(this);
    grid_layout->addWidget(MoneyIn, 0, 0);
    grid_layout->addWidget(ActionM, 0, 1);
    grid_layout->addWidget(RightBtn, 0, 3);
    RightBtn->setObjectName("right");
    RightBtn->setStyleSheet("#right{background-color: #bcffb9;font-weight:bold;}#right:hover{background-color: #dbffd9;font-weight:bold;}");
    QHBoxLayout* radio_layout = new QHBoxLayout;
    radio_layout->addWidget(InLab);
    radio_layout->addWidget(InComeBtn);

    radio_layout->addWidget(OutLab);
    radio_layout->addWidget(OutComeBtn);
    QGroupBox* group_radio = new QGroupBox(tr("模式"), this);
    group_radio->setLayout(radio_layout);
    grid_layout->addWidget(group_radio, 1, 1);

    connect(RightBtn, SIGNAL(clicked()), this, SLOT(EventAd()));
}

void ADDMoney::EventAd() {
    if (ActionM->text().isEmpty()) {
        qDebug() << "EM";
        return;
    }
    if ((InComeBtn->isChecked() + OutComeBtn->isChecked()) == 0) {
        qDebug() << "INOUT";
        return;
    }
    QString strM = ActionM->text();
    SYSTEMTIME ATN;
    GetLocalTime(&ATN);
    string tmp = "select pass,id,priority from bankaccount.account where name = '" + UserName.toStdString()+"'";
    ExecSQL(tmp.c_str());
    string currentTime = WORDToString(ATN.wYear) + "-" + FormatTwo(WORDToString(ATN.wMonth)) + "-" + FormatTwo(WORDToString(ATN.wDay)) + " " + FormatTwo(WORDToString(ATN.wHour)) + ":" + FormatTwo(WORDToString(ATN.wMinute)) + ":" + FormatTwo(WORDToString(ATN.wSecond));
    if (InComeBtn->isChecked()) 
        tmp = "INSERT INTO bankaccount.account (time,balance,pass,priority,name,id,income,expenditure) VALUES ('" + currentTime + "',"+ strM.toStdString() + ", '" + SqlRes[0].toStdString() + "'," + SqlRes[2].toStdString() + ", '"  + UserName.toStdString() + "'," + SqlRes[1].toStdString() + ",1,0)";
    else 
        tmp = "INSERT INTO bankaccount.account (time,balance,pass,priority,name,id,income,expenditure) VALUES ('" + currentTime+"',"+ strM.toStdString() + ", '" + SqlRes[0].toStdString() + "'," + SqlRes[2].toStdString()   + ", '" + UserName.toStdString() + "'," + SqlRes[1].toStdString() + ",0,1)";
    ExecSQL(tmp.c_str());

    QMessageBox::warning(this, tr("成功！"), tr("加入记录成功"), QMessageBox::Yes);
    accept();
}


ChangePass::ChangePass(QDialog* parent):QDialog(parent) {
    this->setWindowTitle(tr("修改密码"));
    this->resize(325, 100);
    this->setObjectName("Dia");
    this->setStyleSheet("#Dia{background-color:#f1feff;}");

    ChPass = new QLabel(tr("新密码"));
    AgPass = new QLabel(tr("重复输入"));
    ActionM = new QLineEdit;
    ActionM->setText(tr(""));
    ActionM->setEchoMode(QLineEdit::Password);
    ActionA = new QLineEdit;
    ActionA->setText(tr(""));
    ActionA->setEchoMode(QLineEdit::Password);
    RightBtn = new QPushButton(tr("确定"));


    QGridLayout* grid_layout = new QGridLayout(this);
    grid_layout->addWidget(ChPass, 0, 0);
    grid_layout->addWidget(AgPass, 1, 0);
    grid_layout->addWidget(ActionM, 0, 1);
    grid_layout->addWidget(ActionA, 1, 1);
    grid_layout->addWidget(RightBtn, 2, 1);
    RightBtn->setObjectName("right");
    RightBtn->setStyleSheet("#right{background-color: #bcffb9;font-weight:bold;}#right:hover{background-color: #dbffd9;font-weight:bold;}");

    connect(RightBtn, SIGNAL(clicked()), this, SLOT(EventCh()));
}

void ChangePass::EventCh() {
    if (ActionM->text().isEmpty() || ActionA->text().isEmpty()) {
        QMessageBox::warning(this, tr("错误！"), tr("输入不完整"), QMessageBox::Yes);
        return;
    }
    if (ActionM->text() != ActionA->text()) {
        QMessageBox::warning(this, tr("错误！"), tr("两次输入密码不一致"), QMessageBox::Yes);
        return;
    }
    string tmp = "UPDATE bankaccount.account SET pass = '"+ActionM->text().toStdString()+"' WHERE name = '" + UserName.toStdString() + "'";
    ExecSQL(tmp.c_str());
    QMessageBox::warning(this, tr("成功！"), tr("已修改密码"), QMessageBox::Yes);
    accept();
}
