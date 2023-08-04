#include "WindAdapterV2.h"

HWND WindAdapterV2::myWorkerW = 0;
HWND WindAdapterV2::myProgmanW = 0;
HWND WindAdapterV2::myDefviewW = 0;
HWND WindAdapterV2::myWorkerWMustHide = 0;
WindAdapterV2* WindAdapterV2::instance = nullptr;

WindAdapterV2::WindAdapterV2()
    :hookthread(nullptr)
{
    getWorker();
    if(myWorkerW){
        hookthread = new HookThread(myWorkerW);
        hookthread->start();
    }
    else{
        QMessageBox::information(nullptr,"初始化失败","无法安装钩子");
    }
}

WindAdapterV2 *WindAdapterV2::getInstance()
{
    if(!instance)
        instance = new  WindAdapterV2;
    return instance;
}

void WindAdapterV2::hideIcon()
{
    ShowWindow(myWorkerW,SW_HIDE);
}

void WindAdapterV2::showIcon()
{
    ShowWindow(myWorkerW,SW_SHOW);
}

void WindAdapterV2::installDesktopEventFilter(HWND wallpaper)
{
    while(SendMessage(hookthread->getMyWorkerW(), ADD_WALLPAPER_W, 0, (LPARAM) wallpaper)!= ADD_WALLPAPER_W);
}

void WindAdapterV2::removeDesktopEventFilter(HWND wallpaper)
{
    while(SendMessage(hookthread->getMyWorkerW(), DELETE_WALLPAPER_W, 0, (LPARAM) wallpaper)!= DELETE_WALLPAPER_W);
}

HWND WindAdapterV2::underOnProgmanW(HWND windowHWND)
{
    if(!myProgmanW){
        loge("WindAdapter::underOnProgmanW","can not find myProgmanW");
    }
    return SetParent(windowHWND,myProgmanW);
}

HWND WindAdapterV2::topOnProgmanW(HWND windowHWND)
{
    if(!myDefviewW){
        findDefviewW();
        if(!myDefviewW)
            loge("WindAdapter::topOnProgmanW","can not find myDefviewW");
    }
    return SetParent(windowHWND,myDefviewW);
}

WINBOOL WindAdapterV2::myEnumWindowsProc(HWND tophandle, LPARAM topparamhandle)
{
    myDefviewW = FindWindowEx(tophandle, nullptr, L"SHELLDLL_DefView", nullptr);
    if (myDefviewW != nullptr)
    {
        WindAdapterV2::myWorkerWMustHide = FindWindowEx(nullptr, tophandle, L"WorkerW", nullptr);

    }
    return true;
}

HWND WindAdapterV2::getProgmanHWND()
{
    if(myWorkerWMustHide == 0){
        getWorker();
    }
    return myWorkerWMustHide;
}

HWND WindAdapterV2::getWorker()
{
    /*
        worker
        |——> SHELLDLL_DefView
            |——>SysListView32|FolderView
        |——> worker  <-it must to be hidden
        Progman
        |——myWallpaper
    */
    PDWORD_PTR result=nullptr;
    myProgmanW = FindWindow(L"Progman", nullptr);
    SendMessageTimeout(myProgmanW, 0x052c, 0 ,0, SMTO_NORMAL, 0x3e8,result);
    findDefviewW();
    EnumWindows(&WindAdapterV2::myEnumWindowsProc,static_cast<LPARAM>(NULL));
    if(myWorkerWMustHide!=0)
        ShowWindow(WindAdapterV2::myWorkerWMustHide,SW_HIDE);
    else
        QMessageBox::information(nullptr,"error","can not get worker");

    return myProgmanW;
}

HWND WindAdapterV2::findDefviewW()
{
    HWND hd = nullptr;
    hd = FindWindowEx(nullptr, nullptr, L"WorkerW", nullptr);
    //通过遍历找到包含SHELLDLL_DefView的WorkerW
    while ((!myDefviewW) && hd)
    {
        myDefviewW = FindWindowEx(hd, nullptr, L"SHELLDLL_DefView", nullptr);
        myWorkerW = hd;
        hd = FindWindowEx(nullptr, hd, L"WorkerW", nullptr);
    }

    return myDefviewW;
}
