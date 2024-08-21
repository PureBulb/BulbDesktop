#ifndef ASSISTANTPLUGINUTILS_H
#define ASSISTANTPLUGINUTILS_H

#include <plugins/IAssistantPlugin.h>
#include <QCoreApplication>
#include <QList>

#include "BasePluginUtils.h"


#define ASSISTANT_PLUGINS_DIR "./AssistantPlugins"

class AssistantPluginUtils : public BasePluginUtils
{
private:
    void object2Interface();
    void doNext(QString query);
    QList<IAssistantPlugin *> plugins;
public:
    AssistantPluginUtils(QObject *parent = nullptr);
    QList<QueryResult> query(QString query);

    void load();

    ~AssistantPluginUtils();


    void unload();
    void setSettings(SettingManager *settings);
};

#endif // ASSISTANTPLUGINUTILS_H
