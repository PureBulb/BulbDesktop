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
namespace Ui {
class WorkerForm;
}

class WorkerForm : public QWidget
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

    void setVideoBackground();
    void setGifBackground();
    void setGraphBackground();

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
