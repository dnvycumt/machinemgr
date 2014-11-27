#include "dbcommon.h"

DBCommon *DBCommon::m_instance = NULL;

DBCommon::DBCommon()
{
}

DBCommon::~DBCommon()
{
    delete m_instance;
}

DBCommon* DBCommon::get_instance()
{
    if(m_instance == NULL)
    {
        m_instance = new DBCommon;
    }
    return m_instance;
}

int DBCommon::init_database()
{
    QSettings settings(INIT_FILE, QSettings::IniFormat);

    QString strKey = QString("database");
    m_config.m_strIp = settings.value(strKey+"/ip").toString();
    m_config.m_strUser = settings.value(strKey+"/user").toString();
    m_config.m_strPwd = settings.value(strKey+"/pwd").toString();
    m_config.m_strDB = DEFAULT_DB;

    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName(m_config.m_strIp);
    m_db.setDatabaseName(m_config.m_strDB);
    m_db.setUserName(m_config.m_strUser);
    m_db.setPassword(m_config.m_strPwd);

    if (!m_db.open())
    {
        QMessageBox::critical(0, QObject::tr("can't connect to DB"),
                              m_db.lastError().databaseText(), QMessageBox::Cancel);
        exit(-1);
    }

    return 0;
}

void DBCommon::uninit_database()
{
    m_db.close();
}

QSqlQuery DBCommon::get_connect(QString strDB)
{
    m_db.close();
    m_db.setDatabaseName(strDB);
    if (!m_db.open())
    {
        QMessageBox::critical(0, QObject::tr("can't connect to DB"),
                              m_db.lastError().databaseText(), QMessageBox::Cancel);
        exit(-1);
    }

    QSqlQuery query(m_db);
    return query;
}

