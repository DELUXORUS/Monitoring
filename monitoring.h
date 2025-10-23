#ifndef MONITORING_H
#define MONITORING_H

#include <vector>
#include <mutex>
#include <QApplication>

#include "baseMonitoringAction.h"
#include "specialCpuMonitoring.h"


class Monitoring : public QObject
{

    Q_OBJECT
signals:
    void updateMetrics(QString metrics, int order);
public:
    template <typename... BaseTypeDevice>
    Monitoring(BaseTypeDevice*... args)
    {
        size_t size = sizeof...(args);

        _devicesIndicators.resize(size);

        _devices.reserve(size);
        (_devices.push_back(args), ...);
    }
public:
    void launchDeviceThreads();
private:
    QString _cpuMetrics(SpecialCpuMonitoring* cpu);
    void _distribByType(BaseMonitoringAction* device, int order);
private:
    std::vector<BaseMonitoringAction*> _devices;
    // std::vector<std::vector<double>> _devicesIndicators;
    std::vector<QString> _devicesIndicators;
    std::mutex _m;
};

#endif // MONITORING_H





