
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
#ifndef PAYMENT_H
#define PAYMENT_H

using namespace std;
class PaymentForm : public QDialog
{
    Q_OBJECT
public:
    explicit PaymentForm(QDialog* parent = 0);

public slots:
    void payment();
private:
    QLabel* loanLbl;
    QLabel* paymentLbl;
    QLineEdit* paymentLEd;
    QLineEdit* loanLEd;
    QPushButton* payBtn;
    QPushButton* exitBtn;
};

#endif 
