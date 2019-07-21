#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QtDebug>
#include <QtSql/QSqlQuery>
#include <QtXml/QtXml>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_MysqlDB(nullptr),
    m_StatusFile(nullptr),
    m_Temperature(nullptr),
    m_AirConditioner(nullptr),
    m_sqlPluginLoader(new QPluginLoader(this)),
    m_statusFilePluginLoader(new QPluginLoader(this)),
    m_temperaturePluginLoader(new QPluginLoader(this)),
    m_airConditionerPluginLoader(new QPluginLoader(this)),
    m_initTimer(new QTimer(this))
{
    ui->setupUi(this);

    QCoreApplication::addLibraryPath("./sqldrivers");
    QCoreApplication::addLibraryPath("./platforms");

    m_initTimer->start(1000);
    connect(m_initTimer,&QTimer::timeout,this,&MainWindow::onInitTimeout);

    loadMysqlPlugin();

}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::onInitTimeout()
{
    if(m_MysqlDB->getConnectionStatus())
    {
        loadStatusFilePlugin();
        loadTemperaturePlugin();
        loadAirConditonerPlugin();
    }

    m_initTimer->stop();
}



void MainWindow::loadMysqlPlugin()
{

    QString mysqlPluginPath;
#ifdef QT_DEBUG
    mysqlPluginPath = "./Plugin/MysqlDB/libMysqlDBd.so";
#else
    mysqlPluginPath = "./Plugin/MysqlDB/libMysqlDB.so";

#endif

   m_sqlPluginLoader->setFileName(mysqlPluginPath);

    m_MysqlDB = qobject_cast<IMysqlDB*>(m_sqlPluginLoader->instance());
    if(!m_sqlPluginLoader->isLoaded())
    {
        m_MysqlDB = nullptr;
        qInfo() << m_sqlPluginLoader->errorString();
        return;
    }
    else
    {
        m_MysqlDB->ConnectToDataBase();
    }
}

void MainWindow::loadStatusFilePlugin()
{
    QString statusFilePluginPath;
#ifdef QT_DEBUG
    statusFilePluginPath = "./Plugin/StatusFile/libStatusFiled.so";   //根据debug或者release加载不同的插件
#else
    statusFilePluginPath = "./Plugin/StatusFile/libStatusFile.so";

#endif
    m_statusFilePluginLoader->setFileName(statusFilePluginPath);

    m_StatusFile = qobject_cast<IStatusFile*>(m_statusFilePluginLoader->instance());  //加载插件
    if(!m_statusFilePluginLoader->isLoaded())
    {
        m_StatusFile = nullptr;
        qInfo() << m_statusFilePluginLoader->errorString();
        return;
    }
    else
    {
        m_StatusFile->setMysqlInstance(m_MysqlDB);
        m_StatusFile->runMonitor();
    }

}

void MainWindow::loadTemperaturePlugin()
{
    QString temperaturePluginPath;
#ifdef QT_DEBUG
    temperaturePluginPath = "./Plugin/Temperature/libStatusFiled.so";
#else
    temperaturePluginPath = "./Plugin/Temperature/libStatusFile.so";

#endif
    m_temperaturePluginLoader->setFileName(temperaturePluginPath);

    m_Temperature = qobject_cast<ITemperature*>(m_temperaturePluginLoader->instance());
    if(!m_temperaturePluginLoader->isLoaded())
    {
        m_Temperature = nullptr;
        qInfo() << m_temperaturePluginLoader->errorString();
        return;
    }
    else
    {
        m_Temperature->setMysqlInstance(m_MysqlDB);
        m_Temperature->setIPAdress(getTemperatureIPAdress());
        m_Temperature->runMonitor();
    }

}

void MainWindow::loadAirConditonerPlugin()
{
    QString airConditionerPluginPath;
#ifdef QT_DEBUG
    airConditionerPluginPath = "./Plugin/AirConditioner/libAirConditionerd.so";
#else
    airConditionerPluginPath = "./Plugin/AirConditioner/libAirConditioner.so";

#endif
    m_airConditionerPluginLoader->setFileName(airConditionerPluginPath);

    m_AirConditioner = qobject_cast<IAirConditioner*>(m_airConditionerPluginLoader->instance());
    if(!m_airConditionerPluginLoader->isLoaded())
    {
        m_AirConditioner = nullptr;
        qInfo() << m_airConditionerPluginLoader->errorString();
        return;
    }
    else
    {
        m_AirConditioner->setControllerIPAdress(getAirConditionerIPAddress());
        m_AirConditioner->setHostIPAdress(getHostIPAdress());
        m_AirConditioner->setAirConfig(getAirConditionerConfigFromDataBase());
        m_AirConditioner->startListening();
    }

}

QString MainWindow::getAirConditionerConfigFromDataBase()
{
    QString airConditoneConfig;
    QString sqlSentence("SELECT param_value FROM sys_config WHERE param_key='airConditioner'");

    auto sqlQuery = m_MysqlDB->RunSQLQuery(sqlSentence);
    if(sqlQuery.size() > 0)
    {
        while(sqlQuery.next())
        {
            airConditoneConfig = sqlQuery.value("param_value").toString();
        }
    }

    return airConditoneConfig;
}

QString MainWindow::getAirConditionerIPAddress()
{
    QString IPAdress;

   QFile file("Airconfig.xml");
   if (!file.open(QFile::ReadOnly | QFile::Text))
   {
       qDebug() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm::ss") << QString(u8"Airconfig.xml打开失败");
       return IPAdress;
   }

   QString errorStr;
   int errorLine;
   int errorColumn;

   QDomDocument doc;

   if (!doc.setContent(&file, false, &errorStr, &errorLine,&errorColumn))
   {
       qDebug() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm::ss") << QString(u8"Airconfig.xml格式有误");
       file.close();
       return IPAdress;
   }

   file.close();



   QDomElement root = doc.documentElement();
   for(QDomNode n = root.firstChild(); !n.isNull(); n = n.nextSibling())
   {

       if(n.toElement().tagName().contains("IP"))
       {
            IPAdress = n.toElement().attribute("AirControllerIP");
       }
   }

   return IPAdress;
}

QString MainWindow::getHostIPAdress()
{
    QString IPAdress;

    QFile file("Airconfig.xml");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm::ss") << QString(u8"Airconfig.xml打开失败");
        return IPAdress;
    }

    QString errorStr;
    int errorLine;
    int errorColumn;

    QDomDocument doc;

    if (!doc.setContent(&file, false, &errorStr, &errorLine,&errorColumn))
    {
        qDebug() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm::ss") << QString(u8"Airconfig.xml格式有误");
        file.close();
        return IPAdress;
    }

    file.close();

    QDomElement root = doc.documentElement();
    for(QDomNode n = root.firstChild(); !n.isNull(); n = n.nextSibling())
    {

        if(n.toElement().tagName().contains("IP"))
        {
             IPAdress = n.toElement().attribute("HostIP");
        }
    }

    return IPAdress;
}

QString MainWindow::getTemperatureIPAdress()
{
    QString IPAdress;

    QFile file("Temperatureconfig.xml");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm::ss") << QString(u8"Temperatureconfig.xml打开失败");
        return IPAdress;
    }

    QString errorStr;
    int errorLine;
    int errorColumn;

    QDomDocument doc;

    if (!doc.setContent(&file, false, &errorStr, &errorLine,&errorColumn))
    {
        qDebug() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm::ss") << QString(u8"Temperatureconfig.xml格式有误");
        file.close();
        return IPAdress;
    }

    file.close();


    QDomElement root = doc.documentElement();
    for(QDomNode n = root.firstChild(); !n.isNull(); n = n.nextSibling())
    {

        if(n.toElement().tagName().contains("IP"))
        {
             IPAdress = n.toElement().attribute("TemperatureIP");
        }
    }

    return IPAdress;
}


void MainWindow::closeEvent(QCloseEvent *event)
{

    m_sqlPluginLoader->unload();

    if(m_StatusFile)
    {
        m_StatusFile->endMonitor();
    }

    if(m_Temperature)
    {
        m_Temperature->endMonitor();
    }

    if(m_AirConditioner)
    {
        m_AirConditioner->stopListening();
    }


    event->accept();
}
