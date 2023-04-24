#ifndef THREADBASE_H
#define THREADBASE_H

#include <QThread>
#include <QMutex>
class ThreadBase :public QThread
{
    Q_OBJECT
signals:
    void threadStop();
    void threadPause();
    void threadResume();
protected:
    QMutex mutex;
    bool _stop;
    bool _pause;
    bool finished;
    void setThreadFinished();
    void lock();
    void unlock();
    virtual void run() override;
public:
    ThreadBase();
    virtual ~ThreadBase() = 0;

    void stop();
    void pause();
    void resume();
    void join();
};

#endif // THREADBASE_H
