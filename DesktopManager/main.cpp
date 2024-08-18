#include <QApplication>

#include <utils/pluginUtils/wallpaperpluginutils.h>
#include <Manager.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString strKey = "Bulb Desktop wallpaper";
    std::wstring str = strKey.toStdWString();
    LPCWSTR wstrKey = str.c_str();
    HANDLE hMetex = CreateMutex(NULL,FALSE,wstrKey);

    if(GetLastError() == ERROR_ALREADY_EXISTS){
        //如果互斥体存在，说明程序已经有实例在运行了,释放资源然后关闭本实例
        if(hMetex){
            CloseHandle(hMetex);
            hMetex = NULL;
        }
        return -1;
    }
    Manager manager;
    return a.exec();
}
