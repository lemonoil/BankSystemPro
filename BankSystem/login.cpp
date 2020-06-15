#include "login.h"
#include "Psql.h"
#include "OSDadmin.h"
#include <QMessageBox>
#pragma execution_character_set("utf-8")

const double rate = 0.001;

LoginForm::LoginForm(QDialog* parent) :
    QDialog(parent)
{

    this->setWindowTitle(tr("��¼����"));
    this->setObjectName("Dia");
    this->setStyleSheet("#Dia{background-color:#f1feff;}");
    userNameLbl = new QLabel(this); 
    userNameLbl->move(70, 80);     
    userNameLbl->setText("�û���:"); 

    userNameLEd = new QLineEdit(this);
    userNameLEd->move(180, 80);
    userNameLEd->setPlaceholderText(tr("�������û���"));

    pwdLbl = new QLabel(this);
    pwdLbl->move(80, 130);
    pwdLbl->setText("����:");

    pwdLEd = new QLineEdit(this);
    pwdLEd->move(180, 130);
    pwdLEd->setPlaceholderText("����������");
    pwdLEd->setEchoMode(QLineEdit::Password);

    loginBtn = new QPushButton(this);
    loginBtn->move(150, 200);
    loginBtn->setText("��¼");
    loginBtn->setObjectName("login");
    loginBtn->setStyleSheet("#login{background-color: #f8fbaf;}#login:hover{background-color: #fdfedf;}");

    exitBtn = new QPushButton(this);
    exitBtn->move(280, 200);
    exitBtn->setText("�˳�");
    exitBtn->setObjectName("exit");
    exitBtn->setStyleSheet("#exit{background-color: #ff5d5d;font-weight:bold;color:#e8e8e8;}#exit:hover{background-color: #ff8989;font-weight:bold;color:#e8e8e8;}");

    connect(loginBtn, &QPushButton::clicked, this, &LoginForm::login);
    connect(exitBtn, &QPushButton::clicked, this, &LoginForm::close);
}

void LoginForm::login()
{
    string st = "select pass,priority from bankaccount.account where name = '"+userNameLEd->text().trimmed().toStdString()+"'";
    ExecSQL(st.c_str());

    if (SqlRes.isEmpty()) {
        QMessageBox::warning(this, tr("���棡"), tr("�û������������"), QMessageBox::Yes);
        userNameLEd->clear();
        pwdLEd->clear();
    }
    else if (SqlRes[1].toInt() > 1 && SqlRes[0] == pwdLEd->text()) {
        UserName = userNameLEd->text().trimmed();
        priRight = SqlRes[1].toInt();
        QMessageBox::warning(this, tr("�ɹ���"), tr("���ѵ�¼Ȩ���˻���"), QMessageBox::Yes);
        close();
        Admin_A();
    }
    else if (SqlRes[0] == pwdLEd->text()) {
        UserName = userNameLEd->text().trimmed();
        priRight = 1;
        QMessageBox::warning(this, tr("�ɹ���"), tr("���ѵ�¼���˺ţ�"), QMessageBox::Yes);
        accept();
    }
    else {  
        QMessageBox::warning(this, tr("���棡"), tr("�û������������"), QMessageBox::Yes);
        userNameLEd->clear();
        pwdLEd->clear();
        userNameLEd->setFocus();
    }
}

void LoginForm::Admin_A() {
    OSDADMIN* osd;
ATM:
    osd = new OSDADMIN;
    if (osd->exec() == QDialog::Accepted)goto ATM;
}