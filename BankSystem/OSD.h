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
#include <QDesktopServices>
#include <QMouseEvent>
#pragma once
#ifndef OSD_H
#define OSD_H
double       Total;
class OSDM : public QDialog
{
    Q_OBJECT
public:

    explicit OSDM(QDialog* parent = 0);
    void InfoOSD();
    

private slots:
    void addInfo();
    void chgPass();
    void profitP();
    void LoAn();
    void TAS();
    void developers();

private:
    QPushButton* addIn;
    QPushButton* changPass;
    QPushButton* profitBtn;
    QTableView*  tableView;
    QGridLayout* mainLayout;
};

class ADDMoney :public QDialog {
    Q_OBJECT
public:
    explicit ADDMoney(QDialog* parent = 0);
    
private slots:
    void EventAd();
private:

    QLabel*         MoneyIn;            
    QLabel*         InLab;
    QLabel*         OutLab;
    QLineEdit*      ActionM;
    QPushButton*    RightBtn;
    QRadioButton*   InComeBtn;
    QRadioButton*   OutComeBtn;
};

class ChangePass :public QDialog {
    Q_OBJECT
public:
    explicit ChangePass(QDialog* parent = 0);

private slots:
    void EventCh();
private:

    QLabel* ChPass;
    QLabel* AgPass;
    QLineEdit* ActionM;
    QLineEdit* ActionA;
    QPushButton* RightBtn;
};

#endif