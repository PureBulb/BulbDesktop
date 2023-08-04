#include "videodecoder.h"
#include "QDebug"



VideoDecoder::VideoDecoder(AVPacketQueue *_packets, AVFrameQueue *_frames, AVCodecParameters *parm)
    :IDecoderBase(_packets,_frames,parm)
    ,swsContext(nullptr)
    ,timeBase({0,0})
    ,pauseDurationTime(0)
    ,pauseTime(0)
{}

VideoDecoder::~VideoDecoder()
{
    if(swsContext)
        sws_freeContext(swsContext);
}
void VideoDecoder::run()
{
    setThreadNotFinished();
    if(isInit()  && !_stop){
        decode();
    }
    setThreadFinished();

}

void VideoDecoder::decode()
{
    int res = 0;
    QString module = "VideoDecoder::run";
    while(!_stop){
        waitResume();
        if(packets->isEmpty()){
            QThread::msleep(1);
            continue;
        }

        // 送包
        AVPacket* pkt = packets->dequeue(10);
        if(pkt){
            res = avcodec_send_packet(codecContext,pkt);
            if (res < 0) {  // 送入数据包失败
                emit error(module,"send packet failed\n");
                return ;
            }
        }
        else{
            res = avcodec_send_packet(codecContext,pkt);
        }
        av_packet_free(&pkt);
        pkt = nullptr;
        //送包后取解码完成的帧
        while(!_stop){
            waitResume();
            AVFrame* frame = av_frame_alloc();
            res = avcodec_receive_frame(codecContext,frame);
            if(res == 0){
//                frames->enqueue(frame);
//                avpicture_fill(frame->data,)
                toImage(*frame);
                av_frame_unref(frame);
                av_frame_free(&frame);
                frame = nullptr;
                continue;
            }
            else if(res == AVERROR(EAGAIN)){
                //无帧可取
                av_frame_unref(frame);
                av_frame_free(&frame);
                frame = nullptr;
                break;
            }
            else if(res == AVERROR_EOF){
                //完成解码

                av_frame_unref(frame);
                av_frame_free(&frame);
                frame = nullptr;
                return;
            }
            av_frame_unref(frame);
            av_frame_free(&frame);
            frame = nullptr;

        }

    }

}

void VideoDecoder::onDisplayAudio(qint64 _startTime)
{
    startTime = _startTime;
}

void VideoDecoder::onDisplayResume(qint64 _pauseDurationTime)
{
    resume();
    lock();
    pauseDurationTime += av_gettime() - pauseTime;
//    pauseDurationTime += _pauseDurationTime;
    unlock();

}

void VideoDecoder::setTimeBase(const AVRational &value)
{
    timeBase = value;
}

void VideoDecoder::pause()
{
    IDecoderBase::pause();
    pauseTime = av_gettime();
}

void VideoDecoder::setClock(SyncClock *_clock)
{
    clock = _clock;
}

void VideoDecoder::toImage(AVFrame &frame)
{
    if(swsContext == nullptr)
        swsContext = sws_getContext(frame.width,frame.height,(enum AVPixelFormat)frame.format,
                                    frame.width,frame.height,AV_PIX_FMT_RGB32,0,0,0,0);
    if(swsContext != nullptr){
        AVFrame* pFrameRGB = av_frame_alloc();
        int numBytes = avpicture_get_size(AV_PIX_FMT_RGB32,frame.width,frame.height);
        uint8_t * rgbBuffer = (uint8_t *) av_malloc(numBytes * sizeof(uint8_t));
        avpicture_fill((AVPicture *) pFrameRGB, rgbBuffer, AV_PIX_FMT_RGB32,frame.width,frame.height);


        int h = sws_scale(swsContext,frame.data,frame.linesize,0,frame.height,pFrameRGB->data,pFrameRGB->linesize);
        QImage tmpImg((uchar *)rgbBuffer,frame.width,frame.height,QImage::Format_RGB32);
        QImage image = tmpImg.copy(); //把图像复制一份 传递给界面显示
//        int64_t realTime_micro = av_gettime()-startTime-pauseDurationTime;
//        double realTime_second = realTime_micro / 1000000.0;
//        double pts_second = frame.pts *av_q2d(timeBase);
//        while(pts_second>realTime_second){
//            QThread::msleep(1);
//            realTime_micro = av_gettime()-startTime-pauseDurationTime;
//            realTime_second = realTime_micro / 1000000.0;
//        }

        double pts = frame.pts *av_q2d(timeBase);
        double diff = pts - clock->getClock();
        while(diff>0){
            msleep(1);
            diff = pts - clock->getClock();
        }
        emit showImage(image);
        av_frame_free(&pFrameRGB);
        av_free(rgbBuffer);

    }
}


