#ifndef WORKERFORM_H
#define WORKERFORM_H

#include <QWidget>
#include <QPixmap>
#include <QMovie>
#include "context.h"
#include "utils/windadapter.h"
namespace Ui {
class WorkerForm;
}

class WorkerForm : public QWidget,Context
{
    Q_OBJECT

public:
    explicit WorkerForm(QWidget *parent = nullptr);
    ~WorkerForm();
    void init();
public slots:
    void onSettingsChange();
    void onQuit();
protected:
    bool eventFilter(QObject *o,QEvent *e);
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
private:
    Ui::WorkerForm *ui;
    WindAdapter* winAdapter;
    void setVideoBackground();
    void setGifBackground();
    void setGraphBackground();
    bool hideIcon;
    QMovie *gif;
};

#endif // WORKERFORM_H
