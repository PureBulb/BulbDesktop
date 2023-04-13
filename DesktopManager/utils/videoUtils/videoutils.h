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
#include "DexmuxThread.h"
#include "AudioDecoder.h"
#include "videodecoder.h"
#include "AVPacketQueue.h"
#include "AvFrameQueue.h"

class VideoUtils:public QObject
{
    Q_OBJECT
public:
    VideoUtils(QString path);
    ~VideoUtils();
    void play();
public slots:
    void onStop();
    void onPause();
    void onResume();
    void onLowError(QString module,QString msg);
    void onVideoDecoderImg(QImage img);
    void videoStart();

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
    DexmuxThread *dmt;
    AudioDecoder *audioDecoder;
    VideoDecoder *videoDecoder;
    AVPacketQueue audioPacketQueue;
    AVPacketQueue videoPacketQueue;
    AVFrameQueue videoFrameQueue;
    AVFrameQueue audioFrameQueue;
    QWidget *background;
};

#endif // VIDEOUTILS_H
