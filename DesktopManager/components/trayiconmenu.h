#ifndef TRAYICONMENU_H
#define TRAYICONMENU_H

#include <QWidget>
#include "../widgets/BaseWidget.h"
namespace Ui {
class TrayIconMenu;
}

class TrayIconMenu : public QWidget
{
    Q_OBJECT

public:
    explicit TrayIconMenu(QWidget *parent = nullptr);
    ~TrayIconMenu();

    void setSettingWidget(BaseWidget *value);

    void setSubregionForm(BaseWidget *value);

private slots:

    void on_quitBtn_clicked();
    void on_pauseBtn_clicked();

    void on_startBtn_clicked();

    void on_nextBtn_clicked();

    void on_settingsBtn_clicked();

    void on_assistorBtn_clicked();

    void on_volumeSlider_valueChanged(int value);

signals:
    void volumeChange(int value);
    void nextWallpaper();
    void pauseWallpaper();
    void resumeWallpaper();
private:
    Ui::TrayIconMenu *ui;

    BaseWidget *settingWidget;
    BaseWidget *SubregionForm;
};

#endif // TRAYICONMENU_H
