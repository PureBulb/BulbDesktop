#include "thumbnaillabel.h"

ThumbnailLabel::ThumbnailLabel(QWidget *parent, WallpaperType _type, QString _path, QImage _thumbnail)
    :QLabel(parent)
    ,type(_type)
    ,path(_path)
    ,thumbnail(_thumbnail)
    ,deleteIcon(":/resource/icons/delete.png")
{
    installEventFilter(this);
    setMinimumSize(192,108);
    thumbnail = thumbnail.scaled(192,108);
    setPixmap(QPixmap::fromImage(thumbnail));
}

bool ThumbnailLabel::eventFilter(QObject *o, QEvent *e)
{
    do {
        if(o != this)
            break;

        if(e->type() == QEvent::Enter){
            setPixmap(QPixmap::fromImage(deleteIcon.scaled(192,108)));
        }
        else if(e->type() == QEvent::Leave){
            setPixmap(QPixmap::fromImage(thumbnail));
        }
        else if(e->type() == QEvent::MouseButtonPress){
            if(type == WallpaperType::video){
                emit removedSelf(path);
                VideoUtils::deleteThumbnail(path);
            }
            if(type == WallpaperType::graph){
                emit removedSelf(path);
            }
            if(type == WallpaperType::gif){
                emit removedSelf(path);
            }
        }
    } while (false);
    return false;
}

WallpaperType ThumbnailLabel::getType() const
{
    return type;
}
