#include "OSDadmin.h"
#include "LAPadmin.h"
#include "Tadmin.h"
#include "Psql.h"
#include "login.h"
#include "logup.h"
#include "developers.h"
#pragma execution_character_set("utf-8")
using namespace std;

OSDADMIN::OSDADMIN(QDialog* parent) :QDialog(parent) {
    this->setWindowTitle(tr("管理员界面"));
    InfoOSD();
    this->resize(800, 500);
    this->setObjectName("Dia");
    this->setStyleSheet("#Dia{background-color:#f1feff;}");

}
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
void OSDADMIN::InfoOSD() {

    mainLayout = new QGridLayout;
    mainLayout->setSpacing(10);
    mainLayout->setMargin(10);
    QPushButton* refreshDialog = new QPushButton(tr("刷新"));

    addIn = new QPushButton("调整用户记录");
    changPass = new QPushButton("修改用户密码");
    QPushButton* exitBtn = new QPushButton("退出");
    //添加QTableView代码
    tableView = new QTableView;
    QStandardItemModel* standItemModel = new QStandardItemModel();

    //添加表头
    standItemModel->setColumnCount(4);
    standItemModel->setHorizontalHeaderLabels({ "User Name", "Balance", "loan","priority" });

    //遍历用户
    QString tmp = "select priority from bankaccount.account where name = '"+UserName + "'";
    ExecSQL(tmp.toStdString().data());
    tmp = "select distinct name,loan,priority,total from bankaccount.account where priority < "+SqlRes[0];
    ExecSQL(tmp.toStdString().data());
    QVector<QString> Vname = SqlRes;
    tmp = "select distinct name,loan,priority,total from bankaccount.account where name ='" + UserName +"'";
    ExecSQL(tmp.toStdString().data());
    for (int i = SqlRes.size()-1; i >=0 ; --i)
        Vname.push_front(SqlRes[i]);
    for (int i = 0; i < Vname.size() / 4; ++i) {
        standItemModel->setItem(i, 0, new QStandardItem(Vname[0 + i * 4]));
        standItemModel->setItem(i, 1, new QStandardItem(Vname[3 + i * 4]));
        standItemModel->setItem(i, 2, new QStandardItem(Vname[1 + i * 4]));
        standItemModel->setItem(i, 3, new QStandardItem(Vname[2 + i * 4]));
    }
    tableView->setModel(standItemModel);

    //设置表格属性
    tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);

    tableView->setColumnWidth(0, 150);
    tableView->setColumnWidth(1, 250);
    tableView->setColumnWidth(2, 220);
    tableView->setColumnWidth(3, 150);


    tableView->verticalHeader()->hide();
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    tableView->setMinimumSize(800, 500);
    tableView->setShowGrid(false);
    QPushButton* tmpA = refreshDialog;
    QPushButton* tmpB = addIn;
    QPushButton* tmpC = changPass;
    QPushButton* tmpD = new QPushButton("贷款情况查询");
    QPushButton* tmpE = exitBtn;
    QPushButton* tmpH = new QPushButton("开发人员");
    QPushButton* tmpF = new QPushButton("转账调整");
    QPushButton* tmpG = new QPushButton("删除账户");
    mainLayout->addWidget(tableView, 0, 1, 10, 1);
    mainLayout->addWidget(tmpA, 0, 0);
    mainLayout->addWidget(tmpB, 3, 0);
    mainLayout->addWidget(tmpC, 6, 0);
    mainLayout->addWidget(tmpD, 0, 2);
    mainLayout->addWidget(tmpF, 3, 2);
    mainLayout->addWidget(tmpE, 9, 2);
    mainLayout->addWidget(tmpG, 6, 2);
    mainLayout->addWidget(tmpH, 9, 0);
    tmpA->setObjectName("A");
    tmpA->setStyleSheet("#A{background-color: #f8fbaf;}#A:hover{background-color: #fdfedf;}");
    tmpB->setObjectName("B");
    tmpB->setStyleSheet("#B{background-color: #f8fbaf;}#B:hover{background-color: #fdfedf;}");
    tmpC->setObjectName("C");
    tmpC->setStyleSheet("#C{background-color: #f8fbaf;}#C:hover{background-color: #fdfedf;}");
    tmpD->setObjectName("D");
    tmpD->setStyleSheet("#D{background-color: #f8fbaf;}#D:hover{background-color: #fdfedf;}");
    tmpF->setObjectName("F");
    tmpF->setStyleSheet("#F{background-color: #f8fbaf;}#F:hover{background-color: #fdfedf;}");
    tmpE->setObjectName("exit");
    tmpE->setStyleSheet("#exit{background-color: #ff5d5d;font-weight:bold;color:#e8e8e8;}#exit:hover{background-color: #ff8989;font-weight:bold;color:#e8e8e8;}");
    tmpH->setObjectName("H");
    tmpH->setStyleSheet("#H{background-color: #f8fbaf;}#H:hover{background-color: #fdfedf;}");
    tmpG->setObjectName("G");
    tmpG->setStyleSheet("#G{background-color: #f8fbaf;}#G:hover{background-color: #fdfedf;}");

    mainLayout->setColumnMinimumWidth(1, 500);
    this->setLayout(mainLayout);
    connect(addIn, SIGNAL(clicked()), this, SLOT(addInfo()));
    connect(refreshDialog, SIGNAL(clicked()), this, SLOT(accept()));
    connect(changPass, SIGNAL(clicked()), this, SLOT(chgPass()));
    connect(exitBtn, SIGNAL(clicked()), this, SLOT(close()));
    connect(tmpD, SIGNAL(clicked()), this, SLOT(LoAn()));
    connect(tmpF, SIGNAL(clicked()), this, SLOT(TAS()));
    connect(tmpG, SIGNAL(clicked()), this, SLOT(DEL()));
    connect(tmpH, SIGNAL(clicked()), this, SLOT(developers()));
}

void OSDADMIN::addInfo() {
    ADDMoneyADMIN* Add_part;
    Add_part = new ADDMoneyADMIN;
    Add_part->exec();
}
void OSDADMIN::chgPass() {
    ChangePassADMIN* Ch_part;
    Ch_part = new ChangePassADMIN;
    Ch_part->exec();
}
void OSDADMIN::developers()
{
    Developers* De;
    De = new Developers;
    De->exec();
}
void OSDADMIN::LoAn() {
    LAPADMIN* LAP_part;
    LAP_part = new LAPADMIN;
    LAP_part->exec();
}

void OSDADMIN::TAS()
{
    TransADMIN* Bk;
    Bk = new TransADMIN;
    Bk->exec();
}

void OSDADMIN::DEL()
{
    DelADMIN* Bk;
    Bk = new DelADMIN;
    Bk->exec();
}


ADDMoneyADMIN::ADDMoneyADMIN(QDialog* parent) :QDialog(parent) {
    this->setWindowTitle(tr("调整用户收入/支出"));
    this->resize(325, 100);

    clientLbl = new QLabel(tr("用户名"));
    MoneyIn = new QLabel(tr("金额"));
    InLab = new QLabel(tr("收入"));
    OutLab = new QLabel(tr("支出"));
    RightBtn = new QPushButton(tr("确定"));
    clientLEd = new QLineEdit;
    clientLEd->setText(tr(""));
    ActionM = new QLineEdit;
    ActionM->setText(tr(""));
    InComeBtn = new QRadioButton;
    OutComeBtn = new QRadioButton;
    QGridLayout* grid_layout = new QGridLayout(this);
    grid_layout->addWidget(clientLbl, 0, 0);
    grid_layout->addWidget(clientLEd, 0, 1);
    grid_layout->addWidget(MoneyIn, 1, 0);
    grid_layout->addWidget(ActionM, 1, 1);
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
    grid_layout->addWidget(group_radio, 2, 1);

    connect(RightBtn, SIGNAL(clicked()), this, SLOT(EventAd()));
}

void ADDMoneyADMIN::EventAd() {
    if (clientLEd->text().isEmpty() || ActionM->text().isEmpty()) {
        QMessageBox::warning(this, tr("错误！"), tr("输入信息不完整"), QMessageBox::Yes);
        return;
    }
    if ((InComeBtn->isChecked() + OutComeBtn->isChecked()) == 0) {
        QMessageBox::warning(this, tr("错误！"), tr("模式未选择"), QMessageBox::Yes);
        return;
    }
    string tmp;
    Client = clientLEd->text();
    if(clientLEd->text()!=UserName)
        tmp = "select pass,id,priority,loan from bankaccount.account where name = '" + Client.toStdString() + "' AND priority < "+QString::number(priRight).toStdString();
    else 
        tmp = "select pass,id,priority,loan from bankaccount.account where name = '" + Client.toStdString() + "'";
    ExecSQL(tmp.c_str());
    if (SqlRes.isEmpty()) {
        QMessageBox::warning(this, tr("错误！"), tr("该用户不存在"), QMessageBox::Yes);
        return;
    }

    QString strM = ActionM->text();
    SYSTEMTIME ATN;
    GetLocalTime(&ATN);
    string currentTime = WORDToString(ATN.wYear) + "-" + FormatTwo(WORDToString(ATN.wMonth)) + "-" + FormatTwo(WORDToString(ATN.wDay)) + " " + FormatTwo(WORDToString(ATN.wHour)) + ":" + FormatTwo(WORDToString(ATN.wMinute)) + ":" + FormatTwo(WORDToString(ATN.wSecond));
    if (InComeBtn->isChecked())
        tmp = "INSERT INTO bankaccount.account (time,balance,pass,priority,name,id,income,expenditure,loan) VALUES ('" + currentTime + "'," + strM.toStdString() + ", '" + SqlRes[0].toStdString() + "'," + SqlRes[2].toStdString() + ", '" + Client.toStdString() + "'," + SqlRes[1].toStdString() + ",1,0," + SqlRes[3].toStdString() + ")";
    else
        tmp = "INSERT INTO bankaccount.account (time,balance,pass,priority,name,id,income,expenditure,loan) VALUES ('" + currentTime + "'," + strM.toStdString() + ", '" + SqlRes[0].toStdString() + "'," + SqlRes[2].toStdString() + ", '" + Client.toStdString() + "'," + SqlRes[1].toStdString() + ",0,1," + SqlRes[3].toStdString() + ")";
    ExecSQL(tmp.c_str());
    getTotal(clientLEd->text());
    QMessageBox::warning(this, tr("成功！"), tr("调整记录成功"), QMessageBox::Yes);
    accept();
}

ChangePassADMIN::ChangePassADMIN(QDialog* parent) :QDialog(parent) {
    this->setWindowTitle(tr("修改用户密码"));
    this->resize(325, 100);

    clientLbl = new QLabel(tr("用户名"));
    ChPass = new QLabel(tr("新密码"));
    AgPass = new QLabel(tr("重复输入"));
    clientLEd = new QLineEdit;
    clientLEd->setText(tr(""));
    ActionM = new QLineEdit;
    ActionM->setText(tr(""));
    ActionM->setEchoMode(QLineEdit::Password);
    ActionA = new QLineEdit;
    ActionA->setText(tr(""));
    ActionA->setEchoMode(QLineEdit::Password);
    RightBtn = new QPushButton(tr("确定"));

    QGridLayout* grid_layout = new QGridLayout(this);
    grid_layout->addWidget(clientLbl, 0, 0);
    grid_layout->addWidget(clientLEd, 0, 1);
    grid_layout->addWidget(ChPass, 1, 0);
    grid_layout->addWidget(AgPass, 2, 0);
    grid_layout->addWidget(ActionM, 1, 1);
    grid_layout->addWidget(ActionA, 2, 1);
    grid_layout->addWidget(RightBtn, 3, 1);
    RightBtn->setObjectName("right");
    RightBtn->setStyleSheet("#right{background-color: #bcffb9;font-weight:bold;}#right:hover{background-color: #dbffd9;font-weight:bold;}");

    connect(RightBtn, SIGNAL(clicked()), this, SLOT(EventCh()));
}

void ChangePassADMIN::EventCh() {
    if (clientLEd->text().isEmpty() || ActionM->text().isEmpty() || ActionA->text().isEmpty()) {
        QMessageBox::warning(this, tr("错误！"), tr("输入不完整"), QMessageBox::Yes);
        return;
    }
    string tmp;
    Client = clientLEd->text();
    if(clientLEd->text()!=UserName)
        tmp = "select pass from bankaccount.account where name = '" + Client.toStdString() + "' AND priority < "+QString::number(priRight).toStdString();
    else 
        tmp = "select pass from bankaccount.account where name = '" + Client.toStdString() + "'";
    ExecSQL(tmp.c_str());
    if (SqlRes.isEmpty()) {
        QMessageBox::warning(this, tr("错误！"), tr("该用户不存在"), QMessageBox::Yes);
        return;
    }

    if (ActionM->text() != ActionA->text()) {
        QMessageBox::warning(this, tr("错误！"), tr("两次输入密码不一致"), QMessageBox::Yes);
        return;
    }

    tmp = "UPDATE bankaccount.account SET pass = '" + ActionM->text().toStdString() + "' WHERE name = '" + Client.toStdString() + "'";
    ExecSQL(tmp.c_str());
    QMessageBox::warning(this, tr("成功！"), tr("已修改密码"), QMessageBox::Yes);
    accept();
}

DelADMIN::DelADMIN(QDialog* parent) :QDialog(parent) {
    this->setWindowTitle(tr("删除账户"));
    this->resize(200, 100);

    clientLbl = new QLabel(tr("用户名"));

    clientEdt = new QLineEdit;
    clientEdt->setText(tr(""));
    RightBtn = new QPushButton(tr("确定"));

    QGridLayout* grid_layout = new QGridLayout(this);
    grid_layout->addWidget(clientLbl, 0, 0);
    grid_layout->addWidget(clientEdt, 0, 1);
    grid_layout->addWidget(RightBtn, 1, 1);
    RightBtn->setObjectName("right");
    RightBtn->setStyleSheet("#right{background-color: #bcffb9;font-weight:bold;}");

    connect(RightBtn, SIGNAL(clicked()), this, SLOT(EventDe()));
}
void DelADMIN::EventDe() {
    if (clientEdt->text().isEmpty()) {
        QMessageBox::warning(this, tr("错误！"), tr("输入不完整"), QMessageBox::Yes);
        return;
    }
    string tmp;
    Client = clientEdt->text();
    tmp = "select pass from bankaccount.account where name = '" + Client.toStdString() + "' AND priority < " + QString::number(priRight).toStdString();
    ExecSQL(tmp.c_str());
    if (SqlRes.isEmpty()) {
        QMessageBox::warning(this, tr("错误！"), tr("该用户不存在"), QMessageBox::Yes);
        return;
    }
    tmp = "DELETE FROM bankaccount.account WHERE name = '" + Client.toStdString() + "'";
    ExecSQL(tmp.c_str());
    QMessageBox::warning(this, tr("成功！"), tr("已删除账户"), QMessageBox::Yes);
    accept();
}