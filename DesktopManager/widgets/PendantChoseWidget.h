#ifndef PENDANTCHOSEWIDGET_H
#define PENDANTCHOSEWIDGET_H

#include <QWidget>

namespace Ui {
class PendantChoseWidget;
}

class PendantChoseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PendantChoseWidget(QWidget *parent = nullptr);
    ~PendantChoseWidget();

private:
    Ui::PendantChoseWidget *ui;
};

#endif // PENDANTCHOSEWIDGET_H
