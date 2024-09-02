#include "PendantChoseWidget.h"
#include "qmimedata.h"
#include "ui_PendantChoseWidget.h"

PendantChoseWidget::PendantChoseWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PendantChoseWidget)
{
    ui->setupUi(this);
}

void PendantChoseWidget::insert(QImage icon, QString name)
{
    PendantIconForm* widget = new PendantIconForm(icon,name,this);
    widget->resize(64,64);
    widget->setAcceptDrops(true);
    widget->setObjectName("pendantForm");
    ui->pendantsView->addWidget(widget);
}

void PendantChoseWidget::insert(QHash<QString, QImage> formInfos)
{
    for(auto key: formInfos.keys()){
        PendantIconForm* widget = new PendantIconForm(formInfos[key],key,this);
        widget->resize(64,64);
        widget->setAcceptDrops(true);
        widget->setObjectName("pendantForm");
        ui->pendantsView->addWidget(widget);
    }
}

PendantChoseWidget::~PendantChoseWidget()
{
    delete ui;
}

bool PendantChoseWidget::event(QEvent *event)
{

    return QWidget::event(event);
}


