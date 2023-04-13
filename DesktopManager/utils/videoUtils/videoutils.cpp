#include "videoutils.h"

VideoUtils::VideoUtils(QString path)
{

    dmt = new DexmuxThread(path,&audioPacketQueue,&videoPacketQueue);
    audioDecoder = new AudioDecoder(&audioPacketQueue,&audioFrameQueue);
    videoDecoder = new VideoDecoder(&videoPacketQueue,&videoFrameQueue);
    connect(dmt,&DexmuxThread::error,this,&VideoUtils::onLowError);
//    connect(dmt,&DexmuxThread::readPacketFinished,this,&VideoUtils::test);
    connect(videoDecoder,&VideoDecoder::showImage,this,&VideoUtils::onVideoDecoderImg);
    connect(audioDecoder,&AudioDecoder::displayAudio,videoDecoder,&VideoDecoder::onDisplayAudio);
    connect(audioDecoder,&AudioDecoder::displayAudio,this,&VideoUtils::videoStart);
}

VideoUtils::~VideoUtils()
{

}

void VideoUtils::play()
{
    dmt->open();
    audioDecoder->init(dmt->getAudioCodecParameters(),dmt->getAudioTimeBase());
    videoDecoder->init(dmt->getvideoCodecParameters(),dmt->getVideoTimeBase());
    dmt->start();

    QThread::msleep(10);

    audioDecoder->start();




}

void VideoUtils::onStop()
{

}

void VideoUtils::onPause()
{

}

void VideoUtils::onResume()
{

}

void VideoUtils::onLowError(QString module, QString msg)
{
    loge(module,msg);
}

void VideoUtils::onVideoDecoderImg(QImage img)
{
    emit sendDecodeImg(img);
}

void VideoUtils::videoStart()
{
    videoDecoder->start();
}



