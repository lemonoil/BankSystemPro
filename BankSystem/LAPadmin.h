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
#ifndef LAPADMIN_H
#define LAPADMIN_H

using namespace std;
class LAPADMIN : public QDialog
{
    Q_OBJECT
public:
    explicit LAPADMIN(QDialog* parent = 0);

public slots:
    void checkLoan();
private:
    QLabel* clientLbl;
    QLabel* loanLbl;
    QLineEdit* clientLEd;
    QLineEdit* loanLEd;
    QPushButton* checkBtn;
    QPushButton* exitBtn;
};

#endif 
