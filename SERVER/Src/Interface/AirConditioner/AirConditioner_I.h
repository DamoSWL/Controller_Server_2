#ifndef AIRCONDITIONER_I_H
#define AIRCONDITIONER_I_H

#include <QObject>
#include <QString>

class IAirConditioner
{
public:

    virtual ~IAirConditioner() {}
    virtual void setControllerIPAdress(const QString& IP) = 0;
    virtual void setHostIPAdress(const QString& IP) = 0;
    virtual void setAirConfig(const QString& configStr) = 0;
    virtual void startListening() = 0;
    virtual void stopListening() = 0;


};



#define AirConditioner_IID  "DD2184E4-1C78-4ADC-A7AD-274146762C4C"
Q_DECLARE_INTERFACE(IAirConditioner, AirConditioner_IID)



#endif


