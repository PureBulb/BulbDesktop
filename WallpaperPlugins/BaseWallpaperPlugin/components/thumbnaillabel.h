#ifndef THUMBNAILLABEL_H
#define THUMBNAILLABEL_H

#include <QLabel>
#include <QEvent>
#include <QImage>
#include "context.h"
#include "../utils/videoUtils/videoutils.h"
class ThumbnailLabel:public QLabel
{
    Q_OBJECT
public:
    ThumbnailLabel(QWidget* parent, Context::WallPaperType _type, QString _path, QImage _thumbnail);
    void removePath();
signals:
    void removedSelf();
protected:
    bool eventFilter(QObject *o,QEvent *e) override;
private:
    Context* getContext();
    Context::WallPaperType type;
    QString path;
    QImage thumbnail;
    QImage deleteIcon;
};

#endif // THUMBNAILLABEL_H
