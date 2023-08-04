#ifndef WALLPAPERSETTINGGFORM_H
#define WALLPAPERSETTINGGFORM_H

#include <QWidget>

namespace Ui {
class WallpaperSettinggForm;
}

class WallpaperSettinggForm : public QWidget
{
    Q_OBJECT

public:
    explicit WallpaperSettinggForm(QWidget *parent = nullptr);
    ~WallpaperSettinggForm();

private:
    Ui::WallpaperSettinggForm *ui;
};

#endif // WALLPAPERSETTINGGFORM_H
