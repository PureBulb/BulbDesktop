#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initui();


    //test config
    setWallpaperType(wallpaperType::graph);
    setWallpaperPath("E:/project/Qt/build-DesktopManagerV2-Desktop_Qt_5_14_2_MSVC2017_64bit-Debug/test2.png");
}

MainWindow::~MainWindow()
{
    delete ui;
    emit quitProcess();
}

bool MainWindow::eventFilter(QObject *o, QEvent *e)
{



    return true;
}

//todo: reset config re-init windows
void MainWindow::initui()
{
    setWindowTitle("Bulb 桌面助手");

    //初始化WorkerForm
    initWorkerForm();

    //设置页面左侧滚动条隐藏
    ui->labelsScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->labelsScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    \
}

void MainWindow::initWorkerForm()
{
    if(w)
        w->deleteLater();
    w = new WorkerForm();
    w->init();

    connect(this,&MainWindow::settingsChanged,w,&WorkerForm::onSettingsChange);
    connect(this,&MainWindow::quitProcess,w,&WorkerForm::onQuit);
}


void MainWindow::on_applyButton_clicked()
{
    setStartWallpaper(true);
    emit settingsChanged();
}

void MainWindow::on_cancelButton_clicked()
{
}
