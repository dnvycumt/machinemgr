#include <QtGui/QApplication>
#include "mainwidget.h"
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QTextCodec * code = QTextCodec::codecForName("system");
    QTextCodec::setCodecForTr(code);
    //QTextCodec::setCodecForLocale(code);
    //QTextCodec::setCodecForCStrings(code);

    QApplication a(argc, argv);
    MainWidget w;
    w.show();

    DBCommon::get_instance()->init_database();//初始化数据库

    return a.exec();
}
