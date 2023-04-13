#ifndef SUBREGIONFORM_H
#define SUBREGIONFORM_H

#include <QWidget>

namespace Ui {
class SubregionForm;
}

class SubregionForm : public QWidget
{
    Q_OBJECT

public:
    explicit SubregionForm(QWidget *parent = nullptr);
    ~SubregionForm();

private:
    Ui::SubregionForm *ui;
};

#endif // SUBREGIONFORM_H
