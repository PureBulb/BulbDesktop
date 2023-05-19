#include "workerform.h"
#include "ui_workerform.h"

#include <QtDebug>
#include <QDesktopWidget>
WorkerForm::WorkerForm(QWidget *parent) :
    BaseWorkerForm(parent),
    ui(new Ui::WorkerForm)
{
    pause = 0;
    ui->setupUi(this);
    winAdapter = WindAdapter::getInstance((HWND)window()->winId());
    winAdapter->getWorker();
    winAdapter->installHook();


    gif = nullptr;
    graphShowTimer = nullptr;
    video = nullptr;

    ui->backgroundLabel->installEventFilter(this);
    connect(getContext(),&Context::settingsChanged,this,&WorkerForm::onSettingsChanged);

}

WorkerForm::~WorkerForm()
{
    onQuit();
}


void WorkerForm::onQuit()
{
    delete ui;
    if(gif)
        gif->deleteLater();
    if(graphShowTimer)
        graphShowTimer->deleteLater();
    gif = nullptr;
    graphShowTimer = nullptr;
    winAdapter->removeHook();
    deleteLater();
}

void WorkerForm::onPause()
{
    if(video){
        video->pause();
    }
    else if(gif){
        gif->setPaused(true);
    }
    else if(graphShowTimer){
        graphShowTimer->stop();
    }
}

void WorkerForm::onResume()
{
    if(video){
        video->resume();
    }
    if(gif){
        gif->setPaused(false);
    }
    else if(graphShowTimer){
        graphShowTimer->start();
    }
}


void WorkerForm::onDecodeImage(QImage _image)
{
    image = _image;
    update();
}

void WorkerForm::onNextWallpaper()
{
    if(getContext()->getWallpaperType() == Context::gif){
        setGifBackground();
    }
    else if(getContext()->getWallpaperType() == Context::graph){
        setGraphBackground();
    }
    else if(getContext()->getWallpaperType() == Context::video){
        setVideoBackground();
    }
}

void WorkerForm::onPauseWallpaper()
{

}

void WorkerForm::onResumeWallpaper()
{

}

void WorkerForm::onVolumeChange(uint8_t volume)
{
    if(video)
        video->setVolume(volume);
}

bool WorkerForm::eventFilter(QObject *o, QEvent *e)
{
    if(o == ui->backgroundLabel && e->type() == QEvent::MouseButtonDblClick){
        if(hideIcon){
            winAdapter->hideIcon();
        }
        else{
            winAdapter->showIcon();
        }

        hideIcon = !hideIcon;

    }

    return QWidget::eventFilter(o,e);
}

//bool WorkerForm::nativeEvent(const QByteArray &eventType, void *message, long *result)
//{
//    MSG* msg = static_cast<MSG*>(message);

//    switch (msg->message) {
//    case WM_MOUSELEAVE:
//        qDebug()<<"test";
//        return true;//这里是为了去掉本来不该存在的mouseleave消息（邪术）
//    case WM_LBUTTONDBLCLK:
//        qDebug()<<"test1";
//        return true;
//    }

//    return false;
//}

void WorkerForm::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(!image.isNull()){
        image = image.scaled(ui->backgroundLabel->width(),ui->backgroundLabel->height());
        painter.drawImage(QPoint(ui->backgroundLabel->x(),ui->backgroundLabel->y()),image);

    }
}

Context *WorkerForm::getContext()
{
    return Context::getInstance();
}

void WorkerForm::init()
{
    QDesktopWidget desktop;
    setWindowTitle("BulbWorkerW");
    setWindowFlags(windowFlags() | Qt::Dialog | Qt::FramelessWindowHint);

    //get Setting Info
    hideIcon = getContext()->isHideIcon();
    isStartWallpaper = getContext()->isStartWallpaper();
    wallpaperType = (Context::WallPaperType)getContext()->getWallpaperType();
    wallpaperPaths = getContext()->getWallpaperPaths();
    if(wallpaperPaths.size()<=0)
        return ;
    if(isStartWallpaper){
        showFullScreen();
        winAdapter->reFindWallpaperW();
        winAdapter->underOnProgmanW((HWND)this->winId());
        if(hideIcon){
            qDebug()<<"hide Icon";
            winAdapter->hideIcon();
        }
        else{
            qDebug()<<"not hide Icon";
            winAdapter->showIcon();
        }
    }
    else{
        this->hide();
        return ;
    }
    switch(wallpaperType){
        case Context::WallPaperType::graph:
            setGraphBackground();
            break;
        case Context::WallPaperType::gif:
            setGifBackground();
            break;
        case Context::WallPaperType::video:
            setVideoBackground();
            break;
        default:
            break;
    }

}

void WorkerForm::onSettingsChanged()
{
    //todo: stop all wallpaper
    if(video){
        video->stop();
        video->deleteLater();
        video = nullptr;
    }
    if(graphShowTimer){
        graphShowTimer->stop();
        graphShowTimer->deleteLater();
        graphShowTimer = nullptr;
        ui->backgroundLabel->clear();
    }
    init();
}

void WorkerForm::setVideoBackground()
{
    if(wallpaperPaths.size()>0){
        if(!video){
            video = new VideoUtils(wallpaperPaths.front());
            connect(video,&VideoUtils::displayFinished,this,&WorkerForm::setVideoBackground);
            connect(video,&VideoUtils::sendDecodeImg,this,&WorkerForm::onDecodeImage);
            wallpaperPaths.pop_front();
            video->play();
        }
        else{
            video->stop();
            video->deleteLater();
            video = nullptr;
            setVideoBackground();
        }
    }
    else{
        wallpaperPaths = getContext()->getWallpaperPaths();
        setVideoBackground();
    }

}

void WorkerForm::setGifBackground()
{
    if(!gif){
        gif = new QMovie;
        connect(gif,&QMovie::finished,this,&WorkerForm::setGifBackground);
    }
    else{
        gif->stop();
    }
    if(wallpaperPaths.size()>0){
        gif->setFileName(wallpaperPaths.front());
        gif->setScaledSize(ui->backgroundLabel->size());
        ui->backgroundLabel->setMovie(gif);
        gif->start();
        wallpaperPaths.pop_front();
    }
    else{
        gif->stop();
        wallpaperPaths = getContext()->getWallpaperPaths();
        setGifBackground();
    }

}

void WorkerForm::setGraphBackground()
{
    if(!graphShowTimer){
        graphShowTimer = new QTimer;
        graphShowTimer->setInterval(getContext()->getGraphShowDelay()*60*1000);
        connect(graphShowTimer,&QTimer::timeout,this,&WorkerForm::setGraphBackground);
    }
    if(wallpaperPaths.size()>0){
        ui->backgroundLabel->setPixmap(QPixmap(wallpaperPaths.front()));
        ui->backgroundLabel->setScaledContents(true);
        wallpaperPaths.pop_front();
        graphShowTimer->start();
    }
    else{
        wallpaperPaths = getContext()->getWallpaperPaths();
        setGraphBackground();
    }


}
