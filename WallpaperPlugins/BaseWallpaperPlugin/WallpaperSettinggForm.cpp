#include "WallpaperSettinggForm.h"
#include "ui_WallpaperSettinggForm.h"

WallpaperSettinggForm::WallpaperSettinggForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WallpaperSettinggForm)
{
    ui->setupUi(this);
}

WallpaperSettinggForm::~WallpaperSettinggForm()
{
    delete ui;
}
