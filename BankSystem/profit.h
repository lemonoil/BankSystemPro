#include <Windows.h>
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
#ifndef PROFIT_H
#define PROFIT_H

using namespace std;

class Profit :public QDialog {
     Q_OBJECT
public:
     explicit Profit(QDialog * parent = 0);

public slots:
    void CheckProfit();

private:
    QLabel* userNameLbl;
    QLabel* profitLbl;
    QLabel* tmLbl;
    QLabel* yearlyRateLbl;
    QLineEdit* userNameLEd;
    QLineEdit* profitLEd;
    QLineEdit* tmLEd;
    QLineEdit* yearlyRateLEd;
    QPushButton* checkBtn;
    QPushButton* exitBtn;

};

#endif
