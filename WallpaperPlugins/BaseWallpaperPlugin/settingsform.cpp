#include "settingsform.h"
#include "ui_settingsform.h"
#include "QDebug"
SettingsForm::SettingsForm(QHash<QString, QVariant> &_settings, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsForm),
    setting(_settings),
    inited(true)
{
    ui->setupUi(this);
    initUi();
    logInstance = LogDispacher::getInstance();
    // connect(this,&SettingsForm::settingChanged,this,&SettingsForm::onSettingChanged);
}

SettingsForm::~SettingsForm()
{
    delete ui;
}

void SettingsForm::setSettings(QHash<QString, QVariant> &_settings)
{
    setting = _settings;
    initUi();
}

void SettingsForm::on_addVieoBtn_clicked()
{
    if(inited){
        QStringList filenames = QFileDialog::getOpenFileNames(this,"选择视频文件","/","Videos(*.mp4 *.avi *.mov *.flv *.mpeg *.mpg);;all(*.*)");
        QStringList originPath = setting[INI_VIDEO_PATHS].toStringList();
        for(auto filename:filenames){
            if(!originPath.contains(filename))
                originPath.append(filename);
        }
        setting[INI_VIDEO_PATHS] = originPath;
        emit settingFormChanged(setting);
    }

}

void SettingsForm::on_addGifBtn_clicked()
{
    if(inited){
       QStringList filenames = QFileDialog::getOpenFileNames(this,"选择视频文件","/","Gifs(*.gif);;all(*.*)");
       QStringList originPath = setting[INI_GIF_PATHS].toStringList();
       for(auto filename:filenames){
           if(!originPath.contains(filename))
               originPath.append(filename);
       }

       setting[INI_GIF_PATHS] = originPath;
       emit settingFormChanged(setting);
   }

}

void SettingsForm::on_addGraphBtn_clicked()
{
    if(inited){
        QStringList filenames = QFileDialog::getOpenFileNames(this,"选择视频文件","/","Graphs(*.png *.jpg *.jpeg *.bmp *.svg);;all(*.*)");
        QStringList originPath = setting[INI_GRAPH_PATHS].toStringList();
        for(auto filename:filenames){
            if(!originPath.contains(filename))
                originPath.append(filename);
            else
                QMessageBox::information(nullptr,"图片已存在列表","不能重复添加");
        }
        setting[INI_GRAPH_PATHS] = originPath;
        emit settingFormChanged(setting);
    }

}

void SettingsForm::on_delaySlider_valueChanged(int value)
{
    if(inited){
        ui->delayLabel->setText(QString::number(value)+QString("分钟"));
        setting[INI_GRAPH_DELAY] = value;
        emit settingFormChanged(setting);
    }

}

void SettingsForm::on_typeComboBox_currentIndexChanged(int index)
{
    if(inited){
        setting[INI_TYPE]=WallpaperType(index-1);
        if(getWallpaperPaths().size()<=0){
            QMessageBox::information(nullptr,"无法选择 ","该模式下缺少壁纸文件 ");
            setting[INI_TYPE]=preType;
            return ;
        }
        preType = WallpaperType(index-1);
        emit settingFormChanged(setting);
    }

}

void SettingsForm::onRemoveThumbnail(QString filename)
{
    ThumbnailLabel * senderObj = (ThumbnailLabel *)sender();
    if(senderObj->getType() == WallpaperType::graph){
        QStringList paths = setting[INI_GRAPH_PATHS].toStringList();
        if(paths.size()<=1){
            QMessageBox::information(nullptr,"警告","至少要有一个壁纸");
            return;
        }
        paths.removeAll(filename);
        setting[INI_GRAPH_PATHS] = paths;
        ui->graphThumbnailLayout->removeWidget(senderObj);
    }

    else if(senderObj->getType() == WallpaperType::video){
        QStringList paths = setting[INI_VIDEO_PATHS].toStringList();
        if(paths.size()<=1){
            QMessageBox::information(nullptr,"警告","至少要有一个壁纸");
            return;
        }
        paths.removeAll(filename);
        setting[INI_VIDEO_PATHS] = paths;

        ui->videoThumbnailLayout->removeWidget(senderObj);
    }

    else if(senderObj->getType() == WallpaperType::gif){
        QStringList paths = setting[INI_GIF_PATHS].toStringList();
        if(paths.size()<=1){
            QMessageBox::information(nullptr,"警告","至少要有一个壁纸");
            return;
        }
        paths.removeAll(filename);
        setting[INI_GIF_PATHS] = paths;
        ui->gifThumbnailLayout->removeWidget(senderObj);

    }
    emit settingFormChanged(setting);

    initThumbnail();
}

void SettingsForm::initUi()
{
        ui->delaySlider->setValue(setting[INI_GRAPH_DELAY].toInt());
        ui->typeComboBox->setItemText(1,typeNames[0]);
        ui->typeComboBox->setItemText(2,typeNames[1]);
        ui->typeComboBox->setItemText(3,typeNames[2]);
        ui->typeComboBox->setCurrentIndex(setting[INI_TYPE].toInt()+1);
        initThumbnail();
}

void SettingsForm::initThumbnail()
{
    for(auto i : thumbnails){
            i->deleteLater();
            ui->videoThumbnailLayout->removeWidget(i);
        }
        thumbnails.clear();
        int row = 0;
        int column = 0;

        for(auto filename : setting[INI_VIDEO_PATHS].toStringList()){
            QImage image = VideoUtils::getThumbnail(filename);
            ThumbnailLabel * thumbnail = new ThumbnailLabel(this,WallpaperType::video,filename,image);
            connect(thumbnail,&ThumbnailLabel::removedSelf,this,&SettingsForm::onRemoveThumbnail);

            thumbnails.push_back(thumbnail);
            if(column%2 == 0 && column!=0){
                row++;
                column = 0;
            }
            ui->videoThumbnailLayout->addWidget(thumbnail,row,column);
            column++;
        }


        for(auto filename : setting[INI_GRAPH_PATHS].toStringList()){
            QImage image(filename);
            ThumbnailLabel * thumbnail = new ThumbnailLabel(this,graph,filename,image);
            thumbnails.push_back(thumbnail);
            connect(thumbnail,&ThumbnailLabel::removedSelf,this,&SettingsForm::onRemoveThumbnail);
            if(column%2 == 0 && column!=0){
                row++;
                column = 0;
            }
            ui->graphThumbnailLayout->addWidget(thumbnail,row,column);
            ui->graphThumbnailLayout->setSpacing(10);
            column++;
        }
        for(auto filename : setting[INI_GIF_PATHS].toStringList()){
            QImage image(filename);
            ThumbnailLabel * thumbnail = new ThumbnailLabel(this,gif,filename,image);
            thumbnails.push_back(thumbnail);
            connect(thumbnail,&ThumbnailLabel::removedSelf,this,&SettingsForm::onRemoveThumbnail);
            if(column%2 == 0 && column!=0){
                row++;
                column = 0;
            }
            ui->gifThumbnailLayout->addWidget(thumbnail,row,column);
            ui->gifThumbnailLayout->setSpacing(10);
            column++;
        }

}

QStringList SettingsForm::getWallpaperPaths()
{
    WallpaperType type=WallpaperType(setting[INI_TYPE].toInt());
    switch (type) {
        case WallpaperType::gif:
            return setting[INI_GIF_PATHS].toStringList();
        case WallpaperType::graph:
            return setting[INI_GRAPH_PATHS].toStringList();
        case WallpaperType::video:
            return setting[INI_VIDEO_PATHS].toStringList();
        default:
            return QStringList();
    }
}

void SettingsForm::updateSettings(QHash<QString, QVariant> _setting)
{
    setting = _setting;
    logInstance->logd("SettingsForm::onSettingChanged","onSettingChanged");
    initUi();
    inited = true;
}


