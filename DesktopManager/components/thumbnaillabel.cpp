#include "thumbnaillabel.h"

ThumbnailLabel::ThumbnailLabel(QWidget *parent, Context::WallPaperType _type, QString _path,QImage _thumbnail)
    :QLabel(parent)
    ,type(_type)
    ,path(_path)
    ,thumbnail(_thumbnail)
    ,deleteIcon(":/recource/icons/delete.png")
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
            if(type == Context::video){
                getContext()->deleteVideoWallpaperPath(path);
                VideoUtils::deleteThumbnail(path);
            }
            if(type == Context::graph){
                getContext()->deleteGraphWallpaperPath(path);
            }
            if(type == Context::gif){
                getContext()->deleteGifWallpaperPath(path);
            }
        }
    } while (false);
    return false;
}


Context *ThumbnailLabel::getContext()
{
    return Context::getInstance();
}
