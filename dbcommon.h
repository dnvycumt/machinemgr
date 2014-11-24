#ifndef DBCOMMON_H
#define DBCOMMON_H

#include <QString>
#include <QMap>
#include <QSettings>

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
    int init_database();
    QMap<QString, Config> m_mapConfig;

    ~DBCommon();

private:
    DBCommon();

    static DBCommon *m_instance;
};

#endif // DBCOMMON_H
