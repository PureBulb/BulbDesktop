#ifndef THREADBASE_H
#define THREADBASE_H

#include <QThread>
#include <QMutex>
#include "logdispacher.h"
class ThreadBase :public QThread
{
    Q_OBJECT
signals:
    void threadStop();
    void threadPause();
    void threadResume();
protected:
    QMutex mutex;
    volatile bool _stop;
    volatile bool _pause;
    volatile bool finished;
    virtual void setThreadFinished();
    virtual void setThreadNotFinished();
    void lock();
    void unlock();
    virtual void waitResume();
    virtual void run() override;
public:
    ThreadBase();
    virtual ~ThreadBase();

    virtual void stop();
    virtual void pause();
    virtual void resume();
    virtual void join();
};

#endif // THREADBASE_H
