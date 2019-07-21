#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPluginLoader>
#include <QTimer>
#include <QCloseEvent>
#include "MysqlDB_I.h"
#include "StatusFile_I.h"
#include "Temperature_I.h"
#include "AirConditioner_I.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onInitTimeout(); //初始化定时器的定时函数，用于开启各个模块功能

private:
   void loadMysqlPlugin();          //加载数据库插件
   void loadStatusFilePlugin();    //加载文件处理插件
   void loadTemperaturePlugin();   //加载温湿度采集插件
   void loadAirConditonerPlugin();  //加载空调控制插件

   QString getAirConditionerConfigFromDataBase();  //从数据库中获取普通关空调配置信息，和标准输出一样
   QString getAirConditionerIPAddress();
   QString getHostIPAdress();
   QString getTemperatureIPAdress();

private:
    Ui::MainWindow *ui;

    IMysqlDB* m_MysqlDB;             //各个插件的接口
    IStatusFile* m_StatusFile;
    ITemperature* m_Temperature;
    IAirConditioner* m_AirConditioner;

    QPluginLoader* m_sqlPluginLoader;
    QPluginLoader* m_statusFilePluginLoader;
    QPluginLoader* m_temperaturePluginLoader;
    QPluginLoader* m_airConditionerPluginLoader;

    QTimer* m_initTimer;  //初始化定时器



    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // MAINWINDOW_H
