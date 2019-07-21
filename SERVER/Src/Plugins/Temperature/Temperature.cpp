#include "Temperature.h"
#include <QNetworkDatagram>
#include <QByteArray>
#include <QThreadPool>
#include <QDateTime>
#include <QtDebug>
#include "MysqlDB_I.h"

TemperaturePlugin::TemperaturePlugin(QObject *parent):QObject(parent),
        m_udpSocket(new QUdpSocket(this)),
        m_MysqlInstance(nullptr),
        m_runState(false),
        m_threadAliveState(false)
{

}

TemperaturePlugin::~TemperaturePlugin()
{

}


void TemperaturePlugin::setIPAdress(const QString &IP)
{
    m_IPAdress = IP;
}

void TemperaturePlugin::setMysqlInstance(IMysqlDB *instance)
{
    m_MysqlInstance = instance;
}

void TemperaturePlugin::runMonitor()
{

    if(m_udpSocket->bind(QHostAddress::AnyIPv4,3152))
    {
        qInfo() << "temperature socket bind success";
    }
    else
    {
        qInfo() << "temperature socket bind fail";
    }

    connect(m_udpSocket,&QUdpSocket::readyRead,this,&TemperaturePlugin::readPendingDatagrams);

    QThreadPool::globalInstance()->start(this);
}

void TemperaturePlugin::endMonitor()
{
    m_udpSocket->close();
    quit();
    wait();

}

void TemperaturePlugin::run()
{
    m_runState = true;
    m_threadAliveState = true;


    char TemperatureCmd[8] = {'\0'};
    TemperatureCmd[0] = '\x11';
    TemperatureCmd[1] = '\x03';
    TemperatureCmd[2] = '\x00';
    TemperatureCmd[3] = '\x00';
    TemperatureCmd[4] = '\x00';
    TemperatureCmd[5] = '\x05';
    TemperatureCmd[6] = '\x87';
    TemperatureCmd[7] = '\x59';

    while(m_runState)
    {

        if(m_udpSocket->isOpen())
        {
             m_udpSocket->writeDatagram(TemperatureCmd,8,QHostAddress(m_IPAdress),26);
        }


        for(auto i = 0;i < 900;i++)
        {
            QThread::msleep(200);
            if(!m_runState)
            {
                break;
            }
        }
    }

    m_threadAliveState = false;
}

void TemperaturePlugin::wait()
{
    while(m_threadAliveState)
    {
        QThread::msleep(50);
    }
}

bool TemperaturePlugin::writeEnvToDataBase(quint8 id,float temperature,float humidity)
{
    quint8 type = 1;

    if(id == 0x11)
    {
        type = 2;
    }



    if(m_MysqlInstance)
    {
         auto sqlSentence = QString("INSERT INTO t_env_humiture(update_time,type,temp,hump) VALUES(%1,%2,%3,%4)")\
                 .arg(QDateTime::currentDateTime().toSecsSinceEpoch())\
                 .arg(type)\
                 .arg(temperature)\
                 .arg(humidity);

         m_MysqlInstance->RunSQLNoQuery(sqlSentence);
    }

    return true;

}

void TemperaturePlugin::readPendingDatagrams()
{
    while (m_udpSocket->hasPendingDatagrams())
    {
         auto datagram = m_udpSocket->receiveDatagram().data();

         if(((quint8)datagram.length() == 13) && ((quint8)datagram[1] == (quint8)0x03) && ((quint8)datagram[0] == (quint8)0x11))  //解析温湿度
         {
             qint32 tmptemperature = ((quint8)datagram[7]) * 256 + (quint8)datagram[8];

             float sign = -1.0;
             if((tmptemperature & (1 << 15)) == 0)
             {
                 sign = 1.0;
             }
             tmptemperature &= 0x7FFF;
             float temperature = tmptemperature * sign / 10.0;
             temperature += (quint8)datagram[5] / 10.0;

             qint32 tmphumidity = ((quint8)datagram[9]) * 256 + (quint8)datagram[10];
             float humidity = tmphumidity / 10.0;

             writeEnvToDataBase(0x11,temperature,humidity);
         }



     }
}
