#ifndef MYSQLPROXY_H
#define MYSQLPROXY_H

#include <QtSql/QtSql>
#include <QObject>
#include <QString>

class MysqlProxy : public QRunnable
{
public:
    MysqlProxy();
    ~MysqlProxy();

    // QRunnable interface
public:
    void run() override;
    bool RunSQLNoQuery(const QString &sql);
    QSqlQuery RunSQLQuery(const QString& sql);
    void quit() {m_runState = false;}
    void wait();

    bool getConnectionStatus() const {return m_connectionState;}

private:
    bool m_runState;   //程序运行标志位
    bool m_connectionState;  //数据库连接成功标志位
    bool m_threadAliveState; //线程运行标志位

};

#endif // MYSQLPROXY_H
