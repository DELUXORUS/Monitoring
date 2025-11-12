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
        _renderReady = 0;
        _mainLayout = new QVBoxLayout(this);
        _mainLayout->setContentsMargins(0, 0, 0, 0);
        _mainLayout->setSpacing(2);
        setLayout(_mainLayout);
        _setFont();
        _setIcon();
        setGeometry(0, 0, 1, 1);
        setAttribute(Qt::WA_TranslucentBackground);
        setAttribute(Qt::WA_TranslucentBackground);  // прозрачный фон
        setAttribute(Qt::WA_NoSystemBackground, true); // отключить системный фон
        setAttribute(Qt::WA_TransparentForMouseEvents);
        setWindowFlags(Qt::WindowStaysOnTopHint |
                             Qt::FramelessWindowHint);
    };
    bool isReady() { return _renderReady; }
private:
    void _setFont();
    void _setIcon();
private:
    bool _renderReady;
    std::unordered_map<int, QLabel*> _indexLabels;
    QVBoxLayout* _mainLayout;
    QFont _font;
    QString _style =
    {
         "QLabel {"
         " color: #2fa64a;"
         " font-size: 14px;"
         "}"
    };
};

#endif // MONITORINGOVERLAY_H
