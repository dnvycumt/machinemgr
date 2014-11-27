#include <QtGui/QApplication>
#include "mainwidget.h"
#include <QTextCodec>

//创建数据库
//create database rf;create database rx;create database mac;

int main(int argc, char *argv[])
{
    QTextCodec * code = QTextCodec::codecForName("system");
    QTextCodec::setCodecForTr(code);
    //QTextCodec::setCodecForLocale(code);
    //QTextCodec::setCodecForCStrings(code);

    QApplication a(argc, argv);
    MainWidget w;
    w.show();

    DBCommon::get_instance()->init_database();

    return a.exec();
}
