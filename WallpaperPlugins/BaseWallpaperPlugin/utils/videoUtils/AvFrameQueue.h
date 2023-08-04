#ifndef AVFRAMEQUEUE_H
#define AVFRAMEQUEUE_H

#include "../safequeue.h"
extern "C"{
#include "libavformat/avformat.h"
}
class AVFrameQueue
{
private:
    SafeQueue<AVFrame *> queue;
public:
    AVFrameQueue();
    ~AVFrameQueue();
    int enqueue(AVFrame* val);
    AVFrame* dequeue(quint64 timeout);
    bool isEmpty();
    bool isAbort();
    quint64 size();
};

#endif // AVFRAMEQUEUE_H
