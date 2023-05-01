#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QFileDialog>
#include <QLabel>


#include "thumbnaillabel.h"
#include "../widgets/BaseWidget.h"
#include "../utils/videoUtils/videoutils.h"

namespace Ui {
class SettingWidget;
}

class SettingWidget : public BaseWidget
{
    Q_OBJECT
private slots:
    void on_autoLaunchCheckBox_stateChanged(int arg1);

    void on_doubleClickedHideCheckBox_stateChanged(int arg1);

    void on_autoHideCheckBox_stateChanged(int arg1);

    void on_addVieoBtn_clicked();

    void on_addGifBtn_clicked();

    void on_addGraphBtn_clicked();

    void on_delaySlider_valueChanged(int value);

    void on_typeComboBox_currentIndexChanged(int index);

    void on_startWallpaperCheckbox_stateChanged(int arg1);

public:
    explicit SettingWidget(QWidget *parent = nullptr);
    ~SettingWidget();

private:
    Ui::SettingWidget *ui;
    QList<QLabel*> thumbnails;
    bool inited;
    void initUi();
    void initThumbnail();

    // BaseWidget interface
protected:
    void init();

protected slots:
    void onSettingsChanged();
    void onNextWallpaper();
    void onPauseWallpaper();
    void onResumeWallpaper();
};

#endif // SETTINGWIDGET_H
