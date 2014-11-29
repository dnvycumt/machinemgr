#include <QtGui/QApplication>
#include "mainwidget.h"
#include <QTextCodec>
#include "qsingleapplication.h"
#include <QDateTime>

//�������ݿ�
//create database rf;create database rx;create database mac;

int main(int argc, char *argv[])
{
    QTextCodec * code = QTextCodec::codecForName("system");
    QTextCodec::setCodecForTr(code);
    //QTextCodec::setCodecForLocale(code);
    //QTextCodec::setCodecForCStrings(code);

    //QApplication a(argc, argv);
    //��ʵ������
    QSingleApplication app(argc,argv);
    if(app.isRunning())
    {
        QMessageBox::critical(NULL,QObject::tr("ע��"), QObject::tr("�Ѿ���һ��������������"), QMessageBox::Ok);
        return 0;
    }

    //ʱ������
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd");
    if(current_date >= "2015-05-30")
    {
        QMessageBox::critical(NULL,QObject::tr("ע��"), QObject::tr("�����ѵ��ڣ�����ϵ����"), QMessageBox::Ok);
        return 0;
    }

    MainWidget w;
    w.show();

    DBCommon::get_instance()->init_database();

    return app.exec();
}
