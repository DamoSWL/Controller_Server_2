#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <QObject>
#include <QRunnable>
#include <QUdpSocket>
#include "Temperature_I.h"


class IMysqlDB;

class TemperaturePlugin : public QObject,public QRunnable,public ITemperature
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID Temperature_IID FILE "Temperature.json")
    Q_INTERFACES(ITemperature)

public:
    TemperaturePlugin(QObject* parent = nullptr);
    ~TemperaturePlugin();

    // ITemperature interface
public:
    void setIPAdress(const QString &IP) override;   //设置环境主机IP地址
    void setMysqlInstance(IMysqlDB *instance) override;
    void runMonitor() override;    //启动采集线程
    void endMonitor() override;    //关闭采集线程

    // QRunnable interface
public:
    void run() override;  //线程入口函数，在线程中采集温湿度



private:
    void quit() {m_runState = false;}
    void wait();

    bool writeEnvToDataBase(quint8 id,float temperature,float humidity);  //将环境温湿度写入数据库中

private slots:
    void readPendingDatagrams();  //接收处理返回的温湿度信息


private:
    QUdpSocket* m_udpSocket;
    IMysqlDB* m_MysqlInstance;

    QString m_IPAdress;

    bool m_runState;  //程序运行标志位
    bool m_threadAliveState;  //线程运行标志位
};


#endif
