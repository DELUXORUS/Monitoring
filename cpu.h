#ifndef CPU_H
#define CPU_H

#include <QString>

#include "specialCpuMonitoring.h"


class Cpu : public SpecialCpuMonitoring
{
public:
    Cpu();
    QString getLoad() override;
    // QString getName() override;
    // double getTemperature() override;
private:
    QString _getName();
private:
    QString _name;
};

#endif // CPU_H
