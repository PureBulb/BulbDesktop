#ifndef EVENTBUS_H
#define EVENTBUS_H

#include <QObject>
#include <QEvent>
class EventBus : public QObject
{
    Q_OBJECT
public:
    explicit EventBus(QObject *parent = nullptr);

protected:
    bool event(QEvent* event) override;
};

#endif // EVENTBUS_H
