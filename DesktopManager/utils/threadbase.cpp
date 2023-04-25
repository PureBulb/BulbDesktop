#include "threadbase.h"

ThreadBase::ThreadBase()
    :_stop(false)
    ,_pause(false)
    ,finished(false)
{}

ThreadBase::~ThreadBase()
{

}

void ThreadBase::setThreadFinished()
{
    lock();
    finished = true;
    unlock();
}

void ThreadBase::lock()
{
    mutex.lock();
}

void ThreadBase::unlock()
{
    mutex.unlock();
}

void ThreadBase::waitResume()
{
    while(_pause && !_stop){
        msleep(1);
    }
}

void ThreadBase::run()
{

}

void ThreadBase::stop()
{
    lock();
    _stop = true;
    unlock();
}

void ThreadBase::pause()
{
    lock();
    _pause = true;
    unlock();
}

void ThreadBase::resume()
{
    lock();
    _pause = false;
    unlock();
}

void ThreadBase::join()
{
    while(!finished);
}


