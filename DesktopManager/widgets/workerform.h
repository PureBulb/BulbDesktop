#ifndef WORKERFORM_H
#define WORKERFORM_H

#include <Windows.h>
#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QMovie>
#include <QList>
#include <QTimer>

#include "context.h"
#include "../utils/videoUtils/videoutils.h"
#include "utils/windadapter.h"
#include "baseworkerform.h"
namespace Ui {
class WorkerForm;
}

class WorkerForm : public BaseWorkerForm
{
    Q_OBJECT

public:
    explicit WorkerForm(QWidget *parent = nullptr);
    ~WorkerForm();
    void init();
public slots:
    void onSettingsChanged();
    void onQuit();
    void onPause();
    void onResume();
    void onDecodeImage(QImage _image);
    void onVolumeChange(uint8_t volume);

    void setVideoBackground();
    void setGifBackground();
    void setGraphBackground();
public slots:
    void onNextWallpaper() override;
    void onPauseWallpaper() override;
    void onResumeWallpaper() override;
protected:
    bool eventFilter(QObject *o,QEvent *e) override;
//    bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;
    void paintEvent(QPaintEvent *event) override;
    bool pause;
    Context* getContext();

private:
    Ui::WorkerForm *ui;
    WindAdapter* winAdapter;
    QTimer* graphShowTimer;

    bool hideIcon;
    bool isStartWallpaper;
    QList<QString> wallpaperPaths;
    Context::WallPaperType wallpaperType;

    QMovie *gif;
    VideoUtils *video;
    QImage image;
};

#endif // WORKERFORM_H
