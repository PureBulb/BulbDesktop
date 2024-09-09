#ifndef MONITORWIDGET_H
#define MONITORWIDGET_H

#include "windows.h"
#include <QWidget>
#include <IPendantPlugin.h>
#include <QQmlContext>
#include <QDir>
#include <QQmlEngine>
#include <logdispacher.h>

#include <sysinfoapi.h>
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
    Q_INVOKABLE double getCpuUsage();
    Q_INVOKABLE unsigned long getMemoryRate();
private:
    Ui::MonitorWidget *ui;

    __int64 Filetime2Int64(const FILETIME &ftime);
    __int64 CompareFileTime2(const FILETIME &preTime, const FILETIME &nowTime);

    const int Byte2MB = 1024 * 1024;

};

#endif // MONITORWIDGET_H
