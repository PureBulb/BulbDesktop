#ifndef ASSISTANTFORM_H
#define ASSISTANTFORM_H

#include <QWidget>

namespace Ui {
class AssistantForm;
}

class AssistantForm : public QWidget
{
    Q_OBJECT

public:
    explicit AssistantForm(QWidget *parent = nullptr);
    ~AssistantForm();

private:
    Ui::AssistantForm *ui;
};

#endif // ASSISTANTFORM_H
