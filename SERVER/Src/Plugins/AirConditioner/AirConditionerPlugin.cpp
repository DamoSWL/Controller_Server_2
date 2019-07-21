#include <QNetworkDatagram>
#include <QThread>
#include "AirConditionerPlugin.h"
#include "CRC.h"


AirConditonerPlugin::AirConditonerPlugin(QObject *parent):QObject(parent),m_currentChannel(0),
    m_udpSocket(new QUdpSocket(this)),
    m_responseFlag(false)
{

}

AirConditonerPlugin::~AirConditonerPlugin()
{
    stopListening();
}


void AirConditonerPlugin::setControllerIPAdress(const QString &IP)
{
    m_controllerIP = IP;
}

void AirConditonerPlugin::setHostIPAdress(const QString &IP)
{
    m_hostIP = IP;
}

void AirConditonerPlugin::setAirConfig(const QString &configStr)  //解析空调配置信息
{
    auto index = -1;

    if(configStr.isEmpty())
    {
        return;
    }

    do
    {
        index++;

        auto nextIndex = configStr.indexOf(";",index);
        if(nextIndex == -1)
        {
            nextIndex = configStr.length();
        }

        auto subStr = configStr.mid(index,nextIndex - index);

        auto indexSub = subStr.mid(0,1).toUInt();
        auto channel = subStr.mid(2,1).toUInt();
        auto deviceID = subStr.mid(4,2).toUInt(nullptr,16);


        m_airConditionConfiguration[indexSub] = qMakePair(channel,deviceID);


    }while((index = configStr.indexOf(";",index)) != -1);
}


void AirConditonerPlugin::startListening()
{
    if(m_udpSocket->bind(QHostAddress::AnyIPv4,6008))
    {
        qInfo() << "airConditioner socket bind success";
    }
    else
    {
        qInfo() << "airConditioner socket bind fail";
    }

    connect(m_udpSocket,&QUdpSocket::readyRead,this,&AirConditonerPlugin::readPendingDatagrams);
}

void AirConditonerPlugin::stopListening()
{
    m_udpSocket->close();
}

void AirConditonerPlugin::readPendingDatagrams()
{
    while (m_udpSocket->hasPendingDatagrams())
    {
         auto datagram = m_udpSocket->receiveDatagram().data();

         parseCmd(datagram);
    }
}

void AirConditonerPlugin::onResponseTimeout()
{
    if(!m_responseFlag)
    {
        m_udpSocket->writeDatagram(QByteArray("FAIL",4),QHostAddress(m_hostIP),6008);
    }
}

int AirConditonerPlugin::parseInstructionCmd(const QString &cmd, int &userData)
{
    int cmdFlag = -1;
    int pos = 0;

    if(cmd.indexOf(":") != -1)
    {
        m_currentChannel = cmd.mid(qstrlen("#ATCTL:"),1).toUInt();
    }
    else
    {
        return cmdFlag;
    }

    if(cmd.indexOf("Power") != -1)
    {
        pos = cmd.indexOf("=") + 1;
        auto value = cmd.mid(pos,cmd.length() - 1 - pos);
        if(value == "1")
        {
            cmdFlag = SWITCHON;
        }
        else if(value == "0")
        {
            cmdFlag = SWITCHOFF;
        }
        else{}

    }
    else if(cmd.indexOf("Mode") != -1)
    {
        pos = cmd.indexOf("=") + 1;;
        auto value = cmd.mid(pos,cmd.length() - 1 - pos);

        cmdFlag = MODE;
        userData = value.toUInt();

    }
    else if(cmd.indexOf("Temp") != -1)
    {
        pos = cmd.indexOf("=") + 1;
        auto value = cmd.mid(pos,cmd.length() - 1 - pos);

        cmdFlag = TEMPERATURE;
        userData = value.toUInt();
    }
    else if(cmd.indexOf("V=") != -1)
    {
        pos = cmd.indexOf("V=") + 2;
        auto commaPos = cmd.indexOf(",",pos);
        if(commaPos == -1)
        {
            commaPos = cmd.length() - 1;
        }

        auto value = cmd.mid(pos,commaPos - pos);

        cmdFlag = WINDDIRECTION;
        userData = value.toUInt();
    }
    else if(cmd.indexOf("Speed") != -1)
    {
        pos = cmd.indexOf("=") + 1;
        auto value = cmd.mid(pos,cmd.length() - 1 - pos);

        cmdFlag = WINDSPEED;
        userData = value.toUInt();
    }
    else{}

    return cmdFlag;
}


quint8 AirConditonerPlugin::getSwitchRegisterAddress()
{
    quint8 address = 0;

    switch(m_airConditionConfiguration[m_currentChannel].first)
    {
    case 1:
        address = 0x11;
        break;
    case 2:
        address = 0x21;
        break;
    case 3:
        address = 0x31;
        break;
    case 4:
        address = 0x41;
        break;
    default:
        break;
    }

    return address;
}

void AirConditonerPlugin::sendInstructionCmd(int cmdFlags, int userData)
{
    QByteArray airCmd;
    switch(cmdFlags)
    {
    case SWITCHON:
        airCmd = fabricateSwitchOnCmd();
        break;
    case SWITCHOFF:
        airCmd = fabricateSwitchOffCmd();
        break;
    case MODE:
        airCmd = fabricateModeCmd(userData);
        break;
    case TEMPERATURE:
        airCmd = fabricateTemperatureCmd(userData);
        break;
    case WINDDIRECTION:
        airCmd = fabricateDirectionCmd(userData);
        break;
    case WINDSPEED:
        airCmd = fabricateSpeedCmd(userData);
        break;
    default:
        break;
    }

    if(!airCmd.isEmpty())
    {
        m_udpSocket->write(airCmd);
    }
}

QByteArray AirConditonerPlugin::fabricateSwitchOnCmd()
{
    QByteArray reponseCmd(11,'\0');
    reponseCmd[0] = m_airConditionConfiguration[m_currentChannel].second;
    reponseCmd[1] = 0x43;
    reponseCmd[2] = 0;
    reponseCmd[3] = getSwitchRegisterAddress();
    reponseCmd[4] = 0;
    reponseCmd[5] = 0x01;
    reponseCmd[6] = 0x02;
    reponseCmd[7] = 0;
    reponseCmd[8] = 0xFF;

    CRC::CRCData CRCCheckData;
    CRCCheckData.crcData = CRC::chkcrc((unsigned char*)reponseCmd.data(),9);

    reponseCmd[9] = CRCCheckData.crcByte[1];
    reponseCmd[10] = CRCCheckData.crcByte[0];

    return reponseCmd;
}

QByteArray AirConditonerPlugin::fabricateSwitchOffCmd()
{
    QByteArray reponseCmd(11,'\0');
    reponseCmd[0] = m_airConditionConfiguration[m_currentChannel].second;
    reponseCmd[1] = 0x43;
    reponseCmd[2] = 0;
    reponseCmd[3] = getSwitchRegisterAddress();
    reponseCmd[4] = 0;
    reponseCmd[5] = 0x01;
    reponseCmd[6] = 0x02;
    reponseCmd[7] = 0;
    reponseCmd[8] = 0;

    CRC::CRCData CRCCheckData;
    CRCCheckData.crcData = CRC::chkcrc((unsigned char*)reponseCmd.data(),9);

    reponseCmd[9] = CRCCheckData.crcByte[1];
    reponseCmd[10] = CRCCheckData.crcByte[0];

    return reponseCmd;
}

QByteArray AirConditonerPlugin::fabricateModeCmd(int param)
{
    QByteArray reponseCmd(11,'\0');
    reponseCmd[0] = m_airConditionConfiguration[m_currentChannel].second;
    reponseCmd[1] = 0x43;
    reponseCmd[2] = 0;
    reponseCmd[3] = getSwitchRegisterAddress() + 1;
    reponseCmd[4] = 0;
    reponseCmd[5] = 0x01;
    reponseCmd[6] = 0x02;
    reponseCmd[7] = 0;
    reponseCmd[8] = param;

    CRC::CRCData CRCCheckData;
    CRCCheckData.crcData = CRC::chkcrc((unsigned char*)reponseCmd.data(),9);

    reponseCmd[9] = CRCCheckData.crcByte[1];
    reponseCmd[10] = CRCCheckData.crcByte[0];

    return reponseCmd;
}

QByteArray AirConditonerPlugin::fabricateTemperatureCmd(int param)
{
    QByteArray reponseCmd(11,'\0');
    reponseCmd[0] = m_airConditionConfiguration[m_currentChannel].second;
    reponseCmd[1] = 0x43;
    reponseCmd[2] = 0;
    reponseCmd[3] = getSwitchRegisterAddress() + 2;
    reponseCmd[4] = 0;
    reponseCmd[5] = 0x01;
    reponseCmd[6] = 0x02;
    reponseCmd[7] = 0;
    reponseCmd[8] = param;

    CRC::CRCData CRCCheckData;
    CRCCheckData.crcData = CRC::chkcrc((unsigned char*)reponseCmd.data(),9);

    reponseCmd[9] = CRCCheckData.crcByte[1];
    reponseCmd[10] = CRCCheckData.crcByte[0];

    return reponseCmd;
}

QByteArray AirConditonerPlugin::fabricateSpeedCmd(int param)
{
    QByteArray reponseCmd(11,'\0');
    reponseCmd[0] = m_airConditionConfiguration[m_currentChannel].second;
    reponseCmd[1] = 0x43;
    reponseCmd[2] = 0;
    reponseCmd[3] = getSwitchRegisterAddress() + 3;
    reponseCmd[4] = 0;
    reponseCmd[5] = 0x01;
    reponseCmd[6] = 0x02;
    reponseCmd[7] = 0;
    reponseCmd[8] = param;

    CRC::CRCData CRCCheckData;
    CRCCheckData.crcData = CRC::chkcrc((unsigned char*)reponseCmd.data(),9);

    reponseCmd[9] = CRCCheckData.crcByte[1];
    reponseCmd[10] = CRCCheckData.crcByte[0];

    return reponseCmd;
}

QByteArray AirConditonerPlugin::fabricateDirectionCmd(int param)
{
    QByteArray reponseCmd(11,'\0');
    reponseCmd[0] = m_airConditionConfiguration[m_currentChannel].second;
    reponseCmd[1] = 0x43;
    reponseCmd[2] = 0;
    reponseCmd[3] = getSwitchRegisterAddress() + 4;
    reponseCmd[4] = 0;
    reponseCmd[5] = 0x01;
    reponseCmd[6] = 0x02;
    reponseCmd[7] = 0;
    reponseCmd[8] = param;

    CRC::CRCData CRCCheckData;
    CRCCheckData.crcData = CRC::chkcrc((unsigned char*)reponseCmd.data(),9);

    reponseCmd[9] = CRCCheckData.crcByte[1];
    reponseCmd[10] = CRCCheckData.crcByte[0];

    return reponseCmd;
}

void AirConditonerPlugin::parseCmd(const QByteArray &cmd)
{
    QString cmdStr(cmd);
    if(cmdStr.contains("#ATCTL"))
    {
        auto userData = 0;
        m_responseFlag = false;

        auto cmdFlag = parseInstructionCmd(cmd,userData);      
        sendInstructionCmd(cmdFlag,userData);

        QTimer::singleShot(5000,this,&AirConditonerPlugin::onResponseTimeout);

    }
    else if(cmd[1] == 0x43)
    {
        m_responseFlag = true;
        m_udpSocket->writeDatagram(QByteArray("SUCCESS",7),QHostAddress(m_hostIP),6008);
    }
    else{}
}








