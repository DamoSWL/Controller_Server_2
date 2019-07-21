
#include "StatusFileplugin.h"
#include <QDir>
#include <QDateTime>
#include <QSet>
#include <cstring>
#include <QTextCodec>
#include <QByteArray>
#include <QDateTime>
#include <QVariant>
#include <QTextStream>
#include "MysqlDB_I.h"



StatusFilePlugin::StatusFilePlugin(QObject *parent):QObject(parent),
     m_updateTimeStatus(0UL),
     m_updateTimeFFT(0UL),
     m_updateTimeCal(0UL),
     m_updateTimeRad(0UL),
     m_updateTimeHOBS(0UL),
     m_updateTimeOOBS(0UL),
     m_updateTimeROBS(0UL),
     m_updateTimeLOG(0UL),
    m_runState(false),
    m_threadAliveState(false),
    m_MysqlInstance(nullptr),
    m_AveReflectPowerCF6(0),
    m_AveOutputPowerCF6(0),
    m_SWRCF6(0),
    m_CalFileObservationTime(0),
    m_NoiseFactor(0),
    m_ReceiverSensitivity(0),
    m_DynamicRange(0),
    m_EmitterPower(0),
    m_SystemCoherence(0),
    m_previousLogLine(0)

{

}

StatusFilePlugin::~StatusFilePlugin()
{

}


void StatusFilePlugin::runMonitor()
{
    readInitFromXML();
    QThreadPool::globalInstance()->start(this);
}

void StatusFilePlugin::run()
{
    m_runState = true;
    m_threadAliveState = true;

    getRadarType();

    while(m_runState)
    {
       traverseFFTFile();
       traverseRadFile();
       traverseOBSFile();
       traverseStatusFile();
       traverseCalFile();
       traverseLogFile();

        for(auto i = 0;i < 100;i++)
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

void StatusFilePlugin::wait()
{
    while(m_threadAliveState)
    {
        QThread::msleep(50);
    }
}

void StatusFilePlugin::traverseRadFile()
{
    qint64 updateTime = 0UL;

    QDir dir("/mnt/data/wprsoc/ftp/radartemp/output/Wind/");
    if(dir.exists())
    {
         dir.setSorting(QDir::Name | QDir::Type);
         dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);

         auto subOneDirStrList = dir.entryList();  //遍历第一级目录

         foreach (QString subOneDirStr, subOneDirStrList)
         {
             QString fullSubOneDirStr = "/mnt/data/wprsoc/ftp/radartemp/output/Wind/";
             fullSubOneDirStr += subOneDirStr;
             fullSubOneDirStr += "/";

             QDir subOneDir(fullSubOneDirStr);

             subOneDir.setSorting(QDir::Name | QDir::Type);
             subOneDir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);

             auto subTwoDirStrList = subOneDir.entryList();  //遍历第二级目录

             foreach (QString subTwoDirStr, subTwoDirStrList)
             {
                 QString fullSubTwoDirStr = fullSubOneDirStr;
                 fullSubTwoDirStr += subTwoDirStr;
                 fullSubTwoDirStr += "/WNDRAD/";

                 QDir subTwoDir(fullSubTwoDirStr);

                 subTwoDir.setSorting(QDir::Name | QDir::Type);
                 subTwoDir.setFilter(QDir::Files | QDir::Readable | QDir::NoDotAndDotDot);
                 subTwoDir.setNameFilters(QStringList() << "*RAD.TXT" << "*RAD.txt");

                 auto FileNameList = subTwoDir.entryList();  //遍历文件
                 foreach (auto fileName, FileNameList)
                 {
                     QString fullFilePathStr = fullSubTwoDirStr;
                     fullFilePathStr += fileName;

                     QFileInfo fileInfo(fullFilePathStr);
                     updateTime = fileInfo.lastModified().toSecsSinceEpoch();
                     if(updateTime > m_updateTimeRad)
                     {
                         writeFileInfoToDatabase(RADFILE,fullFilePathStr);
                     }

                 }

             }

         }
        m_updateTimeRad = updateTime;
        setNewFileNewInXml(RADFILE,QString::number(m_updateTimeRad));
    }
}

void StatusFilePlugin::traverseStatusFile()
{
    qint64 updateTime = 0UL;

    QDir dir("/mnt/data/wprsoc/ftp/radartemp/input");
    if(dir.exists())
    {
        dir.setSorting(QDir::Name | QDir::Type);
        dir.setFilter(QDir::Files | QDir::Readable | QDir::NoDotAndDotDot);
        dir.setNameFilters(QStringList() << "*STA.bin" << "*STA.dat");


        QSet<QString> FileNames;

        auto FileNameList = dir.entryList();  //遍历第一级目录
        foreach (auto fileName, FileNameList)
        {
            QString fullPath = "/mnt/data/wprsoc/ftp/radartemp/input";
            fullPath += "/";
            fullPath += fileName;

            QFileInfo fileInfo(fullPath);
            updateTime = fileInfo.lastModified().toSecsSinceEpoch();
            if(updateTime > m_updateTimeStatus)
            {
                FileNames.insert(fullPath);
            }
        }

        if(m_RadarType == QStringLiteral("CFL6"))  //6公里文件
        {
             for(auto item = FileNames.cbegin();item != FileNames.cend();item++)
             {
                 RadarDef::RadarStatusCF6 radarStatus;
                 std::memset((char*)&radarStatus,'\0',sizeof(RadarDef::RadarStatusCF6));

                 QFile statusFile(*item);
                 if(statusFile.open(QFile::ReadOnly))
                 {
                     statusFile.read((char*)&radarStatus,sizeof(RadarDef::RadarStatusCF6));
                 }
                 statusFile.close();

                 getFaultInSubSystem(radarStatus);
                 writeRadarStatusToDataBase(radarStatus);

                calcAveReflectPowerCF6(radarStatus);
                calcAveOutputPowerCF6(radarStatus);
                calcSWRCF6();

                writeFileInfoToDatabase(STATUSFILE,*item);
                writeKeyStatusParamCF6ToDataBase(radarStatus);

             }
        }
        else if(m_RadarType == QStringLiteral("CFL3"))  //3公里文件
        {
            for(auto item = FileNames.cbegin();item != FileNames.cend();item++)
            {
                RadarDef::RadarStatusCF3 radarStatus;
                std::memset((char*)&radarStatus,'\0',sizeof(RadarDef::RadarStatusCF3));

                QFile statusFile(*item);
                if(statusFile.open(QFile::ReadOnly))
                {
                    statusFile.read((char*)&radarStatus,sizeof(RadarDef::RadarStatusCF3));
                }

                statusFile.close();

                getFaultInSubSystem(radarStatus);

                writeFileInfoToDatabase(STATUSFILE,*item);
                writeRadarStatusToDataBase(radarStatus);

            }
        }
        else{}

        m_updateTimeStatus = updateTime;
        setNewFileNewInXml(STATUSFILE,QString::number(m_updateTimeStatus));

    }
}

void StatusFilePlugin::traverseFFTFile()
{

    qint64 updateTime = 0UL;

    QDir dir("/mnt/data/wprsoc/ftp/radartemp/input");
    if(dir.exists())
    {
        dir.setSorting(QDir::Name | QDir::Type);
        dir.setFilter(QDir::Files | QDir::Readable | QDir::NoDotAndDotDot);
        dir.setNameFilters(QStringList() << "*FFT.BIN" << "*FFT.dat");


        QSet<QString> FileNames;

        auto FileNameList = dir.entryList();   //遍历第一级目录
        foreach (auto fileName, FileNameList)
        {
            QString fullPath = "/mnt/data/wprsoc/ftp/radartemp/input";
            fullPath += "/";
            fullPath += fileName;

            QFileInfo fileInfo(fullPath);
            updateTime = fileInfo.lastModified().toSecsSinceEpoch();
            if(updateTime > m_updateTimeFFT)
            {
                FileNames.insert(fullPath);
            }
        }

        for(auto item = FileNames.cbegin();item != FileNames.cend();item++)
        {
            RadarDef::RadarFFTData radarFFTData;
            std::memset((char*)&radarFFTData,'\0',sizeof(RadarDef::RadarFFTData));

            QFile statusFile(*item);
            if(statusFile.open(QFile::ReadOnly))
            {
                statusFile.read((char*)&radarFFTData,sizeof(RadarDef::RadarFFTData));
            }
            statusFile.close();

            writeFileInfoToDatabase(FFTFILE,*item);
            writekeyStaticParamToDataBase(radarFFTData);

        }

        m_updateTimeFFT = updateTime;
        setNewFileNewInXml(FFTFILE,QString::number(m_updateTimeFFT));
    }


}

void StatusFilePlugin::traverseCalFile()
{
    qint64 updateTime = 0UL;

    QDir dir("/mnt/data/wprsoc/ftp/radartemp/input");
    if(dir.exists())
    {
        dir.setSorting(QDir::Name | QDir::Type);
        dir.setFilter(QDir::Files | QDir::Readable | QDir::NoDotAndDotDot);
        dir.setNameFilters(QStringList() << "*CAL.TXT" << "*CAL.txt");


        QSet<QString> FileNames;

        auto FileNameList = dir.entryList();   //遍历第一级目录
        foreach (auto fileName, FileNameList)
        {
            QString fullPath = "/mnt/data/wprsoc/ftp/radartemp/input";
            fullPath += "/";
            fullPath += fileName;

            QFileInfo fileInfo(fullPath);
            updateTime = fileInfo.lastModified().toSecsSinceEpoch();
            if(updateTime > m_updateTimeCal)
            {
                FileNames.insert(fullPath);
            }
        }

        if(m_RadarType == QStringLiteral("CFL6"))
        {
             for(auto item = FileNames.cbegin();item != FileNames.cend();item++)
             {
                parseCalibrationFile(*item);
                writeFileInfoToDatabase(CALFILE,*item);
                writeCalParamToDataBase();

             }
        }
        m_updateTimeCal = updateTime;
        setNewFileNewInXml(CALFILE,QString::number(m_updateTimeCal));

    }
}

void StatusFilePlugin::traverseOBSFile()
{
    qint64 updateTimeHOBS = 0UL;
    qint64 updateTimeOOBS = 0UL;
    qint64 updateTimeROBS = 0UL;

    QDir dir("/mnt/data/wprsoc/ftp/radartemp/output/Wind/");
    if(dir.exists())
    {
         dir.setSorting(QDir::Name | QDir::Type);
         dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);

         auto subOneDirStrList = dir.entryList();   //遍历第一级目录

         foreach (QString subOneDirStr, subOneDirStrList)
         {
             QString fullSubOneDirStr = "/mnt/data/wprsoc/ftp/radartemp/output/Wind/";
             fullSubOneDirStr += subOneDirStr;
             fullSubOneDirStr += "/";

             QDir subOneDir(fullSubOneDirStr);

             subOneDir.setSorting(QDir::Name | QDir::Type);
             subOneDir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);

             auto subTwoDirStrList = subOneDir.entryList();   //遍历第二级目录

             foreach (QString subTwoDirStr, subTwoDirStrList)
             {
                 QString fullSubTwoDirStr = fullSubOneDirStr;
                 fullSubTwoDirStr += subTwoDirStr;
                 fullSubTwoDirStr += "/WNDOBS/";

                 QString fullHOBSDirStr = fullSubTwoDirStr;
                 fullHOBSDirStr += "HOBS/";

                 QString fullOOBSDirStr = fullSubTwoDirStr;
                 fullOOBSDirStr += "OOBS/";

                 QString fullROBSDirStr = fullSubTwoDirStr;
                 fullROBSDirStr += "ROBS/";

                 traverseHOBSFile(updateTimeHOBS,fullHOBSDirStr);
                 traverseOOBSFile(updateTimeHOBS,fullOOBSDirStr);
                 traverseROBSFile(updateTimeHOBS,fullROBSDirStr);

             }

         }
        m_updateTimeHOBS = updateTimeHOBS;
        m_updateTimeOOBS = updateTimeOOBS;
        m_updateTimeROBS = updateTimeROBS;

        setNewFileNewInXml(HOBSFILE,QString::number(m_updateTimeHOBS));
        setNewFileNewInXml(OOBSFILE,QString::number(m_updateTimeOOBS));
        setNewFileNewInXml(ROBSFILE,QString::number(m_updateTimeROBS));
    }
}

void StatusFilePlugin::traverseLogFile()
{
    qint64 updateTime = 0UL;


    QDir dir("/mnt/data/wprsoc/ftp/radartemp/input");
    if(dir.exists())
    {
        dir.setSorting(QDir::Name | QDir::Type);
        dir.setFilter(QDir::Files | QDir::Readable | QDir::NoDotAndDotDot);
        dir.setNameFilters(QStringList() << "*SYS.LOG" << "*SYS.log");


        QSet<QString> FileNames;

        auto FileNameList = dir.entryList();  //遍历第一级目录
        foreach (auto fileName, FileNameList)
        {
            QString fullPath = "/mnt/data/wprsoc/ftp/radartemp/input";
            fullPath += "/";
            fullPath += fileName;

            QFileInfo fileInfo(fullPath);
            updateTime = fileInfo.lastModified().toSecsSinceEpoch();
            if(updateTime > m_updateTimeLOG)
            {
                FileNames.insert(fullPath);
            }
        }

        for(auto item = FileNames.cbegin();item != FileNames.cend();item++)
        {
            writeFileInfoToDatabase(LOGFILE,*item);
            parseLogFile(*item);

        }

        m_updateTimeLOG = updateTime;
        setNewFileNewInXml(LOGFILE,QString::number(m_updateTimeLOG));
    }
}

void StatusFilePlugin::traverseHOBSFile(qint64 &updateTime, const QString &DirStr)
{
    QDir subTwoDir(DirStr);

    subTwoDir.setSorting(QDir::Name | QDir::Type);
    subTwoDir.setFilter(QDir::Files | QDir::Readable | QDir::NoDotAndDotDot);
    subTwoDir.setNameFilters(QStringList() << "*HOBS.TXT" << "*HOBS.txt");

    auto FileNameList = subTwoDir.entryList();
    foreach (auto fileName, FileNameList)
    {
        QString fullFilePathStr = DirStr;
        fullFilePathStr += fileName;

        QFileInfo fileInfo(fullFilePathStr);
        updateTime = fileInfo.lastModified().toSecsSinceEpoch();
        if(updateTime > m_updateTimeHOBS)
        {
            writeFileInfoToDatabase(HOBSFILE,fullFilePathStr);
        }

    }
}

void StatusFilePlugin::traverseOOBSFile(qint64 &updateTime, const QString &DirStr)
{
    QDir subTwoDir(DirStr);

    subTwoDir.setSorting(QDir::Name | QDir::Type);
    subTwoDir.setFilter(QDir::Files | QDir::Readable | QDir::NoDotAndDotDot);
    subTwoDir.setNameFilters(QStringList() << "*OOBS.TXT" << "*OOBS.txt");

    auto FileNameList = subTwoDir.entryList();
    foreach (auto fileName, FileNameList)
    {
        QString fullFilePathStr = DirStr;
        fullFilePathStr += fileName;

        QFileInfo fileInfo(fullFilePathStr);
        updateTime = fileInfo.lastModified().toSecsSinceEpoch();
        if(updateTime > m_updateTimeOOBS)
        {
            writeFileInfoToDatabase(OOBSFILE,fullFilePathStr);
        }

    }
}

void StatusFilePlugin::traverseROBSFile(qint64 &updateTime, const QString &DirStr)
{
    QDir subTwoDir(DirStr);

    subTwoDir.setSorting(QDir::Name | QDir::Type);
    subTwoDir.setFilter(QDir::Files | QDir::Readable | QDir::NoDotAndDotDot);
    subTwoDir.setNameFilters(QStringList() << "*ROBS.TXT" << "*ROBS.txt");

    auto FileNameList = subTwoDir.entryList();
    foreach (auto fileName, FileNameList)
    {
        QString fullFilePathStr = DirStr;
        fullFilePathStr += fileName;

        QFileInfo fileInfo(fullFilePathStr);
        updateTime = fileInfo.lastModified().toSecsSinceEpoch();
        if(updateTime > m_updateTimeROBS)
        {
            writeFileInfoToDatabase(ROBSFILE,fullFilePathStr);
        }

    }
}

void StatusFilePlugin::readInitFromXML()
{
    QFile file("config.xml");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }

    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!m_DOC.setContent(&file, false, &errorStr, &errorLine,&errorColumn))
    {

        file.close();
        return;
    }

    file.close();

    QDomElement root = m_DOC.documentElement();
    for(QDomNode n = root.firstChild(); !n.isNull(); n = n.nextSibling())
    {

        if(n.toElement().tagName().contains("updateTime"))
        {
            m_updateTimeFFT = n.toElement().attribute("FFT").toLongLong();
            m_updateTimeRad = n.toElement().attribute("RAD").toLongLong();
            m_updateTimeROBS = n.toElement().attribute("ROBS").toLongLong();
            m_updateTimeHOBS = n.toElement().attribute("HOBS").toLongLong();
            m_updateTimeOOBS = n.toElement().attribute("OOBS").toLongLong();
            m_updateTimeStatus = n.toElement().attribute("STATUS").toLongLong();
            m_updateTimeCal = n.toElement().attribute("CAL").toLongLong();
            m_updateTimeLOG = n.toElement().attribute("LOG").toLongLong();

        }
        else if(n.toElement().tagName().contains("LogFile"))
        {
            m_previousLogFileName = n.toElement().attribute("fileName");
            m_previousLogLine = n.toElement().attribute("line").toUInt();
        }
        else{}
    }
}

void StatusFilePlugin::setNewFileNewInXml(quint8 FileType, const QString &updateTime)
{
    QFile file("config.xml");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {

        return;
    }

    QDomElement root = m_DOC.documentElement();
    for(QDomNode n = root.firstChild(); !n.isNull(); n = n.nextSibling())
    {
        if(n.toElement().tagName().contains("updateTime"))
        {
            switch (FileType)
            {
            case FFTFILE:
                n.toElement().setAttribute("FFT",updateTime);
                break;
            case RADFILE:
                n.toElement().setAttribute("RAD",updateTime);
                break;
            case ROBSFILE:
                n.toElement().setAttribute("ROBS",updateTime);
                break;
            case HOBSFILE:
                n.toElement().setAttribute("HOBS",updateTime);
                break;
            case OOBSFILE:
                n.toElement().setAttribute("OOBS",updateTime);
                break;
            case STATUSFILE:
                n.toElement().setAttribute("STATUS",updateTime);
                break;
            case CALFILE:
                n.toElement().setAttribute("CAL",updateTime);
                break;
            case LOGFILE:
                n.toElement().setAttribute("LOG",updateTime);
                break;
            default:
                break;
            }

        }
    }

    QTextStream  out(&file);
    m_DOC.save(out,4);
    file.close();
}

void StatusFilePlugin::setLogFileNameInXml(const QString &fileName)
{
    QFile file("config.xml");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {

        return;
    }

    QDomElement root = m_DOC.documentElement();
    for(QDomNode n = root.firstChild(); !n.isNull(); n = n.nextSibling())
    {
        if(n.toElement().tagName().contains("LogFile"))
        {

            n.toElement().setAttribute("fileName",fileName);

        }
    }

    QTextStream  out(&file);
    m_DOC.save(out,4);
    file.close();
}

void StatusFilePlugin::setLogFileLineInXml(quint32 lineNum)
{
    QFile file("config.xml");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {

        return;
    }

    QDomElement root = m_DOC.documentElement();
    for(QDomNode n = root.firstChild(); !n.isNull(); n = n.nextSibling())
    {
        if(n.toElement().tagName().contains("LogFile"))
        {

            n.toElement().setAttribute("line",lineNum);

        }
    }

    QTextStream  out(&file);
    m_DOC.save(out,4);
    file.close();
}

bool StatusFilePlugin::getRadarType()
{
    if(m_MysqlInstance)
    {
        QString sqlSentence("SELECT param_value FROM sys_config WHERE param_key='RADAR_TYPE'");

        auto sqlQuery = m_MysqlInstance->RunSQLQuery(sqlSentence);
        if(sqlQuery.size() > 0)
        {
            while(sqlQuery.next())
            {
                m_RadarType = sqlQuery.value("param_value").toString();
            }
        }

    }
    return true;
}

qint64 StatusFilePlugin::getObservationTime(const RadarDef::RadarStatusCF6 statusData)
{
    QDateTime observationTime;
    observationTime.setDate(QDate(statusData.Year,statusData.Month,statusData.Day));
    observationTime.setTime(QTime(statusData.Hour,statusData.Minute,statusData.Second));

    return observationTime.toSecsSinceEpoch();
}

qint64 StatusFilePlugin::getObservationTime(const RadarDef::RadarStatusCF3 statusData)
{
    QDateTime observationTime;
    observationTime.setDate(QDate(statusData.Year,statusData.Month,statusData.Day));
    observationTime.setTime(QTime(statusData.Hour,statusData.Minute,statusData.Second));

    return observationTime.toSecsSinceEpoch();
}

qint64 StatusFilePlugin::getObservationTime(const RadarDef::RadarFFTData FFtData)
{
    QDateTime observationTime;
    observationTime.setDate(QDate(FFtData.SYear,FFtData.EMonth,FFtData.EDay));
    observationTime.setTime(QTime(FFtData.EHour,FFtData.EMinute,FFtData.ESecond));

    return observationTime.toSecsSinceEpoch();
}

qint64 StatusFilePlugin::getObservationTime(const QString &TimeStr)
{
    auto year = TimeStr.left(4).toUInt();
    auto month = TimeStr.mid(4,2).toUInt();
    auto day = TimeStr.mid(6,2).toUInt();
    auto hour = TimeStr.mid(8,2).toUInt();
    auto minute = TimeStr.mid(10,2).toUInt();
    auto second = TimeStr.right(2).toUInt();

    QDateTime observationTime;
    observationTime.setDate(QDate(year,month,day));
    observationTime.setTime(QTime(hour,minute,second));

    return observationTime.toSecsSinceEpoch();
}

#define generateFaultInfoForSubsystem(SYSTEMINDEX,DEVICENO)  \
    if(statusData.subsystem##SYSTEMINDEX##_StatusFlag##DEVICENO != 1)  \
    {  \
        m_FaultInSubsystem##SYSTEMINDEX += QString("{%1:%2},").arg(DEVICENO+1).arg(statusData.subsystem##SYSTEMINDEX##_StatusFlag##DEVICENO);  \
    }

void StatusFilePlugin::getFaultInSubSystem0(const RadarDef::RadarStatusCF6 statusData)
{
    m_FaultInSubsystem0 += "[";

    generateFaultInfoForSubsystem(0,0)
    generateFaultInfoForSubsystem(0,1)
    generateFaultInfoForSubsystem(0,2)
    generateFaultInfoForSubsystem(0,3)
    generateFaultInfoForSubsystem(0,4)
    generateFaultInfoForSubsystem(0,5)
    generateFaultInfoForSubsystem(0,6)
    generateFaultInfoForSubsystem(0,7)
    generateFaultInfoForSubsystem(0,8)
    generateFaultInfoForSubsystem(0,9)
    generateFaultInfoForSubsystem(0,10)
    generateFaultInfoForSubsystem(0,11)
    generateFaultInfoForSubsystem(0,12)
    generateFaultInfoForSubsystem(0,13)
    generateFaultInfoForSubsystem(0,14)
    generateFaultInfoForSubsystem(0,15)
    generateFaultInfoForSubsystem(0,16)
    generateFaultInfoForSubsystem(0,17)
    generateFaultInfoForSubsystem(0,18)
    generateFaultInfoForSubsystem(0,19)
    generateFaultInfoForSubsystem(0,20)
    generateFaultInfoForSubsystem(0,21)
    generateFaultInfoForSubsystem(0,22)
    generateFaultInfoForSubsystem(0,23)
    generateFaultInfoForSubsystem(0,24)
    generateFaultInfoForSubsystem(0,26)
    generateFaultInfoForSubsystem(0,26)
    generateFaultInfoForSubsystem(0,27)
    generateFaultInfoForSubsystem(0,28)
    generateFaultInfoForSubsystem(0,29)
    generateFaultInfoForSubsystem(0,30)
    generateFaultInfoForSubsystem(0,31)
    generateFaultInfoForSubsystem(0,32)
    generateFaultInfoForSubsystem(0,33)
    generateFaultInfoForSubsystem(0,34)
    generateFaultInfoForSubsystem(0,35)
    generateFaultInfoForSubsystem(0,36)
    generateFaultInfoForSubsystem(0,37)
    generateFaultInfoForSubsystem(0,38)
    generateFaultInfoForSubsystem(0,39)
    generateFaultInfoForSubsystem(0,40)
    generateFaultInfoForSubsystem(0,41)
    generateFaultInfoForSubsystem(0,42)
    generateFaultInfoForSubsystem(0,43)
    generateFaultInfoForSubsystem(0,44)
    generateFaultInfoForSubsystem(0,45)
    generateFaultInfoForSubsystem(0,46)
    generateFaultInfoForSubsystem(0,47)

    if(m_FaultInSubsystem0.length() > 1)
    {
        m_FaultInSubsystem0.remove(m_FaultInSubsystem0.length()-1,1);
        m_FaultInSubsystem0 += "]";
    }
    else
    {
        m_FaultInSubsystem0.clear();
    }


}

void StatusFilePlugin::getFaultInSubSystem1(const RadarDef::RadarStatusCF6 statusData)
{
    m_FaultInSubsystem1 += "[";

    generateFaultInfoForSubsystem(1,0)
    generateFaultInfoForSubsystem(1,1)
    generateFaultInfoForSubsystem(1,2)
    generateFaultInfoForSubsystem(1,3)
    generateFaultInfoForSubsystem(1,4)
    generateFaultInfoForSubsystem(1,5)
    generateFaultInfoForSubsystem(1,6)
    generateFaultInfoForSubsystem(1,7)
    generateFaultInfoForSubsystem(1,8)
    generateFaultInfoForSubsystem(1,9)
    generateFaultInfoForSubsystem(1,10)
    generateFaultInfoForSubsystem(1,11)
    generateFaultInfoForSubsystem(1,12)
    generateFaultInfoForSubsystem(1,13)
    generateFaultInfoForSubsystem(1,14)
    generateFaultInfoForSubsystem(1,15)
    generateFaultInfoForSubsystem(1,16)
    generateFaultInfoForSubsystem(1,17)
    generateFaultInfoForSubsystem(1,18)
    generateFaultInfoForSubsystem(1,19)
    generateFaultInfoForSubsystem(1,20)
    generateFaultInfoForSubsystem(1,21)
    generateFaultInfoForSubsystem(1,22)
    generateFaultInfoForSubsystem(1,23)
    generateFaultInfoForSubsystem(1,24)
    generateFaultInfoForSubsystem(1,26)
    generateFaultInfoForSubsystem(1,26)
    generateFaultInfoForSubsystem(1,27)
    generateFaultInfoForSubsystem(1,28)
    generateFaultInfoForSubsystem(1,29)
    generateFaultInfoForSubsystem(1,30)
    generateFaultInfoForSubsystem(1,31)
    generateFaultInfoForSubsystem(1,32)
    generateFaultInfoForSubsystem(1,33)
    generateFaultInfoForSubsystem(1,34)
    generateFaultInfoForSubsystem(1,35)
    generateFaultInfoForSubsystem(1,36)
    generateFaultInfoForSubsystem(1,37)
    generateFaultInfoForSubsystem(1,38)
    generateFaultInfoForSubsystem(1,39)
    generateFaultInfoForSubsystem(1,40)
    generateFaultInfoForSubsystem(1,41)
    generateFaultInfoForSubsystem(1,42)
    generateFaultInfoForSubsystem(1,43)
    generateFaultInfoForSubsystem(1,44)
    generateFaultInfoForSubsystem(1,45)
    generateFaultInfoForSubsystem(1,46)
    generateFaultInfoForSubsystem(1,47)
    generateFaultInfoForSubsystem(1,48)
    generateFaultInfoForSubsystem(1,49)
    generateFaultInfoForSubsystem(1,50)
    generateFaultInfoForSubsystem(1,51)
    generateFaultInfoForSubsystem(1,52)
    generateFaultInfoForSubsystem(1,53)
    generateFaultInfoForSubsystem(1,54)
    generateFaultInfoForSubsystem(1,55)
    generateFaultInfoForSubsystem(1,56)
    generateFaultInfoForSubsystem(1,57)
    generateFaultInfoForSubsystem(1,58)
    generateFaultInfoForSubsystem(1,59)
    generateFaultInfoForSubsystem(1,60)
    generateFaultInfoForSubsystem(1,61)
    generateFaultInfoForSubsystem(1,62)
    generateFaultInfoForSubsystem(1,63)
    generateFaultInfoForSubsystem(1,64)
    generateFaultInfoForSubsystem(1,65)
    generateFaultInfoForSubsystem(1,66)
    generateFaultInfoForSubsystem(1,67)
    generateFaultInfoForSubsystem(1,68)
    generateFaultInfoForSubsystem(1,69)
    generateFaultInfoForSubsystem(1,70)
    generateFaultInfoForSubsystem(1,71)
    generateFaultInfoForSubsystem(1,72)
    generateFaultInfoForSubsystem(1,73)
    generateFaultInfoForSubsystem(1,74)
    generateFaultInfoForSubsystem(1,75)
    generateFaultInfoForSubsystem(1,76)
    generateFaultInfoForSubsystem(1,77)
    generateFaultInfoForSubsystem(1,78)
    generateFaultInfoForSubsystem(1,79)
    generateFaultInfoForSubsystem(1,80)
    generateFaultInfoForSubsystem(1,81)

    if(m_FaultInSubsystem1.length() > 1)
    {
        m_FaultInSubsystem1.remove(m_FaultInSubsystem1.length()-1,1);
        m_FaultInSubsystem1 += "]";
    }
    else
    {
        m_FaultInSubsystem1.clear();
    }

}

void StatusFilePlugin::getFaultInSubSystem2(const RadarDef::RadarStatusCF6 statusData)
{
    m_FaultInSubsystem2 += "[";

    generateFaultInfoForSubsystem(2,0)
    generateFaultInfoForSubsystem(2,1)
    generateFaultInfoForSubsystem(2,2)
    generateFaultInfoForSubsystem(2,3)
    generateFaultInfoForSubsystem(2,4)
    generateFaultInfoForSubsystem(2,5)

    if(m_FaultInSubsystem2.length() > 1)
    {
        m_FaultInSubsystem2.remove(m_FaultInSubsystem2.length()-1,1);
        m_FaultInSubsystem2 += "]";
    }
    else
    {
        m_FaultInSubsystem2.clear();
    }

}

void StatusFilePlugin::getFaultInSubSystem3(const RadarDef::RadarStatusCF6 statusData)
{
    m_FaultInSubsystem3 += "[";

    generateFaultInfoForSubsystem(3,0)
    generateFaultInfoForSubsystem(3,1)

    if(m_FaultInSubsystem3.length() > 1)
    {
        m_FaultInSubsystem3.remove(m_FaultInSubsystem3.length()-1,1);
        m_FaultInSubsystem3 += "]";
    }
    else
    {
        m_FaultInSubsystem3.clear();
    }

}

void StatusFilePlugin::getFaultInSubSystem4(const RadarDef::RadarStatusCF6 statusData)
{
    m_FaultInSubsystem4 += "[";

    generateFaultInfoForSubsystem(4,0)

    if(m_FaultInSubsystem4.length() > 1)
    {
        m_FaultInSubsystem4.remove(m_FaultInSubsystem4.length()-1,1);
        m_FaultInSubsystem4 += "]";
    }
    else
    {
        m_FaultInSubsystem4.clear();
    }

}

void StatusFilePlugin::getFaultInSubSystem5(const RadarDef::RadarStatusCF6 statusData)
{
    m_FaultInSubsystem5 += "[";

    generateFaultInfoForSubsystem(5,0)
    generateFaultInfoForSubsystem(5,1)

    if(m_FaultInSubsystem5.length() > 1)
    {
        m_FaultInSubsystem5.remove(m_FaultInSubsystem5.length()-1,1);
        m_FaultInSubsystem5 += "]";
    }
    else
    {
        m_FaultInSubsystem5.clear();
    }

}

void StatusFilePlugin::getFaultInSubSystem6(const RadarDef::RadarStatusCF6 statusData)
{
    m_FaultInSubsystem6 += "[";

    generateFaultInfoForSubsystem(6,0)

    if(m_FaultInSubsystem6.length() > 1)
    {
        m_FaultInSubsystem6.remove(m_FaultInSubsystem6.length()-1,1);
        m_FaultInSubsystem6 += "]";
    }
    else
    {
        m_FaultInSubsystem6.clear();
    }

}

void StatusFilePlugin::getFaultInSubSystem7(const RadarDef::RadarStatusCF6 statusData)
{
    m_FaultInSubsystem7 += "[";

    generateFaultInfoForSubsystem(7,0)

    if(m_FaultInSubsystem7.length() > 1)
    {
        m_FaultInSubsystem7.remove(m_FaultInSubsystem7.length()-1,1);
        m_FaultInSubsystem7 += "]";
    }
    else
    {
        m_FaultInSubsystem7.clear();
    }

}

void StatusFilePlugin::getFaultInSubSystem(const RadarDef::RadarStatusCF3 statusData)
{
    m_FaultInSubsystem0.clear();
    m_FaultInSubsystem1.clear();
    m_FaultInSubsystem2.clear();
    m_FaultInSubsystem3.clear();
    m_FaultInSubsystem4.clear();
    m_FaultInSubsystem5.clear();
    m_FaultInSubsystem6.clear();
    m_FaultInSubsystem7.clear();


    getFaultInSubSystem0(statusData);
    getFaultInSubSystem1(statusData);
    getFaultInSubSystem2(statusData);
    getFaultInSubSystem3(statusData);
    getFaultInSubSystem4(statusData);
    getFaultInSubSystem5(statusData);
    getFaultInSubSystem6(statusData);
    getFaultInSubSystem7(statusData);
}

bool StatusFilePlugin::writeRadarStatusToDataBase(const RadarDef::RadarStatusCF3 statusData)
{
  if(m_MysqlInstance)
   {
        QTextCodec* codec = QTextCodec::codecForName("GB18030");
        QString country = codec->toUnicode(QByteArray(statusData.Country));
        QString province = codec->toUnicode(QByteArray(statusData.Province));
        QString stationNumber = codec->toUnicode(QByteArray(statusData.StationNumber));
        QString station = codec->toUnicode(QByteArray(statusData.Station));
        QString radarType = codec->toUnicode(QByteArray(statusData.RadarType));
        QString longitude = codec->toUnicode(QByteArray(statusData.Longitude));
        QString latitude = codec->toUnicode(QByteArray(statusData.Latitude));
        QString altitude = codec->toUnicode(QByteArray(statusData.Altitude));

        auto observationTime = getObservationTime(statusData);

        auto sqlSentence = QString("INSERT INTO t_fdata_sta3 (country,\
                                            province,\
                                            station,\
                                            station_number,\
                                            radar_type,\
                                            longitude,\
                                            latitude,\
                                            altitude,\
                                            update_time,\
                                            observe_time,\
                                            radar_status,\
                                            sub_num,\
                                            sub_sys0,\
                                            sub_sys1,\
                                            sub_sys2,\
                                            sub_sys3,\
                                            sub_sys4,\
                                            sub_sys5,\
                                            sub_sys6,\
                                            sub_sys7,\
                                            sub_sys8,\
                                            sys_status0_detail,\
                                            sys_status1_detail,\
                                            sys_status2_detail,\
                                            sys_status3_detail,\
                                            sys_status4_detail,\
                                            sys_status5_detail,\
                                            sys_status6_detail,\
                                            sys_status7_detail,\
                                            obsere_data1,\
                                            obsere_data2) VALUES('%1','%2','%3','%4','%5','%6','%7',%8,%9,%10,%11,%12,%13,%14,%15,%16,%17,%18,%19,%20,%21,'%22','%23','%24','%25','%26','%27','%28','%29',%30,%31)")
                        .arg(country)\
                        .arg(province)\
                        .arg(station)\
                        .arg(stationNumber)\
                        .arg(radarType)\
                        .arg(longitude)\
                        .arg(latitude)\
                        .arg(altitude)\
                        .arg(QDateTime::currentDateTime().toSecsSinceEpoch())\
                        .arg(observationTime)\
                        .arg(statusData.RadarStatus)\
                        .arg(statusData.SubsysNum)\
                        .arg(statusData.Subsys0)\
                        .arg(statusData.Subsys1)\
                        .arg(statusData.Subsys2)\
                        .arg(statusData.Subsys3)\
                        .arg(statusData.Subsys4)\
                        .arg(statusData.Subsys5)\
                        .arg(statusData.Subsys6)\
                        .arg(statusData.Subsys7)\
                        .arg(statusData.Subsys8)\
                        .arg(m_FaultInSubsystem0)\
                        .arg(m_FaultInSubsystem1)\
                        .arg(m_FaultInSubsystem2)\
                        .arg(m_FaultInSubsystem3)\
                        .arg(m_FaultInSubsystem4)\
                        .arg(m_FaultInSubsystem5)\
                        .arg(m_FaultInSubsystem6)\
                        .arg(m_FaultInSubsystem7)\
                        .arg(statusData.MOBS_Obsdata0)\
                        .arg(statusData.MOBS_Obsdata1);

        return m_MysqlInstance->RunSQLNoQuery(sqlSentence);
    }

  return false;
}

bool StatusFilePlugin::writeKeyStatusParamCF6ToDataBase(const RadarDef::RadarStatusCF6 statusData)
{
    if(m_MysqlInstance)
    {
        auto observationTime = getObservationTime(statusData);

        auto sqlSentence = QString("INSERT INTO t_keyparam_state(update_time,status,type,swr,reflective_power,out_power) VALUES(%1,%2,%3,%4,%5,%6)")
                            .arg(observationTime)
                            .arg(1)
                            .arg(3)
                            .arg(m_SWRCF6)
                            .arg(m_AveReflectPowerCF6)
                            .arg(m_AveOutputPowerCF6);

        return m_MysqlInstance->RunSQLNoQuery(sqlSentence);

    }

    return false;
}

void StatusFilePlugin::calcAveReflectPowerCF6(const RadarDef::RadarStatusCF6 statusData)
{
    m_AveReflectPowerCF6 = 0;
    m_AveReflectPowerCF6 += statusData.MOBS_Obsdata49;
    m_AveReflectPowerCF6 += statusData.MOBS_Obsdata50;
    m_AveReflectPowerCF6 += statusData.MOBS_Obsdata51;
    m_AveReflectPowerCF6 += statusData.MOBS_Obsdata52;
    m_AveReflectPowerCF6 += statusData.MOBS_Obsdata53;
    m_AveReflectPowerCF6 += statusData.MOBS_Obsdata54;
    m_AveReflectPowerCF6 += statusData.MOBS_Obsdata55;
    m_AveReflectPowerCF6 += statusData.MOBS_Obsdata56;
    m_AveReflectPowerCF6 += statusData.MOBS_Obsdata57;
    m_AveReflectPowerCF6 += statusData.MOBS_Obsdata58;
    m_AveReflectPowerCF6 += statusData.MOBS_Obsdata59;
    m_AveReflectPowerCF6 += statusData.MOBS_Obsdata60;
    m_AveReflectPowerCF6 += statusData.MOBS_Obsdata61;
    m_AveReflectPowerCF6 += statusData.MOBS_Obsdata62;
    m_AveReflectPowerCF6 += statusData.MOBS_Obsdata63;
    m_AveReflectPowerCF6 += statusData.MOBS_Obsdata64;
    m_AveReflectPowerCF6 += statusData.MOBS_Obsdata65;
    m_AveReflectPowerCF6 += statusData.MOBS_Obsdata66;
    m_AveReflectPowerCF6 += statusData.MOBS_Obsdata67;
    m_AveReflectPowerCF6 += statusData.MOBS_Obsdata68;
    m_AveReflectPowerCF6 += statusData.MOBS_Obsdata69;
    m_AveReflectPowerCF6 += statusData.MOBS_Obsdata70;
    m_AveReflectPowerCF6 += statusData.MOBS_Obsdata71;
    m_AveReflectPowerCF6 += statusData.MOBS_Obsdata72;

    m_AveReflectPowerCF6 /= 24;


}

void StatusFilePlugin::calcAveOutputPowerCF6(const RadarDef::RadarStatusCF6 statusData)
{
    m_AveOutputPowerCF6 = 0;
    m_AveOutputPowerCF6 += statusData.MOBS_Obsdata25;
    m_AveOutputPowerCF6 += statusData.MOBS_Obsdata26;
    m_AveOutputPowerCF6 += statusData.MOBS_Obsdata27;
    m_AveOutputPowerCF6 += statusData.MOBS_Obsdata28;
    m_AveOutputPowerCF6 += statusData.MOBS_Obsdata29;
    m_AveOutputPowerCF6 += statusData.MOBS_Obsdata30;
    m_AveOutputPowerCF6 += statusData.MOBS_Obsdata31;
    m_AveOutputPowerCF6 += statusData.MOBS_Obsdata32;
    m_AveOutputPowerCF6 += statusData.MOBS_Obsdata33;
    m_AveOutputPowerCF6 += statusData.MOBS_Obsdata34;
    m_AveOutputPowerCF6 += statusData.MOBS_Obsdata35;
    m_AveOutputPowerCF6 += statusData.MOBS_Obsdata36;
    m_AveOutputPowerCF6 += statusData.MOBS_Obsdata37;
    m_AveOutputPowerCF6 += statusData.MOBS_Obsdata38;
    m_AveOutputPowerCF6 += statusData.MOBS_Obsdata39;
    m_AveOutputPowerCF6 += statusData.MOBS_Obsdata40;
    m_AveOutputPowerCF6 += statusData.MOBS_Obsdata41;
    m_AveOutputPowerCF6 += statusData.MOBS_Obsdata42;
    m_AveOutputPowerCF6 += statusData.MOBS_Obsdata43;
    m_AveOutputPowerCF6 += statusData.MOBS_Obsdata44;
    m_AveOutputPowerCF6 += statusData.MOBS_Obsdata45;
    m_AveOutputPowerCF6 += statusData.MOBS_Obsdata46;
    m_AveOutputPowerCF6 += statusData.MOBS_Obsdata47;
    m_AveOutputPowerCF6 += statusData.MOBS_Obsdata48;

    m_AveOutputPowerCF6 /= 24;
}

void StatusFilePlugin::calcSWRCF6()
{
    m_SWRCF6 = (1 + m_AveReflectPowerCF6 / m_AveOutputPowerCF6) / (1 - m_AveReflectPowerCF6 / m_AveOutputPowerCF6);
}

void StatusFilePlugin::parseCalibrationFile(const QString &fileName)
{
    QFile CalFile(fileName);
    if(!CalFile.open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }
    else
    {
        QTextStream stream(&CalFile);
        stream.setIntegerBase(10);

        QString WNDCALStr;
        QString siteInfo;
        QString observationTimeStr;
        QString frequency;
        int BranchNum;

        stream >> WNDCALStr >> siteInfo >> observationTimeStr >> frequency >> BranchNum;  //解析标定文件中的站址信息
        m_CalSiteInfo = siteInfo;
        m_CalFileObservationTime = getObservationTime(observationTimeStr);

        stream.readLine();
        stream.readLine();
        stream.readLine();


        QString dopplerVelocity25Hz_1;
        QString dopplerVelocity25Hz_2;
        QString dopplerVelocity25Hz_3;
        stream >> dopplerVelocity25Hz_1 >> dopplerVelocity25Hz_2 >> dopplerVelocity25Hz_3;  //解析多普勒速度参数
        m_25HzDopplerVelocity = QString("%1,%2,%3").arg(dopplerVelocity25Hz_1).arg(dopplerVelocity25Hz_2).arg(dopplerVelocity25Hz_3);

        QString dopplerVelocityNE25Hz_1;
        QString dopplerVelocityNE25Hz_2;
        QString dopplerVelocityNE25Hz_3;
        stream >> dopplerVelocityNE25Hz_1 >> dopplerVelocityNE25Hz_2 >> dopplerVelocityNE25Hz_3;
        m_NE25HzDopplerVelocity = QString("%1,%2,%3").arg(dopplerVelocityNE25Hz_1).arg(dopplerVelocityNE25Hz_2).arg(dopplerVelocityNE25Hz_3);

        QString dopplerVelocity75Hz_1;
        QString dopplerVelocity75Hz_2;
        QString dopplerVelocity75Hz_3;
        stream >> dopplerVelocity75Hz_1 >> dopplerVelocity75Hz_2 >> dopplerVelocity75Hz_3;
        m_75HzDopplerVelocity = QString("%1,%2,%3").arg(dopplerVelocity75Hz_1).arg(dopplerVelocity75Hz_2).arg(dopplerVelocity75Hz_3);

        QString dopplerVelocityNE75Hz_1;
        QString dopplerVelocityNE75Hz_2;
        QString dopplerVelocityNE75Hz_3;
        stream >> dopplerVelocityNE75Hz_1 >> dopplerVelocityNE75Hz_2 >> dopplerVelocityNE75Hz_3;
        m_NE75HzDopplerVelocity = QString("%1,%2,%3").arg(dopplerVelocityNE75Hz_1).arg(dopplerVelocityNE75Hz_2).arg(dopplerVelocityNE75Hz_3);

        stream >> m_NoiseFactor >> m_ReceiverSensitivity >> m_DynamicRange >> m_EmitterPower >> m_SystemCoherence;  //解析发射功率等参数

        m_receiveAmplitude = "[";
        for(auto i = 1; i <= BranchNum; i++)
        {

            QString tempStr;
            stream >> tempStr;
            if(tempStr.contains("//"))
            {
               tempStr = "0";
            }

            m_receiveAmplitude += "{";
            m_receiveAmplitude += QString::number(i);  //解析接收幅度参数，组成json
            m_receiveAmplitude += ":";
            m_receiveAmplitude += tempStr;
            m_receiveAmplitude += "}";
            if(i < BranchNum)
            {
                m_receiveAmplitude += ",";
            }
            else
            {
                m_receiveAmplitude += "]";
            }

        }

        m_receivePhase = "[";
        for(auto i = 1; i <= BranchNum; i++)
        {

            QString tempStr;
            stream >> tempStr;
            if(tempStr.contains("//"))
            {
               tempStr = "0";
            }

            m_receivePhase += "{";
            m_receivePhase += QString::number(i);   //解析接收相位参数，组成json
            m_receivePhase += ":";
            m_receivePhase += tempStr;
            m_receivePhase += "}";
            if(i < BranchNum)
            {
                m_receivePhase += ",";
            }
            else
            {
                m_receivePhase += "]";
            }

        }

        m_emitterAmplitude = "[";
        for(auto i = 1; i <= BranchNum; i++)
        {

            QString tempStr;
            stream >> tempStr;
            if(tempStr.contains("//"))
            {
               tempStr = "0";
            }

            m_emitterAmplitude += "{";
            m_emitterAmplitude += QString::number(i);  //解析发射幅度参数，组成json
            m_emitterAmplitude += ":";
            m_emitterAmplitude += tempStr;
            m_emitterAmplitude += "}";
            if(i < BranchNum)
            {
                m_emitterAmplitude += ",";
            }
            else
            {
                m_emitterAmplitude += "]";
            }

        }

        m_emitterPhase = "[";
        for(auto i = 1; i <= BranchNum; i++)
        {

            QString tempStr;
            stream >> tempStr;
            if(tempStr.contains("//"))
            {
               tempStr = "0";
            }

            m_emitterPhase += "{";
            m_emitterPhase += QString::number(i);  //解析接收相位参数，组成json
            m_emitterPhase += ":";
            m_emitterPhase += tempStr;
            m_emitterPhase += "}";
            if(i < BranchNum)
            {
                m_emitterPhase += ",";
            }
            else
            {
                m_emitterPhase += "]";
            }

        }

    }
}

void StatusFilePlugin::parseLogFile(const QString &fullFilePath)
{
    auto index = fullFilePath.lastIndexOf("/");
    auto fileName = fullFilePath.right(fullFilePath.length() - index - 1);

    if(m_previousLogFileName != fileName)
    {
        m_previousLogFileName = fileName;
        m_previousLogLine = 0;

       setLogFileNameInXml(m_previousLogFileName);
       setLogFileLineInXml(m_previousLogLine);
    }

    QFile::copy(fullFilePath,fileName);  //将文件复制一份进行读取

    quint32 lineNum = 0;
    qint64 updateTime = 0;
    QString updateTimeStr;
    QString LogStr;


    QFile file(fileName);
    if(file.open(QFile::ReadOnly | QFile::Text))
    {
        while(!file.atEnd())
        {
            auto content = file.readLine();
            lineNum++;

            if(lineNum > m_previousLogLine)
            {
                QTextStream lineStream(content);
                lineStream.setCodec(QTextCodec::codecForName("GB18030"));

                QString contentStr(content);
                if(contentStr.trimmed().isEmpty())
                {
                    continue;
                }
                else if(contentStr.contains("+"))
                {
                    QString SignStr;
                    QString DateStr;
                    QString TimeStr;

                    lineStream >> SignStr >> DateStr >> TimeStr >> LogStr;  //解析日志内容

                    updateTime = getUpdateTime(DateStr,TimeStr);
                    if(updateTime < 0)
                    {
                        continue;
                    }

                    updateTimeStr = DateStr;
                    updateTimeStr += " ";
                    updateTimeStr += TimeStr;

                }
                else if(contentStr.contains("#"))
                {
                    QString MixStr;
                    QString DateStr;
                    QString TimeStr;

                    lineStream >> MixStr >> TimeStr;  //解析日志内容

                    auto index  = MixStr.indexOf("：");
                    LogStr = MixStr.left(index);
                    LogStr.remove(0,1);

                    DateStr = MixStr.right(MixStr.length() - index - 1);

                    updateTime = getUpdateTime(DateStr,TimeStr);
                    if(updateTime < 0)
                    {
                        continue;
                    }

                    updateTimeStr = DateStr;
                    updateTimeStr += " ";
                    updateTimeStr += TimeStr;


                }
                else{}

                if(writeLogToDataBase(updateTime,updateTimeStr,LogStr))
                {
                    m_previousLogLine = lineNum;
                }


            }
        }
    }

    setLogFileLineInXml(m_previousLogLine);
    file.close();
    file.remove();


}

bool StatusFilePlugin::writekeyStaticParamToDataBase(const RadarDef::RadarFFTData FFTData)
{
    if(m_MysqlInstance)
    {
        QTextCodec* codec = QTextCodec::codecForName("GB18030");
        QString station = codec->toUnicode(QByteArray(FFTData.Station));

        auto observationTime = getObservationTime(FFTData);

        auto sqlSentence = QString("INSERT INTO t_keyparam_static(update_time, \
                                                                type, \
                                                                status, \
                                                                station, \
                                                                station_number, \
                                                                radar_type, \
                                                                longitude, \
                                                                latitude, \
                                                                altitude, \
                                                                north_point, \
                                                                sys_loss, \
                                                                peak_power, \
                                                                buildup, \
                                                                power_avg, \
                                                                fft) VALUES(%1,%2,%3,'%4','%5','%6','%7','%8','%9',%10,%11,%12,%13,%14,%15)")
                 .arg(observationTime)
                 .arg(1)
                 .arg(1)
                 .arg(station)
                 .arg(QLatin1String(FFTData.StationNumber))
                 .arg(QLatin1String(FFTData.RadarType))
                 .arg(QLatin1String(FFTData.Longitude))
                 .arg(QLatin1String(FFTData.Latitude))
                 .arg(QLatin1String(FFTData.Altitude))
                 .arg(FFTData.AzimuthE)
                 .arg(FFTData.AgcWast)
                 .arg(FFTData.TranPp)
                 .arg(FFTData.NNtr)
                 .arg(FFTData.SpAver)
                 .arg(FFTData.Fft);

         return m_MysqlInstance->RunSQLNoQuery(sqlSentence);

    }

    return false;
}

bool StatusFilePlugin::writeCalParamToDataBase()
{
    if(m_MysqlInstance)
    {
        auto sqlSentence = QString("INSERT INTO t_bp_radar_calibration(station, \
                                   update_time, \
                                   calibration_time, \
                                   type, \
                                   type_name, \
                                   sys_coherence, \
                                   launch_max_power, \
                                   in_rece_dnr, \
                                   noise_factor, \
                                   sys_sensitivity, \
                                   in_noise_factor, \
                                   rece_range, \
                                   rece_phase, \
                                   send_range, \
                                   send_phase, \
                                   radial_velocity_p25, \
                                   radial_velocity_s25, \
                                   radial_velocity_p75, \
                                   radial_velocity_s75) VALUES('%1',%2,%3,%4,'%5',%6,%7,%8,%9,%10,%11,'%12','%13','%14','%15','%16','%17','%18','%19')")
                                                               .arg(m_CalSiteInfo)
                                                               .arg(QDateTime::currentDateTime().toSecsSinceEpoch())
                                                               .arg(m_CalFileObservationTime)
                                                               .arg(1)
                                                               .arg(u8"月标定")
                                                               .arg(m_SystemCoherence)
                                                               .arg(m_EmitterPower)
                                                               .arg(m_DynamicRange)
                                                               .arg(m_NoiseFactor)
                                                               .arg(m_ReceiverSensitivity)
                                                               .arg(m_NoiseFactor)
                                                               .arg(m_receiveAmplitude)
                                                               .arg(m_receivePhase)
                                                               .arg(m_emitterAmplitude)
                                                               .arg(m_emitterPhase)
                                                               .arg(m_25HzDopplerVelocity)
                                                               .arg(m_NE25HzDopplerVelocity)
                                                               .arg(m_75HzDopplerVelocity)
                                                               .arg(m_NE75HzDopplerVelocity);

        return m_MysqlInstance->RunSQLNoQuery(sqlSentence);
    }

    return false;
}

bool StatusFilePlugin::writeFileInfoToDatabase(quint8 fileType,const QString &fullFilePath)  //将遍历到的文件信息写入数据库
{
   QFileInfo fileInfo(fullFilePath);
   auto fileSize = fileInfo.size() / 1024.0;

   qint64 birthTime = fileInfo.lastModified().toSecsSinceEpoch() + 8 * 3600;

   QString backupPath = "/mnt/data/wprsoc/radarfile/";
   backupPath.append(fileInfo.lastModified().toString("yyyyMM"));
   backupPath.append("/");
   backupPath.append(fileInfo.lastModified().toString("yyyyMMdd"));  //备份文件路径

   QString tableName;

   switch(fileType)
   {
   case FFTFILE:
       backupPath += "/WNDFFT/";
       tableName = "t_file_fft";
       break;
   case RADFILE:
       backupPath += "/WNDRAD/";
       tableName = "t_file_rad";
       break;
   case HOBSFILE:
       backupPath += "/WNDOBS/HOBS/";
       tableName = "t_file_hobs";
       break;
   case OOBSFILE:
       backupPath += "/WNDOBS/OOBS/";
       tableName = "t_file_oobs";
       break;
   case ROBSFILE:
       backupPath += "/WNDOBS/ROBS/";
       tableName = "t_file_robs";
       break;
   case CALFILE:
       backupPath += "/WNDCBR/";
       tableName = "t_file_calibration";
       break;
   case STATUSFILE:
       backupPath += "/MONITOR/";
       tableName = "t_file_sta";
       break;
   case LOGFILE:
       backupPath += "/WNDLOG/";
       tableName = "t_file_log";
       break;
   default:
       break;
   }

   auto index = fullFilePath.lastIndexOf("/");
   auto fileName = fullFilePath.right(fullFilePath.length() - index - 1);

   QDir dir;

   if(!dir.exists(backupPath))
   {
        dir.mkpath(backupPath);
   }

   QString newFileName = backupPath;
   newFileName += fileName;
   QFile::copy(fullFilePath,newFileName);  //备份文件


   if(m_MysqlInstance)
   {
       auto sqlSentence = QString("INSERT INTO %1(update_time,upload_time,file_name,type,upload_mode,status,file_local_path,file_size) \
                                  VALUES(%2,%3,'%4',%5,%6,%7,'%8',%9)").arg(tableName)
                                                                        .arg(QDateTime::currentDateTime().toSecsSinceEpoch())
                                                                        .arg(birthTime)
                                                                        .arg(fileName)
                                                                        .arg(1)
                                                                        .arg(1)
                                                                        .arg(0)
                                                                        .arg(backupPath)
                                                                        .arg(fileSize);
        return m_MysqlInstance->RunSQLNoQuery(sqlSentence);


   }




    return false;


}

qint64 StatusFilePlugin::getUpdateTime(const QString &Date, const QString &Time)
{

    if(Date.isEmpty() || Time.isEmpty())
    {
        return -1;
    }

    auto index = Date.indexOf("-");
    auto year = Date.left(index).toUInt();

    auto previousIndex = index + 1;
    index = Date.indexOf("-",previousIndex);
    auto month = Date.mid(previousIndex,index - previousIndex).toUInt();

    auto day = Date.right(2).toUInt();

    index = Time.indexOf(":");
    auto hour = Time.left(index).toUInt();

    previousIndex = index + 1;
    index = Time.indexOf(":",previousIndex);
    auto minute = Time.mid(previousIndex,index - previousIndex).toUInt();

    auto second = Time.right(2).toUInt();

    return QDateTime(QDate(year,month,day),QTime(hour,minute,second)).toSecsSinceEpoch();

}

bool StatusFilePlugin::writeLogToDataBase(qint64 updateTime, const QString &updateTimeStr, const QString &logInfo)
{
    if(m_MysqlInstance)
    {
        auto sqlSentence = QString("INSERT INTO t_radar_record_log(update_time,observe_time,log_content) VALUES(%1,'%2','%3')").arg(updateTime).arg(updateTimeStr.arg(logInfo));


        return m_MysqlInstance->RunSQLNoQuery(sqlSentence);


    }

    return false;
}

void StatusFilePlugin::getFaultInSubSystem(const RadarDef::RadarStatusCF6 statusData)
{
    m_FaultInSubsystem0.clear();
    m_FaultInSubsystem1.clear();
    m_FaultInSubsystem2.clear();
    m_FaultInSubsystem3.clear();
    m_FaultInSubsystem4.clear();
    m_FaultInSubsystem5.clear();
    m_FaultInSubsystem6.clear();
    m_FaultInSubsystem7.clear();


    getFaultInSubSystem0(statusData);
    getFaultInSubSystem1(statusData);
    getFaultInSubSystem2(statusData);
    getFaultInSubSystem3(statusData);
    getFaultInSubSystem4(statusData);
    getFaultInSubSystem5(statusData);
    getFaultInSubSystem6(statusData);
    getFaultInSubSystem7(statusData);
}

bool StatusFilePlugin::writeRadarStatusToDataBase(const RadarDef::RadarStatusCF6 statusData)
{


    if(m_MysqlInstance)
    {
        QTextCodec* codec = QTextCodec::codecForName("GB18030");
        QString country = codec->toUnicode(QByteArray(statusData.Country));
        QString province = codec->toUnicode(QByteArray(statusData.Province));
        QString stationNumber = codec->toUnicode(QByteArray(statusData.StationNumber));
        QString station = codec->toUnicode(QByteArray(statusData.Station));
        QString radarType = codec->toUnicode(QByteArray(statusData.RadarType));
        QString longitude = codec->toUnicode(QByteArray(statusData.Longitude));
        QString latitude = codec->toUnicode(QByteArray(statusData.Latitude));
        QString altitude = codec->toUnicode(QByteArray(statusData.Altitude));

        auto observationTime = getObservationTime(statusData);

        auto sqlSentence = QString("INSERT INTO t_fdata_sta6 (country,\
                                            province,\
                                            station,\
                                            station_number,\
                                            radar_type,\
                                            longitude,\
                                            latitude,\
                                            altitude,\
                                            update_time,\
                                            observe_time,\
                                            radar_status,\
                                            sub_num,\
                                            sub_sys0,\
                                            sub_sys1,\
                                            sub_sys2,\
                                            sub_sys3,\
                                            sub_sys4,\
                                            sub_sys5,\
                                            sub_sys6,\
                                            sub_sys7,\
                                            sub_sys8,\
                                            sys_status0_detail,\
                                            sys_status1_detail,\
                                            sys_status2_detail,\
                                            sys_status3_detail,\
                                            sys_status4_detail,\
                                            sys_status5_detail,\
                                            sys_status6_detail,\
                                            sys_status7_detail) \
                                           VALUES('%1','%2','%3','%4','%5','%6','%7',%8,%9,%10,%11,%12,%13,%14,%15,%16,%17,%18,%19,%20,%21,'%22','%23','%24','%25','%26','%27','%28','%29')")
                        .arg(country)\
                        .arg(province)\
                        .arg(station)\
                        .arg(stationNumber)\
                        .arg(radarType)\
                        .arg(longitude)\
                        .arg(latitude)\
                        .arg(altitude)\
                        .arg(QDateTime::currentDateTime().toSecsSinceEpoch())\
                        .arg(observationTime)\
                        .arg(statusData.RadarStatus)\
                        .arg(statusData.SubsysNum)\
                        .arg(statusData.Subsys0)\
                        .arg(statusData.Subsys1)\
                        .arg(statusData.Subsys2)\
                        .arg(statusData.Subsys3)\
                        .arg(statusData.Subsys4)\
                        .arg(statusData.Subsys5)\
                        .arg(statusData.Subsys6)\
                        .arg(statusData.Subsys7)\
                        .arg(statusData.Subsys8)\
                        .arg(m_FaultInSubsystem0)\
                        .arg(m_FaultInSubsystem1)\
                        .arg(m_FaultInSubsystem2)\
                        .arg(m_FaultInSubsystem3)\
                        .arg(m_FaultInSubsystem4)\
                        .arg(m_FaultInSubsystem5)\
                        .arg(m_FaultInSubsystem6)\
                        .arg(m_FaultInSubsystem7);

        m_MysqlInstance->RunSQLNoQuery(sqlSentence);


        qint64 id = 0UL;

        auto queryStr = QString("SELECT id FROM t_fdata_sta6 WHERE observe_time = %1").arg(observationTime);
        auto sqlQuery = m_MysqlInstance->RunSQLQuery(queryStr);
        if(sqlQuery.size() > 0)
        {
            while(sqlQuery.next())
            {
                id = sqlQuery.value("id").toULongLong();
            }
        }

        sqlSentence = QString("INSERT INTO t_fdata_sta6_observe (sta_id,\
                                                        sys_code0,\
                                                        obs_datanum0,\
                                                        obs_data0,\
                                                        sys_code1,\
                                                        obs_datanum1,\
                                                        obs_data1,\
                                                        obs_data2,\
                                                        obs_data3,\
                                                        obs_data4,\
                                                        obs_data5,\
                                                        obs_data6,\
                                                        obs_data7,\
                                                        obs_data8,\
                                                        obs_data9,\
                                                        obs_data10,\
                                                        obs_data11,\
                                                        obs_data12,\
                                                        obs_data13,\
                                                        obs_data14,\
                                                        obs_data15,\
                                                        obs_data16,\
                                                        obs_data17,\
                                                        obs_data18,\
                                                        obs_data19,\
                                                        obs_data20,\
                                                        obs_data21,\
                                                        obs_data22,\
                                                        obs_data23,\
                                                        obs_data24,\
                                                        obs_data25,\
                                                        obs_data26,\
                                                        obs_data27,\
                                                        obs_data28,\
                                                        obs_data29,\
                                                        obs_data30,\
                                                        obs_data31,\
                                                        obs_data32,\
                                                        obs_data33,\
                                                        obs_data34,\
                                                        obs_data35,\
                                                        obs_data36,\
                                                        obs_data37,\
                                                        obs_data38,\
                                                        obs_data39,\
                                                        obs_data40,\
                                                        obs_data41,\
                                                        obs_data42,\
                                                        obs_data43,\
                                                        obs_data44,\
                                                        obs_data45,\
                                                        obs_data46,\
                                                        obs_data47,\
                                                        obs_data48,\
                                                        obs_data49,\
                                                        obs_data50,\
                                                        obs_data51,\
                                                        obs_data52,\
                                                        obs_data53,\
                                                        obs_data54,\
                                                        obs_data55,\
                                                        obs_data56,\
                                                        obs_data57,\
                                                        obs_data58,\
                                                        obs_data59,\
                                                        obs_data60,\
                                                        obs_data61,\
                                                        obs_data62,\
                                                        obs_data63,\
                                                        obs_data64,\
                                                        obs_data65,\
                                                        obs_data66,\
                                                        obs_data67,\
                                                        obs_data68,\
                                                        obs_data69,\
                                                        obs_data70,\
                                                        obs_data71,\
                                                        obs_data72) VALUES(%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15,%16,%17,%18,%19,%20,%21,%22,%23,%24,%25,%26,%27,%28,%29,%30,%31,%32,%33,%34,%35,\
                                                        %36,%37,%38,%39,%40,%41,%42,%43,%44,%45,%46,%47,%48,%49,%50,%51,%52,%53,%54,%55,%56,%57,%58,%59,%60,%61,%62,%63,%64,%65,%66,%67,%68,%69,%70,%71,%72,%73,%74,%75,%76,%77,%78)")\
                .arg(id)\
                .arg(statusData.MOBS_SysCode0)\
                .arg(statusData.MOBS_Obsdatanum0)\
                .arg(statusData.MOBS_Obsdata0)\
                .arg(statusData.MOBS_SysCode1)\
                .arg(statusData.MOBS_Obsdatanum1)\
                .arg(statusData.MOBS_Obsdata1)\
                .arg(statusData.MOBS_Obsdata2)\
                .arg(statusData.MOBS_Obsdata3)\
                .arg(statusData.MOBS_Obsdata4)\
                .arg(statusData.MOBS_Obsdata5)\
                .arg(statusData.MOBS_Obsdata6)\
                .arg(statusData.MOBS_Obsdata7)\
                .arg(statusData.MOBS_Obsdata8)\
                .arg(statusData.MOBS_Obsdata9)\
                .arg(statusData.MOBS_Obsdata10)\
                .arg(statusData.MOBS_Obsdata11)\
                .arg(statusData.MOBS_Obsdata12)\
                .arg(statusData.MOBS_Obsdata13)\
                .arg(statusData.MOBS_Obsdata14)\
                .arg(statusData.MOBS_Obsdata15)\
                .arg(statusData.MOBS_Obsdata16)\
                .arg(statusData.MOBS_Obsdata17)\
                .arg(statusData.MOBS_Obsdata18)\
                .arg(statusData.MOBS_Obsdata19)\
                .arg(statusData.MOBS_Obsdata20)\
                .arg(statusData.MOBS_Obsdata21)\
                .arg(statusData.MOBS_Obsdata22)\
                .arg(statusData.MOBS_Obsdata23)\
                .arg(statusData.MOBS_Obsdata24)\
                .arg(statusData.MOBS_Obsdata25)\
                .arg(statusData.MOBS_Obsdata26)\
                .arg(statusData.MOBS_Obsdata27)\
                .arg(statusData.MOBS_Obsdata28)\
                .arg(statusData.MOBS_Obsdata29)\
                .arg(statusData.MOBS_Obsdata30)\
                .arg(statusData.MOBS_Obsdata31)\
                .arg(statusData.MOBS_Obsdata32)\
                .arg(statusData.MOBS_Obsdata33)\
                .arg(statusData.MOBS_Obsdata34)\
                .arg(statusData.MOBS_Obsdata35)\
                .arg(statusData.MOBS_Obsdata36)\
                .arg(statusData.MOBS_Obsdata37)\
                .arg(statusData.MOBS_Obsdata38)\
                .arg(statusData.MOBS_Obsdata39)\
                .arg(statusData.MOBS_Obsdata40)\
                .arg(statusData.MOBS_Obsdata41)\
                .arg(statusData.MOBS_Obsdata42)\
                .arg(statusData.MOBS_Obsdata43)\
                .arg(statusData.MOBS_Obsdata44)\
                .arg(statusData.MOBS_Obsdata45)\
                .arg(statusData.MOBS_Obsdata46)\
                .arg(statusData.MOBS_Obsdata47)\
                .arg(statusData.MOBS_Obsdata48)\
                .arg(statusData.MOBS_Obsdata49)\
                .arg(statusData.MOBS_Obsdata50)\
                .arg(statusData.MOBS_Obsdata51)\
                .arg(statusData.MOBS_Obsdata52)\
                .arg(statusData.MOBS_Obsdata53)\
                .arg(statusData.MOBS_Obsdata54)\
                .arg(statusData.MOBS_Obsdata55)\
                .arg(statusData.MOBS_Obsdata56)\
                .arg(statusData.MOBS_Obsdata57)\
                .arg(statusData.MOBS_Obsdata58)\
                .arg(statusData.MOBS_Obsdata59)\
                .arg(statusData.MOBS_Obsdata60)\
                .arg(statusData.MOBS_Obsdata61)\
                .arg(statusData.MOBS_Obsdata62)\
                .arg(statusData.MOBS_Obsdata63)\
                .arg(statusData.MOBS_Obsdata64)\
                .arg(statusData.MOBS_Obsdata65)\
                .arg(statusData.MOBS_Obsdata66)\
                .arg(statusData.MOBS_Obsdata67)\
                .arg(statusData.MOBS_Obsdata68)\
                .arg(statusData.MOBS_Obsdata69)\
                .arg(statusData.MOBS_Obsdata70)\
                .arg(statusData.MOBS_Obsdata71)\
                .arg(statusData.MOBS_Obsdata72);

                
        m_MysqlInstance->RunSQLNoQuery(sqlSentence);

    }

    return true;
}

void StatusFilePlugin::getFaultInSubSystem0(const RadarDef::RadarStatusCF3 statusData)
{
    m_FaultInSubsystem0 += "[";

    generateFaultInfoForSubsystem(0,0)
    generateFaultInfoForSubsystem(0,1)
    generateFaultInfoForSubsystem(0,2)
    generateFaultInfoForSubsystem(0,3)
    generateFaultInfoForSubsystem(0,4)
    generateFaultInfoForSubsystem(0,5)
    generateFaultInfoForSubsystem(0,6)
    generateFaultInfoForSubsystem(0,7)
    generateFaultInfoForSubsystem(0,8)
    generateFaultInfoForSubsystem(0,9)
    generateFaultInfoForSubsystem(0,10)
    generateFaultInfoForSubsystem(0,11)
    generateFaultInfoForSubsystem(0,12)
    generateFaultInfoForSubsystem(0,13)
    generateFaultInfoForSubsystem(0,14)
    generateFaultInfoForSubsystem(0,15)
    generateFaultInfoForSubsystem(0,16)
    generateFaultInfoForSubsystem(0,17)
    generateFaultInfoForSubsystem(0,18)
    generateFaultInfoForSubsystem(0,19)
    generateFaultInfoForSubsystem(0,20)
    generateFaultInfoForSubsystem(0,21)
    generateFaultInfoForSubsystem(0,22)
    generateFaultInfoForSubsystem(0,23)
    generateFaultInfoForSubsystem(0,24)
    generateFaultInfoForSubsystem(0,26)
    generateFaultInfoForSubsystem(0,26)
    generateFaultInfoForSubsystem(0,27)
    generateFaultInfoForSubsystem(0,28)


    if(m_FaultInSubsystem0.length() > 1)
    {
        m_FaultInSubsystem0.remove(m_FaultInSubsystem0.length()-1,1);
        m_FaultInSubsystem0 += "]";
    }
    else
    {
        m_FaultInSubsystem0.clear();
    }
}

void StatusFilePlugin::getFaultInSubSystem1(const RadarDef::RadarStatusCF3 statusData)
{
     m_FaultInSubsystem1 += "[";

    generateFaultInfoForSubsystem(1,0)
    generateFaultInfoForSubsystem(1,1)
    generateFaultInfoForSubsystem(1,2)
    generateFaultInfoForSubsystem(1,3)
    generateFaultInfoForSubsystem(1,4)


    if(m_FaultInSubsystem1.length() > 1)
    {
        m_FaultInSubsystem1.remove(m_FaultInSubsystem1.length()-1,1);
        m_FaultInSubsystem1 += "]";
    }
    else
    {
        m_FaultInSubsystem1.clear();
    }
}

void StatusFilePlugin::getFaultInSubSystem2(const RadarDef::RadarStatusCF3 statusData)
{
    m_FaultInSubsystem2 += "[";

    generateFaultInfoForSubsystem(2,0)
    generateFaultInfoForSubsystem(2,1)
    generateFaultInfoForSubsystem(2,2)
    generateFaultInfoForSubsystem(2,3)
    generateFaultInfoForSubsystem(2,4)
    generateFaultInfoForSubsystem(2,5)

    if(m_FaultInSubsystem2.length() > 1)
    {
        m_FaultInSubsystem2.remove(m_FaultInSubsystem2.length()-1,1);
        m_FaultInSubsystem2 += "]";
    }
    else
    {
        m_FaultInSubsystem2.clear();
    }
}

void StatusFilePlugin::getFaultInSubSystem3(const RadarDef::RadarStatusCF3 statusData)
{
    m_FaultInSubsystem3 += "[";

    generateFaultInfoForSubsystem(3,0)
    generateFaultInfoForSubsystem(3,1)

    if(m_FaultInSubsystem3.length() > 1)
    {
        m_FaultInSubsystem3.remove(m_FaultInSubsystem3.length()-1,1);
        m_FaultInSubsystem3 += "]";
    }
    else
    {
        m_FaultInSubsystem3.clear();
    }
}

void StatusFilePlugin::getFaultInSubSystem4(const RadarDef::RadarStatusCF3 statusData)
{
    m_FaultInSubsystem4 += "[";

    generateFaultInfoForSubsystem(4,0)

    if(m_FaultInSubsystem4.length() > 1)
    {
        m_FaultInSubsystem4.remove(m_FaultInSubsystem4.length()-1,1);
        m_FaultInSubsystem4 += "]";
    }
    else
    {
        m_FaultInSubsystem4.clear();
    }
}

void StatusFilePlugin::getFaultInSubSystem5(const RadarDef::RadarStatusCF3 statusData)
{
    m_FaultInSubsystem5 += "[";

    generateFaultInfoForSubsystem(5,0)

    if(m_FaultInSubsystem5.length() > 1)
    {
        m_FaultInSubsystem5.remove(m_FaultInSubsystem5.length()-1,1);
        m_FaultInSubsystem5 += "]";
    }
    else
    {
        m_FaultInSubsystem5.clear();
    }

}

void StatusFilePlugin::getFaultInSubSystem6(const RadarDef::RadarStatusCF3 statusData)
{
    m_FaultInSubsystem6 += "[";

    generateFaultInfoForSubsystem(6,0)

    if(m_FaultInSubsystem6.length() > 1)
    {
        m_FaultInSubsystem6.remove(m_FaultInSubsystem6.length()-1,1);
        m_FaultInSubsystem6 += "]";
    }
    else
    {
        m_FaultInSubsystem6.clear();
    }
}

void StatusFilePlugin::getFaultInSubSystem7(const RadarDef::RadarStatusCF3 statusData)
{
    m_FaultInSubsystem7 += "[";

    generateFaultInfoForSubsystem(7,0)

    if(m_FaultInSubsystem7.length() > 1)
    {
        m_FaultInSubsystem7.remove(m_FaultInSubsystem7.length()-1,1);
        m_FaultInSubsystem7 += "]";
    }
    else
    {
        m_FaultInSubsystem7.clear();
    }
}


void StatusFilePlugin::endMonitor()
{
    quit();
    wait();
}


void StatusFilePlugin::setMysqlInstance(IMysqlDB *instance)
{
    m_MysqlInstance = instance;
}
