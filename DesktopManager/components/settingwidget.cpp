#include "settingwidget.h"
#include "ui_settingwidget.h"

SettingWidget::SettingWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::SettingWidget),
    inited(false)
{
    ui->setupUi(this);
    init();
    preType = (Context::WallPaperType)getContext()->getWallpaperType();
}

SettingWidget::~SettingWidget()
{
    delete ui;
}

void SettingWidget::initUi()
{
    //init content
    ui->delaySlider->setValue(getContext()->getGraphShowDelay());
    ui->autoLaunchCheckBox->setChecked(getContext()->isAutoLaunch());
    ui->autoHideCheckBox->setChecked(getContext()->isHideIcon());

    ui->typeComboBox->setItemText(1,getContext()->getWallpaperTypeName()[0]);
    ui->typeComboBox->setItemText(2,getContext()->getWallpaperTypeName()[1]);
    ui->typeComboBox->setItemText(3,getContext()->getWallpaperTypeName()[2]);
    ui->typeComboBox->setItemText(4,getContext()->getWallpaperTypeName()[3]);
    ui->typeComboBox->setCurrentIndex(getContext()->getWallpaperType()+1);

    ui->doubleClickedHideCheckBox->setChecked(getContext()->isDoubleClickedHideIcon());
    initThumbnail();



    ui->baseCfgGroupBox->installEventFilter(this);
    ui->videoCfgGroupBox->installEventFilter(this);
    ui->graphCfgGroupBox->installEventFilter(this);
    ui->gifCfgGroupBox->installEventFilter(this);
    ui->pluginCfgGroupBox->installEventFilter(this);
}


void SettingWidget::initThumbnail()
{

    for(auto i : thumbnails){
        i->deleteLater();
        ui->videoThumbnailLayout->removeWidget(i);
    }
    thumbnails.clear();
    int row = 0;
    int column = 0;

    for(auto filename : getContext()->getVideoWallpaperPaths()){
        QImage image = VideoUtils::getThumbnail(filename);
        ThumbnailLabel * thumbnail = new ThumbnailLabel(this,Context::video,filename,image);


        thumbnails.push_back(thumbnail);
        if(column%2 == 0 && column!=0){
            row++;
            column = 0;
        }
        ui->videoThumbnailLayout->addWidget(thumbnail,row,column);
        column++;
    }


    for(auto filename : getContext()->getGraphWallpaperPaths()){
        QImage image(filename);
        ThumbnailLabel * thumbnail = new ThumbnailLabel(this,Context::graph,filename,image);
        thumbnails.push_back(thumbnail);

        if(column%2 == 0 && column!=0){
            row++;
            column = 0;
        }
        ui->graphThumbnailLayout->addWidget(thumbnail,row,column);
        ui->graphThumbnailLayout->setSpacing(10);
        column++;
    }
    for(auto filename : getContext()->getGifWallpaperPaths()){
        QImage image(filename);
        ThumbnailLabel * thumbnail = new ThumbnailLabel(this,Context::graph,filename,image);
        thumbnails.push_back(thumbnail);

        if(column%2 == 0 && column!=0){
            row++;
            column = 0;
        }
        ui->gifThumbnailLayout->addWidget(thumbnail,row,column);
        ui->gifThumbnailLayout->setSpacing(10);
        column++;
    }

}

void SettingWidget::init()
{
    inited = false;
    initUi();
    inited = true;
}

void SettingWidget::onSettingsChanged()
{
    init();
}

void SettingWidget::onNextWallpaper()
{

}

void SettingWidget::onPauseWallpaper()
{

}

void SettingWidget::onResumeWallpaper()
{

}


void SettingWidget::on_autoLaunchCheckBox_stateChanged(int arg1)
{
    if(inited){
        if(arg1 == Qt::CheckState::Checked){
            getContext()->setAutoLaunch(true);
            return;
        }

        getContext()->setAutoLaunch(false);
    }

}

void SettingWidget::on_doubleClickedHideCheckBox_stateChanged(int arg1)
{
    if(inited){
        if(arg1 == Qt::CheckState::Checked){
            getContext()->setDoubleClickedHideIcon(true);
            return ;
        }
        getContext()->setDoubleClickedHideIcon(false);
    }
}

void SettingWidget::on_autoHideCheckBox_stateChanged(int arg1)
{
    if(inited){
        if(arg1 == Qt::CheckState::Checked){
            getContext()->setHideIcon(true);
            return ;
        }
        getContext()->setHideIcon(false);
    }

}


void SettingWidget::on_addVieoBtn_clicked()
{
    if(inited){
        QStringList filenames = QFileDialog::getOpenFileNames(this,"选择视频文件","/","Videos(*.mp4 *.avi *.mov *.flv *.mpeg *.mpg);;all(*.*)");
        getContext()->addVideoWallpaperPath(filenames);
    }
}

void SettingWidget::on_addGifBtn_clicked()
{
    if(inited){
        QStringList filenames = QFileDialog::getOpenFileNames(this,"选择视频文件","/","Gifs(*.gif);;all(*.*)");
        getContext()->addGifWallpaperPath(filenames);

    }
}

void SettingWidget::on_addGraphBtn_clicked()
{
    if(inited){
        QStringList filenames = QFileDialog::getOpenFileNames(this,"选择视频文件","/","Graphs(*.png *.jpg *.jpeg *.bmp *.svg);;all(*.*)");
        getContext()->addGraphWallpaperPath(filenames);

    }

}

void SettingWidget::on_delaySlider_valueChanged(int value)
{
    if(inited){
        ui->delayLabel->setText(QString::number(value)+QString("分钟"));
        getContext()->setGraphShowDelay(value);
    }
}
void SettingWidget::on_typeComboBox_currentIndexChanged(int index)
{
    if(inited){
        getContext()->setWallpaperType(Context::WallPaperType(index-1));
        if(getContext()->getWallpaperPaths().size()<=0){
            QMessageBox::information(nullptr,"无法选择 ","该模式下缺少壁纸文件 ");
            getContext()->setWallpaperType((Context::WallPaperType)preType);
            return ;
        }
        preType = (Context::WallPaperType)(index-1);
    }
}



void SettingWidget::on_startWallpaperCheckbox_stateChanged(int arg1)
{
    if(Qt::CheckState::Checked == arg1){
        if(getContext()->getWallpaperPaths().size()<=0){
            QMessageBox::information(this,getContext()->getWallpaperTypeName()[getContext()->getWallpaperType()]+"至少要添加有一个壁纸",getContext()->getWallpaperTypeName()[getContext()->getWallpaperType()]+"至少要添加有一个壁纸");
            return;
        }
        getContext()->setStartWallpaper(true);
    }
    else{
        getContext()->setStartWallpaper(false);
    }

}
