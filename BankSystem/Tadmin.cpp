#include "Psql.h"
#include "login.h"
#include "logup.h"
#include "Tadmin.h"
#include "OSDadmin.h"
#include <QtWidgets\qgridlayout.h>
#pragma execution_character_set("utf-8")
using namespace std;

TransADMIN::TransADMIN(QDialog* parent) :QDialog(parent)
{
	this->setWindowTitle(tr("转账"));
	this->resize(325, 100);
	this->setObjectName("Dia");
	this->setStyleSheet("#Dia{background-color:#f1feff;}");
	clientLbl = new QLabel(tr("转出用户"));
	clientLEd = new QLineEdit;
	clientLEd->setText(tr(""));
	TasOut = new QLabel(tr("转入用户"));
	TasAmount = new QLabel(tr("转账金额"));
	RightBtn = new QPushButton(tr("确定"));
	ExitBtn = new QPushButton(tr("退出"));
	ActionM1 = new QLineEdit;
	ActionM1->setText(tr(""));
	ActionM2 = new QLineEdit;
	ActionM2->setText(tr(""));
	QGridLayout* grid_layout = new QGridLayout(this);
	grid_layout->addWidget(clientLbl, 0, 0);
	grid_layout->addWidget(clientLEd, 0, 1);
	grid_layout->addWidget(TasOut, 1, 0);
	grid_layout->addWidget(ActionM1, 1, 1);
	grid_layout->addWidget(TasAmount, 2, 0);
	grid_layout->addWidget(ActionM2, 2, 1);
	grid_layout->addWidget(RightBtn, 0, 2);
	grid_layout->addWidget(ExitBtn, 1, 2);
	RightBtn->setObjectName("right");
	RightBtn->setStyleSheet("#right{background-color: #bcffb9;font-weight:bold;}#right:hover{background-color: #dbffd9;font-weight:bold;}");
	ExitBtn->setObjectName("exit");
	ExitBtn->setStyleSheet("#exit{background-color: #ff5d5d;font-weight:bold;color:#e8e8e8;}#exit:hover{background-color: #ff8989;font-weight:bold;color:#e8e8e8;}");

	connect(RightBtn, SIGNAL(clicked()), this, SLOT(EventTAS()));
	connect(ExitBtn, SIGNAL(clicked()), this, SLOT(close()));
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
	tmp = "UPDATE bankaccount.account set total = " + QString::number(tot, 10, 6) + " where name = '" + UserN + "'";
	ExecSQL(tmp.toStdString().data());
	return QString::number(tot, 10, 6);
}
void TransADMIN::EventTAS()
{
	if (clientLEd->text().isEmpty() || ActionM1->text().isEmpty() || ActionM2->text().isEmpty()) {
		QMessageBox::warning(this, tr("错误！"), tr("输入不完整"), QMessageBox::Yes);
		return;
	}

	Client = clientLEd->text();
	string tmp = "select total from bankaccount.account where name = '" + Client.toStdString() + "'";
	ExecSQL(tmp.c_str());
	if (SqlRes.isEmpty()) {
		QMessageBox::warning(this, tr("错误！"), tr("转出用户不存在"), QMessageBox::Yes);
		return;
	}

	double a = SqlRes[0].toDouble();
	double b = ActionM2->text().toDouble();
	if (a < b)
	{
		QMessageBox::warning(this, tr("错误！"), tr("余额不足以支付转账金额"), QMessageBox::Yes);
		return;
	}

	QString strM1 = ActionM1->text();
	QString strM2 = ActionM2->text();
	SYSTEMTIME ATN;
	GetLocalTime(&ATN);
	string currentTime = WORDToString(ATN.wYear) + "-" + FormatTwo(WORDToString(ATN.wMonth)) +
		"-" + FormatTwo(WORDToString(ATN.wDay)) + " " + FormatTwo(WORDToString(ATN.wHour)) +
		":" + FormatTwo(WORDToString(ATN.wMinute)) + ":" + FormatTwo(WORDToString(ATN.wSecond));
	if(ActionM1->text()!=UserName)
		tmp = "select pass,id,priority,loan from bankaccount.account where name = '" + ActionM1->text().toStdString() + "' AND priority < " + QString::number(priRight).toStdString();
	else 
		tmp = "select pass,id,priority,loan from bankaccount.account where name = '" + ActionM1->text().toStdString() + "'";
	ExecSQL(tmp.c_str());
	if (SqlRes.isEmpty()) {
		QMessageBox::warning(this, tr("错误！"), tr("转入用户不存在"), QMessageBox::Yes);
		return;
	}
	tmp = "INSERT INTO bankaccount.account (balance,pass,priority,time,name,id,income,expenditure,loan) VALUES ("
		+ strM2.toStdString() + ", '" + SqlRes[0].toStdString() + "'," + SqlRes[2].toStdString() + ", '"
		+ currentTime + "', '" + ActionM1->text().toStdString() + "'," + SqlRes[1].toStdString() + ",1,0," + SqlRes[3].toStdString() + ")";
	ExecSQL(tmp.c_str());

	tmp = "select pass,id,priority,loan from bankaccount.account where name = '" + Client.toStdString() + "'";
	ExecSQL(tmp.c_str());
	tmp = "INSERT INTO bankaccount.account (balance,pass,priority,time,name,id,income,expenditure,loan) VALUES ("
		+ strM2.toStdString() + ", '" + SqlRes[0].toStdString() + "'," + SqlRes[2].toStdString() + ", '"
		+ currentTime + "', '" + Client.toStdString() + "'," + SqlRes[1].toStdString() + ",0,1," + SqlRes[3].toStdString() + ")";
	ExecSQL(tmp.c_str());

	QMessageBox::warning(this, tr("成功！"), tr("转账成功"), QMessageBox::Yes);
	getTotal(Client);
	getTotal(strM1);
	qDebug() << strM1;
	accept();

}
