#include "videoutils.h"

VideoUtils::VideoUtils(QString path)
{

    videoFinished = audioFinished = false;
    dmt = new DexmuxThread(path,&audioPacketQueue,&videoPacketQueue);
    audioDecoder = new AudioDecoder(&audioPacketQueue,&audioFrameQueue);
    videoDecoder = new VideoDecoder(&videoPacketQueue,&videoFrameQueue);
    //错误收集
    connect(dmt,&DexmuxThread::error,this,&VideoUtils::onLowError);
    // 转发解码数据
    connect(videoDecoder,&VideoDecoder::showImage,this,&VideoUtils::onVideoDecoderImg);
    //通过audio的播放启动video
    connect(audioDecoder,&AudioDecoder::displayAudio,videoDecoder,&VideoDecoder::onDisplayAudio);
    connect(audioDecoder,&AudioDecoder::displayAudio,this,&VideoUtils::videoStart);
    //判断是否结束
    connect(videoDecoder,&VideoDecoder::displayFinished,this,&VideoUtils::onDecodeFinished);
    connect(audioDecoder,&AudioDecoder::displayFinished,this,&VideoUtils::onDecodeFinished);
    // 绑定暂停停止恢复信号
    connect(this,&VideoUtils::displayStop,dmt,&DexmuxThread::onStop);
    connect(this,&VideoUtils::displayResume,dmt,&DexmuxThread::onResume);
    connect(this,&VideoUtils::displayPause,dmt,&DexmuxThread::onPause);

    connect(this,&VideoUtils::displayStop,videoDecoder,&VideoDecoder::onStop);
    connect(this,&VideoUtils::displayResume,videoDecoder,&VideoDecoder::onResume);
    connect(this,&VideoUtils::displayPause,videoDecoder,&VideoDecoder::onPause);

    connect(this,&VideoUtils::displayStop,audioDecoder,&AudioDecoder::onStop);
    connect(this,&VideoUtils::displayResume,audioDecoder,&AudioDecoder::onResume);
    connect(this,&VideoUtils::displayPause,audioDecoder,&AudioDecoder::onPause);
}

VideoUtils::~VideoUtils()
{
    dmt->deleteLater();
    videoDecoder->terminate();
//    audioDecoder->onStop();
    audioDecoder->destroyed();
    audioDecoder = nullptr;
    AVFrame frame;

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
    emit displayStop();
    audioDecoder->wait();
    videoDecoder->wait();
    dmt->wait();
//    AudioUtils::getInstance()->stop();

}

void VideoUtils::onPause()
{
    emit displayPause();
}

void VideoUtils::onResume()
{
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

void VideoUtils::onDecodeFinished()
{

    emit displayFinished();
}





