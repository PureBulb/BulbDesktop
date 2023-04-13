#include "videodecoder.h"
#include "QDebug"

void VideoDecoder::realse()
{
    if(codecContext){
        avcodec_close(codecContext);
        avcodec_free_context(&codecContext);
    }
    if(swsContext)
        sws_freeContext(swsContext);
    startTime = 0;
    swsContext = nullptr;
    codecContext = nullptr;
}

VideoDecoder::VideoDecoder(AVPacketQueue *_packQueue, AVFrameQueue *_frameQueue)
    :packQueue(_packQueue)
    ,frameQueue(_frameQueue)
    ,codecContext(nullptr)
    ,swsContext(nullptr)
    ,startTime(0)
    ,pts(0)
{}

VideoDecoder::~VideoDecoder()
{

}

int VideoDecoder::init(AVCodecParameters *parm, AVRational _timeBase)
{
    //todo: add error emit signal
    pts = 0;
    int res = 0;
    if(parm == nullptr){
        return -1;
    }
    codecContext = avcodec_alloc_context3(NULL);
    if(codecContext == nullptr){
        return -1;
    }
    res = avcodec_parameters_to_context(codecContext,parm);
    if(res<0){
        return -1;
    }
    const AVCodec* codec = avcodec_find_decoder(codecContext->codec_id);
    res = avcodec_open2(codecContext,codec,NULL);
    if(res < 0){
        return -1;
    }
    timeBase = _timeBase;
}

void VideoDecoder::run()
{
    int i = 0;
    int res = 0;
    QString module = "VideoDecoder::run";
    while(!_stop){
        if(_pause){
            QThread::msleep(1);
            continue;
        }
        if(packQueue->isEmpty()){
            QThread::msleep(1);
            continue;
        }

        // 送包
        AVPacket* pkt = packQueue->dequeue(10);
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
        while(true){

            AVFrame* frame = av_frame_alloc();
            res = avcodec_receive_frame(codecContext,frame);
            if(res == 0){
//                avpicture_fill(frame->data,)
                toImage(*frame);
                av_frame_unref(frame);
                av_frame_free(&frame);
                continue;
            }
            else if(res == AVERROR(EAGAIN)){
                //无帧可取
                break;
            }
            else if(res == AVERROR_EOF){
                //完成解码
                return;
            }

        }
    }
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
        int64_t realTime_micro = av_gettime()-startTime;
        double realTime_second = realTime_micro / 1000000.0;
        double pts_second = frame.pts *av_q2d(timeBase);
        while(pts_second>realTime_second){
            QThread::msleep(1);
            realTime_micro = av_gettime()-startTime;
            realTime_second = realTime_micro / 1000000.0;
        }
        //add



//        if(frame.pts>realTime && startTime != 0){
//            quint64 test = realTime-frame.pts;
//            QThread::msleep(test);
//            emit showImage(image);  //发送信号，将次imamge发送到要显示的控件，用paintEvent绘制出来
//        }
//        else if(frame.pts < realTime && startTime != 0){

//        }

        emit showImage(image);
        av_frame_free(&pFrameRGB);
        av_free(rgbBuffer);

    }
}

void VideoDecoder::onDisplayAudio(quint64 _startTime)
{
    startTime = _startTime;
}
