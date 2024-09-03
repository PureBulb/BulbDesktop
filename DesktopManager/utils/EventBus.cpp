#include "EventBus.h"
//TODO: add event bus to solve setting log and some event that cross moudle(such as pendant drag drop)
EventBus::EventBus(QObject *parent)
    : QObject{parent}
{}

bool EventBus::event(QEvent *event)
{

    return QObject::event(event);
}
