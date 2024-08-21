#include "wallpaper.h"
#include "ui_Wallpaper.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include "utils/logdispacher.h"

Wallpaper::Wallpaper(QWidget *parent)
    :QWidget(parent)
    ,ui(new Ui::Wallpaper)
{
    ui->setupUi(this);
    ui->backgroundLabel->installEventFilter(this);
    // this->setMouseTracking(true);
    ui->backgroundLabel->setMouseTracking(true);
    ui->backgroundLabel->lower();
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
    //minihook 已经可以钩住 鼠标的 hover move lbtnclick lbtndblclick rbtnclick rbtndblclick mbtnclick mbtndblclick事件

    if(o == ui->backgroundLabel && e->type() == QEvent::MouseButtonDblClick){
        emit triggedIcons();
    }

    if(o == ui->backgroundLabel && e->type() == QEvent::MouseMove){
        lstTestx = testx;
        lstTesty = testy;
        testx = ((QMouseEvent*)e)->x();
        testy = ((QMouseEvent*)e)->y();


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
    //展示鼠标痕迹
    painter.drawLine(lstTestx,lstTesty,testx,testy);
    QWidget::paintEvent(event);
}




bool Wallpaper::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG *msg = static_cast<MSG*>(message);

    //屏蔽鼠标离开事件，否则hook发送消息这边接收后总是会多一个leave消息导致捕获鼠标移动事件失败
    if(msg->message == WM_MOUSELEAVE){
        return true;
    }
   if(msg->message == WM_MOUSEMOVE ){
        auto point = QCursor::pos();
        *result=true;
        QMouseEvent event(QEvent::MouseMove, QPoint(point.x()-screen()->geometry().x(), point.y()-screen()->geometry().y()), Qt::LeftButton, Qt::NoButton, Qt::NoModifier);
        qDebug()<<winId()<<screen()->geometry().contains(point);
        if(screen()->geometry().contains(point))
           QApplication::sendEvent(ui->backgroundLabel,&event);
        return true;
        // qDebug()<<winId()<<pos<<screen()->geometry()<< QPoint(msg->pt.x, msg->pt.y);
        // msg->pt.x = pos.x();
        // msg->pt.y = pos.y();
   }
    if(msg->message == WM_LBUTTONDBLCLK){
        auto point = QCursor::pos();
        QMouseEvent event(QEvent::MouseButtonDblClick, QPoint(msg->pt.x, msg->pt.y), Qt::LeftButton, Qt::NoButton, Qt::NoModifier);
        if(screen()->geometry().contains(point))
            QApplication::sendEvent(ui->backgroundLabel,&event);
        return true;
    }

    return QWidget::nativeEvent(eventType,message,result);
}
