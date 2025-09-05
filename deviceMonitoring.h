#ifndef LOADMONITORING_H
#define LOADMONITORING_H

class DeviceMonitoring
{
public:
    DeviceMonitoring() {};
    virtual ~DeviceMonitoring() {};
    virtual double getLoad() = 0;
private:

};

#endif // LOADMONITORING_H
