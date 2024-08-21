#ifndef PLUGINUTILS_H
#define PLUGINUTILS_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QDir>
#include <QCoreApplication>
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
public slots:
    void logInfoHandler(const QString &module, const QString &msg);
    void logDebugHandler(const QString &module, const QString &msg);
    void logWarringHandler(const QString &module, const QString &msg);
    void logErrorHandler(const QString &module, const QString &msg);
};

#endif // PLUGINUTILS_H
