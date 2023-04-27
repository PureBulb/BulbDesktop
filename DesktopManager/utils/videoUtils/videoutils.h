#ifndef VIDEOUTILS_H
#define VIDEOUTILS_H

#include <QImage>
#include <QObject>
// 纯c项目在c++ 中使用
extern "C"{
    #include "libavcodec/avcodec.h"
    #include "libavformat/avformat.h"
}

#include "log.h"
#include "../audioUtils/audioutils.h"
#include "DexmuxThread.h"
#include "AudioDecoder.h"
#include "videodecoder.h"
#include "AVPacketQueue.h"
#include "AvFrameQueue.h"
#include "displayworker.h"
#include "syncclock.h"
class VideoUtils:public QObject
{
    Q_OBJECT
public:
    VideoUtils(QString path);
    ~VideoUtils();
    void play();
    static QImage getThumbnail(QString filename);
public slots:
    void stop();
    void pause();
    void resume();
    void onLowError(QString module,QString msg);
    void onVideoDecoderImg(QImage img);
    void videoStart();
    void onDisplayFinished();
    /*
        range:0-100
    */
    void setVolume(uint8_t volume);
signals:
    void error();
    void displayFinished();
    void displayStop();
    void displayResume();
    void displayStart();
    void displayPause();
    void sendDecodeImg(QImage);
private:
    void close();
    DexmuxThread*   dmt;
    AudioDecoder*   audioDecoder;
    VideoDecoder*   videoDecoder;
    AudioUtils*     audio;
    AVPacketQueue   audioPacketQueue;
    AVPacketQueue   videoPacketQueue;
    AVFrameQueue    videoFrameQueue;
    AVFrameQueue    audioFrameQueue;
    bool            _stop;
    SyncClock       clock;

};

#endif // VIDEOUTILS_H
