#ifndef MONITORWIDGET_H
#define MONITORWIDGET_H

#include <QWidget>
#include <IPendantPlugin.h>
#include <QQmlContext>
#include <QDir>
namespace Ui {
class MonitorWidget;
}

class MonitorWidget : public BasePendantWidget
{
    Q_OBJECT

public:
    explicit MonitorWidget(QWidget *parent = nullptr);
    ~MonitorWidget();

    Q_INVOKABLE QString getUsername();

private:
    Ui::MonitorWidget *ui;
};

#endif // MONITORWIDGET_H
