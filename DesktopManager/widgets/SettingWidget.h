#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>

namespace Ui {
class SettingWidget;
}

class SettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWidget(QWidget *parent = nullptr);
    ~SettingWidget();

    void addSettingItem(QHash<QString,QWidget*> widgets);


private:
    Ui::SettingWidget *ui;
};

#endif // SETTINGWIDGET_H
