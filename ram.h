#ifndef RAM_H
#define RAM_H

#include <QString>

#include "baseMonitoringAction.h"


#define CONVERT_MB (1024 * 1024)


class Ram : public BaseMonitoringAction
{
public:
    Ram();
    QString getLoad() override;
};

#endif // RAM_H
