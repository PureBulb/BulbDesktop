#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QWidget>
#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>
#include <QHash>
#include <QVariant>

#include "common.h"
#include "utils/logdispacher.h"
#include "utils/videoUtils/videoutils.h"
#include "components/thumbnaillabel.h"
namespace Ui {
class SettingsForm;
}

class SettingsForm : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsForm(QHash<QString, QVariant> &_settings, QWidget *parent = nullptr);
    ~SettingsForm();

    void setSettings(QHash<QString,QVariant>& _settings);

private slots:
    void on_addVieoBtn_clicked();

    void on_addGifBtn_clicked();

    void on_addGraphBtn_clicked();

    void on_delaySlider_valueChanged(int value);

    void on_typeComboBox_currentIndexChanged(int index);

    void onRemoveThumbnail(QString filename);

private:
    Ui::SettingsForm *ui;
    QList<QLabel*> thumbnails;
    QHash<QString,QVariant>& setting;
    WallpaperType preType;
    bool inited;
    LogDispacher* logInstance;
    // SettingDispacher* settingInstance;
private:
    void initUi();
    void initThumbnail();
    QStringList getWallpaperPaths();
protected:
    void init();
public slots:
    void updateSettings(QHash<QString, QVariant>);
signals:
    void settingFormChanged(QHash<QString, QVariant>);
};

#endif // SETTINGSFORM_H
