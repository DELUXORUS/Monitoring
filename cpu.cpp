#include <windows.h>
#include <stdint.h>

#include "cpu.h"


Cpu::Cpu() {}

double Cpu::getLoad()
{
    static FILETIME oldUserTime32 = {}, oldKernelTime32 = {}, oldIdleTime32 = {};
    FILETIME newUserTime32, newKernelTime32, newIdleTime32;

    if (!GetSystemTimes(&newIdleTime32, &newKernelTime32, &newUserTime32))
        return 0;

    auto toUint64 = [](FILETIME ft)
    {
        return (static_cast<uint64_t>(ft.dwHighDateTime) << 32) | ft.dwLowDateTime;
    };

    uint64_t difKernelTime = toUint64(newKernelTime32) - toUint64(oldKernelTime32);
    uint64_t difUserTime = toUint64(newUserTime32) - toUint64(oldUserTime32);

    uint64_t workTime = difKernelTime + difUserTime;
    uint64_t idleTime = toUint64(newIdleTime32) - toUint64(oldIdleTime32);

    double totalUsageCpu = (1 - static_cast<double>(idleTime) / workTime) * 100;

    oldUserTime32 = newUserTime32;
    oldKernelTime32 = newKernelTime32;
    oldIdleTime32 = newIdleTime32;

    return totalUsageCpu;
}
