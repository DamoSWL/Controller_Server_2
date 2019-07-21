#ifndef STATUSFILEPLUGIN_H
#define STATUSFILEPLUGIN_H

#include <QObject>
#include <QThreadPool>
#include <QRunnable>
#include <QtXml/QtXml>
#include "StatusFile_I.h"
#include "StatusFileDef.h"


class IMysqlDB;

class StatusFilePlugin :public QObject,public QRunnable,public IStatusFile
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID Status_IID FILE "StatusFile.json")
    Q_INTERFACES(IStatusFile)

public:
    StatusFilePlugin(QObject* parent = nullptr);
    ~StatusFilePlugin();

public:
    enum  //文件类型定义
    {
        FFTFILE = 0,
        RADFILE,
        ROBSFILE,
        HOBSFILE,
        OOBSFILE,
        STATUSFILE,
        CALFILE,
        LOGFILE
    };


    // IStatusFile interface
public:
    void setMysqlInstance(IMysqlDB *instance) override;
    void runMonitor() override;   //启动监控线程
    void endMonitor() override;   //停止线程

    // QRunnable interface
public:
    void run() override;    //线程入口函数，执行遍历解析文件


private:
    void quit() {m_runState = false;}
    void wait();

    void traverseFFTFile();  //遍历功率谱文件
    void traverseRadFile();   //遍历径向文件
    void traverseStatusFile();    //遍历状态文件
    void traverseCalFile();    //遍历标定文件
    void traverseOBSFile();    //遍历产品文件
    void traverseLogFile();    //遍历日志文件

    void traverseHOBSFile(qint64& updateTime,const QString& DirStr);  //遍历半小时产品文件
    void traverseOOBSFile(qint64& updateTime,const QString& DirStr);  //遍历一小时产品文件
    void traverseROBSFile(qint64& updateTime,const QString& DirStr);  //遍历实时产品文件

    void readInitFromXML();
    void setNewFileNewInXml(quint8 FileType,const QString& updateTime);
    void setLogFileNameInXml(const QString& fileName);  //将最近日志文件名写入xml
    void setLogFileLineInXml(quint32 lineNum);  //将最近日志文件读取的行数写入xml



    bool getRadarType();
    qint64 getObservationTime(const RadarDef::RadarStatusCF6 statusData);
    qint64 getObservationTime(const RadarDef::RadarStatusCF3 statusData);
    qint64 getObservationTime(const RadarDef::RadarFFTData FFtData);
    qint64 getObservationTime(const QString& TimeStr);

    void getFaultInSubSystem0(const RadarDef::RadarStatusCF6 statusData);  //获取状态文件中分系统状态，组成json
    void getFaultInSubSystem1(const RadarDef::RadarStatusCF6 statusData);
    void getFaultInSubSystem2(const RadarDef::RadarStatusCF6 statusData);
    void getFaultInSubSystem3(const RadarDef::RadarStatusCF6 statusData);
    void getFaultInSubSystem4(const RadarDef::RadarStatusCF6 statusData);
    void getFaultInSubSystem5(const RadarDef::RadarStatusCF6 statusData);
    void getFaultInSubSystem6(const RadarDef::RadarStatusCF6 statusData);
    void getFaultInSubSystem7(const RadarDef::RadarStatusCF6 statusData);
    
    void getFaultInSubSystem(const RadarDef::RadarStatusCF6 statusData);  //获取雷达状态分系统状态
    bool writeRadarStatusToDataBase(const RadarDef::RadarStatusCF6 statusData);  //将雷达状态参数写入数据库中


    void getFaultInSubSystem0(const RadarDef::RadarStatusCF3 statusData);  //获取状态文件中分系统状态，组成json
    void getFaultInSubSystem1(const RadarDef::RadarStatusCF3 statusData);
    void getFaultInSubSystem2(const RadarDef::RadarStatusCF3 statusData);
    void getFaultInSubSystem3(const RadarDef::RadarStatusCF3 statusData);
    void getFaultInSubSystem4(const RadarDef::RadarStatusCF3 statusData);
    void getFaultInSubSystem5(const RadarDef::RadarStatusCF3 statusData);
    void getFaultInSubSystem6(const RadarDef::RadarStatusCF3 statusData);
    void getFaultInSubSystem7(const RadarDef::RadarStatusCF3 statusData);

    void getFaultInSubSystem(const RadarDef::RadarStatusCF3 statusData);
    bool writeRadarStatusToDataBase(const RadarDef::RadarStatusCF3 statusData);

    bool writeKeyStatusParamCF6ToDataBase(const RadarDef::RadarStatusCF6 statusData);  //将雷达关键参数写入数据库中
    void calcAveReflectPowerCF6(const RadarDef::RadarStatusCF6 statusData);  //计算状态文件里面的关键参数
    void calcAveOutputPowerCF6(const RadarDef::RadarStatusCF6 statusData);
    void calcSWRCF6();

    void parseCalibrationFile(const QString& fileName);  //解析标定文件
    void parseLogFile(const QString& fullFilePath);   //解析日志文件

    bool writekeyStaticParamToDataBase(const RadarDef::RadarFFTData FFTData);
    bool writeCalParamToDataBase();

    bool writeFileInfoToDatabase(quint8 fileType, const QString& fullFilePath);  //将遍历的文件信息写入数据库中

    qint64 getUpdateTime(const QString& Date,const QString& Time);
    bool writeLogToDataBase(qint64 updateTime,const QString& updateTimeStr,const QString& logInfo);

private:
    QDomDocument m_DOC;
    QString m_RadarType;

    qint64 m_updateTimeStatus;  //最新文件的修改时间
    qint64 m_updateTimeFFT;
    qint64 m_updateTimeCal;
    qint64 m_updateTimeRad;
    qint64 m_updateTimeHOBS;
    qint64 m_updateTimeOOBS;
    qint64 m_updateTimeROBS;
    qint64 m_updateTimeLOG;


    bool m_runState;  //程序运行标志位
    bool m_threadAliveState;  //线程运行标志位

    IMysqlDB* m_MysqlInstance;

    QString m_FaultInSubsystem0;  //分系统状态
    QString m_FaultInSubsystem1;
    QString m_FaultInSubsystem2;
    QString m_FaultInSubsystem3;
    QString m_FaultInSubsystem4;
    QString m_FaultInSubsystem5;
    QString m_FaultInSubsystem6;
    QString m_FaultInSubsystem7;

    float m_AveReflectPowerCF6;  //雷达状态关键参数
    float m_AveOutputPowerCF6;
    float m_SWRCF6;

    qint64 m_CalFileObservationTime;  //标定文件参数
    QString m_CalSiteInfo;
    QString m_25HzDopplerVelocity;
    QString m_NE25HzDopplerVelocity;
    QString m_75HzDopplerVelocity;
    QString m_NE75HzDopplerVelocity;

    float m_NoiseFactor;
    float m_ReceiverSensitivity;
    float m_DynamicRange;
    float m_EmitterPower;
    float m_SystemCoherence;

    QString m_receiveAmplitude;
    QString m_receivePhase;
    QString m_emitterAmplitude;
    QString m_emitterPhase;

    QString m_previousLogFileName;
    quint32 m_previousLogLine;

};






















#endif
