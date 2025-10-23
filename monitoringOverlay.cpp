#include <QPainter>

#include "monitoringOverlay.h"


void MonitoringOverlay::showUpdateMetrics(QString metrics, int order)
{
    if (_indexLabels.find(order) != _indexLabels.end())
    {
        _indexLabels[order]->setText(metrics);
    }
    else
    {
        QLabel* label = new QLabel(metrics, this);
        label->setStyleSheet(_style);

        auto searchIndexFromLayout = [&order, this]()
        {
            int realIndex = 0;
            for (const auto& orderInMap : _indexLabels)
            {
                if (order < orderInMap.first)
                {
                    break;
                }

                ++realIndex;
            }
            return realIndex;
        };

        _mainLayout->insertWidget(searchIndexFromLayout(), label, 0, Qt::AlignTop);
        _indexLabels[order] = label;
    }

    if (size() != sizeHint())
    {
        resize(sizeHint());
    }
}

