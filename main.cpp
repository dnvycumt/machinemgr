#include <QtGui/QApplication>
#include "mainwidget.h"
#include <QTextCodec>
#include "qsingleapplication.h"
#include <QDateTime>

//创建数据库
//create database rf;create database rx;create database mac;

int main(int argc, char *argv[])
{
    QTextCodec * code = QTextCodec::codecForName("system");
    QTextCodec::setCodecForTr(code);
    //QTextCodec::setCodecForLocale(code);
    //QTextCodec::setCodecForCStrings(code);

    //QApplication a(argc, argv);
    //单实例运行
    QSingleApplication app(argc,argv);
    if(app.isRunning())
    {
        QMessageBox::critical(NULL,QObject::tr("注意"), QObject::tr("已经有一个程序在运行了"), QMessageBox::Ok);
        return 0;
    }

    //时间限制
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd");
    if(current_date >= "2015-05-30")
    {
        QMessageBox::critical(NULL,QObject::tr("注意"), QObject::tr("程序已到期，请联系作者"), QMessageBox::Ok);
        return 0;
    }

    MainWidget w;
    w.show();

    DBCommon::get_instance()->init_database();

    return app.exec();
}
