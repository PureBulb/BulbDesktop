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
    ui->quickWidget->engine()->addImportPath("qrc:/MonitorPlugin");
    ui->quickWidget->setSource(QUrl("qrc:/MonitorPlugin/MonitorQml.qml"));
    // setAttribute(Qt::WA_TranslucentBackground);
    ui->quickWidget->rootContext()->setContextProperty("methods",this);

}

MonitorWidget::~MonitorWidget()
{
    delete ui;
}

void MonitorWidget::setCity(const QString &city)
{
    infos.insert("city", city);
}

QString MonitorWidget::getUsername()
{
    QDir dir;
    infos.insert("username", dir.home().dirName());
    return dir.home().dirName();
}
__int64 MonitorWidget::Filetime2Int64(const FILETIME &ftime)
{
    LARGE_INTEGER li;
    li.LowPart = ftime.dwLowDateTime;
    li.HighPart = ftime.dwHighDateTime;
    return li.QuadPart;
}

__int64 MonitorWidget::CompareFileTime2(const FILETIME &preTime, const FILETIME &nowTime)
{
    return Filetime2Int64(nowTime) - Filetime2Int64(preTime);
}

double MonitorWidget::getCpuUsage()
{
    FILETIME preIdleTime;
    FILETIME preKernelTime;
    FILETIME preUserTime;
    GetSystemTimes(&preIdleTime, &preKernelTime, &preUserTime);

    Sleep(1000);

    FILETIME idleTime;
    FILETIME kernelTime;
    FILETIME userTime;
    GetSystemTimes(&idleTime, &kernelTime, &userTime);

    auto idle = CompareFileTime2(preIdleTime, idleTime);
    auto kernel = CompareFileTime2(preKernelTime, kernelTime);
    auto user = CompareFileTime2(preUserTime, userTime);

    if (kernel + user == 0)
        return 0;

    infos.insert("cpuUsage",(1.0*(kernel + user - idle) / (kernel + user))*100);
    return 1.0*(kernel + user - idle) / (kernel + user);
}

unsigned long MonitorWidget::getMemoryRate()
{

    MEMORYSTATUSEX memStatus;
    memStatus.dwLength = sizeof(memStatus);

    GlobalMemoryStatusEx(&memStatus);
    // int nAvail = (int)(memStatus.ullAvailPhys / Byte2MB);
    // int nTotal = (int)(memStatus.ullTotalPhys / Byte2MB);
    infos.insert("memoryUsage", memStatus.dwMemoryLoad*1.0);
    return memStatus.dwMemoryLoad;
    // cout << "Memory: " <<  << "%, " << nAvail << "/" << nTotal << endl;
}

QVariantMap MonitorWidget::getInfos()
{
    QtConcurrent::run([=](){
        getCpuUsage();
        getUsername();
        getMemoryRate();
    });
    return infos;
}
