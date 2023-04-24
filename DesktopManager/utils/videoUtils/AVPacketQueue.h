#ifndef SAFEAVPACKETQUEUE_H
#define SAFEAVPACKETQUEUE_H

#include <QObject>
#include "../safequeue.h"
extern "C"{
#include "libavformat/avformat.h"
}
class AVPacketQueue
{

    SafeQueue<AVPacket *> queue;
public:
    AVPacketQueue();
    ~AVPacketQueue();
    int enqueue(AVPacket* val);
    AVPacket* dequeue(quint64 timeout);
    bool isEmpty();
    bool isAbort();

    quint64 size();
};

#endif // SAFEAVPACKETQUEUE_H
