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
#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H


class BankSystem : public QMainWindow{
    Q_OBJECT
public:
    explicit BankSystem(QWidget* parent = 0);
    void OSD_A();
signals:

public slots:
    void loginMain();
    void logupMain();
    void DeveloperAct();
    
private:
    QLabel* tipLbl;
    QPushButton* loginBtnM;
    QPushButton* logupBtnM;
};

#endif 
