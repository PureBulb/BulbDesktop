#ifndef VIDEODECODER_H
#define VIDEODECODER_H

#include<QImage>

#include "IDecoderBase.h"
#include "AVPacketQueue.h"
#include "AvFrameQueue.h"
extern "C"{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/time.h"
}
class VideoDecoder:public IDecoderBase
{
    Q_OBJECT
private:
    QMutex mutex;
    AVPacketQueue*  packQueue;
    AVFrameQueue*   frameQueue;
    AVCodecContext* codecContext;
    SwsContext*     swsContext;
    uint64_t        startTime;
    uint64_t        pts;
    AVRational timeBase;

    void realse();
public:
    VideoDecoder(AVPacketQueue* _packQueue,AVFrameQueue* _frameQueue);
    ~VideoDecoder();
    int init(AVCodecParameters *parm,AVRational _timeBase);
    void run() override;
    void toImage(AVFrame &frame);
signals:
    void showImage(QImage);
    void displayFinished();
public slots:
    void onDisplayAudio(quint64 _baseTime);

};

#endif // VIDEODECODER_H
