#ifndef BASEWORKERFORM_H
#define BASEWORKERFORM_H

#include "BaseWidget.h"

class BaseWorkerForm : public BaseWidget
{
public:
    explicit BaseWorkerForm(QWidget *parent = nullptr);
    virtual ~BaseWorkerForm();
public slots:
    virtual void onNextWallpaper() = 0;
    virtual void onPauseWallpaper() = 0;
    virtual void onResumeWallpaper() = 0;
};

#endif // BASEWORKERFORM_H
