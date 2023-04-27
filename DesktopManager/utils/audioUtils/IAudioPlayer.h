#ifndef IAUDIOPLAY_H
#define IAUDIOPLAY_H

#include <QIODevice>
#include "../AVConfig.h"

class IAudioPlayer
{
protected:
   IAudioPlayer();
   virtual ~IAudioPlayer();
public:
    virtual QIODevice* start() =0;
    virtual void stop() =0;
    virtual void resume() = 0;
    virtual void pause() = 0;
    // 0-100
    virtual void setVolume(uint8_t volume) = 0;
};

#endif // IAUDIOPLAY_H
