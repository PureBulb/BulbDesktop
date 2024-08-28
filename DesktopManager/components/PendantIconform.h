#ifndef PENDANTICONFORM_H
#define PENDANTICONFORM_H

#include <QWidget>

namespace Ui {
class PendantIconForm;
}

class PendantIconForm : public QWidget
{
    Q_OBJECT

public:
    explicit PendantIconForm(QWidget *parent = nullptr);
    ~PendantIconForm();

private:
    Ui::PendantIconForm *ui;
};

#endif // PENDANTICONFORM_H
