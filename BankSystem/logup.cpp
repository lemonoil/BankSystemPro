#include "logup.h"
#include "Psql.h"
#include <QMessageBox>
#pragma execution_character_set("utf-8")
LogupForm::LogupForm(QDialog* parent) :
    QDialog(parent)
{

    this->setWindowTitle(tr("注册界面"));
    this->setObjectName("Dia");
    this->setStyleSheet("#Dia{background-color:#f1feff;}");

    userNameLbl = new QLabel(this);  
    userNameLbl->move(70, 80);    
    userNameLbl->setText("用户名:");  

  
    userNameLEd = new QLineEdit(this);
    userNameLEd->move(180, 80);
    userNameLEd->setPlaceholderText(tr("请输入真实姓名"));

  
    pwdLbl = new QLabel(this);
    pwdLbl->move(80, 130);
    pwdLbl->setText("密码:");

    
    pwdLEd = new QLineEdit(this);
    pwdLEd->move(180, 130);
    pwdLEd->setPlaceholderText("请输入6位数字或字母密码");
    pwdLEd->setEchoMode(QLineEdit::Password);

    
    logupBtn = new QPushButton(this);
    logupBtn->move(150, 200);
    logupBtn->setText("注册");
    logupBtn->setObjectName("logup");
    logupBtn->setStyleSheet("#logup{background-color: #f8fbaf;}#logup:hover{background-color: #fdfedf;}");

   
    exitBtn = new QPushButton(this);
    exitBtn->move(280, 200);
    exitBtn->setText("退出");
    exitBtn->setObjectName("exit");
    exitBtn->setStyleSheet("#exit{background-color: #ff5d5d;font-weight:bold;color:#e8e8e8;}#exit:hover{background-color: #ff8989;font-weight:bold;color:#e8e8e8;}");

    connect(logupBtn, &QPushButton::clicked, this, &LogupForm::logup);
    connect(exitBtn, &QPushButton::clicked, this, &LogupForm::close);

}

void LogupForm::logup()
{
    if (pwdLEd->text().toStdString().length() != 6) {
        QMessageBox::warning(this, tr("错误！"), tr("请检查密码长度！"), QMessageBox::Yes);
        userNameLEd->clear();
        pwdLEd->clear();
        userNameLEd->setFocus();
        return;
    }
    string tmp = "select id from bankaccount.account where name  = '" + userNameLEd->text().trimmed().toStdString() + "'";
    ExecSQL(tmp.c_str());
    if (SqlRes.size()) {
        QMessageBox::warning(this, tr("错误！"), tr("该用户名已被使用！"), QMessageBox::Yes);
        userNameLEd->clear();
        pwdLEd->clear();
        userNameLEd->setFocus();
        return;
    }
    SYSTEMTIME now;
    GetLocalTime(&now);
    string currentTime= WORDToString(now.wYear)+"-"+ FormatTwo(WORDToString(now.wMonth))+"-"+ FormatTwo(WORDToString(now.wDay))+" "+ FormatTwo(WORDToString(now.wHour))+":"+ FormatTwo(WORDToString(now.wMinute))+":"+ FormatTwo(WORDToString(now.wSecond));
    int id = GetnewID();
    string st = "select pass from bankaccount.account where name = '" + userNameLEd->text().trimmed().toStdString() + "'";
    qDebug() << SqlRes[0].toStdString().data();
    tmp = "INSERT INTO bankaccount.account (balance,pass,priority,time,name,id,income,expenditure) VALUES ( 0.00,'" + pwdLEd->text().toStdString() + "',1,'" 
        + currentTime + "','" + userNameLEd->text().trimmed().toStdString() + "'," + to_string(id) + ",0,0)";

    if (ExecSQL(tmp.c_str()) == 1) {

        QMessageBox::warning(this, tr("成功！"), tr("您已注册该账号！"), QMessageBox::Yes);
        accept();
    }
    else {                      
        QMessageBox::warning(this, tr("错误！"), tr("注册失败！"), QMessageBox::Yes);
        userNameLEd->clear();
        pwdLEd->clear();
        userNameLEd->setFocus();
    }
}
