#include <QtGui/QApplication>
#include "mainwidget.h"
#include "dbcommon.h"
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QTextCodec * code = QTextCodec::codecForName("system");
    QTextCodec::setCodecForTr(code);
    //QTextCodec::setCodecForLocale(code);
    //QTextCodec::setCodecForCStrings(code);
    DBCommon::get_instance()->init_database();
    QApplication a(argc, argv);
    MainWidget w;
    w.show();

    return a.exec();
}
