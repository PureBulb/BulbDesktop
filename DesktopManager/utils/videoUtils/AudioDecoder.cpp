#include "AudioDecoder.h"
#include "QtDebug"


void AudioDecoder::setAudio(AudioUtils *value)
{
    audio = value;
}

AudioDecoder::AudioDecoder(AVPacketQueue* _packets,AVFrameQueue* _frames,AVCodecParameters *parm)
    :IDecoderBase(_packets,_frames,parm)
    ,swrContext(nullptr)
    ,audio(nullptr)
{}

AudioDecoder::~AudioDecoder()
{
}

void AudioDecoder::run()
{
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
        waitResume();
        if(packets->isEmpty()){
            msleep(1);
            continue;
        }
        // 送包

        AVPacket* pkt = packets->dequeue(10);
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
//                frames->enqueue(frame);
                char out[60000] ={0};
                int len = toPCM(*frame,out);
                buffer.append(out,len);
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
                emit displayAudio(av_gettime());
                while(!_stop){
                    waitResume();
                    //判断所需要的是否大于空闲空间，进行写入以免造成覆写
                    if(audio->getFree()<audio->getPeriodSize()){
                        QThread::msleep(1);
                        continue;
                    }
                    audio->writeData(buffer.mid(0,audio->getPeriodSize()));
                    buffer.remove(0,audio->getPeriodSize());

                }


                return;
            }

        }
    }


}

int AudioDecoder::toPCM(AVFrame &frame,char *out)
{
    lock();
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
    unlock();
    return outsize;

}


