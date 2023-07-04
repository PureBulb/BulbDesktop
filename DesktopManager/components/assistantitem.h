#ifndef ASSISTANTITEM_H
#define ASSISTANTITEM_H

#include <QListWidgetItem>
#include <QFileIconProvider>
#include <QPicture>

#include "../plugins/IAssistantPlugin.h"

namespace Ui {
class AssistantItem;
}

class AssistantItem :public QWidget, public QListWidgetItem
{
    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent *event) override;
public:
    explicit AssistantItem(QListWidget *parent = nullptr);
    explicit AssistantItem(QueryResult &result,QListWidget *parent = nullptr);
    AssistantItem* setIcon(QIcon &image);
    AssistantItem* setTitle(QString title);
    AssistantItem* setDescription(QString description);
    ~AssistantItem();
signals:
    void clicked();
private:
    Ui::AssistantItem *ui;
    ResultType type;
};

#endif // ASSISTANTITEM_H
