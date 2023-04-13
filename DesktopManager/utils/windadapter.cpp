#include "windadapter.h"
#include <QtDebug>


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
{
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
    //todo: test myself hook
    HookThread thead(myWorkerW);
    // #######################
    return myDefviewW;
}

HWND WindAdapter::underOnProgmanW(HWND windowHWND)
{

    if(!myProgmanW){
        qDebug()<<"WindAdapter::topOnProgmanW:\t"<<"can not find myProgmanW";
    }
    return SetParent(windowHWND,myProgmanW);
}

HWND WindAdapter::topOnProgmanW(HWND windowHWND)
{
    if(!myDefviewW){
        findDefviewW();
        if(!myDefviewW)
            qDebug()<<"WindAdapter::topOnProgmanW:\t"<<"can not find myDefviewW";
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
    return UnhookWindowsHookEx(mouseHook);
}

bool WindAdapter::installHook()
{
    mouseHook = SetWindowsHookEx( WH_MOUSE_LL,&WindAdapter::mouseProc,GetModuleHandle(NULL),0);//设置钩子
    return mouseHook;
}

void WindAdapter::hideIcon()
{
    ShowWindow(myWorkerW,SW_HIDE);
}

void WindAdapter::showIcon()
{
    ShowWindow(myWorkerW,SW_SHOW);
}


BOOL WindAdapter::myEnumWindowsProc(HWND tophandle, LPARAM topparamhandle)
{
    myDefviewW = FindWindowEx(tophandle, nullptr, L"SHELLDLL_DefView", nullptr);
    if (myDefviewW != nullptr)
    {
        WindAdapter::myWorkerWMustHide = FindWindowEx(nullptr, tophandle, L"WorkerW", nullptr);

    }
    return true;
}

LRESULT WindAdapter::mouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{

    if(GetForegroundWindow()==myWorkerW && nCode==HC_ACTION)//当最前面的窗口是WorkerW（就是只有桌面）
    {

        POINT p;//定义一个坐标
        GetCursorPos(&p);//获取鼠标坐标
        ClientToScreen(myWallpaperW,&p);//转换成窗口坐标
        //给buttonMsg赋值
        if(wParam&MK_LBUTTON){
//            qDebug()<<"左键";
            buttonMsg=MK_LBUTTON;

        }
        else if(wParam&MK_MBUTTON){
//            qDebug()<<"中键";
            buttonMsg=MK_MBUTTON;
        }
        else if(wParam&MK_RBUTTON){
//            qDebug()<<"右键";
            buttonMsg=MK_MBUTTON;
        }
        else if(lastMsg==WM_MOUSEMOVE){
//            qDebug()<<"移动";
            buttonMsg=0;
        }
        SendMessage(myWallpaperW,wParam,buttonMsg,MAKEWPARAM(p.x,p.y));
        if(wParam==lastMsg)
            lastMsg=wParam;//将二者比较，判断状态变化，用于响应拖拽消息
    }
    return CallNextHookEx(mouseHook,nCode,wParam,lParam);
}

void WindAdapter::setMyWallpaperW(const HWND &value)
{
    myWallpaperW = value;
}
