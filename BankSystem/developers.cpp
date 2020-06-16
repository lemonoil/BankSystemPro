#include"developers.h"
#pragma execution_character_set("utf-8")
Developers::Developers(QDialog* parent) :QDialog(parent) {
    this->setWindowTitle(tr("开发人员"));
    this->resize(700, 350);
    this->setMaximumSize(700, 350);
    this->setMinimumSize(700, 350);
    this->setObjectName("Dia");
    this->setStyleSheet("#Dia{background-color:#f1feff;}");
    AAA = new ClickLabel(tr("AAAA"));
    BBB = new ClickLabel(tr("BBBB"));
    CCC = new ClickLabel(tr("CCCC"));
    DDD = new ClickLabel(tr("DDDD"));
    Git = new QLabel(tr("github: "));
    Link = new ClickLabel(tr("star!fork!follow!"));
    ExitBtn = new QPushButton(tr("退出"));
    AAA->setObjectName("AAA");
    AAA->setStyleSheet("#AAA{font-weight:bold;}#AAA:hover{color:#FF00FF;}");
    BBB->setObjectName("BBB");
    BBB->setStyleSheet("#BBB{font-weight:bold;}#BBB:hover{color:#FF00FF;}");
    CCC->setObjectName("CCC");
    CCC->setStyleSheet("#CCC{font-weight:bold;}#CCC:hover{color:#FF00FF;}");
    DDD->setObjectName("DDD");
    DDD->setStyleSheet("#DDD{font-weight:bold;}#DDD:hover{color:#FF00FF;}");
    Link->setObjectName("Link");
    Link->setStyleSheet("#Link{text-decoration:underline;color:blue;font-style:italic;}#Link:hover{color:#FF00FF;}");
    ExitBtn->setObjectName("exit");
    ExitBtn->setStyleSheet("#exit{background-color: #ff5d5d;font-weight:bold;color:#e8e8e8;}#exit:hover{background-color: #ff8989;font-weight:bold;color:#e8e8e8;}");
    QGridLayout* grid_layout = new QGridLayout(this);
    grid_layout->addWidget(AAA, 0, 1, 1, 2, Qt::AlignRight);
    grid_layout->addWidget(BBB, 0, 4, 1, 3, Qt::AlignLeft);
    grid_layout->addWidget(CCC, 1, 1, 1, 2, Qt::AlignRight);
    grid_layout->addWidget(DDD, 1, 4, 1, 3, Qt::AlignLeft);
    grid_layout->addWidget(Git, 2, 0, 1, 2, Qt::AlignRight);
    grid_layout->addWidget(Link, 2, 2, 1, 5, Qt::AlignLeft);
    grid_layout->addWidget(ExitBtn, 3, 6);
    connect(AAA, SIGNAL(clicked()), this, SLOT(AAAGithub()));
    connect(BBB, SIGNAL(clicked()), this, SLOT(BBBBlog()));
    connect(CCC, SIGNAL(clicked()), this, SLOT(CCCQQ()));
    connect(DDD, SIGNAL(clicked()), this, SLOT(DDDQQ()));
    connect(Link, SIGNAL(clicked()), this, SLOT(githubE()));
    connect(ExitBtn, SIGNAL(clicked()), this, SLOT(close()));
}

ClickLabel::ClickLabel(QString st, QWidget* parent) :QLabel(st)
{}
void ClickLabel::mouseReleaseEvent(QMouseEvent* e)
{
    emit clicked(); // 在点击事件中发送信号
}
void Developers::AAAGithub()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://github.com/")));
}
void Developers::BBBBlog()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://blog.csdn.net/")));
}
void Developers::CCCQQ()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("http://wpa.qq.com/msgrd?v=3&uin=10000&site=qq&menu=yes")));
}
void Developers::DDDQQ()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("http://wpa.qq.com/msgrd?v=3&uin=10000&site=qq&menu=yes")));
}
void Developers::githubE()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://github.com/")));
}
