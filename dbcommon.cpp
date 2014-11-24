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
    int iDbNum = settings.value("sysconfig/db_num").toInt();

    for(int i = 0; i < iDbNum; ++i)
    {
        Config cfg;
        QString strKey = "database"+i;
        cfg.m_strIp = settings.value(strKey+"/ip").toString();
        cfg.m_strUser = settings.value(strKey+"/user").toString();
        cfg.m_strPwd = settings.value(strKey+"/pwd").toString();
        cfg.m_strDB = settings.value(strKey+"/name").toString();
        m_mapConfig.insert(cfg.m_strDB, cfg);


    }
    return 0;
}

