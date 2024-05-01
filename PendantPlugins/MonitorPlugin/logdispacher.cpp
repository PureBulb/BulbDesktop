#include "logdispacher.h"

LogDispacher *LogDispacher::instance = nullptr;
LogDispacher *LogDispacher::getInstance()
{
    if(!instance)
        instance = new LogDispacher;
    return instance;
}

void LogDispacher::logd(const QString &module, const QString &msg)
{
    emit sendLogd(module,msg);
}

void LogDispacher::logw(const QString &module, const QString &msg)
{
    emit sendLogw(module,msg);
}

void LogDispacher::loge(const QString &module, const QString &msg)
{
    emit sendLoge(module,msg);
}

void LogDispacher::logi(const QString &module, const QString &msg)
{
    emit sendLogi(module,msg);
}

LogDispacher::LogDispacher() {}
