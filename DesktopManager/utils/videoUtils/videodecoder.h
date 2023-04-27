#ifndef VIDEODECODER_H
#define VIDEODECODER_H

#include<QImage>

#include "IDecoderBase.h"
#include "AVPacketQueue.h"
#include "AvFrameQueue.h"
#include "syncclock.h"
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
    SwsContext*     swsContext;
    int64_t         startTime;
    AVRational      timeBase;
    qint64          pauseDurationTime;
    qint64          pauseTime;
    qint64          resumeTime;
    SyncClock*      clock;
    void toImage(AVFrame &frame);

public:
    VideoDecoder(AVPacketQueue* _packets,AVFrameQueue* _frames,AVCodecParameters *parm);
    ~VideoDecoder();
    void run() override;
    void decode() override;

    void setTimeBase(const AVRational &value);
    void pause();

    void setClock(SyncClock *_clock);

public slots:
    void onDisplayAudio(qint64 _startTime);
    void onDisplayResume(qint64 _pauseDurationTime);
signals:
    void showImage(QImage);

};

#endif // VIDEODECODER_H
