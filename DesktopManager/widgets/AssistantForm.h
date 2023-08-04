#ifndef ASSISTANTFORM_H
#define ASSISTANTFORM_H

#include <QTimer>
#include <QIcon>
#include <QScrollBar>
#include "../components/assistantitem.h"
#include "../utils/pluginUtils/AssistantPluginUtils.h"
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
    QTimer *editorQueryTimer;
    //FIXME: i should in context
    AssistantPluginUtils utils;
    QList<QueryResult> results;
    const int64_t PAGE_SIZE = 10;
    int64_t pageCount;

    ATOM atomId;

    void nextPage();
    void cleanData();
    // BaseWidget interface

protected:
    void init();


protected slots:

    void onSettingsChanged();

    void onItemWidgetScrollBarChanged(int);

    void query(const QString &arg1);

private slots:
    void on_inputEdit_textChanged(const QString &arg1);


    // QObject interface
//public:
//    bool eventFilter(QObject *watched, QEvent *event);

    // QObject interface
public:
    //TODO: hot key
    bool event(QEvent *event);

    // QWidget interface
protected:
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
};

#endif // ASSISTANTFORM_H
