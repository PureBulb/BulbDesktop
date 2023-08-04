#include "AssistantPluginUtils.h"
#include <QtDebug>

void AssistantPluginUtils::object2Interface()
{
    for(auto loader:loaders){

        QObject* instance = loader->instance();
        IAssistantPlugin* plugin = qobject_cast<IAssistantPlugin*>(instance);
        if(plugin){
            qDebug()<<instance->metaObject()->className();
            plugin->loaded();
            int i = 0;
            for(i = 0;i<plugins.size();i++){
                if(plugins.at(i)->getPluginProperty()<=plugin->getPluginProperty()){
                    i++;
                }
                else{
                    break;
                }
            }
            plugins.insert(i,plugin);
        }
        else{
            QMessageBox::information(nullptr,"error","can't cast object instance to plugin instance");
        }
    }
}

AssistantPluginUtils::AssistantPluginUtils(QObject *parent)
    :BasePluginUtils(ASSISTANT_PLUGINS_DIR,parent)
{

}

QList<QueryResult> AssistantPluginUtils::query(QString query)
{
    QList<QueryResult> result;
    for(auto plugin:plugins){
        if(!plugin->query(query,result))
            break;
    }
    return result;
}

void AssistantPluginUtils::load()
{
    BasePluginUtils::load();
    object2Interface();
}



AssistantPluginUtils::~AssistantPluginUtils()
{
    for(auto i :plugins){
        i->unload();
    }
}

void AssistantPluginUtils::unload()
{

}

void AssistantPluginUtils::setSettings(SettingManager *settings)
{

}
