#include "injectlib.h"



BOOL UninstallHook()
{
    return UnhookWindowsHookEx(g_hook);
}

LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    //拿到当前操作窗口的句柄
    HWND hWnd = ::GetActiveWindow();  //拿当前活动窗口
    if (hWnd == NULL)
    {
        hWnd = ::GetForegroundWindow(); //拿顶层窗口
        if (hWnd == NULL)
        {
            return CallNextHookEx(g_hook, nCode, wParam, lParam);
        }
    }

    //拿标题
    if(nCode==HC_ACTION)//当最前面的窗口是WorkerW（就是只有桌面）
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

    return CallNextHookEx(g_hook, nCode, wParam, lParam);
}


void getHWNDW()
{
    HWND hd = nullptr;
    HWND myDefviewW = nullptr;
    hd = FindWindowEx(nullptr, nullptr, L"Progman", nullptr);

    //通过遍历找到包含SHELLDLL_DefView的WorkerW
    while ((!myDefviewW) && hd)
    {
        myDefviewW = FindWindowEx(hd, nullptr, L"Qt5QWindowIcon", nullptr);
    }
    myWallpaperW = myDefviewW;
}

BOOL InstallHook()
{
    qDebug()<<"start inject";
    buttonMsg = 0;
    lastMsg = 0;
    getHWNDW();
    g_hook = SetWindowsHookEx(WH_MOUSE, mouseProc, GetModuleHandle(L"KeyHook"), 0);
    if (g_hook == NULL)
    {
        return FALSE;
    }
    return TRUE;
}
BOOL DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {

        case DLL_PROCESS_ATTACH: {
            // 当DLL被进程 <<第一次>> 调用时，导致DllMain函数被调用，
            // 同时ul_reason_for_call的值为DLL_PROCESS_ATTACH，
            // 如果同一个进程后来再次调用此DLL时，操作系统只会增加DLL的使用次数，
            // 不会再用DLL_PROCESS_ATTACH调用DLL的DllMain函数。
            // 获取窗口对象
            HWND hwnd = GetActiveWindow();
            MessageBox(hwnd, L"dll entry", L"info", MB_ICONINFORMATION);

        }
    }
        return TRUE;

}
