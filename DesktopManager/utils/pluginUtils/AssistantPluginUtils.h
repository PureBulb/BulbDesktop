#ifndef ASSISTANTPLUGINUTILS_H
#define ASSISTANTPLUGINUTILS_H

#include <plugins/IAssistantPlugin.h>
#include <algorithm>
#include <QList>

#include "pluginutils.h"


#define ASSISTANT_PLUGINS_DIR "./AssistantPlugins"

class AssistantPluginUtils : public PluginUtils
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
     //todo: context setting manager link
};

#endif // ASSISTANTPLUGINUTILS_H
