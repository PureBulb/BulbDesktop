#ifndef WORKERFORM_H
#define WORKERFORM_H

#include <Windows.h>
#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QMovie>
#include <QList>
#include <QTimer>
#include <QDesktopWidget>
#include <QMouseEvent>

//#include "../utils/videoUtils/videoutils.h"

namespace Ui {
class Wallpaper;
}

class Wallpaper : public QWidget
{
    Q_OBJECT

public:
    explicit Wallpaper(QWidget *parent = nullptr);
    ~Wallpaper();

    void setGif(QMovie *gif);
    void setGraph(QPixmap pixmap);
    void cleanGraph();
public slots:
    void onDecodeImage(QImage _image);
protected:
    bool eventFilter(QObject *o,QEvent *e) override;
    void paintEvent(QPaintEvent *event) override;
    bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;
signals:
    void triggedIcons();

private:
    QImage image;
    Ui::Wallpaper *ui;
    //鼠标痕迹使用的，感觉未来会删掉先起名test
    int testx;
    int testy;
    int lstTestx = 0;
    int lstTesty = 0;

};

#endif // WORKERFORM_H
