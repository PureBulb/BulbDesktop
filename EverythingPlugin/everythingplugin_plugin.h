#ifndef EVERYTHINGPLUGIN_PLUGIN_H
#define EVERYTHINGPLUGIN_PLUGIN_H

#include <QQmlExtensionPlugin>

class EverythingPluginPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri) override;
};

#endif // EVERYTHINGPLUGIN_PLUGIN_H
