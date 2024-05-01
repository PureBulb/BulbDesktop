#ifndef PENDANTPLUGIN_H
#define PENDANTPLUGIN_H

#include <QObject>
#include <IPendantPlugin.h>
#include <logdispacher.h>
#include <monitorwidget.h>.h>
class PendantPlugin : public IPendantPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PLUGIN_IID FILE "MonitorPlugin.json")
    Q_INTERFACES(IPendantPlugin)

private:
    LogDispacher* logInstance;
public:
    explicit PendantPlugin();
    void loaded();
    BasePendantWidget * createNewWidget(int x,int y,int w,int h);
};

#endif // PENDANTPLUGIN_H
