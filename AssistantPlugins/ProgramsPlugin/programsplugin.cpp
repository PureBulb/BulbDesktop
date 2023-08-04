#include "programsplugin.h"

void ProgramsPlugin::programsFromStartMenu(QList<QueryResult> &result)
{
    wchar_t buff[512];
    SHGetSpecialFolderPath(nullptr ,buff,CSIDL_COMMON_STARTMENU,0);
    QString startMenuPath = QString::fromWCharArray(buff);
    SHGetSpecialFolderPath(nullptr, buff, CSIDL_PROGRAMS, 0);
    QString programsPath = QString::fromWCharArray(buff);
    qDebug()<<startMenuPath<<"\n"<<programsPath;
    QDir starMenuDir(startMenuPath+"/Programs");
    QDir programsDir(programsPath);
    QFileInfoList infoList = starMenuDir.entryInfoList(QDir::NoDotAndDotDot|QDir::Files|QDir::Executable|QDir::System|QDir::Dirs);
    for(auto i :infoList){
        findExecAndLinkFromSubDir(i,result);
    }
    infoList = programsDir.entryInfoList(QDir::NoDotAndDotDot|QDir::Files|QDir::Executable|QDir::System|QDir::Dirs);
    for(auto i :infoList){
        findExecAndLinkFromSubDir(i,result);
    }
}

void ProgramsPlugin::programsFromHKey(QList<QueryResult> &result)
{
    QStringList keyList = regMachine.childGroups();
    for(auto key:keyList){

        regMachine.beginGroup(key);
        QString displayName = regMachine.value("InstallLocation").toString();
        regMachine.endGroup();
    }
}

void ProgramsPlugin::findExecAndLinkFromSubDir(QFileInfo info, QList<QueryResult> &result)
{

    if(info.isDir()){
        auto infos = QDir(info.dir().path()+"/"+info.fileName()).entryInfoList(QDir::NoDotAndDotDot|QDir::Files|QDir::Executable|QDir::System|QDir::Dirs);
        for(auto i:infos){
            findExecAndLinkFromSubDir(i,result);
        }

    }
    else{
        if(info.isSymLink()|info.isExecutable()){
            QueryResult data;
            data.setType(program);
            data.setTitle(info.fileName());
            data.setDescription(info.absoluteFilePath());
            data.setItemClick(getOnItemClickFunc());
            data.setBtn1Click(getOnBtn1ClickFunc());
            data.setBtn2Click(getOnBtn2ClickFunc());

            result.append(data);
        }
    }

}

void ProgramsPlugin::store(QList<QueryResult> &result)
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db =  QSqlDatabase::database("qt_sql_default_connection");
    else
        db = QSqlDatabase::addDatabase("QSQLITE");
     db.setDatabaseName(DB_NAME);
     if(db.open()){
         qDebug()<<"program index db open success";
         if(!db.tables().contains(TABLE_NAME))
             createTable();
         for(auto i : result){
             QString letter = ChineseLetterHelper::GetPinyins(i.getTitle());

             QString update_sql = QString()+ "replace into "+TABLE_NAME+"(filename,path,pinyin) values(:filename,:path,:pinyin)";
             QSqlQuery query;
             query.prepare(update_sql);
             query.bindValue(":filename",i.getTitle());
             query.bindValue(":path",i.getDescription());
             query.bindValue(":pinyin",(letter!=""?letter:i.getTitle()).toLower());



             if(!query.exec())
             {
                 qDebug() << query.lastError();
             }

         }

     }
}

void ProgramsPlugin::createTable()
{
    const QString sql=QString()+"\
                          CREATE TABLE IF NOT EXISTS  "+TABLE_NAME+" (\
                          id   INTEGER   PRIMARY KEY AUTOINCREMENT NOT NULL,\
                          filename VARCHAR (255) UNIQUE NOT NULL,\
                          path VARCHAR (512)  NOT NULL,\
                          pinyin VARCHAR (255)  NOT NULL\
                          );";
        //QSqlQuery构造前，需要db已打开并连接
        //未指定db或者db无效时使用默认连接进行操作
        QSqlQuery query;

        if(query.exec(sql)){
            qDebug()<<"init table success";
        }else{
            //打印sql语句错误信息
            qDebug()<<"init table error"<<query.lastError();
        }
}

ProgramsPlugin::ProgramsPlugin(QObject *parent)
    :QObject(parent)
    ,regMachine(_HKEY_LOCAL_MACHINE,QSettings::NativeFormat)
    ,regUser(_HKEY_CURRENT_USER,QSettings::NativeFormat)
    ,regMachine3264(_HKEY_CURRENT_USER,QSettings::NativeFormat)

{

    pluginProperty = 0;

    // create index
    QList<QueryResult> res;
    programsFromStartMenu(res);
    store(res);

}

void ProgramsPlugin::loaded()
{
    qDebug()<<"programs plugin is loaded";
}

void ProgramsPlugin::unload()
{
    QSqlQuery query;
    if(query.exec(QString()+"drop table "+TABLE_NAME)){
        qDebug()<<query.lastError();
    }
    db.close();
    qDebug()<<"programs plugin is unloaded";
}

ProgramsPlugin::~ProgramsPlugin()
{
    unload();
}

void ProgramsPlugin::onItemClick(QueryResult result)
{
    qDebug()<<"Programs plugin is clciked";
    const QString cmd = QString("%1").arg(result.getDescription());

        // 执行命令
    qDebug()<<cmd.toStdString().c_str();
    ShellExecute(NULL, L"open", cmd.toStdWString().c_str() ,NULL,NULL,SW_SHOWMAXIMIZED);
}

QIcon ProgramsPlugin::getIconFunc(QueryResult result)
{
    QFileIconProvider provider;
    QIcon icon = provider.icon(QFileInfo(result.getDescription()));
    return icon;
}




bool ProgramsPlugin::query(QString queryStr, QList<QueryResult> &result)
{
    //TODO: reg table , link
    if(queryStr.size() == 0){
        return false;
    }
    QSqlQuery query;
    query.prepare("select * from programs where pinyin like :pinyin");
    query.bindValue(":pinyin",QString("%")+queryStr.toLower()+"%");
    int64_t resultCount = 0;
    query.exec();
    while(query.next()){
        QueryResult data;
        data.setTitle(query.value("filename").toString());
        data.setDescription(query.value("path").toString());
        data.setType(program);
        data.setItemClick(getOnItemClickFunc());
        data.setBtn1Click(getOnBtn1ClickFunc());
        data.setBtn2Click(getOnBtn2ClickFunc());
        data.setIconFunc(getGetIconFunc());
        result.append(data);
        resultCount++;
    }
    qDebug()<<"ProgramsPlugin query finished";
    return resultCount>0?false:true; // only return this plugin result
//    return true;  // programs+ next plugin
}
