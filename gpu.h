#ifndef GPU_H
#define GPU_H
#include <dxgi1_4.h>
#include <d3dkmthk.h>
#include <QString>
#include <vector>

#include <dxgi1_4.h>
#include <d3dkmthk.h>
#include <QString>
#include <vector>

#include "baseMonitoringAction.h"


class Gpu : public BaseMonitoringAction
{
public:
    Gpu();
    QString getLoad() override;
private:
    struct AdapterInfo
    {
        LUID luid;
        QString name;
        ULONGLONG prevTime;
    };
    std::vector<AdapterInfo> _adapters;
private:
    void _initializeAdapters();
    double _queryAdapterLoad(AdapterInfo &adapter);
};

#endif // GPU_H
