#include "widgets/mainwindow.h"

#include <QApplication>
#include <utils/pluginUtils/assistantpluginutils.h>
#include "windows.h"

int main(int argc, char *argv[])
{



    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    AssistantPluginUtils utils;
//    utils.load();
//    QList<QueryResult> result = utils.query("huochai");
//    for(auto i : result){

//        const QString cmd = QString("%1").arg(i.description);

//            // 执行命令
//        qDebug()<<cmd.toStdString().c_str();
//        ShellExecute(NULL, L"open", cmd.toStdWString().c_str() ,NULL,NULL,SW_SHOWMAXIMIZED);
//    }


    return a.exec();
}
