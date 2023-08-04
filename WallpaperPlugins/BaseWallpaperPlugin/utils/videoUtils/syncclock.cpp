#include "syncclock.h"

SyncClock::SyncClock()
    :driftPts(0)
    ,pts(0)
{
    setClock(NAN);
}

void SyncClock::setClock(double _pts)
{

    double time = getSeconds();
    setClockAt(_pts,time);
}

void SyncClock::setClockAt(double _pts, double time)
{
    pts = _pts;
    driftPts = pts - time;
}

double SyncClock::getClock()
{
    double time = getSeconds();
    return driftPts + time;
}

double SyncClock::getSeconds()
{
    return av_gettime()/1000000.0;
}

