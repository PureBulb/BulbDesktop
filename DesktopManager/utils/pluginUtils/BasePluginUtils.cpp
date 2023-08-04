#include "BasePluginUtils.h"
#include <QtDebug>

BasePluginUtils::BasePluginUtils(QObject *parent)
    :QObject(parent)
{
}

BasePluginUtils::BasePluginUtils(QString pathName, QObject *parent)
    :QObject(parent)
    ,path(pathName)
{
    subDir =  path.entryList(QDir::Dirs|QDir::NoDot|QDir::NoDotDot);
    qDebug()<<subDir;

}

void BasePluginUtils::load()
{
    for(auto dirName:subDir){
        QString realDir = (path.absolutePath()+"/"+ dirName+"/");
        SetDllDirectoryW(realDir.toStdWString().c_str());
        QString pluginName = realDir+dirName+".dll";
        qDebug()<<realDir;
        qDebug()<<pluginName;
        QFile file(pluginName);
        if (!file.exists())
        {
            QMessageBox::warning(nullptr,"错误信息","找不到文件");
            return ;
        }
        QPluginLoader *pluginLoader = new QPluginLoader(pluginName);


        if(pluginLoader->load()){
            loaders.push_back(pluginLoader);
        }
        else{

            QMessageBox::information(nullptr,"error",pluginLoader->errorString());
            pluginLoader->deleteLater();
        }
    }

}

void BasePluginUtils::unload()
{
    for(auto loader:loaders){
        if(!loader->unload()){
            qDebug()<<loader->errorString();
        }
    }
}

BasePluginUtils::~BasePluginUtils()
{
    for(auto loader:loaders){
        loader->deleteLater();
    }
}

void BasePluginUtils::setSettings(SettingManager *settings)
{

}
