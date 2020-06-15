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
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include "LAP.h"
#include "loan.h"
#include "payment.h"
#include "OSD.h"
#include <QtWidgets\qgridlayout.h>
#pragma execution_character_set("utf-8")
using namespace std;

LAPM::LAPM(QWidget* parent) : QDialog(parent) {
    this->resize(QSize(400, 200));
    this->setObjectName("Dia");
    this->setStyleSheet("#Dia{background-color:#f1feff;}");
    loanBtn = new QPushButton("´û¿î");
    paymentBtn = new QPushButton("»¹´û");
    exitBtn = new QPushButton("ÍË³ö");


    QGridLayout* grid_layout = new QGridLayout(this);
    grid_layout->addWidget(loanBtn,0,0);
    grid_layout->addWidget(paymentBtn,0, 1);
    grid_layout->addWidget(exitBtn, 1, 1);
    loanBtn->setObjectName("loan");
    loanBtn->setStyleSheet("#loan{background-color: #f8fbaf;}#loan:hover{background-color: #fdfedf;}");
    paymentBtn->setObjectName("payment");
    paymentBtn->setStyleSheet("#payment{background-color: #f8fbaf;}#payment:hover{background-color: #fdfedf;}");
    exitBtn->setObjectName("exit");
    exitBtn->setStyleSheet("#exit{background-color: #ff5d5d;font-weight:bold;color:#e8e8e8;}#exit:hover{background-color: #ff8989;font-weight:bold;color:#e8e8e8;}");
    connect(loanBtn, SIGNAL(clicked()), this, SLOT(LoanMain()));
    connect(paymentBtn, SIGNAL(clicked()), this, SLOT(PaymentMain()));
    connect(exitBtn, SIGNAL(clicked()), this, SLOT(close()));
}

void LAPM::LoanMain() {
    LoanForm* Moneyloan;
    Moneyloan = new LoanForm;
    Moneyloan->exec();
}

void LAPM::PaymentMain() {
    PaymentForm* MoneyPayment;
    MoneyPayment = new PaymentForm;
    MoneyPayment->exec();
}