#ifndef PENDANTICONFORM_H
#define PENDANTICONFORM_H

#include <QWidget>
#include <QImage>
#include <QString>
#include <QPixmap>
#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>
namespace Ui {
class PendantIconForm;
}

class PendantIconForm : public QWidget
{
    Q_OBJECT

public:
    explicit PendantIconForm(QWidget *parent = nullptr);
    explicit PendantIconForm(QImage icon,QString name,QWidget *parent = nullptr);
    void setIcon(QImage icon);
    void setName(QString& name);
    QString getName();
    QImage getIcon();
    ~PendantIconForm();
protected:
    bool event(QEvent* event) override;

private:
    Ui::PendantIconForm *ui;
    QString m_pluginName;
    QImage m_icon;
};

#endif // PENDANTICONFORM_H
