#ifndef PLUGINUTILS_H
#define PLUGINUTILS_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QDir>
#include <windows.h>
#include <QPluginLoader>
#include <QMessageBox>
class PluginUtils:public QObject
{
    Q_OBJECT
protected:
    QDir path;
    QList<QFile> files;
    QStringList subDir;
    QVector<QPluginLoader *> loaders;

public:

    PluginUtils(QObject * parent = nullptr);
    PluginUtils(QString pathName, QObject * parent = nullptr);

    virtual void load();
    virtual void unload();

    virtual ~PluginUtils();
};

#endif // PLUGINUTILS_H
