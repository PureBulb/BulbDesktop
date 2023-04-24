#ifndef AUDIODECODER_H
#define AUDIODECODER_H

#include <QFile>

#include <QMutex>
#include <QByteArray>
#include "IDecoderBase.h"
#include "AVPacketQueue.h"
#include "AvFrameQueue.h"
#include "../audioUtils/AudioUtils.h"

class AudioDecoder:public IDecoderBase
{
    Q_OBJECT
    SwrContext*     swrContext;

public:
    AudioDecoder(AVPacketQueue* _packets,AVFrameQueue* _frames,AVCodecParameters *parm);
    ~AudioDecoder();
protected:
    void run() override;
    void decode() override;
    int toPCM(AVFrame &frame, char* out);
signals:
    void displayAudio(quint64);
    void displayFinished();


};

#endif // AUDIODECODER_H
