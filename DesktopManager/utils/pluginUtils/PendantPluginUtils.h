#ifndef PENDANTPLUGINUTILS_H
#define PENDANTPLUGINUTILS_H

#include <QWidget>
#include <QHash>
#include <QScreen>
#include <QJsonArray>
#include <QJsonObject>
#include <QtConcurrent/QtConcurrent>
#include "../../utils/WindAdapterV2.h"
#include "BasePluginUtils.h"
#include "../../plugins/IPendantPlugin.h"
#include "../../widgets/PendantChoseWidget.h"
#define PENDANT_PLUGINS_DIR "./PendantPlugins"

class PendantPluginUtils : public BasePluginUtils
{
private:
    QHash<QString,IPendantPlugin *> plugins;
    QHash<QString,QImage> icons;
    SettingManager* settingsManager;
    PendantChoseWidget pendantChooseWidget;
    const char PLUGIN_SETTING_NAME[50]= "PendantPluginUtils";
public:
    explicit PendantPluginUtils(QObject *parent = nullptr);
    virtual  ~PendantPluginUtils() override;

    void load() override;

    void object2Interface();

    void startEditorMode();
    void stopEditorMode(const QVector<QWidget *> &wallpapers);

    [[deprecated( "use void createByConfig(const QVector<QWidget*>& wallpapers)" )]]\
    void createByConfig(QWidget* parent);
    void createByConfig(const QVector<QWidget*>& wallpapers);
    BasePendantWidget* newPendant(QString pluginName,int x,int y,int w,int h);
    void setSettings(SettingManager* setting) override;
    QHash<QString,QImage> getPluginThumbnails();
    QImage getPluginThumbnailByName(const QString& name);

private slots:
    void onPendantChange(uint64_t id,QRect geometry);
    void onPendantClose(uint64_t id);
};

#endif // PENDANTPLUGINUTILS_H
