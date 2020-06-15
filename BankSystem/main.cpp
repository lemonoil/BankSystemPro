#include <QApplication>
#include <QFontDatabase>
#include "BankSystem.h"
#include "Psql.h"
#include "login.h"
#include "profit.h"
#pragma execution_character_set("utf-8")
int main(int argc, char** argv){
    QApplication app(argc, argv);
    QString pat = QDir::currentPath() + "/SourceCodePro-Regular.ttf";
    int fontId = QFontDatabase::addApplicationFont(pat);
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    qDebug() << fontId;
    QFont font(QFontDatabase::applicationFontFamilies(fontId).at(0));
    QApplication::setFont(font);
    
    ExecSQL("select name from bankaccount.account where id=0 ");
    BankSystem* main = new BankSystem();
    main->setWindowTitle("»¶Ó­½øÈëSEUBC");
    main->show();
    return app.exec();
}