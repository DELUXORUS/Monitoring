#ifndef MONITORING_H
#define MONITORING_H

#include <iostream>

#include "deviceMonitoring.h"


// template <typename T>
class Monitoring
{
public:
    Monitoring(DeviceMonitoring& device) : device_(device) {};
    // Monitoring(T& device) : device_(device) {}
    void getMonitoringDevice();
private:
    DeviceMonitoring& device_;
    // T& device_;
    //IRam* iram_;
    //IGpu* igpu_;

};

#endif // MONITORING_H
