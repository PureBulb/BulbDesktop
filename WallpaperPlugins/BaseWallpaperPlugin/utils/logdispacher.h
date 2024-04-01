#ifndef LOGDISPACHER_H
#define LOGDISPACHER_H

#include <QObject>
#include <QString>
class LogDispacher:public QObject
{
    Q_OBJECT
public:
    static LogDispacher* getInstance();
    void logd(QString module,QString msg);
    void logw(QString module,QString msg);
    void loge(QString module,QString msg);
    void logi(QString module,QString msg);

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
