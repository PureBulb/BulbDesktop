#ifndef PENDANTCHOSEWIDGET_H
#define PENDANTCHOSEWIDGET_H

#include <QWidget>
#include <QDrag>
#include <QMouseEvent>
#include "../components/PendantIconform.h"
namespace Ui {
class PendantChoseWidget;
}

class PendantChoseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PendantChoseWidget(QWidget *parent = nullptr);
    void insert(QImage icon,QString name);
    void insert(QHash<QString,QImage> formInfos);
    ~PendantChoseWidget();
protected:
    bool event(QEvent* event) override;
private:
    Ui::PendantChoseWidget *ui;
};

#endif // PENDANTCHOSEWIDGET_H
