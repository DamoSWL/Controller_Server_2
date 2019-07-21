#ifndef IMYSQLDB_I_H
#define IMYSQLDB_I_H

#include <QObject>
#include <QString>
#include <QtSql/QSqlQuery>

class IMysqlDB
{
public:
    virtual ~IMysqlDB() {}
    virtual void ConnectToDataBase() = 0;
    virtual bool RunSQLNoQuery(const QString& sql) = 0;
    virtual QSqlQuery RunSQLQuery(const QString& sql) = 0;
    virtual bool getConnectionStatus() = 0;
     
};


#define MysqlDB_IID  "28654FD1-36F1-468E-8CC8-5BDCF9A2D3F2"
Q_DECLARE_INTERFACE(IMysqlDB, MysqlDB_IID)

#endif // IMYSQLDB_I_H
