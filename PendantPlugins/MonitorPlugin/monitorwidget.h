#ifndef MONITORWIDGET_H
#define MONITORWIDGET_H

#include "windows.h"
#include <QWidget>
#include <IPendantPlugin.h>
#include <QQmlContext>
#include <QDir>
#include <QQmlEngine>
#include <logdispacher.h>
#include <QVariantMap>
#include <sysinfoapi.h>
#include <QtConcurrent/QtConcurrent>
namespace Ui {
class MonitorWidget;
}

class MonitorWidget : public BasePendantWidget
{
    Q_OBJECT

public:
    explicit MonitorWidget(QWidget *parent = nullptr);

    ~MonitorWidget();
    void setCity(const QString& city);

    Q_INVOKABLE QString getUsername();
    Q_INVOKABLE double getCpuUsage();
    Q_INVOKABLE unsigned long getMemoryRate();
    Q_INVOKABLE QVariantMap getInfos();
    int test;
private:
    Ui::MonitorWidget *ui;

    __int64 Filetime2Int64(const FILETIME &ftime);
    __int64 CompareFileTime2(const FILETIME &preTime, const FILETIME &nowTime);

    const int Byte2MB = 1024 * 1024;
    QVariantMap infos;

};

#endif // MONITORWIDGET_H
