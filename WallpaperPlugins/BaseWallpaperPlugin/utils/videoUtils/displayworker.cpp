#include "displayworker.h"
#include <QtDebug>
void DisplayWorker::setAudioUtils(AudioUtils *value)
{
    audioUtils = value;
}

void DisplayWorker::setAduioCodecContext(AVCodecContext *value)
{
    aduioCodecContext = value;
}

void DisplayWorker::setVideoCodecContext(AVCodecContext *value)
{
    videoCodecContext = value;
}

void DisplayWorker::run()
{
    while(!audioFrames->isEmpty() || !videoFrames->isEmpty()){

    }
}




DisplayWorker::DisplayWorker()
    :aduioCodecContext(nullptr)
    ,videoCodecContext(nullptr)
    ,videoFrames(nullptr)
    ,audioFrames(nullptr)
    ,swrContext(nullptr)
    ,swsContext(nullptr)
    ,audioUtils(nullptr)
    ,clock({0,0,0})
{

}

DisplayWorker::DisplayWorker(AVCodecContext* _audioCodecContext,AVCodecContext* _videoCodecContext, AVFrameQueue *_videoFrames, AVFrameQueue *_audioFrames,AudioUtils* audio)
    :clock({0,0,0})
{
    setAduioCodecContext(_audioCodecContext);
    setVideoCodecContext(_videoCodecContext);
    setVideoFrames(_videoFrames);
    setAudioFrames(_audioFrames);
    setAudioUtils(audio);
    swrContext = nullptr;
    swsContext = nullptr;
}

void DisplayWorker::setVideoFrames(AVFrameQueue *value)
{
    videoFrames = value;
}

void DisplayWorker::setAudioFrames(AVFrameQueue *value)
{
    audioFrames = value;
}


