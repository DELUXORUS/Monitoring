#include <QPainter>
#include <QFontDatabase>
#include <QDir>

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
        label->setFont(_font);
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

    auto newSize = sizeHint();
    static auto prevSize = sizeHint();

    if (newSize == prevSize &&
        prevSize.width() > 0 &&
        prevSize.height() > 0)
    {
        resize(newSize);
    }

    prevSize = sizeHint();
}

void MonitoringOverlay::_setFont()
{
    int id = QFontDatabase::addApplicationFont(":/fonts/minecraft.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font(family, 12);
    _font = std::move(font);
}

void MonitoringOverlay::_setIcon()
{
    QIcon icon(":/icon/icon.ico");
    setWindowIcon(icon);
}
