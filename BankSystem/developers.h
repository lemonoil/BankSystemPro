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
#ifndef DEVELOPERS_H
#define DEVELOPERS_H
#pragma once
class ClickLabel :public QLabel
{
    Q_OBJECT
public:
    explicit ClickLabel(QString st, QWidget* parent = 0);
signals:
    void clicked(); // 点击信号
protected:
    void mouseReleaseEvent(QMouseEvent* e); // 重载了鼠标释放事件

};
class Developers :public QDialog {
    Q_OBJECT
public:
    explicit Developers(QDialog* parent = 0);
private slots:
    void LmyGithub();
    void WtBlog();
    void XzhQQ();
    void ChhQQ();
    void githubE();
private:

    ClickLabel* Lmy;
    ClickLabel* Wt;
    ClickLabel* Xzh;
    ClickLabel* Chh;
    QLabel* Git;
    ClickLabel* Link;
    QPushButton* ExitBtn;
};

#endif