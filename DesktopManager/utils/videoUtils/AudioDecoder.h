#ifndef AUDIODECODER_H
#define AUDIODECODER_H


#include <Windows.h>
#include <QFile>

#include <QMutex>
#include <QByteArray>
#include "IDecoderBase.h"
#include "AVPacketQueue.h"
#include "AvFrameQueue.h"
#include "syncclock.h"
#include "../audioUtils/AudioUtils.h"
extern "C"{
#include "libavcodec/codec.h"
#include "libswresample/swresample.h"
#include "libavutil/time.h"
}
class AudioDecoder:public IDecoderBase
{
    Q_OBJECT
    SwrContext*     swrContext;
    AudioUtils*     audio;
    qint64          pauseTime;
    qint64          resumeTime;
    qint64          pauseDurationTime;
    AVRational      timeBase;
    bool            decodeFinished;
    int64_t         pts;
    SyncClock*      clock;
    double          volume; //0.0-1.0
public:
    AudioDecoder(AVPacketQueue* _packets,AVFrameQueue* _frames,AVCodecParameters *parm);
    ~AudioDecoder();
    void setAudio(AudioUtils *value);
    void pause();
    void resume();

    void setTimeBase(const AVRational &_timeBase);

    void setClock(SyncClock *_clock);

    void setVolume(double value);

protected:
    void run() override;
    void decode() override;
    int toPCM(AVFrame &frame, char* out);
    void waitResume();
    void chageVolume(char* buf, uint32_t size, uint32_t uRepeat=1, double vol = 1);

signals:
    void displayAudio(qint64);
    void displayResume(qint64);

};

#endif // AUDIODECODER_H
