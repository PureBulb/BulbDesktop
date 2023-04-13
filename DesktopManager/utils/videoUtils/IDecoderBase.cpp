#include "IDecoderBase.h"

IDecoderBase::IDecoderBase()
    :_pause(false)
    ,_stop(false)
{}

void IDecoderBase::stop()
{
    mutex.lock();
    _stop = true;
    mutex.unlock();

}

void IDecoderBase::pause()
{
    mutex.lock();
    _pause = true;
    mutex.unlock();

}

void IDecoderBase::resume()
{
    mutex.lock();
    _pause = false;
    mutex.unlock();
}

void IDecoderBase::run()
{

}
