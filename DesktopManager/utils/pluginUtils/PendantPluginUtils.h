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
#include <QEvent>
#include <QDragEnterEvent>
#include <QDebug>
#include <QMimeData>
#define PENDANT_PLUGINS_DIR "./PendantPlugins"
class DragDropEventHandler :public QObject{
    Q_OBJECT
protected:
    bool eventFilter(QObject *obj, QEvent *event) override{
        if(event->type() == QEvent::DragEnter){
            auto e = static_cast<QDragEnterEvent*>(event);
            if(e->mimeData()->hasFormat("pendant")){
                QString pendantName(e->mimeData()->data("pendant"));
                e->accept();
                return true;
            }
            else{
                e->ignore();
            }
        }
        if (event->type() == QEvent::Drop){
            auto e = static_cast<QDropEvent*>(event);
            e->accept();
            qDebug()<<e->mimeData()->data("pendant");
            emit pendantDrop(e->mimeData()->data("pendant"),e->pos());
            return true;

        }
        return false;
    }
signals:
    void pendantDrop(QString pendantName,QPoint pos);
};
class PendantPluginUtils : public BasePluginUtils
{
    Q_OBJECT
private:
    QHash<QString,IPendantPlugin *> plugins;
    QHash<QString,QImage> icons;
    SettingManager* settingsManager;
    PendantChoseWidget pendantChooseWidget;
    const char PLUGIN_SETTING_NAME[50]= "PendantPluginUtils";
    DragDropEventHandler handler;
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

    void installDragDropHandler(const QVector<QWidget *> &wallpapers);
private slots:
    void onPendantChange(uint64_t id,QRect geometry);
    void onPendantClose(uint64_t id);
    void onDropPendantEvent(QString pendantName,QPoint pos);
};

#endif // PENDANTPLUGINUTILS_H
