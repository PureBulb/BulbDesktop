#include "monitorwidget.h"
#include "ui_monitorwidget.h"

MonitorWidget::MonitorWidget(QWidget *parent)
    : BasePendantWidget(parent)
    , ui(new Ui::MonitorWidget)
{
    ui->setupUi(this);
    //设置主窗口透明
    // setAttribute(Qt::WA_DeleteOnClose,true);
    setAttribute(Qt::WA_TranslucentBackground);
    //设置背景透明
    ui->quickWidget->engine()->addImportPath(QApplication::applicationDirPath()+"/qml");
    ui->quickWidget->setAttribute(Qt::WA_AlwaysStackOnTop);
    ui->quickWidget->setClearColor(QColor(Qt::transparent));
    ui->quickWidget->setSource(QUrl("qrc:/MonitorPlugin/MonitorQml.qml"));
    // setAttribute(Qt::WA_TranslucentBackground);
    ui->quickWidget->rootContext()->setContextProperty("methods",this);

}

MonitorWidget::~MonitorWidget()
{
    delete ui;
}

QString MonitorWidget::getUsername()
{
    QDir dir;
    return dir.home().dirName();
}
