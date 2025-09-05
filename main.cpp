#include <QCoreApplication>
#include <thread>
// #include <iostream>

#include "monitoring.h"
#include "cpu.h"


int main()
{
    //Cpu cpu;
    // Gpu gpu;
    // Ram ram;
    // Monitoring monitoring(cpu, gpu, ram);

    std::thread t1([&]()
    {
        Cpu cpu;
        // Gpu gpu;
        // Ram ram;
        // Monitoring monitoring(cpu, gpu, ram);
        Monitoring monitoring(cpu);

        while(1)
        {
            monitoring.getMonitoringDevice();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    });

    t1.join();

    // while(1)
    // {
    //     monitoring.getMonitoringDevice();
    //     std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    // }
}

