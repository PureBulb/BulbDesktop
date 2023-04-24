#ifndef AUDIOUTILS_H
#define AUDIOUTILS_H
#include <QMutex>
#include <QIODevice>
#include <QAudioOutput>
#include "../AVConfig.h"
#include "IAudioPlayer.h"

class AudioUtils:public IAudioPlayer
{
public:
    static AudioUtils* getInstance();
    QIODevice *start() override;
    void stop() override;
    void resume() override;
    void pause() override;
    bool writeData(const char * buff,int buffSize);
    bool writeData(QByteArray buff);
    int getFree();
    int getPeriodSize();
    void setVolume(uint32_t value) override;
protected:
    AudioUtils();
    ~AudioUtils();
    static AudioUtils* instance;
    int sampleSize;
    int sampleRate;
    int channels;
    QAudioOutput* output;
    QIODevice* io;
    static QMutex mutex;




};

#endif // AUDIOUTILS_H
