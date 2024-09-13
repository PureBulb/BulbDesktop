#ifndef DECODERBASE_H
#define DECODERBASE_H


#include "../threadbase.h"
#include "../AVConfig.h"
#include "AVPacketQueue.h"
#include "AVFrameQueue.h"
extern "C"{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswresample/swresample.h"
#include "libavutil/time.h"
}
#include "syncclock.h"


class IDecoderBase:public ThreadBase
{
    Q_OBJECT
public:
    IDecoderBase();
    IDecoderBase(AVPacketQueue* _packets,AVFrameQueue* _frames,AVCodecParameters *parm);
    virtual ~IDecoderBase();
    virtual void setPacketQueue(AVPacketQueue* _packets);
    virtual void setFrameQueue(AVFrameQueue* _frames);
    virtual void setParameters(AVCodecParameters *parm);
    virtual void init(AVPacketQueue* _packets,AVFrameQueue* _frames,AVCodecParameters *parm);

    AVCodecContext *getCodecContext() const;
    void setClockType(ClockType type);
protected:
    virtual void decode() = 0;
    bool isInit();
    virtual void run() override;
    void setThreadFinished() override;
    bool packetQueueInit;
    bool frameQueueInit;
    bool parmInit;
    AVPacketQueue *packets;
    AVFrameQueue *frames;
    AVCodecContext* codecContext;
    ClockType clockType;
signals:
    void error(QString,QString);
    void decodeFinished();
    void displayFinished();


};

#endif // DECODERBASE_H
