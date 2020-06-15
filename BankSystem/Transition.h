#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QProcess>
#include <QDebug>
#include <QAction>
#include <QTextEdit>
#include <QIcon>
#include <QFile>
#include <QGroupBox>
#include <QTextStream>
#include <QMessageBox>
#include <QTextDocument>
#include <QTextCursor>
#include <QToolBar>
#include <QPushButton>
#include <QRadioButton>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QtPrintSupport/QPageSetupDialog>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <Windows.h>
#include <QTableView>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QString>
#include <QStandardItemModel>
#pragma once

#ifndef TRANSITION_H
#define TRANSITION_H

class Transition :public QDialog
{
	Q_OBJECT
public:
	explicit Transition(QDialog* parent = 0);
private slots:
	void EventTAS();
private:
	QLabel* TasOut;
	QLabel* TasAmount;
	QLineEdit* ActionM1;
	QLineEdit* ActionM2;
	QPushButton* RightBtn;
	QPushButton* ExitBtn;
	//QPushButton* ConfirmTasOut;
};
#endif#pragma once
