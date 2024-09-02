#ifndef EVENTBUS_H
#define EVENTBUS_H

#include <QObject>

class EventBus : public QObject
{
    Q_OBJECT
public:
    explicit EventBus(QObject *parent = nullptr);

signals:
};

#endif // EVENTBUS_H
