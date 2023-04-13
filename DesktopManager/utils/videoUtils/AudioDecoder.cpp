#include "AudioDecoder.h"
#include "QtDebug"

void AudioDecoder::realse()
{
    if(audioUtils)
        audioUtils->stop();


    if(codecContext){
        avcodec_close(codecContext);
        avcodec_free_context(&codecContext);
    }
    if(swrContext){
        swr_free(&swrContext);
    }
    audioUtils = nullptr;
    codecContext = nullptr;
    swrContext = nullptr;


}

AudioDecoder::AudioDecoder(AVPacketQueue *_packQueue, AVFrameQueue *_frameQueue)
    :packQueue(_packQueue)
    ,frameQueue(_frameQueue)
    ,codecContext(nullptr)
    ,audioUtils(nullptr)
    ,swrContext(nullptr)
{}

int AudioDecoder::init(AVCodecParameters *parm, AVRational _timeBase)
{
    QString module("AudioDecoder::init");

    int res = 0;
    if(parm == nullptr){
        emit error(module,"parm can't be null");
        return -1;
    }
    //获取解码器上下文
    codecContext = avcodec_alloc_context3(NULL);
    if(codecContext == nullptr){
        emit error(module,"avcodec_alloc_context3 failed");
        return -1;
    }
    //复制参数给上下文
    res = avcodec_parameters_to_context(codecContext,parm);
    if(res<0){
        emit error(module,"avcodec_parameters_to_context failed");
        return -1;
    }
    //寻找最佳解码器
    const AVCodec* codec = avcodec_find_decoder(codecContext->codec_id);
    res = avcodec_open2(codecContext,codec,NULL);
    if(res < 0){
        emit error(module,"avcodec_open2 failed");
        return -1;
    }
    timeBase = _timeBase;
    //开启音频播放流
    audioUtils = AudioUtils::getInstance();
    audioUtils->start();
}

AudioDecoder::~AudioDecoder()
{
    realse();
}

void AudioDecoder::run()
{
    int i = 0;
    byteBuff.clear();
    packQueue->dequeue(10);
    QString module = "AudioDecoder::run";
    int res = 0;

    while(!_stop){
        if(_pause){
            QThread::msleep(1);
            continue;
        }
        if(packQueue->isEmpty()){
            //todo:fixed me out the while
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
            //最后发送个空包确保帧都被推出来
            res = avcodec_send_packet(codecContext,pkt);
        }
        av_packet_free(&pkt);
        pkt = nullptr;
        //送包后取解码完成的帧
        while(true){


            AVFrame* frame = av_frame_alloc();
            res = avcodec_receive_frame(codecContext,frame);
            if(res == 0){
//                frameQueue->enqueue(frame);
                char out[60000] ={0};
                int len = toPCM(*frame,out);
                byteBuff.append(out,len);
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
                QFile f("D:/test2.pcm");
                f.open(QIODevice::WriteOnly);
                f.write(byteBuff);
                f.close();
                emit displayAudio(av_gettime());
                while(true){
                    //判断所需要的是否大于空闲空间，进行写入以免造成覆写
                    if(audioUtils->getFree()<audioUtils->getPeriodSize()){
                        QThread::msleep(1);
                        continue;
                    }
                    audioUtils->writeData(byteBuff.mid(0,audioUtils->getPeriodSize()));
                    byteBuff.remove(0,audioUtils->getPeriodSize());

                }
                realse();
                emit displayFinished();
                return;
            }

        }
    }


}

int AudioDecoder::toPCM(AVFrame &frame,char *out)
{
    mutex.lock();
    if (!codecContext || !audioUtils)//文件未打开，解码器未打开，无数据
    {
        mutex.unlock();
        return 0;
    }
    //初始化转换参数
    int outRate = SAMPLE_RATE;
    enum AVSampleFormat sampleFmt = SAMPLE_FMT;
    int inRate = frame.sample_rate;
    int inSample = frame.nb_samples;
    qint64 outCount = 0 ;
    quint64 maxOutCount = 0;
    quint64 channel_layout = av_get_default_channel_layout(codecContext->channels);
    if(swrContext == NULL)
    {
        swrContext = swr_alloc_set_opts(NULL,channel_layout,sampleFmt,
              outRate,
              channel_layout,
              codecContext->sample_fmt,
              codecContext->sample_rate, 0,0);

        swr_init(swrContext);

    }
    outCount = av_rescale_rnd(swr_get_delay(swrContext, outRate) + inSample, outRate, inRate, AV_ROUND_UP);
    outCount = (int64_t) inSample * outRate / inRate +256;  //最有效
//    maxOutCount = av_rescale_rnd(inSample, outRate, inRate, AV_ROUND_UP);
//    if (outCount > maxOutCount) {
//        maxOutCount = outCount;
//    }


    uint8_t  *data[1];
    data[0] = (uint8_t *)out;
    int len = swr_convert(swrContext, data, outCount, (const uint8_t **)frame.extended_data, frame.nb_samples);

    if(len <= 0)
    {
        char errorBuff[256] = {0};
        av_strerror(len,errorBuff,256);
        qDebug()<<errorBuff;
        mutex.unlock();
        return 0;
    }
    int outsize = av_samples_get_buffer_size(NULL, codecContext->channels,
        len,AV_SAMPLE_FMT_FLT,1);//对齐会出问题
    mutex.unlock();
    return outsize;
}
