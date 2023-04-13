#ifndef SAFEQUEUE_H
#define SAFEQUEUE_H

#include <QMutex>
#include <QQueue>
#include <QWaitCondition>

template <typename T>
class SafeQueue
{
protected:
    QQueue<T> queue;
    QWaitCondition conditionLock;
    QMutex mutex;
    bool _abort;
public:
    enum DEQUEUE_TYPE{SUCCESS=1,ABORT=-1,EMPTY=-2};
    bool isAbort(){
        return _abort;
    }
    void abort(){
        mutex.lock();
        _abort = true;
        mutex.unlock();
    }
    DEQUEUE_TYPE enqueue(T val){

        mutex.lock();
        if(_abort)
            return ABORT;
        queue.enqueue(val);
        mutex.unlock();
        conditionLock.wakeOne();
        return SUCCESS;

    }
    DEQUEUE_TYPE  dequeue(T &val,quint64 timeout){
        mutex.lock();
        if(queue.isEmpty())
            conditionLock.wait(&mutex,timeout);

        if(queue.isEmpty()){
            mutex.unlock();
            return EMPTY;
        }
        if(_abort){
            mutex.unlock();
            return ABORT;
        }
        val = queue.dequeue();
        mutex.unlock();
        return SUCCESS;

    }
    bool isEmpty(){
        mutex.lock();
        bool empty = queue.isEmpty();
        mutex.unlock();
        return empty;
    }
    quint64 size(){
        mutex.lock();
        quint64 s = queue.size();
        mutex.unlock();
        return s;
    }

    SafeQueue(){
        _abort = false;
    }
    ~SafeQueue(){

    }
};

#endif // SAFEQUEUE_H
