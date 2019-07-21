#ifndef STATUSFILE_I_H
#define STATUSFILE_I_H

#include <QObject>
#include <QString>

class IMysqlDB;

class IStatusFile
{
public:
    virtual ~IStatusFile() {}
    virtual void setMysqlInstance(IMysqlDB* instance) = 0;
    virtual void runMonitor() = 0;
    virtual void endMonitor() = 0;


};


#define Status_IID  "B682DD07-976C-41A7-9A79-4972F474F0A7"
Q_DECLARE_INTERFACE(IStatusFile, Status_IID)


#endif
