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
#ifndef LOGIN_H
#define LOGIN_H

using namespace std;
QString UserName;
int priRight;
class LoginForm : public QDialog
{
    Q_OBJECT
public:
    explicit LoginForm(QDialog* parent = 0); 

signals:

public slots:
    void login();
    void Admin_A();
private:
    QLabel* userNameLbl;      
    QLabel* pwdLbl;           
    QLineEdit* userNameLEd;  
    QLineEdit* pwdLEd;        
    QPushButton* loginBtn;     
    QPushButton* exitBtn;   
};

#endif // LOGIN_H