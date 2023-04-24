#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollBar>
#include <windows.h>
#include <process.h>
#include <QCloseEvent>
#include <QSystemTrayIcon>
#include <QWidgetAction>
#include "BaseWidget.h"
#include "workerform.h"
#include "context.h"
#include "utils/videoUtils/videoutils.h"
#include "../components/trayiconmenu.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public BaseWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool eventFilter(QObject *o, QEvent *e) override;



    //TODO: 退出时要重新set parent把窗口转回本进程

protected:
    Context* getContext();
    void closeEvent(QCloseEvent *event) override;
    void init() override;

signals:

    void quitProcess();
private slots:

    void on_autoLaunchCheckBox_stateChanged(int arg1);
    void on_doubleClickedHideCheckBox_stateChanged(int arg1);
    void on_autoHideCheckBox_stateChanged(int arg1);


    void on_addVieoBtn_clicked();

    void on_addGifBtn_clicked();

    void on_addGraphBtn_clicked();

    void on_delaySlider_valueChanged(int value);
    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void on_typeComboBox_currentIndexChanged(int index);

public slots:
    void onSettingsChanged() override;
private:
    Ui::MainWindow *ui;

    void areaScrollerEventProcess(QObject *o,QEvent *e);

    void initui();
    void initTrayIcon();
    void initWorkerForm();
    void bindEvent();

    WorkerForm *w;
    QSystemTrayIcon *trayIcon;
    TrayIconMenu* trayIconMenu;

    // BaseWidget interface
protected slots:
    void onNextWallpaper() override;
    void onPauseWallpaper() override;
    void onResumeWallpaper() override;
};
#endif // MAINWINDOW_H
