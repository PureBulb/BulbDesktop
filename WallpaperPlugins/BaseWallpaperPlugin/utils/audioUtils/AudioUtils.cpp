#include "AudioUtils.h"
#include <QtDebug>
AudioUtils* AudioUtils::instance = nullptr;
QMutex AudioUtils::mutex;
AudioUtils *AudioUtils::getInstance()
{
    mutex.lock();
    if(instance == nullptr){
        instance = new AudioUtils;
    }
    mutex.unlock();
    return instance;
}

AudioUtils::AudioUtils()
    :sampleSize(SAMPLE_SIZE)
    ,sampleRate(SAMPLE_RATE)
    ,channels(AUDIO_CHANNEL)
    ,output(nullptr)
    ,io(nullptr)
{ }

AudioUtils::~AudioUtils()
{
    stop();
}

QIODevice *AudioUtils::start()
{
    mutex.lock();
    QAudioFormat format;
    format.setChannelCount(channels);
    format.setSampleRate(sampleRate);
    format.setSampleSize(sampleSize);
    format.setCodec("audio/pcm");//解码格式
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);//设置音频类型

//    if(output){
//        output->deleteLater();
//        output = nullptr;
//    }
    if(!output){
        output = new QAudioOutput(format);        
    }
    io = output->start();
    mutex.unlock();
    return io;
}



void AudioUtils::stop()
{
    mutex.lock();
    if(output != nullptr ){
        output->reset();
        output->stop();
        output->deleteLater();
        output = nullptr;
        io = nullptr;
    }
    mutex.unlock();
}

void AudioUtils::resume()
{
    mutex.lock();
    output->resume();
    mutex.unlock();
}

void AudioUtils::pause()
{
    mutex.lock();
    output->suspend();
    mutex.unlock();
}

bool AudioUtils::writeData(const char *buff, int buffSize)
{
    mutex.lock();
    if(!io){
        mutex.unlock();
        return false;
    }
    io->write(buff,buffSize);
    mutex.unlock();
    return true;
}
bool AudioUtils::writeData(QByteArray buff)
{
    // 注意这里一定要将plugin/audio正确导入否则io 请求写入的buffsize为0
    mutex.lock();
    if(!io ){
        mutex.unlock();
        return false;
    }
    io->write(buff);
    mutex.unlock();
    return true;
}
int AudioUtils::getFree()
{

    mutex.lock();
    int size = 0;
    if(output)
        size = output->bytesFree();
    mutex.unlock();
    return size;
}

int AudioUtils::getPeriodSize()
{
    mutex.lock();
    int size = 0;
    if(output)
        size = output->periodSize();
    else
        qDebug()<<"output is null";
    mutex.unlock();
    return size;
}



void AudioUtils::setVolume(uint8_t value)
{
    qreal linearVolume = value/100.0;

    output->setVolume(linearVolume);
}



