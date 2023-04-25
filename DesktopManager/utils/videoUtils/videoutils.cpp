#include "videoutils.h"

VideoUtils::VideoUtils(QString path)
    :_stop(false)
{

    audio = AudioUtils::getInstance();
    dmt = new DexmuxThread(path,&audioPacketQueue,&videoPacketQueue);
    dmt->open();
    audioDecoder = new AudioDecoder(&audioPacketQueue,&audioFrameQueue,dmt->getAudioCodecParameters());
    videoDecoder = new VideoDecoder(&videoPacketQueue,&videoFrameQueue,dmt->getvideoCodecParameters());
    videoDecoder->setTimeBase(dmt->getVideoTimeBase());
    //
    connect(videoDecoder,&VideoDecoder::displayFinished,this,&VideoUtils::onDisplayFinished);
//    connect(audioDecoder,&AudioDecoder::displayFinished,this,&VideoUtils::onDisplayFinished);

    //错误收集
    connect(dmt,&DexmuxThread::error,this,&VideoUtils::onLowError);
    // 转发解码数据
    connect(videoDecoder,&VideoDecoder::showImage,this,&VideoUtils::onVideoDecoderImg);
    //音视频线程同步
    connect(audioDecoder,&AudioDecoder::displayAudio,videoDecoder,&VideoDecoder::onDisplayAudio);
    connect(audioDecoder,&AudioDecoder::displayAudio,this,&VideoUtils::videoStart);
    connect(audioDecoder,&AudioDecoder::displayResume,videoDecoder,&VideoDecoder::onDisplayResume);

}

VideoUtils::~VideoUtils()
{
//    stop();
}

void VideoUtils::play()
{
    audio->start();
    audioDecoder->setAudio(audio);
    dmt->start();
    QThread::msleep(100);
    audioDecoder->start();

}

void VideoUtils::stop()
{
    audioDecoder->stop();
    videoDecoder->stop();
    dmt->stop();
    audioDecoder->join();
    videoDecoder->join();
    dmt->join();
    audioDecoder->deleteLater();
    videoDecoder->deleteLater();
    dmt->deleteLater();
    audioDecoder = nullptr;
    videoDecoder = nullptr;
    dmt = nullptr;
    audio->stop();
    _stop = true;

    emit displayStop();
}

void VideoUtils::pause()
{
    audioDecoder->pause();
    videoDecoder->pause();
    dmt->pause();
    emit displayPause();
}

void VideoUtils::resume()
{
    audioDecoder->resume();
    videoDecoder->resume();
    dmt->resume();
    emit displayResume();
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

void VideoUtils::onDisplayFinished()
{
    if(!_stop)
        emit displayFinished();
}



