#include "workerform.h"
#include "ui_workerform.h"

#include <QtDebug>
#include <QDesktopWidget>
WorkerForm::WorkerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkerForm)
{
    ui->setupUi(this);
    winAdapter = WindAdapter::getInstance((HWND)window()->winId());
    winAdapter->getWorker();
    winAdapter->installHook();
    ui->backgroundLabel->installEventFilter(this);
    hideIcon = isHideIcon();
    gif = nullptr;
}

WorkerForm::~WorkerForm()
{
    delete ui;
    winAdapter->removeHook();
    setHideIcon(hideIcon);
}

void WorkerForm::onSettingsChange()
{
    init();
}

void WorkerForm::onQuit()
{

    deleteLater();
}

bool WorkerForm::eventFilter(QObject *o, QEvent *e)
{
    if(o == ui->backgroundLabel && e->type() == QEvent::MouseButtonDblClick){
        if(hideIcon)
            winAdapter->hideIcon();
        else
            winAdapter->showIcon();
        hideIcon = !hideIcon;

    }
    return QWidget::eventFilter(o,e);
}

bool WorkerForm::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG* msg = static_cast<MSG*>(message);

    switch (msg->message) {
    case WM_MOUSELEAVE:
//        qDebug()<<"test";
        return true;//这里是为了去掉本来不该存在的mouseleave消息（邪术）
    case WM_LBUTTONDBLCLK:
//        qDebug()<<"test1";
        return true;
    }

    return false;
}

void WorkerForm::init()
{
    QDesktopWidget desktop;



    setWindowTitle("BulbWorkerW");
    setWindowFlags(windowFlags() | Qt::Dialog | Qt::FramelessWindowHint);

    if(isStartWallpaper()){
        showFullScreen();
        winAdapter->underOnProgmanW((HWND)this->winId());
        if(isHideIcon()){
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
    switch(getWallpaperType()){
        case wallpaperType::graph:
            setGraphBackground();
            break;
        case wallpaperType::gif:
            setGifBackground();
            break;
        case wallpaperType::video:
            setVideoBackground();
            break;
        default:
            break;
    }

}

void WorkerForm::setVideoBackground()
{

}

void WorkerForm::setGifBackground()
{
    if(!gif)
        gif = new QMovie;
    gif->setFileName(getWallpaperPath());
    gif->setScaledSize(ui->backgroundLabel->size());
    ui->backgroundLabel->setMovie(gif);
    gif->start();
}

void WorkerForm::setGraphBackground()
{
    QString graphPath = getWallpaperPath();
    ui->backgroundLabel->setPixmap(QPixmap(graphPath));
    ui->backgroundLabel->setScaledContents(true);
}
