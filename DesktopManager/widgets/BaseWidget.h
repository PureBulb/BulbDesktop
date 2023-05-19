#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>
#include <context.h>
class BaseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BaseWidget(QWidget *parent = nullptr);
    virtual ~BaseWidget();

protected:
    virtual void init() = 0;
    Context* getContext();
protected slots:
    virtual void onSettingsChanged() = 0;

};

#endif // BASEWIDGET_H
