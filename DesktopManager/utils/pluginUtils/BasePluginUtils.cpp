#include "BasePluginUtils.h"
#include <QtDebug>
#include "../../log.h"
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
    for(const auto &dirName:qAsConst(subDir)){
        QString realDir = (path.absolutePath()+"/"+ dirName+"/");
        SetDllDirectoryW(realDir.toStdWString().c_str());
        QString pluginName = realDir+dirName+".dll";
        QFile file(pluginName);
        if (!file.exists())
        {

            QMessageBox::warning(nullptr,"错误信息","找不到文件"+pluginName);
            logErrorHandler("BasePluginUtils::load","can't find file :"+pluginName);
            return ;
        }
        QPluginLoader *pluginLoader = new QPluginLoader(pluginName);


        if(pluginLoader->load()){
            loaders.push_back(pluginLoader);
        }
        else{
            loge("pluginLoader::load",pluginLoader->errorString());
            QMessageBox::information(nullptr,"error",pluginLoader->errorString());
            pluginLoader->deleteLater();
        }
    }

}

void BasePluginUtils::unload()
{
    for(auto loader:qAsConst(loaders)){
        if(!loader->unload()){
            qDebug()<<loader->errorString();
        }
    }
}

BasePluginUtils::~BasePluginUtils()
{
    for(auto loader:qAsConst(loaders)){
        loader->deleteLater();
    }
}

void BasePluginUtils::setSettings(SettingManager *settings)
{

}


void BasePluginUtils::logInfoHandler(const QString &module, const QString &msg)
{
    logi(module,msg);
}

void BasePluginUtils::logDebugHandler(const QString &module, const QString &msg)
{
    logd(module,msg);
}

void BasePluginUtils::logWarringHandler(const QString &module, const QString &msg)
{
    logw(module,msg);
}

void BasePluginUtils::logErrorHandler(const QString &module, const QString &msg)
{
    loge(module,msg);
}
