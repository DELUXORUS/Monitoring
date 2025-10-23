#include <windows.h>
#include <stdint.h>
#include <intrin.h>

// #include <cpuid.h>

#include "cpu.h"


Cpu::Cpu()
{
    _name = _getName();
}

QString Cpu::getLoad()
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

    QString nameDevice = "CPU";

    return nameDevice + " : " + QString::number(totalUsageCpu, 'f', 2) + "%" " ";
}

QString Cpu::_getName()
{
    std::string strBrand;
    const int sizeInfoType = 3;
    const int sizeCpuInfo = 4;
    int cpuInfo[sizeCpuInfo];
    uint32_t infoType[sizeInfoType] = {0x80000002, 0x80000003, 0x80000004};

    // for (int i = 0; i < sizeInfoType; ++i)
    // {
    for (const auto& curInfoType : infoType)
    {
        // __cpuid(cpuInfo, infoType[i]);
        __cpuid(cpuInfo, curInfoType);
        // for (int j = 0; j < sizeCpuInfo; ++j)
        // {
        for (const auto& curInfoCpu : cpuInfo)
        {
            // uint32_t curInfoCpu = cpuInfo[j];
            char const *ptr = reinterpret_cast<char const *>(&curInfoCpu);
            for (int k = 0; k < sizeof(curInfoCpu); ++k)
            {
                strBrand += ptr[k];
            }
        }
    }

    if (int pos = strBrand.find('\0'); pos != std::string::npos)
    {
        return QString::fromStdString(strBrand.substr(0, pos));
    }


    return QString::fromStdString(strBrand);
}
