#include "Psql.h"
#include "login.h"
#include "logup.h"
#include"Transition.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#pragma execution_character_set("utf-8")
using namespace std;

Transition::Transition(QDialog* parent) :QDialog(parent)
{
	this->setWindowTitle(tr("转账"));
	this->resize(325, 100);
	this->setObjectName("Dia");
	this->setStyleSheet("#Dia{background-color:#f1feff;}");
	TasOut = new QLabel(tr("转账对象的用户名"));
	TasAmount = new QLabel(tr("转账金额"));
	RightBtn = new QPushButton(tr("确定"));
	ExitBtn = new QPushButton(tr("退出"));
	ActionM1 = new QLineEdit;
	ActionM1->setText(tr(""));
	ActionM2 = new QLineEdit;
	ActionM2->setText(tr(""));
	QGridLayout* grid_layout = new QGridLayout(this);
	grid_layout->addWidget(TasOut, 0, 0);
	grid_layout->addWidget(ActionM1, 0, 1);
	grid_layout->addWidget(TasAmount, 1, 0);
	grid_layout->addWidget(ActionM2, 1, 1);
	grid_layout->addWidget(RightBtn, 0, 2);
	grid_layout->addWidget(ExitBtn, 1, 2);
	RightBtn->setObjectName("right");
	RightBtn->setStyleSheet("#right{background-color: #bcffb9;font-weight:bold;}#right:hover{background-color: #dbffd9;font-weight:bold;}");
	ExitBtn->setObjectName("exit");
	ExitBtn->setStyleSheet("#exit{background-color: #ff5d5d;font-weight:bold;color:#e8e8e8;}#exit:hover{background-color: #ff8989;font-weight:bold;color:#e8e8e8;}");

	connect(RightBtn, SIGNAL(clicked()), this, SLOT(EventTAS()));
	connect(ExitBtn, SIGNAL(clicked()), this, SLOT(close()));
}

void Transition::EventTAS()
{
	if (ActionM1->text().isEmpty() || ActionM2->text().isEmpty()) {
		QMessageBox::warning(this, tr("错误！"), tr("输入不完整"), QMessageBox::Yes);
		return;
	}

	QString strM1 = ActionM1->text();
	QString strM2 = ActionM2->text();
	SYSTEMTIME ATN;
	GetLocalTime(&ATN);
	string currentTime = WORDToString(ATN.wYear) + "-" + FormatTwo(WORDToString(ATN.wMonth)) +
		"-" + FormatTwo(WORDToString(ATN.wDay)) + " " + FormatTwo(WORDToString(ATN.wHour)) +
		":" + FormatTwo(WORDToString(ATN.wMinute)) + ":" + FormatTwo(WORDToString(ATN.wSecond));
	
	string tmp3 = "select total from bankaccount.account where name = '" + UserName.toStdString() + "'";
	ExecSQL(tmp3.c_str());
	double a = SqlRes[0].toDouble();
	double b = ActionM2->text().toDouble();
		
	if (a < b)
	{
		QMessageBox::warning(this, tr("错误！"), tr("余额不足以支付转账金额"), QMessageBox::Yes);
		return;
	}
	else
	{
    	string tmp2 = "select pass,id,priority from bankaccount.account where name = '" + ActionM1->text().toStdString() + "'";
		ExecSQL(tmp2.c_str());
		if (SqlRes.isEmpty()) {
			QMessageBox::warning(this, tr("错误！"), tr("转账对象不存在"), QMessageBox::Yes);
			return;
		}
		tmp2 = "INSERT INTO bankaccount.account (balance,pass,priority,time,name,id,income,expenditure) VALUES ("
			+ strM2.toStdString() + ", '" + SqlRes[0].toStdString() + "'," + SqlRes[2].toStdString() + ", '"
			+ currentTime + "', '" + ActionM1->text().toStdString() + "'," + SqlRes[1].toStdString() + ",1,0)";
		ExecSQL(tmp2.c_str());

		string tmp1 = "select pass,id,priority from bankaccount.account where name = '" + UserName.toStdString() + "'";
		ExecSQL(tmp1.c_str());
		tmp1 = "INSERT INTO bankaccount.account (balance,pass,priority,time,name,id,income,expenditure) VALUES ("
			+ strM2.toStdString() + ", '" + SqlRes[0].toStdString() + "'," + SqlRes[2].toStdString() + ", '"
			+ currentTime + "', '" + UserName.toStdString() + "'," + SqlRes[1].toStdString() + ",0,1)";
		ExecSQL(tmp1.c_str());
	}

	QMessageBox::warning(this, tr("成功！"), tr("转账成功"), QMessageBox::Yes);
	accept();
	
}
