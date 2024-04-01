#include "logdispacher.h"

LogDispacher *LogDispacher::instance = nullptr;
LogDispacher *LogDispacher::getInstance()
{
    if(!instance)
        instance = new LogDispacher;
    return instance;
}

void LogDispacher::logd(QString module, QString msg)
{
    emit sendLogd(module,msg);
}

void LogDispacher::logw(QString module, QString msg)
{
    emit sendLogw(module,msg);
}

void LogDispacher::loge(QString module, QString msg)
{
    emit sendLoge(module,msg);
}

void LogDispacher::logi(QString module, QString msg)
{
    emit sendLogi(module,msg);
}

LogDispacher::LogDispacher() {}
