#ifndef QSINGLEAPPLICATION_H
#define QSINGLEAPPLICATION_H
#include <QLocalServer>
#include <QApplication>

class QSingleApplication:public QApplication
{
    Q_OBJECT
public:
    QSingleApplication(int argc,char **argv);

    bool isRunning();

private slots:
    void newLocalConnection();

private:
    QLocalServer *server;

    bool _isRunning;
};

#endif // QSINGLEAPPLICATION_H
