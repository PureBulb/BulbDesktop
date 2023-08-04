#ifndef GENERICPLUGIN_H
#define GENERICPLUGIN_H

#include <IAssistantPlugin.h>
#include <Everything.h>
#include <QFileIconProvider>
class EverythingPlugin : public QObject,public IAssistantPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PLUGIN_IID FILE "EverythingPlugin.json")
    Q_INTERFACES(IAssistantPlugin)

public:
    explicit EverythingPlugin(QObject *parent = nullptr);

    // IAssistantPlugin interface


    bool query(QString queryStr, QList<QueryResult>& result);

    void loaded();

    void unload();

    // IAssistantPlugin interface
protected:
    void onItemClick(QueryResult result);
    void onBtn1Click(QueryResult result);
    void onBtn2Click(QueryResult result);


    QIcon getIconFunc(QueryResult result);
};

#endif // GENERICPLUGIN_H
