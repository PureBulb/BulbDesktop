#ifndef BASE_H
#define BASE_H

#include <QObject>
#include <QWidget>

class Base : public QWidget
{
    Q_OBJECT
public:
    explicit Base(QWidget *parent = nullptr);

signals:

};

#endif // BASE_H
