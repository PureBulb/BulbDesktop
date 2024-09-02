#include "PendantIconform.h"
#include "ui_PendantIconform.h"

PendantIconForm::PendantIconForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PendantIconForm)
{
    ui->setupUi(this);
    ui->iconLabel->setAcceptDrops(true);
    ui->nameLabel->setAcceptDrops(true);
}

PendantIconForm::PendantIconForm(QImage icon, QString name,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PendantIconForm)
    , m_pluginName(name)
    , m_icon(icon)
{
    ui->setupUi(this);
    ui->iconLabel->setPixmap(QPixmap::fromImage(m_icon));
    ui->nameLabel->setText(m_pluginName);
    ui->iconLabel->setAcceptDrops(true);
    ui->nameLabel->setAcceptDrops(true);
}

void PendantIconForm::setIcon(QImage icon)
{
    m_icon = icon;
    ui->iconLabel->setPixmap(QPixmap::fromImage(m_icon));
}

void PendantIconForm::setName(QString &name)
{
    m_pluginName = name;
    ui->nameLabel->setText(m_pluginName);
}

QString PendantIconForm::getName()
{
    return m_pluginName;
}

QImage PendantIconForm::getIcon()
{
    return m_icon;
}

PendantIconForm::~PendantIconForm()
{
    delete ui;
}

bool PendantIconForm::event(QEvent *event)
{
    if(QEvent::MouseButtonPress == event->type()){
        QMouseEvent* e = static_cast<QMouseEvent*>(event);
        if( e->button() == Qt::LeftButton){
            QMimeData* data = new QMimeData;
            data->setData("pendant",m_pluginName.toUtf8());
            data->setImageData(m_icon);
            QDrag* drag = new QDrag(this);
            drag->setMimeData(data);
            drag->exec();
            drag->deleteLater();
            return true;
        }
    }
    return QWidget::event(event);
}
