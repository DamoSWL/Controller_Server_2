#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QList>
#include <QDateTime>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    m_LogModel(new QStandardItemModel(this))
{
    ui->setupUi(this);

    initUI();

    for(auto i = 0; i< m_FileTypeNum; i++)
    {
        m_accessFTPManager[i] = new QNetworkAccessManager(this);
        m_accessFTPManager[i]->setNetworkAccessible(QNetworkAccessManager::Accessible);
        m_FTPManager[i] = new FTPUpload(this);
        m_FTPManager[i]->setAutoDelete(false);
        m_FTPManager[i]->setFileType(i);

        connect(m_FTPManager[i],SIGNAL(upload(quint8,QUrl,QByteArray)),this,SLOT(upload(quint8,QUrl,QByteArray)),Qt::QueuedConnection);
        connect(m_FTPManager[i],SIGNAL(newFileTime(quint8,QString)),this,SLOT(setNewFileNewInXml(quint8,QString)),Qt::QueuedConnection);
        connect(m_FTPManager[i],SIGNAL(addLog(QStringList)),this,SLOT(addLog(QStringList)),Qt::QueuedConnection);
        connect(m_accessFTPManager[i],SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)),Qt::QueuedConnection);
    }


    QThreadPool::globalInstance()->setMaxThreadCount(m_FileTypeNum + 3);
    connectToDataBase();
    readInitFromXML();
    getFTPConfigFromXML();

}

Widget::~Widget()
{

    for(auto i = 0; i < m_FileTypeNum; i++)
    {
        m_FTPManager[i]->quit();
    }

    for(auto i = 0; i < m_FileTypeNum; i++)
    {
        m_FTPManager[i]->wait();
    }
    delete ui;
}



void Widget::on_pushButton_configConfirm_clicked()
{
    if(ui->lineEdit_remoteIP->text().isEmpty())
    {
        QMessageBox::warning(this,u8"报警",u8"远程IP地址为空");
        return;
    }

    if(ui->lineEdit_userName->text().isEmpty())
    {
        QMessageBox::warning(this,u8"报警",u8"用户名为空");
        return;
    }

    if(ui->lineEdit_code->text().isEmpty())
    {
        QMessageBox::warning(this,u8"报警",u8"密码为空");
        return;
    }

    if(ui->lineEdit_localPath->text().isEmpty())
    {
        QMessageBox::warning(this,u8"报警",u8"本地路径为空");
        return;
    }

    if(ui->lineEdit_remotePath->text().isEmpty())
    {
        QMessageBox::warning(this,u8"报警",u8"远程路径为空");
        return;
    }

    FTPConfigure tempConfig;
    tempConfig.fileType = ui->comboBox_fileType->currentIndex();
    tempConfig.remoteIP = ui->lineEdit_remoteIP->text();
    tempConfig.userName = ui->lineEdit_userName->text();
    tempConfig.password = ui->lineEdit_code->text();
    tempConfig.localPath = ui->lineEdit_localPath->text();
    tempConfig.remotePath = ui->lineEdit_remotePath->text();

    m_FTPConfiguration.insert(tempConfig);

    auto rowIndex = ui->tableWidget_FTPConfig->rowCount();
    ui->tableWidget_FTPConfig->insertRow(rowIndex);

    ui->tableWidget_FTPConfig->setItem(rowIndex,0,new QTableWidgetItem(getFileTypeName(tempConfig.fileType)));  //配置信息添加到界面上
    ui->tableWidget_FTPConfig->setItem(rowIndex,1,new QTableWidgetItem(tempConfig.remoteIP));
    ui->tableWidget_FTPConfig->setItem(rowIndex,2,new QTableWidgetItem(tempConfig.userName));
    ui->tableWidget_FTPConfig->setItem(rowIndex,3,new QTableWidgetItem(tempConfig.password));
    ui->tableWidget_FTPConfig->setItem(rowIndex,4,new QTableWidgetItem(tempConfig.localPath));
    ui->tableWidget_FTPConfig->setItem(rowIndex,5,new QTableWidgetItem(tempConfig.remotePath));

    if(ui->radioButton_country->isChecked())
    {
        m_NationalIPAdress = ui->lineEdit_remoteIP->text();
    }
    else if(ui->radioButton_province->isChecked())
    {
        m_ProvinceIPAdress = ui->lineEdit_remoteIP->text();
    }
    else{}

    setFTPConfigInXML();

}

void Widget::on_pushButton_upload_clicked()
{

    if(ui->pushButton_upload->text() == u8"开始")
    {
        for(auto i = 0; i < m_FileTypeNum; i++)
        {
            m_FTPManager[i]->setFTPConfiguration(m_FTPConfiguration);  //设置配置信息
            QThreadPool::globalInstance()->start(m_FTPManager[i]);  //启动线程
        }

        ui->pushButton_upload->setText(u8"停止");
        ui->pushButton_configConfirm->setEnabled(false);
        ui->pushButton_configCancel->setEnabled(false);
    }
    else if(ui->pushButton_upload->text() == u8"停止")
    {

        ui->pushButton_upload->setEnabled(false);
        for(auto i = 0; i < m_FileTypeNum; i++)
        {
            m_FTPManager[i]->quit();
            m_FTPManager[i]->wait();
        }
        ui->pushButton_upload->setEnabled(true);

        ui->pushButton_upload->setText(u8"开始");
        ui->pushButton_configConfirm->setEnabled(true);
        ui->pushButton_configCancel->setEnabled(true);

    }
    else{}
}

void Widget::on_pushButton_configCancel_clicked()
{
    auto currentRow = ui->tableWidget_FTPConfig->currentRow();

    if(currentRow >= 0)
    {
        if(QMessageBox::Yes == QMessageBox::information(this,u8"提示",u8"确定要删除该FTP上传配置吗?",QMessageBox::Yes | QMessageBox::No,QMessageBox::No))
        {
            FTPConfigure tempConfig;

            tempConfig.fileType = getFileTypeFromCNName(ui->tableWidget_FTPConfig->item(currentRow,0)->text());
            tempConfig.remoteIP = ui->tableWidget_FTPConfig->item(currentRow,1)->text();
            tempConfig.userName = ui->tableWidget_FTPConfig->item(currentRow,2)->text();
            tempConfig.password = ui->tableWidget_FTPConfig->item(currentRow,3)->text();
            tempConfig.localPath = ui->tableWidget_FTPConfig->item(currentRow,4)->text();
            tempConfig.remotePath = ui->tableWidget_FTPConfig->item(currentRow,5)->text();

            m_FTPConfiguration -= tempConfig;

            ui->tableWidget_FTPConfig->removeRow(currentRow);

            setFTPConfigInXML();

        }

    }
}

void Widget::upload(quint8 fileType, const QUrl &url, const QByteArray &data)
{
    if(m_accessFTPManager[fileType])
    {
        m_accessFTPManager[fileType]->put(QNetworkRequest(url),data);  //上传执行动作
    }
}

void Widget::replyFinished(QNetworkReply *reply)
{
    auto IPAdress = getIPAdressFromReply(reply);
    auto fileName = getFileNameFromReply(reply);

    if(IPAdress.isEmpty() || fileName.isEmpty())
    {
        return;
    }

    auto fileType = getFileTypeFromName(fileName);
    auto uploadType = getUploadType(IPAdress);
    auto pathInfo = getRemoteAndLocalPath(fileType,IPAdress);  //获取远程和本地路径信息

    QString logStr;
    logStr += fileName;
    logStr += u8"上传至";
    logStr += IPAdress;

    if(reply->error() == QNetworkReply::NoError)
    {
        logStr += u8"成功";
        addLog(QStringList() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm::ss") << logStr);
    }
    else
    {
        logStr += u8"失败";
        addLog(QStringList() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm::ss") << logStr);
        addLog(QStringList() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm::ss") << reply->errorString());
    }

    auto uploadStatus = getUploadStatus(reply->error());

    QList<qint8> uploadInfo;
    uploadInfo << fileType << uploadType << uploadStatus;

    writeFTPUploadInfoToDataBase(uploadInfo,fileName,pathInfo);  //将上传信息写入数据库中
    writeFTPUploadStatisticsToDataBase(fileType,uploadStatus);  //将上传统计信息写入数据库中
}


void Widget::addLog(const QStringList &logStr)
{

    QList<QStandardItem*> newItem;
    newItem << new QStandardItem(logStr.at(0)) << new QStandardItem(logStr.at(1));
    m_LogModel->appendRow(newItem);

    if(m_LogModel->rowCount() >= 1e6)
    {
        m_LogModel->removeRows(0,1e5);
    }

    ui->tableView_FTPview->scrollToBottom();

}

void Widget::setNewFileNewInXml(quint8 FileType, const QString &updateTime)
{
    QFile file("config.xml");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        addLog(QStringList() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm::ss") << QString(u8"config.xml打开失败"));
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

void Widget::initUI()
{

    QTableWidgetItem* item = new QTableWidgetItem;
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(u8"文件类型");
    ui->tableWidget_FTPConfig->setHorizontalHeaderItem(0,item);

    item = new QTableWidgetItem;
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(u8"远程IP");
    ui->tableWidget_FTPConfig->setHorizontalHeaderItem(1,item);

    item = new QTableWidgetItem;
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(u8"用户名");
    ui->tableWidget_FTPConfig->setHorizontalHeaderItem(2,item);

    item = new QTableWidgetItem;
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(u8"密码");
    ui->tableWidget_FTPConfig->setHorizontalHeaderItem(3,item);

    item = new QTableWidgetItem;
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(u8"监控路径");
    ui->tableWidget_FTPConfig->setHorizontalHeaderItem(4,item);

    item = new QTableWidgetItem;
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(u8"远程路径");
    ui->tableWidget_FTPConfig->setHorizontalHeaderItem(5,item);

    m_LogModel->setColumnCount(2);
    m_LogModel->setHorizontalHeaderItem(0,new QStandardItem(u8"日期"));
    m_LogModel->setHorizontalHeaderItem(1,new QStandardItem(u8"日志"));
    ui->tableView_FTPview->setModel(m_LogModel);
    ui->tableView_FTPview->setColumnWidth(0,180);

}

void Widget::readInitFromXML()
{
    QFile file("config.xml");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        addLog(QStringList() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm::ss") << QString(u8"config.xml打开失败"));
        return;
    }

    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!m_DOC.setContent(&file, false, &errorStr, &errorLine,&errorColumn))
    {
        addLog(QStringList() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm::ss") << QString(u8"config.xml格式有误"));
        file.close();
        return;
    }

    file.close();

    QDomElement root = m_DOC.documentElement();
    for(QDomNode n = root.firstChild(); !n.isNull(); n = n.nextSibling())
    {

        if(n.toElement().tagName().contains("updateTime"))
        {
            m_FTPManager[FFTFILE]->setUpdateTime(n.toElement().attribute("FFT").toLongLong());
            m_FTPManager[RADFILE]->setUpdateTime(n.toElement().attribute("RAD").toLongLong());
            m_FTPManager[ROBSFILE]->setUpdateTime(n.toElement().attribute("ROBS").toLongLong());
            m_FTPManager[HOBSFILE]->setUpdateTime(n.toElement().attribute("HOBS").toLongLong());
            m_FTPManager[OOBSFILE]->setUpdateTime(n.toElement().attribute("OOBS").toLongLong());
            m_FTPManager[STATUSFILE]->setUpdateTime(n.toElement().attribute("STATUS").toLongLong());
            m_FTPManager[CALFILE]->setUpdateTime(n.toElement().attribute("CAL").toLongLong());
            m_FTPManager[LOGFILE]->setUpdateTime(n.toElement().attribute("LOG").toLongLong());

        }
    }
}

bool Widget::connectToDataBase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("root");
    db.setDatabaseName("wprsoc");

    db.setConnectOptions("MYSQL_OPT_RECONNECT=true;MYSQL_OPT_CONNECT_TIMEOUT=300");

    if(db.open())
    {
        addLog(QStringList() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm::ss") << u8"数据库打开成功");
    }
    else
    {
        addLog(QStringList() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm::ss") << u8"数据库打开失败");
    }

    return true;
}

QString Widget::getFileTypeName(quint8 FileTypeNO)
{

    QString FileTypeName;

    switch (FileTypeNO)
    {
    case FFTFILE:
        FileTypeName = u8"功率谱文件";
        break;
    case RADFILE:
        FileTypeName = u8"径向文件";
        break;
    case HOBSFILE:
        FileTypeName = u8"半小时数据文件";
        break;
    case OOBSFILE:
        FileTypeName = u8"一小时数据文件";
        break;
    case ROBSFILE:
        FileTypeName = u8"实时数据文件";
        break;
    case STATUSFILE:
        FileTypeName = u8"状态文件";
        break;
    case CALFILE:
        FileTypeName = u8"标定文件";
        break;
    case LOGFILE:
        FileTypeName = u8"日志文件";
        break;
    default:
        break;
    }

    return FileTypeName;

}

qint8 Widget::getFileTypeFromCNName(const QString &fileName)
{
    if(fileName == u8"功率谱文件")
    {
        return FFTFILE;
    }
    else if(fileName == u8"径向文件")
    {
        return RADFILE;
    }
    else if(fileName == u8"半小时数据文件")
    {
        return HOBSFILE;
    }
    else if(fileName == u8"一小时数据文件")
    {
        return OOBSFILE;
    }
    else if(fileName == u8"实时数据文件")
    {
        return ROBSFILE;
    }
    else if(fileName == u8"状态文件")
    {
        return STATUSFILE;
    }
    else if(fileName == u8"标定文件")
    {
        return CALFILE;
    }
    else if(fileName == u8"日志文件")
    {
        return LOGFILE;
    }

    return -1;
}

QString Widget::getIPAdressFromReply(QNetworkReply *reply)
{
    auto urlStr = reply->url().toString();

    auto indexAt = urlStr.indexOf("@");
    auto indexComma = urlStr.indexOf(":",indexAt);

    QString IPAdress;


    if((indexAt != -1) && (indexComma != -1))
    {
        IPAdress = urlStr.mid(indexAt + 1,indexComma - indexAt - 1);
    }

    return IPAdress;
}

QString Widget::getFileNameFromReply(QNetworkReply *reply)
{
    auto urlStr = reply->url().toString();

    auto indexLastSlash = urlStr.lastIndexOf("/");

    QString fileName;

    if(indexLastSlash != -1)
    {
        fileName = urlStr.right(urlStr.length() - indexLastSlash - 1);
    }

    return fileName;
}

qint8 Widget::getFileTypeFromName(const QString &fileName)
{
    if(fileName.contains("LC_FFT"))
    {
        return FFTFILE;
    }
    else if(fileName.contains("LC_RAD"))
    {
        return RADFILE;
    }
    else if(fileName.contains("LC_HOBS"))
    {
        return HOBSFILE;
    }
    else if(fileName.contains("LC_OOBS"))
    {
        return OOBSFILE;
    }
    else if(fileName.contains("LC_ROBS"))
    {
        return ROBSFILE;
    }
    else if(fileName.contains("LC_STA"))
    {
        return STATUSFILE;
    }
    else if(fileName.contains("LC_CAL"))
    {
        return CALFILE;
    }
    else if(fileName.contains("LC_SYS"))
    {
        return LOGFILE;
    }
    else{}

    return -1;

}

qint8 Widget::getUploadType(const QString &IPAdress)
{
    if(IPAdress == m_NationalIPAdress)
    {
        return 3;
    }
    else if(IPAdress == m_ProvinceIPAdress)
    {
        return 2;
    }
    else
    {
        return -1;
    }

    return -1;

}

qint8 Widget::getUploadStatus(QNetworkReply::NetworkError Status)
{
    if(Status == QNetworkReply::NoError)
    {
        return 0;
    }

    return 1;
}

QString Widget::getTableName(qint8 fileType)
{
    QString tableName;

    switch(fileType)
    {
    case FFTFILE:
        tableName = "t_file_fft";
        break;
    case RADFILE:
        tableName = "t_file_rad";
        break;
    case HOBSFILE:
        tableName = "t_file_hobs";
        break;
    case OOBSFILE:
        tableName = "t_file_oobs";
        break;
    case ROBSFILE:
        tableName = "t_file_robs";
        break;
    case STATUSFILE:
        tableName = "t_file_sta";
        break;
    case CALFILE:
        tableName = "t_file_calibration";
        break;
    case LOGFILE:
        tableName = "t_file_log";
        break;
    default:
        break;

    }

    return tableName;
}

QStringList Widget::getRemoteAndLocalPath(qint8 fileType,const QString& IPAdress)
{
    QStringList pathInfo;

    foreach(auto item,m_FTPConfiguration)
    {
        if((item.fileType == fileType) && (item.remoteIP == IPAdress))
        {
            pathInfo << item.localPath << item.remotePath;
            break;
        }
    }

    return pathInfo;
}

void Widget::getFTPConfigFromXML()
{
    QFile file("FTPconfig.xml");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        addLog(QStringList() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm::ss") << QString(u8"FTPconfig.xml打开失败"));
        return;
    }


    QString errorStr;
    int errorLine;
    int errorColumn;


    QDomDocument FTPDOC;

    if (!FTPDOC.setContent(&file, false, &errorStr, &errorLine,&errorColumn))
    {
        addLog(QStringList() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm::ss") << QString(u8"FTPconfig.xml格式有误"));
        file.close();
        return;
    }

    file.close();

    QDomElement root = FTPDOC.documentElement();
    for(QDomNode n = root.firstChild(); !n.isNull(); n = n.nextSibling())
    {
        FTPConfigure tempConfig;

        tempConfig.fileType = n.toElement().attribute("fileType").toUInt();
        tempConfig.remoteIP = n.toElement().attribute("remoteIP");
        tempConfig.userName = n.toElement().attribute("userName");
        tempConfig.password = n.toElement().attribute("password");
        tempConfig.localPath = n.toElement().attribute("localPath");
        tempConfig.remotePath = n.toElement().attribute("remotePath");

        m_FTPConfiguration += tempConfig;
    }

    foreach(auto tempConfig,m_FTPConfiguration)
    {
        auto rowIndex = ui->tableWidget_FTPConfig->rowCount();
        ui->tableWidget_FTPConfig->insertRow(rowIndex);

        ui->tableWidget_FTPConfig->setItem(rowIndex,0,new QTableWidgetItem(getFileTypeName(tempConfig.fileType)));  //配置信息添加到界面上
        ui->tableWidget_FTPConfig->setItem(rowIndex,1,new QTableWidgetItem(tempConfig.remoteIP));
        ui->tableWidget_FTPConfig->setItem(rowIndex,2,new QTableWidgetItem(tempConfig.userName));
        ui->tableWidget_FTPConfig->setItem(rowIndex,3,new QTableWidgetItem(tempConfig.password));
        ui->tableWidget_FTPConfig->setItem(rowIndex,4,new QTableWidgetItem(tempConfig.localPath));
        ui->tableWidget_FTPConfig->setItem(rowIndex,5,new QTableWidgetItem(tempConfig.remotePath));
    }

}

void Widget::setFTPConfigInXML()
{
    QFile file("FTPconfig.xml");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        addLog(QStringList() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm::ss") << QString(u8"FTPconfig.xml打开失败"));
        return;
    }

    QDomDocument FTPDOC;

    QDomProcessingInstruction instruction;
    instruction = FTPDOC.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    FTPDOC.appendChild(instruction);

    QDomElement root = FTPDOC.createElement("config");
    FTPDOC.appendChild(root);

     quint8 index = 0;
     foreach(auto item,m_FTPConfiguration)
     {
         QDomElement element = FTPDOC.createElement(QString("index_%1").arg(++index));

         QDomAttr attr_fileType = FTPDOC.createAttribute("fileType");
         attr_fileType.setValue(QString::number(item.fileType));
         element.setAttributeNode(attr_fileType);

         QDomAttr attr_remoteIP = FTPDOC.createAttribute("remoteIP");
         attr_remoteIP.setValue(item.remoteIP);
         element.setAttributeNode(attr_remoteIP);

         QDomAttr attr_userName = FTPDOC.createAttribute("userName");
         attr_userName.setValue(item.userName);
         element.setAttributeNode(attr_userName);

         QDomAttr attr_password = FTPDOC.createAttribute("password");
         attr_password.setValue(item.password);
         element.setAttributeNode(attr_password);

         QDomAttr attr_localPath = FTPDOC.createAttribute("localPath");
         attr_localPath.setValue(item.localPath);
         element.setAttributeNode(attr_localPath);

         QDomAttr attr_remotePath = FTPDOC.createAttribute("remotePath");
         attr_remotePath.setValue(item.remotePath);
         element.setAttributeNode(attr_remotePath);

         root.appendChild(element);
     }

     QTextStream  out(&file);
     FTPDOC.save(out,4);
     file.close();

}

bool Widget::writeFTPUploadInfoToDataBase(const QList<qint8> uploadInfo,const QString& fileName,const QStringList& pathInfo)
{
    if(uploadInfo.isEmpty() || pathInfo.isEmpty())
    {
        return false;
    }

    auto tableName = getTableName(uploadInfo[0]);

    QString sqlSentence = QString("INSERT INTO %1(update_time, upload_time, file_name, type, upload_mode, status, file_local_path, file_server_path) VALUES(%2,%3,'%4',%5,%6,%7,'%8','%9')")
                                                                        .arg(tableName)
                                                                        .arg(QDateTime::currentDateTime().toSecsSinceEpoch())
                                                                        .arg(QDateTime::currentDateTime().toSecsSinceEpoch())
                                                                        .arg(fileName)
                                                                        .arg(uploadInfo[1])
                                                                        .arg(1)
                                                                        .arg(uploadInfo[2])
                                                                        .arg(pathInfo[0])
                                                                        .arg(pathInfo[1]);



    QSqlQuery query;
    bool ret =  query.exec(sqlSentence);
    if(!ret)
    {
        qDebug() << query.lastError();
    }
    return true;
}

bool Widget::writeFTPUploadStatisticsToDataBase(quint8 FileType, quint8 flag)
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    currentDateTime.setTime(QTime(0,0,0));

    qint64 currentTimeStatmp = currentDateTime.toSecsSinceEpoch();

    QString sqlSentence = QString("SELECT * FROM t_file_upload_info WHERE update_time=%1 AND type=%2").arg(currentTimeStatmp).arg((FileType + 1) * 10);

    QSqlQuery query;
    query.exec(sqlSentence);
    if(query.size() < 1)
    {
        sqlSentence = QString("INSERT INTO t_file_upload_info(update_time,type,num_succ,num_fail) VALUES(%1,%2,%3,%4)").arg(currentTimeStatmp)
                                                                                                                       .arg((FileType + 1) * 10)
                                                                                                                       .arg(0)
                                                                                                                        .arg(0);
        query.exec(sqlSentence);

    }

    QString fieldName;
    quint32 num = 0;

    if(flag == 0)
    {
        fieldName = "num_succ";
    }
    else
    {
        fieldName = "num_fail";
    }

    sqlSentence = QString("SELECT %1 FROM t_file_upload_info WHERE update_time=%2 AND type=%3").arg(fieldName).arg(currentTimeStatmp).arg((FileType + 1) * 10);

    while(query.next())
    {
        num = query.value(fieldName).toUInt();
    }

    num++;

    sqlSentence = QString("UPDATE t_file_upload_info SET %1=%2 WHERE update_time=%3 AND type=%4").arg(fieldName)
                                                                                               .arg(num)
                                                                                               .arg(currentTimeStatmp)
                                                                                               .arg((FileType + 1) * 10);

    query.exec(sqlSentence);
    return true;

}


uint qHash(const FTPConfigure &key)
{
   return QHostAddress(key.remoteIP).toIPv4Address() + key.fileType;
}


FTPUpload::FTPUpload(QObject* parent):QObject(parent),
    m_FTPFileType(0),
    m_updateTime(0),
    m_threadAliveState(false),
    m_runState(false)
{

}

FTPUpload::~FTPUpload()
{

}

void FTPUpload::run()
{
    m_runState = true;
    m_threadAliveState = true;


    while(m_runState)
    {
        if(!m_FTPConfiguration.isEmpty())
        {
            auto item = m_FTPConfiguration.cbegin();
            auto newFileInfo = getNewFile(item->localPath);  //获取到新文件

            if(!newFileInfo.isEmpty())
            {
                auto content = getFileContent(newFileInfo.at(0));  //获取文件内容

                for(item = m_FTPConfiguration.cbegin(); item != m_FTPConfiguration.cend(); item++)
                {

                    QUrl url;
                    url.setScheme("ftp");
                    url.setHost(item->remoteIP);
                    url.setPort(21);
                    url.setUserName(item->userName);
                    url.setPassword(item->password);

                    auto remotePath = item->remotePath;
                    if(remotePath.right(1) != "/")
                    {
                        remotePath.append("/");
                    }

                    remotePath += newFileInfo.at(1);
                    url.setPath(remotePath);

                    emit upload(m_FTPFileType,url,content);
                    emit newFileTime(m_FTPFileType,newFileInfo.at(2));

                }
            }

        }

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

void FTPUpload::wait()
{
    while(m_threadAliveState)
    {
        QThread::msleep(50);
        qApp->processEvents();
    }
}



void FTPUpload::setFTPConfiguration(const QSet<FTPConfigure>& FTPConfiguration)
{
    m_FTPConfiguration.clear();

    FTPConfigure tempConfiguration;

    foreach (tempConfiguration, FTPConfiguration)  //在总的上传配置信息中取出同自己上传类型相同的配置信息
    {
        if(tempConfiguration.fileType == m_FTPFileType)
        {
            m_FTPConfiguration.insert(tempConfiguration);
        }
    }
}



QStringList FTPUpload::getNewFile(const QString &Dir)
{
    QString fullPath;
    QString fileName;
    qint64 updateTime = 0UL;
    QStringList fileInfo;
    bool newFileFlag = false;


    if((m_FTPFileType == FFTFILE) || (m_FTPFileType == STATUSFILE) || (m_FTPFileType == CALFILE) || (m_FTPFileType == LOGFILE))
    {
        QDir dir(Dir);
        if(dir.exists())
        {
            dir.setSorting(QDir::Name | QDir::Type);
            dir.setFilter(QDir::Files | QDir::Readable | QDir::NoDotAndDotDot);
            dir.setNameFilters(getFileFilter());

            auto FileNameList = dir.entryList();
            foreach (fileName, FileNameList)
            {
                fullPath = Dir;
                if(fullPath.right(1) != "/")
                {
                    fullPath += "/";
                }
                fullPath += fileName;

                QFileInfo fileInfo(fullPath);
                updateTime = fileInfo.lastModified().toSecsSinceEpoch();
                if(updateTime > m_updateTime)
                {
                   newFileFlag = true;
                   m_updateTime = updateTime;
                   break;
                }
            }

        }
    }
    else if(m_FTPFileType == RADFILE)
    {
        QDir dir(Dir);
        if(dir.exists())
        {
             dir.setSorting(QDir::Name | QDir::Type);
             dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);

             auto subOneDirStrList = dir.entryList();

             foreach (QString subOneDirStr, subOneDirStrList)
             {
                 QString fullSubOneDirStr = Dir;
                 if(fullSubOneDirStr.right(1) != "/")
                 {
                     fullSubOneDirStr += "/";
                 }
                 fullSubOneDirStr += subOneDirStr;
                 fullSubOneDirStr += "/";

                 QDir subOneDir(fullSubOneDirStr);

                 subOneDir.setSorting(QDir::Name | QDir::Type);
                 subOneDir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);

                 auto subTwoDirStrList = subOneDir.entryList();

                foreach (QString subTwoDirStr, subTwoDirStrList)
                {
                    QString fullSubTwoDirStr = fullSubOneDirStr;
                    fullSubTwoDirStr += subTwoDirStr;
                    fullSubTwoDirStr += "/WNDRAD/";

                     QDir subTwoDir(fullSubTwoDirStr);

                     subTwoDir.setSorting(QDir::Name | QDir::Type);
                     subTwoDir.setFilter(QDir::Files | QDir::Readable | QDir::NoDotAndDotDot);
                     subTwoDir.setNameFilters(getFileFilter());

                     auto FileNameList = subTwoDir.entryList();
                     foreach (fileName, FileNameList)
                     {
                         fullPath = fullSubTwoDirStr;
                         fullPath += fileName;

                         QFileInfo fileInfo(fullPath);
                         updateTime = fileInfo.lastModified().toSecsSinceEpoch();
                         if(updateTime > m_updateTime)
                         {
                             newFileFlag = true;
                             m_updateTime = updateTime;
                             break;
                         }

                     }
                }
             }
        }
    }
    else if((m_FTPFileType == HOBSFILE) || (m_FTPFileType == OOBSFILE) || (m_FTPFileType == ROBSFILE))
    {
        QDir dir(Dir);
        if(dir.exists())
        {
             dir.setSorting(QDir::Name | QDir::Type);
             dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);

             auto subOneDirStrList = dir.entryList();

             foreach (QString subOneDirStr, subOneDirStrList)
             {
                 QString fullSubOneDirStr = Dir;
                 if(fullSubOneDirStr.right(1) != "/")
                 {
                     fullSubOneDirStr += "/";
                 }
                 fullSubOneDirStr += subOneDirStr;
                 fullSubOneDirStr += "/";

                 QDir subOneDir(fullSubOneDirStr);

                 subOneDir.setSorting(QDir::Name | QDir::Type);
                 subOneDir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);

                 auto subTwoDirStrList = subOneDir.entryList();

                 foreach (QString subTwoDirStr, subTwoDirStrList)
                 {
                     QString fullSubTwoDirStr = fullSubOneDirStr;
                     fullSubTwoDirStr += subTwoDirStr;
                     fullSubTwoDirStr += "/WNDOBS/";

                     QString fullDOBSDirStr = fullSubTwoDirStr;
                     if(m_FTPFileType == HOBSFILE)
                     {
                         fullDOBSDirStr += "HOBS/";
                     }
                     else if(m_FTPFileType == OOBSFILE)
                     {
                         fullDOBSDirStr += "OOBS/";
                     }
                     else if(m_FTPFileType == ROBSFILE)
                     {
                        fullDOBSDirStr += "ROBS/";
                     }
                     else
                     {
                         return fileInfo;
                     }

                     QDir subTwoDir(fullDOBSDirStr);

                     subTwoDir.setSorting(QDir::Name | QDir::Type);
                     subTwoDir.setFilter(QDir::Files | QDir::Readable | QDir::NoDotAndDotDot);
                     subTwoDir.setNameFilters(getFileFilter());

                     auto FileNameList = subTwoDir.entryList();
                     foreach (fileName, FileNameList)
                     {
                         fullPath = fullDOBSDirStr;
                         fullPath += fileName;

                         QFileInfo fileInfo(fullPath);
                         updateTime = fileInfo.lastModified().toSecsSinceEpoch();
                         if(updateTime > m_updateTime)
                         {
                             newFileFlag = true;
                             m_updateTime = updateTime;
                             break;
                         }
                     }
                 }
             }


        }
    }
    else{}

    if(newFileFlag)
    {
       fileInfo << fullPath << fileName << QString::number(updateTime);
    }
    return fileInfo;
}

QStringList FTPUpload::getFileFilter()
{
    QStringList fileFilter;
    switch (m_FTPFileType)
    {
    case FFTFILE:
        fileFilter << "*FFT.BIN" << "*FFT.dat";
        break;
    case RADFILE:
        fileFilter << "*RAD.TXT" << "*RAD.txt";
        break;
    case HOBSFILE:
        fileFilter << "*HOBS.TXT" << "*HOBS.txt";
        break;
    case OOBSFILE:
        fileFilter << "*OOBS.TXT" << "*OOBS.txt";
        break;
    case ROBSFILE:
        fileFilter << "*ROBS.TXT" << "*ROBS.txt";
        break;
    case STATUSFILE:
        fileFilter << "*STA.bin" << "*STA.dat";
        break;
    case CALFILE:
        fileFilter << "*CAL.TXT" << "*CAL.txt";
        break;
    case LOGFILE:
        fileFilter << "*LOG.TXT" << "*LOG.txt";
        break;
    default:
        break;
    }

    return fileFilter;
}

QByteArray FTPUpload::getFileContent(const QString &fileName)
{
    QByteArray content;

    QFile File(fileName);
    if(File.open(QFile::ReadOnly))
    {
       content = File.readAll();
    }

    return content;
}




