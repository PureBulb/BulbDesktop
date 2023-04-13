#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollBar>
#include <windows.h>
#include <process.h>

#include "workerform.h"
#include "context.h"
#include "utils/videoUtils/videoutils.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow,Context
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool eventFilter(QObject *o, QEvent *e);

    //TODO: 退出时要重新set parent把窗口转回本进程
signals:
    void settingsChanged();
    void quitProcess();
private slots:
    void on_applyButton_clicked();
    void on_cancelButton_clicked();

    void on_autoLaunchCheckBox_stateChanged(int arg1);

    void on_doubleClickedHideCheckBox_stateChanged(int arg1);

    void on_autoHideCheckBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    void initui();
    void initWorkerForm();
    WorkerForm *w;
    VideoUtils *vu;
};
#endif // MAINWINDOW_H
