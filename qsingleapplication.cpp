#include "qsingleapplication.h"
#include <QCoreApplication>
#include <QLocalSocket>
#include <QFile>
#include <QStringList>

QSingleApplication::QSingleApplication(int argc, char **argv):QApplication(argc,argv)
{
    _isRunning=false;

    QCoreApplication::setApplicationName("localserver");
    QString serverName=QCoreApplication::applicationName();

    QLocalSocket socket;
    socket.connectToServer(serverName);

    if(socket.waitForConnected(500))
    {
        QTextStream stream(&socket);
        QStringList args=QCoreApplication::arguments();

        if(args.count()>1)
        {
            stream<<args.last();
        }else
        {
            stream<<QString();
        }
        stream.flush();
        qDebug()<<"Connected server,program will quit";

        socket.waitForBytesWritten();

        /**
         *qApp->quit(); �˴����������˳��¼�ѭ����;�ڹ��캯����,�¼�ѭ��
         *��δ����,��˾��޷��˳�. ��þ������ñ�־�ж����ⲿ�ж�
         */


        _isRunning=true;

        return;
    }

    qDebug()<<"Can't connect to server,build a server";
    server=new QLocalServer(this);
    connect(server,SIGNAL(newConnection()),this,SLOT(newLocalConnection()));

    if(server->listen(serverName))
    {
        //��ֹ�������ʱ,�������̷���,�Ƴ�֮
        if(server->serverError()==QAbstractSocket::AddressInUseError&&QFile::exists(server->serverName()))
        {
            QFile::remove(server->serverName());
            server->listen(serverName);
        }
    }


}


void QSingleApplication::newLocalConnection()
{
    QLocalSocket *socket=server->nextPendingConnection();
    if(!socket)
        return;

    socket->waitForReadyRead(1000);

    //��ʾ�������ֵ
    QTextStream in(socket);
    QString vl;
    in>>vl;
    qDebug()<<"The value is: "<<vl;

    delete socket;
}


bool QSingleApplication::isRunning()
{
    return _isRunning;
}
