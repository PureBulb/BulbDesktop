#ifndef PENDANTPLUGINUTILS_H
#define PENDANTPLUGINUTILS_H

#include <QHash>
#include "BasePluginUtils.h"
#include "../../plugins/IPendantPlugin.h"
#define PENDANT_PLUGINS_DIR "./PendantPlugins"

class PendantPluginUtils : public BasePluginUtils
{
private:
    QHash<QString,IPendantPlugin *> plugins;

public:
    explicit PendantPluginUtils(QObject *parent = nullptr);
    virtual  ~PendantPluginUtils() override;

    void object2Interface();

    void startEditorMode();
    void stopEditorMode();

    void newPendant(QString pluginName,int x,int y,int w,int h);
};

#endif // PENDANTPLUGINUTILS_H
