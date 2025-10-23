#include <Windows.h>
#include <dxgi1_4.h>
#include <d3dkmthk.h>
#include <QString>
#include <QVector>

#include "gpu.h"


Gpu::Gpu()
{
    _initializeAdapters();
}

void Gpu::_initializeAdapters() {
    if (!_adapters.empty())
        return;

    IDXGIFactory1* factory = nullptr;
    if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&factory))))
        return;

    for (UINT i = 0;; ++i) {
        IDXGIAdapter1* adapter = nullptr;
        if (factory->EnumAdapters1(i, &adapter) == DXGI_ERROR_NOT_FOUND)
            break;

        DXGI_ADAPTER_DESC1 desc;
        if (SUCCEEDED(adapter->GetDesc1(&desc))) {
            if ((desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) == 0) {
                AdapterInfo info;
                info.luid     = desc.AdapterLuid;
                info.name     = QString::fromWCharArray(desc.Description);
                info.prevTime = 0;
                _adapters.push_back(info);
            }
        }
        adapter->Release();
    }
    factory->Release();
}

double Gpu::_queryAdapterLoad(AdapterInfo &adapter) {
    D3DKMT_QUERYSTATISTICS stats = {};
    stats.Type             = D3DKMT_QUERYSTATISTICS_NODE;
    stats.AdapterLuid      = adapter.luid;
    stats.QueryNode.NodeId = 0;

    NTSTATUS status = D3DKMTQueryStatistics(&stats);
    if (status == 0) {
        ULONGLONG newTime = stats.QueryResult
                                .NodeInformation.GlobalInformation.RunningTime.QuadPart;

        if (adapter.prevTime != 0) {
            ULONGLONG delta = newTime - adapter.prevTime;
            double usage = (double)delta / 10000000.0 * 100.0;
            if (usage > 100.0) usage = 100.0;
            if (usage < 0.0)   usage = 0.0;
            adapter.prevTime = newTime;
            return usage;
        }
        adapter.prevTime = newTime;
    }
    return 0.0;
}

QString Gpu::getLoad() {
    QStringList lines;
    for (auto &adapter : _adapters) {
        double load = _queryAdapterLoad(adapter);
        lines << QString("%1: %2%").arg(adapter.name).arg(QString::number(load, 'f', 1));
    }

    return lines.join("\n");
}
