#include "AudioDecoder.h"
#include "QtDebug"

void AudioDecoder::setAudio(AudioUtils *value)
{
    audio = value;
}

void AudioDecoder::pause()
{
    IDecoderBase::pause();
    if(decodeFinished){
        lock();
        pauseTime = av_gettime();
        unlock();
    }
}

void AudioDecoder::resume()
{
    IDecoderBase::resume();
    if(decodeFinished){
        lock();
        resumeTime = av_gettime();
        pauseDurationTime = resumeTime - pauseTime;
        emit displayResume(pauseDurationTime);
        unlock();
    }



}

void AudioDecoder::setTimeBase(const AVRational &_timeBase)
{
    lock();
    timeBase = _timeBase;
    unlock();
}

void AudioDecoder::setClock(SyncClock *_clock)
{

    lock();
    clock = _clock;
    unlock();
}

void AudioDecoder::setVolume(double value)
{
    lock();
    volume = value;
    unlock();
}

AudioDecoder::AudioDecoder(AVPacketQueue* _packets,AVFrameQueue* _frames,AVCodecParameters *parm)
    :IDecoderBase(_packets,_frames,parm)
    ,swrContext(nullptr)
    ,audio(nullptr)
    ,pauseTime(0)
    ,resumeTime(0)
    ,pauseDurationTime(0)
    ,timeBase({0,0})
    ,decodeFinished(false)
    ,pts(AV_NOPTS_VALUE)
    ,clock(nullptr)
    ,volume(1.0)
    ,logInstance(nullptr)

{}

AudioDecoder::~AudioDecoder()
{
    if(swrContext)
        swr_free(&swrContext);
}

void AudioDecoder::run()
{
    setThreadNotFinished();
    if(isInit() && !_stop){
        decode();
    }
    setThreadFinished();

}

void AudioDecoder::decode()
{

    QByteArray buffer;
    QString module = "AudioDecoder::run";
    int res = 0;
    while(!_stop){
//        qDebug()<<"wait resume";
        waitResume();
//         qDebug()<<"wait resume ok---";
        if(packets->isEmpty()){
            msleep(1);
            continue;
        }
        // 送包

        AVPacket* pkt = packets->dequeue(20);
        if(pkt){
            res = avcodec_send_packet(codecContext,pkt);
            if (res < 0) {  // 送入数据包失败
                emit error(module,"send packet failed\n");
                setThreadFinished();
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
        while(!_stop){
            waitResume();
            AVFrame* frame = av_frame_alloc();
            res = avcodec_receive_frame(codecContext,frame);
            if(res == 0){
                frames->enqueue(frame);
                av_frame_unref(frame);
                av_frame_free(&frame);
                frame = nullptr;
                continue;
            }
            else if(res == AVERROR(EAGAIN)){
                av_frame_unref(frame);
                av_frame_free(&frame);
                frame = nullptr;
                //无帧可取
                break;
            }
            else if(res == AVERROR_EOF){
                av_frame_unref(frame);
                av_frame_free(&frame);
                frame = nullptr;
                //完成解码
                lock();
                emit displayAudio(av_gettime());
                decodeFinished = true;
                unlock();

                while(!frames->isEmpty() && !_stop){
                    waitResume();
                    frame = frames->dequeue(1);
                    char out[60000] ={0};
                    double currentPts = frame->pts*av_q2d(timeBase);
                    int len = toPCM(*frame,out);
                    buffer.append(out,len);
                    av_frame_unref(frame);

                    //判断所需要的是否大于空闲空间，进行写入以免造成覆写
                    while(audio->getFree()<audio->getPeriodSize()){
                        QThread::msleep(1);
                    }
                    bool writeResult = audio->writeData(buffer.mid(0,audio->getPeriodSize()));
                    buffer.remove(0,audio->getPeriodSize());
                    if(!writeResult){
                        while(!_stop){}
                    }

                    av_frame_free(&frame);
                }

                return;
            }
            av_frame_unref(frame);
            av_frame_free(&frame);
            frame = nullptr;


        }
    }
}

int AudioDecoder::toPCM(AVFrame &frame,char *out)
{
    lock();
    pts = frame.pts;
    if (!codecContext || !audio)//文件未打开，解码器未打开，无数据
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
        logInstance->loge("AudioDecoder::toPCM",errorBuff);
        mutex.unlock();
        return 0;
    }
    int outsize = av_samples_get_buffer_size(NULL, codecContext->channels,
        len,sampleFmt,1);//对齐会出问题
    if(pts!= AV_NOPTS_VALUE){

        double _pts = frame.pts*av_q2d(timeBase);
        clock->setClock(_pts);

    }
    chageVolume(out,outsize,1,volume);
    unlock();
    return outsize;

}

void AudioDecoder::waitResume()
{
    IDecoderBase::waitResume();

}
//come from https://zhuanlan.zhihu.com/p/258454762
void AudioDecoder::chageVolume(char *buf, uint32_t size, uint32_t uRepeat, double vol)
{
    if (!size)
    {
        return;
    }
    for (int i = 0; i < size; i += 2)
    {
        short wData;
        wData = MAKEWORD(buf[i], buf[i + 1]);
        long dwData = wData;
        for (int j = 0; j < uRepeat; j++)
        {
            dwData = dwData * vol;
            if (dwData < -0x8000)
            {
                dwData = -0x8000;
            }
            else if (dwData > 0x7FFF)
            {
                dwData = 0x7FFF;
            }
        }
        wData = LOWORD(dwData);
        buf[i] = LOBYTE(wData);
        buf[i + 1] = HIBYTE(wData);
    }
}


