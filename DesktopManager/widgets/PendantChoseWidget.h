#ifndef PENDANTCHOSEWIDGET_H
#define PENDANTCHOSEWIDGET_H

#include <QWidget>
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
    ~PendantChoseWidget();

private:
    Ui::PendantChoseWidget *ui;
};

#endif // PENDANTCHOSEWIDGET_H
