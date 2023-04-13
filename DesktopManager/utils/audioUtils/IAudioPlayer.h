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
//    virtual void play() =0;
    virtual void stop() =0;
    virtual void resume() = 0;
    virtual void pause() = 0;
};

#endif // IAUDIOPLAY_H
