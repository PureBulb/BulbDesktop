#ifndef SYNCCLOCK_H
#define SYNCCLOCK_H


#include <math.h>
#include <stdint.h>
extern "C"{
#include "libavutil/time.h"
}
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
