#ifndef DBCOMMON_H
#define DBCOMMON_H

#include <QString>
#include <QMap>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

#define INIT_FILE "db_config.ini"

class Config
{
public:
    QString m_strIp;
    QString m_strUser;
    QString m_strPwd;
    QString m_strDB;
};

class DBCommon
{
public:
    static DBCommon* get_instance();
    QSqlQuery get_connect(QString strDB="rf");
    void uninit_database();
    int init_database();

    ~DBCommon();

private:
    DBCommon();
    //QMap<QString, QSqlDatabase> m_mapDb;
    Config m_config;
    QSqlDatabase m_db;
    QSqlDatabase dbConnect;

    static DBCommon *m_instance;
};

#endif // DBCOMMON_H
