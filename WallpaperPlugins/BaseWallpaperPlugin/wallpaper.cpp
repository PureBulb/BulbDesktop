#include "wallpaper.h"
#include "ui_Wallpaper.h"

#include <QtDebug>

Wallpaper::Wallpaper(QWidget *parent)
    :QWidget(parent)
    ,ui(new Ui::Wallpaper)
{
    ui->setupUi(this);
    ui->backgroundLabel->installEventFilter(this);
    // this->setMouseTracking(true);
    ui->backgroundLabel->setMouseTracking(true);

    setWindowTitle("BulbWorkerW");
    setWindowFlags(windowFlags() | Qt::Dialog | Qt::FramelessWindowHint);

}

Wallpaper::~Wallpaper()
{
    delete  ui;
}

void Wallpaper::setGif(QMovie *gif)
{
    ui->backgroundLabel->setMovie(gif);
}

void Wallpaper::setGraph(QPixmap pixmap)
{
    ui->backgroundLabel->setPixmap(pixmap);
    ui->backgroundLabel->setScaledContents(true);
}



void Wallpaper::onDecodeImage(QImage _image)
{
    image = _image;
    update();
}


bool Wallpaper::eventFilter(QObject *o, QEvent *e)
{
    if(o == ui->backgroundLabel && e->type() == QEvent::MouseButtonDblClick){
        emit triggedIcons();
    }
    if(e->type() == QEvent::MouseMove){
        qDebug()<<"MOUSE-MOVE"<<((QMouseEvent*)e)->pos();
    }
    return QWidget::eventFilter(o,e);
}

void Wallpaper::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(!image.isNull()){
        image = image.scaled(ui->backgroundLabel->width(),ui->backgroundLabel->height());
        painter.drawImage(QPoint(ui->backgroundLabel->x(),ui->backgroundLabel->y()),image);

    }
}

void Wallpaper::mouseMoveEvent(QMouseEvent *e)
{
    qDebug()<<"wallpaper move:"<<e->pos();
}

bool Wallpaper::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG *msg = static_cast<MSG*>(message);
    if(msg->message == 675){
        return true;
    }
    return false;
}
