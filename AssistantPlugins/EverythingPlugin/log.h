#ifndef LOG_H
#define LOG_H
#include <QFile>
#include <QDateTime>
#include <QtDebug>
// void myLog(QString module,QString msg,QString level);
void myLog(QString module,QString msg,QString level){
    QFile file("runtime.log");
    char logFormatStr[] = "%1 [%2,%3]:%4\n";
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString logStr(logFormatStr);
    file.open(QIODevice::Append);
    logStr = logStr.arg(currentDateTime.toString("yyyy-MM-dd hh:mm:ss")).arg(level).arg(module).arg(msg);
    qDebug()<<logStr;
    file.write(logStr.toStdString().c_str(),logStr.toStdString().size());
    file.close();
}
#define logd(module,msg) myLog(module,msg,"debug")
#define loge(module,msg) myLog(module,msg,"error")
#define logw(module,msg) myLog(module,msg,"warn")
#define logi(module,msg) myLog(module,msg,"info")
#endif // LOG_H
