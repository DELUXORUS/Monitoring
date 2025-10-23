#ifndef MONITORINGOVERLAY_H
#define MONITORINGOVERLAY_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>


class MonitoringOverlay : public QWidget
{

Q_OBJECT

public slots:
    void showUpdateMetrics(QString metrics, int order);
public:
    explicit MonitoringOverlay(QWidget* parent = nullptr)
            : QWidget(parent)
    {
        _mainLayout = new QVBoxLayout(this);
        _mainLayout->setContentsMargins(0, 0, 0, 0);
        _mainLayout->setSpacing(2);
        setLayout(_mainLayout);
        this->setGeometry(0, 0, 0, 0);
        this->setAttribute(Qt::WA_TranslucentBackground);
        this->setAttribute(Qt::WA_TranslucentBackground);  // прозрачный фон
        this->setAttribute(Qt::WA_NoSystemBackground, true); // отключить системный фон
        this->setAttribute(Qt::WA_TransparentForMouseEvents);
        this->setWindowFlags(Qt::WindowStaysOnTopHint |
                             Qt::FramelessWindowHint);
    };
private:
    std::unordered_map<int, QLabel*> _indexLabels;
    QVBoxLayout* _mainLayout;
    QString _style =
    {
         "QLabel {"
         " color: #2fa64a;"
         " font-family: 'Segoe UI Semibold', 'Verdana', 'Arial', sans-serif;"
         " font-size: 14px;"
         " font-weight: bold;"
         " border-radius: 3px;"
         " padding: 2px 2px;"
         "}"
    };
};

#endif // MONITORINGOVERLAY_H
