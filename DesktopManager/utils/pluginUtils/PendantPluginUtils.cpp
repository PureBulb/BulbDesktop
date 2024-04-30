#include "PendantPluginUtils.h"

PendantPluginUtils::PendantPluginUtils(QObject *parent)
    :BasePluginUtils(PENDANT_PLUGINS_DIR,parent)
{

}

PendantPluginUtils::~PendantPluginUtils()
{

}

void PendantPluginUtils::object2Interface()
{
    // for(auto loader: loaders){
    //     QObject *obj = nullptr;
    //     IPendantPlugin *instance = nullptr;
    //     obj = loader->instance();
    //     instance = qobject_cast<IPendantPlugin*>(obj);
    //     if(instance){
    //         QString pluginName = loader->metaData().value("MetaData").toObject().value("plugin-name").toString();
    //         plugins.insert(pluginName,instance);
    //         instance->loaded();

    //         //绑定日志功能
    //         connect(instance,&IPendantPlugin::reportDebug,this,&PendantPluginUtils::logDebugHandler);
    //         connect(instance,&IPendantPlugin::reportInfo,this,&PendantPluginUtils::logInfoHandler);
    //         connect(instance,&IPendantPlugin::reportWarring,this,&PendantPluginUtils::logWarringHandler);
    //         connect(instance,&IPendantPlugin::reportError,this,&PendantPluginUtils::logErrorHandler);
    //     }

    // }
}
