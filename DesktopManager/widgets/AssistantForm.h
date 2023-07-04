#ifndef ASSISTANTFORM_H
#define ASSISTANTFORM_H

#include <QTimer>
#include <QIcon>
#include "BaseWidget.h"
#include "../components/assistantitem.h"
#include "../utils/pluginUtils/assistantpluginutils.h"
namespace Ui {
class AssistantForm;
}

class AssistantForm : public BaseWidget
{
    Q_OBJECT

public:
    explicit AssistantForm(QWidget *parent = nullptr);
    ~AssistantForm();

private:
    Ui::AssistantForm *ui;
    QTimer *editorQueryTimer;
    AssistantPluginUtils utils;
    // BaseWidget interface
protected:
    void init();

protected slots:
    void onSettingsChanged();

    void query(const QString &arg1);

private slots:
    void on_inputEdit_textChanged(const QString &arg1);

};

#endif // ASSISTANTFORM_H
