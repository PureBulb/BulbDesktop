#ifndef LOG_H
#define LOG_H
#include <QFile>
#include <QDateTime>
#include <QtDebug>
void myLog(QString module,QString msg,QString level);

#define logd(module,msg) myLog(module,msg,"debug")
#define loge(module,msg) myLog(module,msg,"error")
#define logw(module,msg) myLog(module,msg,"warn")
#define logi(module,msg) myLog(module,msg,"info")
#endif // LOG_H
