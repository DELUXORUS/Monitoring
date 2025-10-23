#include <thread>

#include "monitoring.h"
#include "threadGuard.h"
#include "specialCpuMonitoring.h"


QString Monitoring::_cpuMetrics(SpecialCpuMonitoring* cpu)
{
    // QString brand = cpu->getName();
    // QString result;
    // result += brand;
    // return result + " ";
    return " ";
}

void Monitoring::_distribByType(BaseMonitoringAction* device, int order)
{
    SpecialCpuMonitoring* cpu = dynamic_cast<SpecialCpuMonitoring*>(device);

    while (true)
    {
        QString curDevInfo;
        curDevInfo = device->getLoad();
        // std::cout << "order: " << order << std::endl;

        if (cpu != nullptr)
        {
            curDevInfo += _cpuMetrics(cpu);
        }

        {
            _devicesIndicators[order] = curDevInfo;
            emit updateMetrics(_devicesIndicators[order], order);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void Monitoring::launchDeviceThreads()
{
    std::vector<ThreadGuard> threads;

    int order = 0;
    for (BaseMonitoringAction* curDevice : _devices)
    {
        try
        {
            ThreadGuard tg(std::thread(&Monitoring::_distribByType, this, curDevice, order));
            threads.push_back(std::move(tg));
        }
        catch (...)
        {
            throw std::runtime_error("Couldn't allocate a thread!");
        }

        ++order;
    }

    // int running = 1;
    // while (running)
    // {
    //     int order = 0;

    //     {
    //         std::unique_lock<std::mutex> lock(_m);
    //         for (const double metrics : _devicesIndicators[order])
    //         {
    //             overlay.outMetrics(metrics);
    //         }

    //         ++order;
    //     }

    //     app.processEvents();

    //     if (app.closingDown()) {
    //         running = 0;;
    //     }

    // }
}
