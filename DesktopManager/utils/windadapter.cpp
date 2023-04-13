#include "windadapter.h"


HWND WindAdapter::myWorkerWMustHide = 0;
HWND WindAdapter::myWorkerW = 0;
HWND WindAdapter::myProgmanW = 0;
HWND WindAdapter::myDefviewW = 0;
HWND WindAdapter::myWallpaperW = 0;
WindAdapter* WindAdapter::instance = nullptr;
HHOOK WindAdapter::mouseHook = nullptr;
UINT16 WindAdapter::lastMsg = 0;;
UINT16 WindAdapter::buttonMsg = 0;
WindAdapter::WindAdapter()
    :Hookthread(nullptr)
{}

BOOL WindAdapter::myEnumWindowsProc(HWND tophandle, LPARAM topparamhandle)
{
    myDefviewW = FindWindowEx(tophandle, nullptr, L"SHELLDLL_DefView", nullptr);
    if (myDefviewW != nullptr)
    {
        WindAdapter::myWorkerWMustHide = FindWindowEx(nullptr, tophandle, L"WorkerW", nullptr);

    }
    return true;
}

HWND WindAdapter::getProgmanHWND()
{
    if(myWorkerWMustHide == 0){
        getWorker();
    }
    return myWorkerWMustHide;
}

HWND WindAdapter::getWorker()
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
    EnumWindows(&WindAdapter::myEnumWindowsProc,static_cast<LPARAM>(NULL));
    if(myWorkerWMustHide!=0)
        ShowWindow(WindAdapter::myWorkerWMustHide,SW_HIDE);
    else
        QMessageBox::information(nullptr,"error","can not get worker");

    return myProgmanW;
}

HWND WindAdapter::findDefviewW()
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

HWND WindAdapter::underOnProgmanW(HWND windowHWND)
{

    if(!myProgmanW){
        loge("WindAdapter::underOnProgmanW","can not find myProgmanW");
    }
    return SetParent(windowHWND,myProgmanW);
}

HWND WindAdapter::topOnProgmanW(HWND windowHWND)
{
    if(!myDefviewW){
        findDefviewW();
        if(!myDefviewW)
            loge("WindAdapter::topOnProgmanW","can not find myDefviewW");
    }
    return SetParent(windowHWND,myDefviewW);
}

WindAdapter *WindAdapter::getInstance(HWND wallpaperW)
{
    myWallpaperW = wallpaperW;
    if(instance)
        return instance;
    instance = new WindAdapter;

    return instance;
}

bool WindAdapter::removeHook()
{
    return true;
}

bool WindAdapter::installHook()
{
    //todo: test myself hook
    if(myWorkerW == 0)
        return false;
    if(Hookthread == nullptr)
        Hookthread = new HookThread(myWorkerW);
    Hookthread->start();
    while(SendMessage(Hookthread->getMyWorkerW(), WM_USER+100, 0, (LPARAM) myWallpaperW)!= WM_USER+100);


    // todo: connect finished
    // #######################
    return true;
}

void WindAdapter::hideIcon()
{
    ShowWindow(myWorkerW,SW_HIDE);
}

void WindAdapter::showIcon()
{
    ShowWindow(myWorkerW,SW_SHOW);


}






void WindAdapter::setMyWallpaperW(const HWND &value)
{
    myWallpaperW = value;
}

void WindAdapter::reFindWallpaperW()
{
//    SendMessage(Hookthread->getMyWorkerW(), WM_USER+100, 0, 0);
}

