#include "DexmuxThread.h"
#include <QtDebug>
DexmuxThread::DexmuxThread(const QString &_filePath, AVPacketQueue *_audioPacketQueue,AVPacketQueue *_videoPacketQueue)
    :audioStreamIndex(-1)
    ,videoStreamIndex(-1)
    ,formatContex(nullptr)
    ,filePath(_filePath)

{
    audioPacketQueue = _audioPacketQueue;
    videoPacketQueue = _videoPacketQueue;
}

DexmuxThread::~DexmuxThread()
{

    close();
}

int DexmuxThread::open()
{
    int res = 0;
    QString module("dexmuxThread::open");
    //打开文件
    res = avformat_open_input(&formatContex,filePath.toStdString().c_str(),nullptr,nullptr);
    if(formatContex == nullptr){
        QString msg("can not open file,res=%1");
        msg = msg.arg(res);
        emit error(module,msg);
        return res;
    }
    //寻找流信息
    res = avformat_find_stream_info(formatContex,nullptr);
    if(res == AVERROR_EOF){
        emit error(module,QString("reached file end,res=%1").arg(res));
        close();
        return -1;
    }
    //寻找流
    videoStreamIndex = av_find_best_stream(formatContex,AVMEDIA_TYPE_VIDEO,-1,-1,nullptr,0);
    audioStreamIndex = av_find_best_stream(formatContex,AVMEDIA_TYPE_AUDIO,-1,-1,nullptr,0);
    if(videoStreamIndex < 0 || audioStreamIndex <0){
        emit error(module,QString("viedoStreamIndex=%1,audiostreamIndex=%2").arg(videoStreamIndex,audioStreamIndex));
        close();
        return -1;
    }
    return res;
}
//返回音频解码器参数
AVCodecParameters *DexmuxThread::getAudioCodecParameters()
{

    if(formatContex!=nullptr){

        return formatContex->streams[audioStreamIndex]->codecpar;
    }
    return  nullptr;
}

//返回视频解码器参数
AVCodecParameters *DexmuxThread::getvideoCodecParameters()
{
    if(formatContex!=nullptr){

        return formatContex->streams[videoStreamIndex]->codecpar;
    }
    return  nullptr;
}

AVRational DexmuxThread::getVideoTimeBase()
{
    if(formatContex!=nullptr){

        return formatContex->streams[videoStreamIndex]->time_base;
    }
    return  AVRational{0,0};
}

AVRational DexmuxThread::getAudioTimeBase()
{
    if(formatContex!=nullptr){

        return formatContex->streams[audioStreamIndex]->time_base;
    }
    return  AVRational{0,0};
}
//从流中读取数据包放到队列
void DexmuxThread::run()
{
    QString module("dexmuxThread::run");
    int res = 0;

    while(!_stop){
        waitResume();
        AVPacket *pkt = av_packet_alloc();
        res = av_read_frame(formatContex,pkt);
        if(res<0){
            if(res == AVERROR_EOF){
                setThreadFinished();
                break;
            }
            char errorBuff[256] = {0};
            av_strerror(res,errorBuff,256);
            emit error(module,QString(errorBuff));
            setThreadFinished();
            break;
        }
        if(pkt->stream_index == videoStreamIndex){
            videoPacketQueue->enqueue(pkt);
        }
        else if(pkt->stream_index == audioStreamIndex){
            audioPacketQueue->enqueue(pkt);
        }
        else{
            av_packet_unref(pkt);
        }

        av_packet_free(&pkt);
    }
    //塞一个空包才能够解码结束
    audioPacketQueue->enqueue(nullptr);
    videoPacketQueue->enqueue(nullptr);
    if(!_stop)
        emit readPacketFinished();
    setThreadFinished();
}


void DexmuxThread::close()
{
    if(formatContex!=nullptr){
        avformat_free_context(formatContex);
        formatContex = nullptr;
    }
}
