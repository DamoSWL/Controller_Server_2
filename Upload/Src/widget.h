#ifndef WIDGET_H
#define WIDGET_H


#include <QWidget>
#include <QtNetwork/QtNetwork>
#include <QSet>
#include <QMap>
#include <QString>
#include <QtGlobal>
#include <QHostAddress>
#include <QRunnable>
#include <QStandardItemModel>
#include <QStringList>
#include <QtSql/QtSql>
#include <QtXml/QtXml>


class QNetworkReply;


namespace Ui {
class Widget;
}

class FTPUpload;

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

struct FTPConfigure  //上传配置信息
{
    quint8 fileType;
    QString remoteIP;
    QString userName;
    QString password;
    QString localPath;
    QString remotePath;

    bool operator==(const FTPConfigure& other) const
    {
        return (fileType == other.fileType) && (remoteIP == other.remoteIP);
    }

};

uint qHash(const FTPConfigure &key);


class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();


private slots:
    void on_pushButton_configConfirm_clicked();  //确定添加配置信息
    void on_pushButton_upload_clicked();         //启动线程，开始上传或停止
    void on_pushButton_configCancel_clicked();   //删除配置信息


private slots:
    void upload(quint8 fileType,const QUrl& url, const QByteArray& data);  //执行FTP上传动作
    void replyFinished(QNetworkReply* reply);  //处理文件上传后返回的状态信息
    void addLog(const QStringList& logStr);
    void setNewFileNewInXml(quint8 FileType,const QString& updateTime);  //将上传文件的最新时间写入xml

private:
    void initUI();
    void readInitFromXML();
    bool connectToDataBase();
    QString getFileTypeName(quint8 FileTypeNO);  //从文件类型编号获取文件名
    qint8 getFileTypeFromCNName(const QString& fileName);
    QString getIPAdressFromReply(QNetworkReply* reply);  //从返回状态的URL中获取上传IP地址
    QString getFileNameFromReply(QNetworkReply* reply);  //从返回状态的URL中获取文件名

    qint8 getFileTypeFromName(const QString& fileName);  //从文件名中获取文件类型
    qint8 getUploadType(const QString& IPAdress);  //从IP地址判断上传的是国家级还是省级
    qint8 getUploadStatus(QNetworkReply::NetworkError Status);  //获取上传状态
    QString getTableName(qint8 fileType);
    QStringList getRemoteAndLocalPath(qint8 fileType,const QString& IPAdress);

    void getFTPConfigFromXML();
    void setFTPConfigInXML();


    bool writeFTPUploadInfoToDataBase(const QList<qint8> uploadInfo,const QString& fileName,const QStringList& pathInfo);  //将文件上传信息保存到数据库中
    bool writeFTPUploadStatisticsToDataBase(quint8 FileType,quint8 flag);  //将每月上传统计信息写入数据库中


private:
    Ui::Widget *ui;

    static const quint8 m_FileTypeNum = 8;  //总上传文件类型数

    QNetworkAccessManager *m_accessFTPManager[m_FileTypeNum];
    QSet<FTPConfigure> m_FTPConfiguration;
    QString m_NationalIPAdress;
    QString m_ProvinceIPAdress;

    FTPUpload* m_FTPManager[m_FileTypeNum];  //上传处理类

    QStandardItemModel* m_LogModel;
    QDomDocument m_DOC;




};




//该类遍历文件并上传
class FTPUpload :public QObject, public QRunnable
{
    Q_OBJECT


public:
    explicit FTPUpload(QObject* parent = 0);
     ~FTPUpload();
    // QRunnable interface


public:
    void run() override;  //线程入口函数,遍历并上传文件

    void quit() {m_runState = false;}
    void wait();

    void setFTPConfiguration(const QSet<FTPConfigure>& FTPConfiguration);  //设置FTP上传配置信息
    inline void setFileType(quint8 type) {m_FTPFileType = type;}
    inline void setUpdateTime(qint64 updateTime) {m_updateTime = updateTime;}

signals:
    void upload(quint8 fileType,const QUrl& url, const QByteArray& data);  //信号，将文件上传
    void newFileTime(quint8 FileType,const QString& updateTime);  //信号，发送新的文件的类型和时间
    void addLog(const QStringList& logStr);

private:
    QStringList getNewFile(const QString& Dir);  //遍历文件夹，获取新文件
    QStringList getFileFilter();
    QByteArray getFileContent(const QString& fileName);
    inline QString getCurrentTime(){return QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");}




private:
    quint8 m_FTPFileType;
    qint64 m_updateTime;

    QSet<FTPConfigure> m_FTPConfiguration;

    bool m_threadAliveState;
    bool m_runState;


};

#endif // WIDGET_H
