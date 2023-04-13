#include "AvFrameQueue.h"

AVFrameQueue::AVFrameQueue()
{

}

int AVFrameQueue::enqueue(AVFrame *val)
{
    AVFrame* frame = av_frame_alloc();
    av_frame_move_ref(frame,val);
    return queue.enqueue(frame);
}

AVFrame *AVFrameQueue::dequeue(quint64 timeout)
{
    AVFrame* res = nullptr;
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


bool AVFrameQueue::isEmpty()
{
    return queue.isEmpty();
}

bool AVFrameQueue::isAbort()
{
    return queue.isAbort();
}

quint64 AVFrameQueue::size()
{
    return queue.size();
}

AVFrameQueue::~AVFrameQueue()
{
    while(!queue.isEmpty()){
        AVFrame* res = nullptr;
        queue.dequeue(res,1);
        av_frame_free(&res);
    }
    queue.abort();
}
