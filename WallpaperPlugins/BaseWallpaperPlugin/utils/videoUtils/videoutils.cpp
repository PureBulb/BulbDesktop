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
    audioDecoder->setTimeBase(dmt->getAudioTimeBase());
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
    clock = SyncClock();
    audioDecoder->setClock(&clock);
    videoDecoder->setClock(&clock);
    audio->start();
    audioDecoder->setAudio(audio);
    dmt->start();
    QThread::msleep(100);
    audioDecoder->start();

}

QImage VideoUtils::getThumbnail(QString filename)
{
    //./bin/ffmpeg.exe -i D:/test.mp4 -vf select='eq(pict_type\,I)' -vsync 2 -s 1920*1080 -frames 1 -f image2 ./thumbnail/thumbnail-test.jpg
    QString filenameWithoutPath = filename.split("/").back();

    QString workPath = QCoreApplication::applicationDirPath();

    #ifdef QT_DEBUG
        QString exec = "./bin/ffmpeg.exe";
        QString outputFilename = QString("./thumbnail/thumbnail-%2.jpg").arg(filenameWithoutPath);
    #else
        QString exec = "./ffmpeg.exe";
        QString outputFilename = QString("../thumbnail/thumbnail-%2.jpg").arg(filenameWithoutPath);
    #endif
    QStringList cmd;
    cmd<<"-i" <<filename<< "-vf" <<"select=\'eq\(pict_type\\,I)\'"<<"-vsync"<< "2"<< "-s"<<"192*108"<< "-frames" <<"1" <<"-f"<<"image2"<<outputFilename;
    //QString cmd("start ./bin/ffmpeg.exe -i %1 -vf select=\'eq\(pict_type\\,I)\' -vsync 2 -s 192*108 -frames 1 -f image2 %2\n");
    //cmd = cmd.arg(filename).arg(outputFilename);
    if(!QFile(outputFilename).exists()){
        QProcess p;
        int code = p.execute(exec,cmd);
    }
    return QImage(outputFilename);
}

void VideoUtils::deleteThumbnail(QString filename)
{
    QString filenameWithoutPath = filename.split("/").back();
    #ifdef QT_DEBUG
    QString outputFilename = QString("./thumbnail/thumbnail-%2.jpg").arg(filenameWithoutPath);
    #else
    QString outputFilename = QString("../thumbnail/thumbnail-%2.jpg").arg(filenameWithoutPath);
    #endif
    QFile file(outputFilename);
    if(file.exists()){
        file.remove();
    }
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
//    loge(module,msg);
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

void VideoUtils::setVolume(uint8_t volume)
{
    audioDecoder->setVolume(volume/100.0);
}



