#ifndef VIDEOUTILS_H
#define VIDEOUTILS_H

#include <QtDebug>

// 纯c项目在c++ 中使用
extern "C"{
    #include "libavcodec/avcodec.h"
    #include "libavformat/avformat.h"
}

#include "log.h"


class VideoUtils
{
public:
    AVFormatContext* pAvFormatCtx    ; // 流文件解析上下文
    AVCodecContext*  pVidDecodeCtx   ; // 视频解码器上下文
    uint32_t         nVidStreamIndex ;      // 视频流索引值
    AVCodecContext*  pAudDecodeCtx   ; // 音频解码器上下文
    uint32_t         nAudStreamIndex ;      // 音频流索引值
    VideoUtils();

    int open(QString videoPath);
    void findDecoder(AVCodec *&pVideoDecoder, AVCodec *&pAudioDecoder);
    void close();

    void readFrames();
    int decodePtkToFrame(AVCodecContext* pDecoderCtx,        // 解码器上下文信息
                          AVPacket*       pInPacket,          // 输入的数据包
                          AVFrame**       ppOutFrame
                          );

};

#endif // VIDEOUTILS_H
