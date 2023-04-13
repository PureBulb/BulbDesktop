#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , w(nullptr)
    , vu(nullptr)
{
    ui->setupUi(this);
    vu = new VideoUtils("D:/test.mp4");
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

    if(o == this->ui->baseCfgLabel && e->type() == QEvent::MouseButtonPress){
        ui->ConfigScrollArea->verticalScrollBar()->setValue(ui->baseCfgGroupBox->y());
    }
    if(o == this->ui->videoCfgLabel && e->type() == QEvent::MouseButtonPress){
        ui->ConfigScrollArea->verticalScrollBar()->setValue(ui->videoCfgGroupBox->y());
    }
    if(o == this->ui->graphCfgLabel && e->type() == QEvent::MouseButtonPress){
        ui->ConfigScrollArea->verticalScrollBar()->setValue(ui->graphCfgGroupBox->y());
    }
    if(o == this->ui->gifCfgLabel && e->type() == QEvent::MouseButtonPress){
        ui->ConfigScrollArea->verticalScrollBar()->setValue(ui->gifCfgGroupBox->y());
    }
    if(o == this->ui->pluginCfgLabel && e->type() == QEvent::MouseButtonPress){
        ui->ConfigScrollArea->verticalScrollBar()->setValue(ui->pluginCfgGroupBox->y());
    }

    return false;
}

//todo: reset config re-init windows
void MainWindow::initui()
{
    setWindowTitle("Bulb 桌面助手");
    ui->baseCfgGroupBox->setMinimumSize(ui->ConfigScrollArea->size());
    ui->videoCfgGroupBox->setMinimumSize(ui->ConfigScrollArea->size());
    ui->graphCfgGroupBox->setMinimumSize(ui->ConfigScrollArea->size());
    ui->gifCfgGroupBox->setMinimumSize(ui->ConfigScrollArea->size());
    ui->pluginCfgGroupBox->setMinimumSize(ui->ConfigScrollArea->size());
    ui->videoCfgLabel->installEventFilter(this);
    ui->baseCfgLabel->installEventFilter(this);
    ui->graphCfgLabel->installEventFilter(this);
    ui->gifCfgLabel->installEventFilter(this);
    ui->pluginCfgLabel->installEventFilter(this);



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
    //todo:fix me
    connect(vu,&VideoUtils::sendDecodeImg,w,&WorkerForm::onDecodeImage);
    w->show();
    vu->play();

}


void MainWindow::on_applyButton_clicked()
{
    setStartWallpaper(true);
    emit settingsChanged();
}

void MainWindow::on_cancelButton_clicked()
{
    this->hide();
}

void MainWindow::on_autoLaunchCheckBox_stateChanged(int arg1)
{
    if(arg1 == Qt::CheckState::Checked){
        setAutoLaunch(true);
    }
    else{
        setAutoLaunch(false);
    }
}

void MainWindow::on_doubleClickedHideCheckBox_stateChanged(int arg1)
{
    if(arg1 == Qt::CheckState::Checked){
        setDoubleClickedHideIcon(true);
    }
    else{
        setDoubleClickedHideIcon(false);
    }
}

void MainWindow::on_autoHideCheckBox_stateChanged(int arg1)
{
    if(arg1 == Qt::CheckState::Checked){
        setHideIcon(true);
    }
    else{
        setHideIcon(false);
    }
}
