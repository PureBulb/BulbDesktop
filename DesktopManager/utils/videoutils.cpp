#include "videoutils.h"

VideoUtils::VideoUtils()
{

    pAudDecodeCtx = nullptr;
    pAvFormatCtx = nullptr;
    nAudStreamIndex = -1;
    nVidStreamIndex = -1;
}

int VideoUtils::pen(QString videoPath)
{
    int result;
    AVCodec*  pVidDecoder = nullptr;
    AVCodec*  pAudDecoder = nullptr;
    //打开文件流
    result =avformat_open_input(&pAvFormatCtx,videoPath.toStdString().c_str(),nullptr,nullptr);
    if(pAvFormatCtx == nullptr){
        loge("videoutils::open","open format error\n");
        return result;
    }
    //获取文件流信息
    result = avformat_find_stream_info(pAvFormatCtx,nullptr);
    if(result ==AVERROR_EOF){

        logd("videoutils::open","reached to file end\n");
        close();
        return -1;
    }
    //遍历流，寻找解码器
    findDecoder(pVidDecoder,pAudDecoder);

    if (pVidDecoder == nullptr && pAudDecoder == nullptr)
    {
        loge("videoutils::open","can not find video or audio stream\n");
        close();
        return -1;
    }
    // seek到第0ms开始读取
    //result = avformat_seek_file(pAvFormatCtx, -1, INT64_MIN, nSeekTime, INT64_MAX, 0);

    // 创建视频解码器并且打开
    if (pVidDecoder != nullptr)
    {
        pVidDecodeCtx = avcodec_alloc_context3(pVidDecoder);
        if (pVidDecodeCtx == nullptr)
        {
            loge("videoutils::open","fail to video avcodec_alloc_context3()\n");
            close();
            return -1;
        }
        result = avcodec_parameters_to_context(pVidDecodeCtx, pAvFormatCtx->streams[nVidStreamIndex]->codecpar);

        result = avcodec_open2(pVidDecodeCtx, nullptr, nullptr);
        if (result != 0)
        {
            loge("videoutils::open",QString("fail to video avcodec_open2(), result=%1\n").arg(result));
            close();
            return -1;
        }
    }


    // 创建音频解码器并且打开
    if (pAudDecoder != nullptr)
    {
        pAudDecodeCtx = avcodec_alloc_context3(pAudDecoder);
        if (pAudDecodeCtx == nullptr)
        {
            loge("videoutils::open","fail to audio avcodec_alloc_context3()\n");
            close();
            return -1;
        }
        result = avcodec_parameters_to_context(pAudDecodeCtx, pAvFormatCtx->streams[nAudStreamIndex]->codecpar);

        result = avcodec_open2(pAudDecodeCtx, nullptr, nullptr);
        if (result != 0)
        {
            loge("videoutils::open",QString("fail to audio avcodec_open2(), result=%1\n").arg(result));
            close();
            return -1;
        }
    }

    return 0;

}

void VideoUtils::findDecoder(AVCodec* &pVideoDecoder, AVCodec* &pAudioDecoder)
{

    for(unsigned int i = 0; i<pAvFormatCtx->nb_streams;i++){
        AVStream * pavStream = pAvFormatCtx->streams[i];
        if(pavStream->codecpar->codec_type == AVMEDIA_TYPE_VIDEO){
            if ((pavStream->codecpar->width <= 0) || (pavStream->codecpar->height <= 0))
            {
                loge("videoutils::open",QString("invalid resolution, streamIndex=%1\n").arg(i));
                continue;
            }
            pVideoDecoder = (AVCodec*) avcodec_find_decoder(pavStream->codecpar->codec_id);  // 找到视频解码器
            if (pVideoDecoder == nullptr)
            {
                loge("videoutils::open","can not find video codec\n");
                continue;
            }

            nVidStreamIndex = (uint32_t)i;
            logd("videoutils::open",QString("pxlFmt=%1, frameSize=%2*%3\n")
                 .arg((int)pavStream->codecpar->format)
                 .arg(pavStream->codecpar->width)
                 .arg( pavStream->codecpar->height)
                 );
        }
        else if(pavStream->codecpar->codec_type == AVMEDIA_TYPE_AUDIO){
            if ((pavStream->codecpar->channels <= 0) || (pavStream->codecpar->sample_rate <= 0))
            {
                loge("videoutils::open",QString("invalid resolution, streamIndex=%1\n").arg(i));
                continue;
            }

            pAudioDecoder = (AVCodec *) avcodec_find_decoder(pavStream->codecpar->codec_id);  // 找到音频解码器
            if (pAudioDecoder == nullptr)
            {
                loge("videoutils::open","can not find Audio codec\n");
                continue;
            }

            nAudStreamIndex = (uint32_t)i;
            logi("videoutils::open",QString("sample_fmt=%1, sampleRate=%2, channels=%3, chnl_layout=%4\n")
                 .arg((int)pavStream->codecpar->format)
                 .arg(pavStream->codecpar->sample_rate)
                 .arg(pavStream->codecpar->channels)
                 .arg(pavStream->codecpar->channel_layout)
                 );
        }
    }
}

void VideoUtils::close()
{
    // 关闭媒体文件解析
      if (pAvFormatCtx != nullptr)
      {
        avformat_close_input(&pAvFormatCtx);
        pAvFormatCtx = nullptr;
      }

      // 关闭视频解码器
      if (pVidDecodeCtx != nullptr)
      {
        avcodec_close(pVidDecodeCtx);
        avcodec_free_context(&pVidDecodeCtx);
        pVidDecodeCtx = nullptr;
      }

      // 关闭音频解码器
      if (pAudDecodeCtx != nullptr)
      {
        avcodec_close(pAudDecodeCtx);
        avcodec_free_context(&pAudDecodeCtx);
        pAudDecodeCtx = nullptr;
      }
      nAudStreamIndex = -1;
      nVidStreamIndex = -1;

}

int VideoUtils::decodePtkToFrame(AVCodecContext *pDecoderCtx, AVPacket *pInPacket, AVFrame **ppOutFrame)
{
    AVFrame*  pOutFrame = nullptr;
      int       res       = 0;

      // 送入要解码的数据包
      res = avcodec_send_packet(pDecoderCtx, pInPacket);
      if (res == AVERROR(EAGAIN)) // 缓冲区已满，要从内部缓冲区读取解码后的音视频帧
      {
        logd("videoutils::decodePtkToFrame","avcodec_send_frame() EAGAIN\n");
      }
      else if (res == AVERROR_EOF) // 数据包送入结束不再送入,但是可以继续可以从内部缓冲区读取解码后的音视频帧
      {
        //    LOGD("<DecodePktToFrame> avcodec_send_frame() AVERROR_EOF\n");
      }
      else if (res < 0)  // 送入输入数据包失败
      {
        loge("videoutils::decodePtkToFrame",QString("fail to avcodec_send_frame(), res=%1\n").arg(res));
        return res;
      }


      // 获取解码后的视频帧或者音频帧
      pOutFrame = av_frame_alloc();
      res       = avcodec_receive_frame(pDecoderCtx, pOutFrame);
      if (res == AVERROR(EAGAIN)) // 当前这次没有解码没有音视频帧输出,需要送入更多的数据包
      {
          logi("videoutils::decodePtkToFrame",QString("no data output\n"));
        av_frame_free(&pOutFrame);
        (*ppOutFrame) = nullptr;
        return 0;
      }
      else if (res == AVERROR_EOF) // 解码缓冲区已经刷新完成,后续不再有音视频帧输出
      {
          logi("videoutils::decodePtkToFrame",QString("avcodec_receive_packet() EOF\n"));
        av_frame_free(&pOutFrame);
        (*ppOutFrame) = nullptr;
        return AVERROR_EOF;
      }
      else if (res < 0)
      {
          loge("videoutils::decodePtkToFrame",QString("fail to avcodec_receive_packet(), res=%1\n").arg(res));
        av_frame_free(&pOutFrame);
        (*ppOutFrame) = nullptr;
        return res;
      }


      (*ppOutFrame) = pOutFrame;
      return 0;
}
