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
        data.setItemClick(getOnItemClickFunc());
        data.setBtn1Click(getOnBtn1ClickFunc());
        data.setBtn2Click(getOnBtn2ClickFunc());
        Everything_GetResultFullPathNameW(i,buff,512);
        data.setDescription(QString::fromWCharArray(buff));
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
}

void EverythingPlugin::onBtn1Click(QueryResult result)
{

}

void EverythingPlugin::onBtn2Click(QueryResult result)
{

}





