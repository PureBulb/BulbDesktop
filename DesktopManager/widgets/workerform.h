#ifndef WORKERFORM_H
#define WORKERFORM_H

#include <Windows.h>
#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QMovie>
#include "context.h"
#include "utils/windadapter.h"
namespace Ui {
class WorkerForm;
}

class WorkerForm : public QWidget,Context
{
    Q_OBJECT

public:
    explicit WorkerForm(QWidget *parent = nullptr);
    ~WorkerForm();
    void init();
public slots:
    void onSettingsChange();
    void onQuit();
    void onDecodeImage(QImage _image);

protected:
    bool eventFilter(QObject *o,QEvent *e);
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::WorkerForm *ui;
    WindAdapter* winAdapter;
    void setVideoBackground();
    void setGifBackground();
    void setGraphBackground();
    bool hideIcon;
    QMovie *gif;
    QImage image;
};

#endif // WORKERFORM_H
