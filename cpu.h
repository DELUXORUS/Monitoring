#ifndef CPU_H
#define CPU_H

#include <QString>

#include "specialCpuMonitoring.h"


class Cpu : public SpecialCpuMonitoring
{
public:
    Cpu();
<<<<<<< HEAD
    QString getLoad() override;
=======
    QString getLoad();
>>>>>>> 22e07e3 (Icons, fonts and v 1.1)
private:
    QString _getName();
private:
    QString _name;
};

#endif // CPU_H
