#include <windows.h>
#include <cmath>

#include "ram.h"


Ram::Ram() {}

QString Ram::getLoad()
{
    MEMORYSTATUSEX memStatus;
    memStatus.dwLength = sizeof(memStatus);
    if (!GlobalMemoryStatusEx(&memStatus))
        return 0;
    // double freeMemory = (static_cast<double>(memStatus.ullTotalPhys) - memStatus.ullAvailPhys) / CONVERT_MB;
    double freeMemory = (static_cast<double>(memStatus.ullTotalPhys) - memStatus.ullAvailPhys) / CONVERT_MB;

    QString nameDevice = "RAM";

    return nameDevice + " : " + QString::number(freeMemory, 'f', 2) + " " + "MB";
}
