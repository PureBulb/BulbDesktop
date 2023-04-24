#ifndef TRAYICONMENU_H
#define TRAYICONMENU_H

#include <QWidget>

namespace Ui {
class TrayIconMenu;
}

class TrayIconMenu : public QWidget
{
    Q_OBJECT

public:
    explicit TrayIconMenu(QWidget *parent = nullptr);
    ~TrayIconMenu();

private:
    Ui::TrayIconMenu *ui;
};

#endif // TRAYICONMENU_H
