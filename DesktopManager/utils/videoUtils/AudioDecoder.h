#ifndef AUDIODECODER_H
#define AUDIODECODER_H

#include <QFile>

#include <QMutex>
#include <QByteArray>
#include "IDecoderBase.h"
#include "AVPacketQueue.h"
#include "AvFrameQueue.h"
#include "../audioUtils/AudioUtils.h"
#include "../AVConfig.h"
extern "C"{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswresample/swresample.h"
#include "libavutil/time.h"
}
class AudioDecoder:public IDecoderBase
{
    Q_OBJECT
private:
    QMutex mutex;
    AVPacketQueue*  packQueue;
    AVFrameQueue*   frameQueue;
    AVCodecContext* codecContext;
    AudioUtils*     audioUtils;
    SwrContext*     swrContext;
    QByteArray      byteBuff;
    AVRational      timeBase;
    void realse();

public:
    AudioDecoder(AVPacketQueue* _packQueue,AVFrameQueue* _frameQueue);
    ~AudioDecoder();
    int init(AVCodecParameters *parm,AVRational _timeBase);
protected:
    void run() override;
    int toPCM(AVFrame &frame, char* out);
signals:
    void displayAudio(quint64);
    void displayFinished();



};

#endif // AUDIODECODER_H
