#ifndef ASSISTANTITEM_H
#define ASSISTANTITEM_H

#include <QWidget>

namespace Ui {
class AssistantItem;
}

class AssistantItem : public QWidget
{
    Q_OBJECT

public:
    explicit AssistantItem(QWidget *parent = nullptr);
    ~AssistantItem();

private:
    Ui::AssistantItem *ui;
};

#endif // ASSISTANTITEM_H
