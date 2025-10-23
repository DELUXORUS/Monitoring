#include <QApplication>
#include <QObject>

#include "monitoringOverlay.h"
#include "monitoring.h"
#include "cpu.h"
#include "ram.h"
#include "gpu.h"


int main(int argc, char **argv)
{
    Ram ram;
    Cpu cpu;
    Gpu gpu;
    Monitoring monitoring(&cpu, &ram, &gpu);
    QApplication app(argc, argv);
    MonitoringOverlay overlay;
    monitoring.launchDeviceThreads();
    QObject::connect(&monitoring,
                     &Monitoring::updateMetrics,
                     &overlay,
                     &MonitoringOverlay::showUpdateMetrics,
                     Qt::QueuedConnection);
    overlay.show();
    return app.exec();
}

