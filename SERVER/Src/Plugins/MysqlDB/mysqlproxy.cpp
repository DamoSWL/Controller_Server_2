#include "mysqlproxy.h"
#include <sys/stat.h>
#include <unistd.h>
#include <QProcess>


MysqlProxy::MysqlProxy():m_runState(true),m_connectionState(false),m_threadAliveState(false)
{

}

MysqlProxy::~MysqlProxy()
{
    m_runState = false;
    m_connectionState = false;
    m_threadAliveState = false;
}


void MysqlProxy::run()
{
    m_threadAliveState = true;

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("root");


    db.setConnectOptions("MYSQL_OPT_RECONNECT=true;MYSQL_OPT_CONNECT_TIMEOUT=300");

    while(m_runState)
    {
        if(!m_connectionState)
        {
            if(db.open())
            {
                QSqlQuery query;

                if(!query.exec("USE wprsoc"))
                {
                    if(query.exec("CREATE DATABASE IF NOT EXISTS wprsoc"))
                    {

                        QFile sqlFile("./init.sh");
                        if(!sqlFile.open(QFile::WriteOnly | QFile::Text))
                        {
                            qInfo() << sqlFile.errorString();
                        }
                        else
                        {
                            sqlFile.write("#! /bin/sh\nmysql -h localhost -uroot -pcdyw wprsoc < wprsoc.sql");
                        }

                        sqlFile.flush();
                        sqlFile.close();


                        struct stat fileStat;
                        stat("init.sh",&fileStat);

                        chmod("init.sh",fileStat.st_mode | S_IRWXU);

                        QProcess process;
                        process.setProgram("./init.sh");   //启动进程初始化数据库
                        process.start();
                        process.waitForFinished(-1);

                        if(process.exitStatus() == 0)
                        {
                            m_connectionState = true;
                            query.exec("USE wrsocdb");
                        }
                        else
                        {
                            qInfo() << process.error();
                        }

                    }
                }
                else
                {
                    m_connectionState = true;
                }

            }
            else
            {
                qInfo() << "database open fail";
            }


        }

        for(auto i = 0;i < 100;i++)
        {
            QThread::msleep(200);
            if(!m_runState)
            {
                break;
            }
        }
    }

    db.close();
}

bool MysqlProxy::RunSQLNoQuery(const QString &sql)
{
   QSqlQuery query;
   bool ok = query.exec(sql);
   if(!ok)
   {
       qInfo() << query.lastError().text();
   }

   return ok;

}

QSqlQuery MysqlProxy::RunSQLQuery(const QString& sql)
{
    QSqlQuery query;
    if(!query.exec(sql))
    {
        qInfo() << query.lastError().text();
    }

    return query;
}

void MysqlProxy::wait()
{
    while(m_threadAliveState)
    {
        QThread::msleep(50);
    }
}

