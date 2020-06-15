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
#ifndef LOAN_H
#define LOAN_H
using namespace std;

const double rate = 0.001;
class LoanForm : public QDialog
{
    Q_OBJECT
public:
    explicit LoanForm(QDialog* parent = 0);

public slots:
    void loanMoney();

private:
    QLabel* loanMoneyLbl;
    QLabel* loanRateLbl;
    QLineEdit* loanMoneyLEd;
    QPushButton* loanBtn;
    QPushButton* exitBtn;
};

#endif // LOAN_H