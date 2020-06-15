#ifndef LOGUP_H
#define LOGUP_H
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QProcess>
#include <QDebug>
#include <QAction>
#include <QTextEdit>
#include <QIcon>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QTextDocument>
#include <QTextCursor>
#include <QToolBar>
#include <QPushButton>
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
#include <iostream>
#include <sstream>
using namespace std;
#include "Psql.h"
class LogupForm : public QDialog
{
    Q_OBJECT
public:
    explicit LogupForm(QDialog* parent = 0);  

signals:

public slots:
    void logup();
private:
    QLabel* userNameLbl;       
    QLabel* pwdLbl;           
    QLineEdit* userNameLEd;    
    QLineEdit* pwdLEd;         
    QPushButton* logupBtn;     
    QPushButton* exitBtn;   
};

int GetnewID() {
    ExecSQL("select MAX(id) from bankaccount.account");
    QString id = SqlRes[0];
    int I = atoi(id.toStdString().data());
    I++;
    return I;
}
string FormatTwo(string oi) {
    while (oi.length() != 2) {
        oi = "0" + oi;
    }
    return oi;
}
string WORDToString(WORD w) {
    char tmpbuff[16];
    sprintf(tmpbuff, "%d", w);
    string res = tmpbuff;
    return res;
}

#endif
