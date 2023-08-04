#include "AVPacketQueue.h"

AVPacketQueue::AVPacketQueue()
{

}

AVPacketQueue::~AVPacketQueue()
{


    while(!queue.isEmpty()){
        AVPacket* res = nullptr;
        queue.dequeue(res,1);
        if(res!=nullptr)
            av_packet_unref(res);
        av_packet_free(&res);
    }
    queue.abort();
}

int AVPacketQueue::enqueue(AVPacket *val)
{
    if(val == nullptr)
        return queue.enqueue(nullptr);
    AVPacket* pack = av_packet_alloc();
    av_packet_move_ref(pack,val);
    return queue.enqueue(pack);
}

AVPacket *AVPacketQueue::dequeue(quint64 timeout)
{
    AVPacket* res = nullptr;
    int code = queue.dequeue(res,timeout);
    if(code == 2){
        //abort
        return nullptr;
    }
    if(code == 3){
        //empty
        return nullptr;
    }
    return res;
}

bool AVPacketQueue::isEmpty()
{
    return queue.isEmpty();
}

bool AVPacketQueue::isAbort()
{
    return queue.isAbort();
}

quint64 AVPacketQueue::size()
{
    return queue.size();
}


