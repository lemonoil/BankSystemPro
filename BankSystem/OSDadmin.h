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
#include <string>
#include <cstring>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <string>
#include <Windows.h>
#include <QTableView>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QStandardItemModel>
#pragma once
#ifndef OSDADMIN_H
#define OSDADMIN_H
double Total;
QString Client;
class OSDADMIN : public QDialog
{
    Q_OBJECT
public:

    explicit OSDADMIN(QDialog* parent = 0);
    void InfoOSD();


private slots:
    void addInfo();
    void chgPass();
    void LoAn();
    void TAS();
    void DEL();
    void developers();

private:
    QPushButton* addIn;
    QPushButton* changPass;
    QTableView* tableView;
    QGridLayout* mainLayout;
};

class ADDMoneyADMIN :public QDialog {
    Q_OBJECT
public:
    explicit ADDMoneyADMIN(QDialog* parent = 0);

private slots:
    void EventAd();
private:

    QLabel* clientLbl;
    QLabel* MoneyIn;
    QLabel* InLab;
    QLabel* OutLab;
    QLineEdit* ActionM;
    QLineEdit* clientLEd;
    QPushButton* RightBtn;
    QRadioButton* InComeBtn;
    QRadioButton* OutComeBtn;
};

class ChangePassADMIN :public QDialog {
    Q_OBJECT
public:
    explicit ChangePassADMIN(QDialog* parent = 0);

private slots:
    void EventCh();
private:

    QLabel* clientLbl;
    QLabel* ChPass;
    QLabel* AgPass;
    QLineEdit* clientLEd;
    QLineEdit* ActionM;
    QLineEdit* ActionA;
    QPushButton* RightBtn;
};


class DelADMIN :public QDialog {
    Q_OBJECT
public:
    explicit DelADMIN(QDialog* parent = 0);

private slots:
    void EventDe();
private:

    QLabel* clientLbl;
    QLineEdit* clientEdt;
    QPushButton* RightBtn;
};
#endif //

