#ifndef BASEMONITORINGACTION_H
#define BASEMONITORINGACTION_H

#include <QString>


class BaseMonitoringAction
{
public:
    BaseMonitoringAction() {}
    virtual ~BaseMonitoringAction() {}
    virtual QString getLoad() = 0;
};

#endif // BASEMONITORINGACTION_H
