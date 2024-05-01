#ifndef LOGDISPACHER_H
#define LOGDISPACHER_H

#include <QObject>
#include <QString>
class LogDispacher:public QObject
{
    Q_OBJECT
public:
    static LogDispacher* getInstance();
    void logd(const QString &module, const QString &msg);
    void logw(const QString &module, const QString &msg);
    void loge(const QString &module, const QString &msg);
    void logi(const QString &module, const QString &msg);

private:
    static LogDispacher* instance;
    LogDispacher();
signals:
    void sendLogd(QString module,QString msg);
    void sendLogw(QString module,QString msg);
    void sendLoge(QString module,QString msg);
    void sendLogi(QString module,QString msg);

};

#endif // LOGDISPACHER_H
