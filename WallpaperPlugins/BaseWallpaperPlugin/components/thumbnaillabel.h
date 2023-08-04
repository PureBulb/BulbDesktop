#ifndef THUMBNAILLABEL_H
#define THUMBNAILLABEL_H

#include <QLabel>
#include <QEvent>
#include <QImage>

#include "../common.h"
#include "../utils/videoUtils/videoutils.h"
class ThumbnailLabel:public QLabel
{
    Q_OBJECT
public:
    ThumbnailLabel(QWidget* parent,WallpaperType _type, QString _path, QImage _thumbnail);
    WallpaperType getType() const;

signals:
    void removedSelf(QString filename);
protected:
    bool eventFilter(QObject *o,QEvent *e) override;
private:

    WallpaperType type;
    QString path;
    QImage thumbnail;
    QImage deleteIcon;
};

#endif // THUMBNAILLABEL_H
