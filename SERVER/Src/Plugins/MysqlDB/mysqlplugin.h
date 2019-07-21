#ifndef MYSQLPLUGIN_H
#define MYSQLPLUGIN_H

#include <QObject>
#include "MysqlDB_I.h"

class MysqlProxy;


class MysqlDBPlugin :public QObject, public IMysqlDB
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID MysqlDB_IID FILE "MysqlPlugin.json")
    Q_INTERFACES(IMysqlDB)

public:

    MysqlDBPlugin(QObject* parent = nullptr);
    ~MysqlDBPlugin();

    // IMysqlDB interface
public:
    void ConnectToDataBase() override;  //连接数据库并进行初始化
    bool RunSQLNoQuery(const QString &sql) override;   //将数据插入数据库中
    QSqlQuery RunSQLQuery(const QString& sql) override;  //从数据库中查询数据
    bool getConnectionStatus() override;  //标志位，判断数据库初始化是否完成

private:
    MysqlProxy* m_SqlProxy;



};

#endif // MYSQLDB_H
