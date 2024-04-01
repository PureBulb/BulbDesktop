#ifndef VIDEOUTILS_H
#define VIDEOUTILS_H

#include <QImage>
#include <QObject>
#include <QDir>
#include "utils/logdispacher.h"
// 纯c项目在c++ 中使用
extern "C"{
    #include "libavcodec/avcodec.h"
    #include "libavformat/avformat.h"
}
#include <QCoreApplication>

#include "../audioUtils/audioutils.h"
#include "DexmuxThread.h"
#include "AudioDecoder.h"
#include "videodecoder.h"
#include "AVPacketQueue.h"
#include "AvFrameQueue.h"
#include "displayworker.h"
#include "syncclock.h"

#include<QProcess>
// TODO: 1. pre-load video 2. add a display thread
class VideoUtils:public QObject
{
    Q_OBJECT
public:
    VideoUtils(QString path);
    ~VideoUtils();
    void play();
    static QImage getThumbnail(QString filename);
    static void deleteThumbnail(QString filename);
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
    LogDispacher*   logInstance;

};

#endif // VIDEOUTILS_H
