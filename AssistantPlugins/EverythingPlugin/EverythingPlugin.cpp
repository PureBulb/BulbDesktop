#include "EverythingPlugin.h"
#include <QtDebug>
EverythingPlugin::EverythingPlugin(QObject *parent)
    : QObject(parent)
{
    pluginProperty = 0xff;
}



bool EverythingPlugin::query(QString queryStr, QList<QueryResult> &result)
{
    if(queryStr.size() == 0){
        return true;
    }
    Everything_SetSearchW(queryStr.toStdWString().c_str());
    Everything_SetSort(EVERYTHING_SORT_DATE_MODIFIED_ASCENDING);
    Everything_SetMatchWholeWord(true);
    Everything_QueryW(true);
    for(DWORD i = 0; i< Everything_GetNumResults();i++){
        QueryResult data;
        wchar_t buff[512];
        data.setType(Everything_IsFileResult(i)?file:folder);
        data.setTitle(QString::fromWCharArray(Everything_GetResultFileNameW(i)));
        Everything_GetResultFullPathNameW(i,buff,512);
        data.setDescription(QString::fromWCharArray(buff));
        data.setItemClick(getOnItemClickFunc());
        data.setBtn1Click(getOnBtn1ClickFunc());
        data.setBtn2Click(getOnBtn2ClickFunc());
        data.setIconFunc(getGetIconFunc());

        result.push_back(data);
    }
    qDebug()<<"EverythingPlugin query finished";
    return true;
}

void EverythingPlugin::loaded()
{
    qDebug()<<"Everything plugin is loaded";
}

void EverythingPlugin::unload()
{
    qDebug()<<"Everything plugin is unloaded";
}

void EverythingPlugin::onItemClick(QueryResult result)
{
    qDebug()<<"everything plugin is clciked";
    const QString cmd = QString("%1").arg(result.getDescription());

        // 执行命令
    qDebug()<<cmd.toStdString().c_str();
    ShellExecute(NULL, L"open", cmd.toStdWString().c_str() ,NULL,NULL,SW_SHOWMAXIMIZED);
}

void EverythingPlugin::onBtn1Click(QueryResult result)
{

}

void EverythingPlugin::onBtn2Click(QueryResult result)
{

}

QIcon EverythingPlugin::getIconFunc(QueryResult result)
{
    QFileIconProvider provider;
    QIcon icon = provider.icon(QFileInfo(result.getDescription()));
    return icon;
}





