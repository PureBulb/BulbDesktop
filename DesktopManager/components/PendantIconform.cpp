#include "PendantIconform.h"
#include "ui_PendantIconform.h"

PendantIconForm::PendantIconForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PendantIconForm)
{
    ui->setupUi(this);
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

PendantIconForm::~PendantIconForm()
{
    delete ui;
}
