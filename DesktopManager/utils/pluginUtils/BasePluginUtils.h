#ifndef PLUGINUTILS_H
#define PLUGINUTILS_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QDir>
#include <windows.h>
#include <QPluginLoader>
#include <QMessageBox>

#include "../../SettingManager.h"
class BasePluginUtils:public QObject
{
    Q_OBJECT
protected:
    QDir path;
    QList<QFile> files;
    QStringList subDir;
    QVector<QPluginLoader *> loaders;

public:

    BasePluginUtils(QObject * parent = nullptr);
    BasePluginUtils(QString pathName, QObject * parent = nullptr);

    virtual void load();
    virtual void unload();

    virtual void setSettings(SettingManager * settings);

    virtual ~BasePluginUtils();
};

#endif // PLUGINUTILS_H
