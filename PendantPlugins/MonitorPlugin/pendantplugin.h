#ifndef PENDANTPLUGIN_H
#define PENDANTPLUGIN_H

#include <QObject>
#include <IPendantPlugin.h>
#include <logdispacher.h>
#include <monitorwidget.h>
#include <QDateTime>
#include <QUrl>
class PendantPlugin : public IPendantPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PLUGIN_IID FILE "MonitorPlugin.json")
    Q_INTERFACES(IPendantPlugin)

private:
    LogDispacher* logInstance;
public:
    explicit PendantPlugin();
    void loaded() override;
    BasePendantWidget * createNewWidget(int x, int y, int w, int h, uint64_t id=0) override;
    QImage getIcon() override;
};

#endif // PENDANTPLUGIN_H
