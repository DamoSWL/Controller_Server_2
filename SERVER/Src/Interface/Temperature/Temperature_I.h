#ifndef TEMPERATURE_I_H
#define TEMPERATURE_I_H


#include <QObject>
#include <QString>

class IMysqlDB;

class ITemperature
{
public:
    virtual ~ITemperature() {}
    virtual void setIPAdress(const QString& IP) = 0;
    virtual void setMysqlInstance(IMysqlDB* instance) = 0;
    virtual void runMonitor() = 0;
    virtual void endMonitor() = 0;

};



#define Temperature_IID  "61091363-551E-4641-9B55-E5C7F5A04B12"
Q_DECLARE_INTERFACE(ITemperature, Temperature_IID)



#endif
