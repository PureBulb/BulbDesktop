#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
MainWindow::MainWindow(QWidget *parent)
    : BaseWidget(parent)
    , ui(new Ui::MainWindow)
    , w(nullptr)
{
    ui->setupUi(this);
    initTrayIcon();
    initui();

    SettingWidget* settingW = new SettingWidget();
    ui->ConfigScrollArea->setWidget(settingW);

}

MainWindow::~MainWindow()
{
    delete ui;
    emit quitProcess();
    w->deleteLater();
    w = nullptr;
}

bool MainWindow::eventFilter(QObject *o, QEvent *e)
{
    areaScrollerEventProcess(o,e);

    return false;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(event->type() == QCloseEvent::Close){
        event->ignore();
        this->hide();
        trayIcon->show();
    }
}

void MainWindow::init()
{

    initui();
}

void MainWindow::onSettingsChanged()
{

    init();
}

//todo: reset config re-init windows
void MainWindow::initui()
{
    setWindowTitle("Bulb 桌面助手");

    //初始化WorkerForm
    initWorkerForm();
    //初始化 助手从窗口

    //设置页面左侧滚动条隐藏
    ui->labelsScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->labelsScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    bindEvent();
}

void MainWindow::initTrayIcon()
{
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setToolTip("SystemTray Program");
    trayIcon->setIcon(QIcon(":/resource/icons/icon.png"));
    trayIconMenu = new TrayIconMenu(this);
    trayIconMenu->setSettingWidget(this);
    assistantForm = new AssistantForm();
    trayIconMenu->setAssistantForm(assistantForm);
//    trayIconMenu->setSubregionForm();
    QWidgetAction* action = new QWidgetAction(this);
    QMenu* menu = new QMenu(this);
    action->setDefaultWidget(trayIconMenu);
    menu->addAction(action);
    trayIcon->setContextMenu(menu);



}

void MainWindow::bindEvent()
{
    ui->videoCfgLabel->installEventFilter(this);
    ui->baseCfgLabel->installEventFilter(this);
    ui->graphCfgLabel->installEventFilter(this);
    ui->gifCfgLabel->installEventFilter(this);
    ui->pluginCfgLabel->installEventFilter(this);

    //    connect(trayIcon,&QSystemTrayIcon::activated,this,&MainWindow::onTrayIconActivated);
}




void MainWindow::areaScrollerEventProcess(QObject *o, QEvent *e)
{
//    if(o == this->ui->baseCfgLabel && e->type() == QEvent::MouseButtonPress){
//        ui->ConfigScrollArea->verticalScrollBar()->setValue(ui->baseCfgGroupBox->y());
//    }
//    else if(o == this->ui->videoCfgLabel && e->type() == QEvent::MouseButtonPress){
//        ui->ConfigScrollArea->verticalScrollBar()->setValue(ui->videoCfgGroupBox->y());
//    }
//    else if(o == this->ui->graphCfgLabel && e->type() == QEvent::MouseButtonPress){
//        ui->ConfigScrollArea->verticalScrollBar()->setValue(ui->graphCfgGroupBox->y());
//    }
//    else if(o == this->ui->gifCfgLabel && e->type() == QEvent::MouseButtonPress){
//        ui->ConfigScrollArea->verticalScrollBar()->setValue(ui->gifCfgGroupBox->y());
//    }
//    else if(o == this->ui->pluginCfgLabel && e->type() == QEvent::MouseButtonPress){
//        ui->ConfigScrollArea->verticalScrollBar()->setValue(ui->pluginCfgGroupBox->y());
//    }
//    else if(o == this->ui->baseCfgGroupBox && e->type() == QEvent::MouseButtonPress){
//        ui->labelsScrollArea->verticalScrollBar()->setValue(ui->baseCfgLabel->y());
//    }
//    else if(o == this->ui->videoCfgLabel && e->type() == QEvent::MouseButtonPress){
//        ui->labelsScrollArea->verticalScrollBar()->setValue(ui->videoCfgLabel->y());
//    }
//    else if(o == this->ui->gifCfgGroupBox && e->type() == QEvent::MouseButtonPress){
//        ui->labelsScrollArea->verticalScrollBar()->setValue(ui->gifCfgLabel->y());
//    }
//    else if(o == this->ui->graphCfgGroupBox && e->type() == QEvent::MouseButtonPress){
//        ui->labelsScrollArea->verticalScrollBar()->setValue(ui->graphCfgLabel->y());
//    }
//    else if(o == this->ui->pluginCfgGroupBox && e->type() == QEvent::MouseButtonPress){
//        ui->labelsScrollArea->verticalScrollBar()->setValue(ui->pluginCfgLabel->y());
//    }
}



void MainWindow::initWorkerForm()
{
    if(!w){
        w = new WorkerForm();
        w->init();
        w->show();
        connect(this,&MainWindow::quitProcess,w,&WorkerForm::onQuit);
        connect(trayIconMenu,&TrayIconMenu::pauseWallpaper,w,&WorkerForm::onPause);
        connect(trayIconMenu,&TrayIconMenu::resumeWallpaper,w,&WorkerForm::onResume);
        connect(trayIconMenu,&TrayIconMenu::nextWallpaper,w,&WorkerForm::onNextWallpaper);
        connect(trayIconMenu,&TrayIconMenu::volumeChange,w,&WorkerForm::onVolumeChange);
    }





}



void MainWindow::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason){
        case QSystemTrayIcon::DoubleClick:
            this->show();
        break;
        case QSystemTrayIcon::Trigger:
            trayIcon->showMessage("提示","双击打开设置,右键打开菜单",QIcon(":/resource/icons/icon.png"));
        break;
        case QSystemTrayIcon::Context:
            trayIcon->contextMenu()->show();
        break;
        case QSystemTrayIcon::Unknown:
            logd("MainWindow::onTrayIconActivated","Unknown");
        break;
    }
}

