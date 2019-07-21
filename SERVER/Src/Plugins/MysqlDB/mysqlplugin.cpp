#include "mysqlplugin.h"
#include "mysqlproxy.h"




MysqlDBPlugin::MysqlDBPlugin(QObject *parent):QObject(parent),m_SqlProxy(new MysqlProxy)
{

}

MysqlDBPlugin::~MysqlDBPlugin()
{
    m_SqlProxy->quit();
    m_SqlProxy->wait();
}

void MysqlDBPlugin::ConnectToDataBase()
{
    QThreadPool::globalInstance()->start(m_SqlProxy);
}

bool MysqlDBPlugin::RunSQLNoQuery(const QString &sql)
{
    if(m_SqlProxy)
    {
        return m_SqlProxy->RunSQLNoQuery(sql);
    }

    return false;
}


QSqlQuery MysqlDBPlugin::RunSQLQuery(const QString& sql)
{
    return m_SqlProxy->RunSQLQuery(sql);
}


bool MysqlDBPlugin::getConnectionStatus()
{
    return m_SqlProxy->getConnectionStatus();
}
