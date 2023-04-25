#include "IDecoderBase.h"

IDecoderBase::IDecoderBase()
    :packetQueueInit(false)
    ,frameQueueInit(false)
    ,parmInit(false)

{}

IDecoderBase::IDecoderBase(AVPacketQueue *_packets, AVFrameQueue *_frames, AVCodecParameters *parm)
{
    init(_packets,_frames,parm);
}

void IDecoderBase::setPacketQueue(AVPacketQueue *_packets)
{
    packets = _packets;
    packetQueueInit = true;
}

void IDecoderBase::setFrameQueue(AVFrameQueue *_frames)
{
    frames = _frames;
    frameQueueInit = true;
}

void IDecoderBase::setParameters(AVCodecParameters *parm)
{
//    QString module("AudioDecoder::init");

    int res = 0;
    if(parm == nullptr){
//        emit error(module,"parm can't be null");
        return;
    }
    //获取解码器上下文
    codecContext = avcodec_alloc_context3(NULL);
    if(codecContext == nullptr){
//        emit error(module,"avcodec_alloc_context3 failed");
        return;
    }
    //复制参数给上下文
    res = avcodec_parameters_to_context(codecContext,parm);
    if(res<0){
//        emit error(module,"avcodec_parameters_to_context failed");
        return ;
    }
    //寻找最佳解码器
    const AVCodec* codec = avcodec_find_decoder(codecContext->codec_id);
    res = avcodec_open2(codecContext,codec,NULL);
    if(res < 0){
//        emit error(module,"avcodec_open2 failed");
        return;
    }
    parmInit = true;

}

void IDecoderBase::init(AVPacketQueue *_packets, AVFrameQueue *_frames, AVCodecParameters *parm)
{
    setPacketQueue(_packets);
    setFrameQueue(_frames);
    setParameters(parm);

}

bool IDecoderBase::isInit()
{
    return packetQueueInit && frameQueueInit && parmInit;
}

void IDecoderBase::run()
{

}

void IDecoderBase::setThreadFinished()
{
    ThreadBase::setThreadFinished();
    emit displayFinished();
}

AVCodecContext *IDecoderBase::getCodecContext() const
{
    return codecContext;
}

IDecoderBase::~IDecoderBase()
{
    if(codecContext)
        avcodec_free_context(&codecContext);

}


