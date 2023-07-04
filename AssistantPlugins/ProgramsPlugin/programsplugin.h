#ifndef PROGRAMSPLUGIN_H
#define PROGRAMSPLUGIN_H

#include <shlobj.h>
#include <QObject>

#include <QtDebug>

#include <QSettings>
#include <QDir>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include <IAssistantPlugin.h>

#include <pinyin.h>

#define DB_NAME "programs_index"
#define TABLE_NAME "programs"
#define _HKEY_LOCAL_MACHINE  "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall"
#define _HKEY_CURRENT_USER  "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall"
#define HKEY_LOCAL_MACHINE3264 "HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall"
class ProgramsPlugin: public QObject,public IAssistantPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PLUGIN_IID FILE "ProgramsPlugin.json")
    Q_INTERFACES(IAssistantPlugin)
private:
    QSqlDatabase db;
    QSettings regMachine;
    QSettings regUser;
    QSettings regMachine3264;
    void programsFromStartMenu(QList<QueryResult> &result);
    void programsFromHKey(QList<QueryResult> &result);
    void findExecAndLinkFromSubDir(QFileInfo info, QList<QueryResult> &result);
    void store(QList<QueryResult> &result);
    void createTable();

public:
    explicit ProgramsPlugin(QObject *parent = nullptr);

    // IAssistantPlugin interface

    bool query(QString queryStr, QList<QueryResult>& result);

    void loaded();

    void unload();

    ~ProgramsPlugin();


    // IAssistantPlugin interface
protected:
    void onItemClick(QueryResult result);
};

#endif // PROGRAMSPLUGIN_H
