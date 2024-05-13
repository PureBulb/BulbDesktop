#ifndef TRAYICONMENU_H
#define TRAYICONMENU_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class TrayIconMenu;
}

class TrayIconMenu : public QWidget
{
    Q_OBJECT

public:
    explicit TrayIconMenu(QWidget *parent = nullptr);
    ~TrayIconMenu();

    void setSettingWidget(QWidget *value);

    void setAssistantForm(QWidget *value);

private slots:

    void on_quitBtn_clicked();
    void on_pauseBtn_clicked();

    void on_startBtn_clicked();

    void on_nextBtn_clicked();

    void on_settingsBtn_clicked();

    void on_assistorBtn_clicked();

    void on_volumeSlider_valueChanged(int value);

    void on_editBtn_clicked();

signals:
    void volumeChange(int value);
    void nextWallpaper();
    void pauseWallpaper();
    void resumeWallpaper();
    void triggedEditMode();
    void exit();
private:
    Ui::TrayIconMenu *ui;

    QWidget *settingWidget;
    QWidget *assistantForm;
};

#endif // TRAYICONMENU_H
