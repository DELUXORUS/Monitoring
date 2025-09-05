#ifndef CPU_H
#define CPU_H

#include "temperatureMonitoring.h"

class Cpu : public TemperatureMonitoring
{
public:
    Cpu();
    double getLoad() override;
    double getTemperature() override;
private:
};

#endif // CPU_H
