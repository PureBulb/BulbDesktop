#ifndef PENDANTPLUGIN_H
#define PENDANTPLUGIN_H

#include <QObject>
#include <IPendantPlugin.h>

class PendantPlugin : public IPendantPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PLUGIN_IID FILE "MonitorPlugin.json")
    Q_INTERFACES(PendantPlugin)
public:
    explicit PendantPlugin();
};

#endif // PENDANTPLUGIN_H
