#ifndef AUDIODECODER_H
#define AUDIODECODER_H

#include <QFile>

#include <QMutex>
#include <QByteArray>
#include "IDecoderBase.h"
#include "AVPacketQueue.h"
#include "AvFrameQueue.h"
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
public:
    AudioDecoder(AVPacketQueue* _packets,AVFrameQueue* _frames,AVCodecParameters *parm);
    ~AudioDecoder();
    void setAudio(AudioUtils *value);

protected:
    void run() override;
    void decode() override;
    int toPCM(AVFrame &frame, char* out);

signals:
    void displayAudio(qint64);

};

#endif // AUDIODECODER_H
