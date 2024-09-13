#ifndef DEECODEBASE_H
#define DEECODEBASE_H

#include <QThread>
extern "C"{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
}
#include "IDecoderBase.h"
#include "AvFrameQueue.h"
#include "AVPacketQueue.h"
#include "../logdispacher.h"
#include "syncclock.h"
class DexmuxThread:public ThreadBase
{
    Q_OBJECT
signals:
    void error(QString module,QString msg);
    void warring(QString module,QString msg);
    void readPacketFinished();
private:
    int audioStreamIndex;
    int videoStreamIndex;
    AVFormatContext *formatContex;
    QString filePath;
    AVPacketQueue *videoPacketQueue;
    AVPacketQueue *audioPacketQueue;
    void close();
public:
    explicit DexmuxThread(const QString &_filePath, AVPacketQueue *_audioPacketQueue, AVPacketQueue *_videoPacketQueue);
    ~DexmuxThread() override;
    int open();
    AVCodecParameters * getAudioCodecParameters();
    AVCodecParameters * getvideoCodecParameters();
    AVRational getVideoTimeBase();
    AVRational getAudioTimeBase();
    ClockType getClockType();
protected:
    void run() override;

};

#endif // DEECODEBASE_H
