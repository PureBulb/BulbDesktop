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
class DexmuxThread:public QThread
{
    Q_OBJECT
signals:
    void error(QString module,QString msg);
    void readPacketFinished();
private:
    int audioStreamIndex;
    int videoStreamIndex;
    AVFormatContext *formatContex;
    QString filePath;
    IDecoderBase *audioDecoder;
    IDecoderBase *videoDecoder;
    bool stop;
    bool pause;
    AVPacketQueue *videoPacketQueue;
    AVPacketQueue *audioPacketQueue;
    void close();

public:

    explicit DexmuxThread(QString _filePath, AVPacketQueue *_audioPacketQueue,AVPacketQueue *_videoPacketQueue);
    int open();
    AVCodecParameters * getAudioCodecParameters();
    AVCodecParameters * getvideoCodecParameters();
    AVRational getVideoTimeBase();
    AVRational getAudioTimeBase();
protected:
    void run() override;
//public slots:
//    void onStop();
//    void onPause();
//    void onResume();

};

#endif // DEECODEBASE_H
