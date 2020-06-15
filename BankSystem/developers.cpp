#include"developers.h"
#pragma execution_character_set("utf-8")
Developers::Developers(QDialog* parent) :QDialog(parent) {
    this->setWindowTitle(tr("开发人员"));
    this->resize(700, 350);
    this->setMaximumSize(700, 350);
    this->setMinimumSize(700, 350);
    this->setObjectName("Dia");
    this->setStyleSheet("#Dia{background-color:#f1feff;}");
    Lmy = new ClickLabel(tr("李明洋 JS319111"));
    Wt = new ClickLabel(tr("吴桐 JS319102"));
    Xzh = new ClickLabel(tr("许志豪 JS319130"));
    Chh = new ClickLabel(tr("程瀚 JS319114"));
    Git = new QLabel(tr("github: "));
    Link = new ClickLabel(tr("https://github.com/lemonoil/Bank-System"));
    ExitBtn = new QPushButton(tr("退出"));
    Lmy->setObjectName("Lmy");
    Lmy->setStyleSheet("#Lmy{font-weight:bold;}#Lmy:hover{color:#FF00FF;}");
    Wt->setObjectName("Wt");
    Wt->setStyleSheet("#Wt{font-weight:bold;}#Wt:hover{color:#FF00FF;}");
    Xzh->setObjectName("Xzh");
    Xzh->setStyleSheet("#Xzh{font-weight:bold;}#Xzh:hover{color:#FF00FF;}");
    Chh->setObjectName("Chh");
    Chh->setStyleSheet("#Chh{font-weight:bold;}#Chh:hover{color:#FF00FF;}");
    Link->setObjectName("Link");
    Link->setStyleSheet("#Link{text-decoration:underline;color:blue;font-style:italic;}#Link:hover{color:#FF00FF;}");
    ExitBtn->setObjectName("exit");
    ExitBtn->setStyleSheet("#exit{background-color: #ff5d5d;font-weight:bold;color:#e8e8e8;}#exit:hover{background-color: #ff8989;font-weight:bold;color:#e8e8e8;}");
    QGridLayout* grid_layout = new QGridLayout(this);
    grid_layout->addWidget(Lmy, 0, 1, 1, 2, Qt::AlignRight);
    grid_layout->addWidget(Wt, 0, 4, 1, 3, Qt::AlignLeft);
    grid_layout->addWidget(Xzh, 1, 1, 1, 2, Qt::AlignRight);
    grid_layout->addWidget(Chh, 1, 4, 1, 3, Qt::AlignLeft);
    grid_layout->addWidget(Git, 2, 0, 1, 2, Qt::AlignRight);
    grid_layout->addWidget(Link, 2, 2, 1, 5, Qt::AlignLeft);
    grid_layout->addWidget(ExitBtn, 3, 6);
    connect(Lmy, SIGNAL(clicked()), this, SLOT(LmyGithub()));
    connect(Wt, SIGNAL(clicked()), this, SLOT(WtBlog()));
    connect(Xzh, SIGNAL(clicked()), this, SLOT(XzhQQ()));
    connect(Chh, SIGNAL(clicked()), this, SLOT(ChhQQ()));
    connect(Link, SIGNAL(clicked()), this, SLOT(githubE()));
    connect(ExitBtn, SIGNAL(clicked()), this, SLOT(close()));
}

ClickLabel::ClickLabel(QString st, QWidget* parent) :QLabel(st)
{}
void ClickLabel::mouseReleaseEvent(QMouseEvent* e)
{
    emit clicked(); // 在点击事件中发送信号
}
void Developers::LmyGithub()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://github.com/lemonoil")));
}
void Developers::WtBlog()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://blog.csdn.net/wu_tongtong")));
}
void Developers::XzhQQ()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("http://wpa.qq.com/msgrd?v=3&uin=1905175128&site=qq&menu=yes")));
}
void Developers::ChhQQ()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("http://wpa.qq.com/msgrd?v=3&uin=398957747&site=qq&menu=yes")));
}
void Developers::githubE()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://github.com/lemonoil/Bank-System")));
}
