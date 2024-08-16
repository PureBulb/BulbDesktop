#ifndef PENDANTPLUGINUTILS_H
#define PENDANTPLUGINUTILS_H

#include <QWidget>
#include <QHash>
#include <QScreen>
#include <QJsonArray>
#include <QJsonObject>
#include <QtConcurrent/QtConcurrent>
#include "BasePluginUtils.h"
#include "../../plugins/IPendantPlugin.h"
#define PENDANT_PLUGINS_DIR "./PendantPlugins"

class PendantPluginUtils : public BasePluginUtils
{
private:
    QHash<QString,IPendantPlugin *> plugins;
    SettingManager* settingsManager;
    const char PLUGIN_SETTING_NAME[50]= "PendantPluginUtils";
public:
    explicit PendantPluginUtils(QObject *parent = nullptr);
    virtual  ~PendantPluginUtils() override;

    void load() override;

    void object2Interface();

    void startEditorMode();
    void stopEditorMode();

    void createByConfig(QWidget* parent);
    void createByConfig(const QVector<QWidget*>& wallpapers);
    BasePendantWidget* newPendant(QString pluginName,int x,int y,int w,int h);
    void setSettings(SettingManager* setting) override;
private slots:
    void onPendantChange(uint64_t id,QRect geometry);
    void onPendantClose(uint64_t id);
};

#endif // PENDANTPLUGINUTILS_H
