#ifndef SYNCCLOCK_H
#define SYNCCLOCK_H


#include <math.h>
#include <stdint.h>
extern "C"{
#include "libavutil/time.h"
}
enum class ClockType:int{
    VIDEO_MASTER,
    AUDIO_MASTER,
    CLOCK_TYPE_ERROR
};
class SyncClock
{
public:
    SyncClock();
    void setClock(double _pts);
    void setClockAt(double _pts,double time);
    double getClock();
private:
    double driftPts;
    double getSeconds();
    double pts;

};

#endif // SYNCCLOCK_H
