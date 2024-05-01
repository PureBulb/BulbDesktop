#include "PendantPluginUtils.h"

PendantPluginUtils::PendantPluginUtils(QObject *parent)
    :BasePluginUtils(PENDANT_PLUGINS_DIR,parent)
{

}

PendantPluginUtils::~PendantPluginUtils()
{

}

void PendantPluginUtils::load()
{
    BasePluginUtils::load();
    object2Interface();
}

void PendantPluginUtils::object2Interface()
{
    foreach(auto loader,loaders){
        QObject *obj = nullptr;
        IPendantPlugin *instance = nullptr;
        obj = loader->instance();
        instance = qobject_cast<IPendantPlugin*>(obj);
        if(instance){
            QString pluginName = loader->metaData().value("MetaData").toObject().value("plugin-name").toString();
            plugins.insert(pluginName,instance);


            //绑定日志功能
            connect(instance,&IPendantPlugin::reportDebug,this,&BasePluginUtils::logDebugHandler);
            connect(instance,&IPendantPlugin::reportInfo,this,&BasePluginUtils::logInfoHandler);
            connect(instance,&IPendantPlugin::reportWarring,this,&BasePluginUtils::logWarringHandler);
            connect(instance,&IPendantPlugin::reportError,this,&BasePluginUtils::logErrorHandler);

            instance->loaded();
        }

    }
}

void PendantPluginUtils::startEditorMode()
{
    foreach (auto plugin, plugins) {
        plugin->startEditMode();
    }
}

void PendantPluginUtils::stopEditorMode()
{
    foreach (auto plugin, plugins) {
        plugin->endEditMode();
    }
}

BasePendantWidget *PendantPluginUtils::newPendant(QString pluginName, int x, int y, int w, int h)
{
    return plugins[pluginName]->createNewWidget(x,y,w,h);
}
