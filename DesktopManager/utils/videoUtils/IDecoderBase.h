#ifndef DECODERBASE_H
#define DECODERBASE_H

#include <QThread>
#include <QMutex>
class IDecoderBase:public QThread
{
    Q_OBJECT
public:
    IDecoderBase();
protected:
    QMutex mutex;
    bool _pause;
    bool _stop;
public slots:
    void stop();
    void pause();
    void resume();
protected:
    void run() override;
signals:
    void error(QString,QString);
};

#endif // DECODERBASE_H
