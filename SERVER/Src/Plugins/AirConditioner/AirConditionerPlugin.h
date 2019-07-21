
#ifndef AIRCONDITIONER_H
#define AIRCONDITIONER_H


#include <QObject>
#include <QUdpSocket>
#include <QString>
#include <QMap>
#include <QByteArray>
#include <QTimer>
#include "AirConditioner_I.h"


class AirConditonerPlugin :public QObject,public IAirConditioner
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID AirConditioner_IID FILE "AirConditioner.json")
    Q_INTERFACES(IAirConditioner)

public:
    AirConditonerPlugin(QObject* parent = nullptr);
    ~AirConditonerPlugin();


    // IAirConditioner interface
public:
    void setControllerIPAdress(const QString &IP) override;  //设置空调控制器IP地址
    void setHostIPAdress(const QString &IP) override;  //设置java接收端的IP地址
    void setAirConfig(const QString &configStr) override;  //设置空调配置信息
    void startListening() override;   //启动网络监听
    void stopListening() override;  //关闭网络监听


private slots:
    void readPendingDatagrams();  //处理接收到的命令和返回信息
    void onResponseTimeout();    //响应定时器，超过时间没接收到数据则向java端发送失败


private:
    enum
    {
        SWITCHOFF = 0,
        SWITCHON,
        MODE,
        TEMPERATURE,
        WINDDIRECTION,
        WINDSPEED
    };

    enum
    {
        MODEAUTO = 0,
        MODECOLD,
        MODEHUMIDITY,
        MODEWIND,
        MODEWARM,
    };


private:
    void parseCmd(const QByteArray& cmd);
    int parseInstructionCmd(const QString& cmd,int& userData);  //处理接收到的空调控制命令

    quint8 getSwitchRegisterAddress();  //获取空调控制器寄存器地址

    void sendInstructionCmd(int cmdFlags,int userData);  //组建命令
    QByteArray fabricateSwitchOnCmd();
    QByteArray fabricateSwitchOffCmd();
    QByteArray fabricateModeCmd(int param);
    QByteArray fabricateTemperatureCmd(int param);
    QByteArray fabricateSpeedCmd(int param);
    QByteArray fabricateDirectionCmd(int param);

private:
    QString m_controllerIP;
    QString m_hostIP;

    quint8 m_currentChannel;
    QUdpSocket* m_udpSocket;
    QMap<quint8, QPair<quint8,quint8> > m_airConditionConfiguration;  //空调配置信息
    bool m_responseFlag;  //标志位，判断是否收到回复




};

















#endif
