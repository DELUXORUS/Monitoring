#ifndef TEMPERATUREMONITORING_H
#define TEMPERATUREMONITORING_H

#include "deviceMonitoring.h"


class TemperatureMonitoring : public DeviceMonitoring
{
public:
    virtual double getTemperature() = 0;
private:
};

#endif // TEMPERATUREMONITORING_H
