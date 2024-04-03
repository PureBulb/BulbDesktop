#ifndef WINDADAPTERV2_H
#define WINDADAPTERV2_H

#include <QMessageBox>
#include <QApplication>
#include <windows.h>
#include "hookthread.h"

#define ADD_WALLPAPER_W (WM_USER + 101)
#define DELETE_WALLPAPER_W (WM_USER + 102)

class WindAdapterV2
{
public:
    static WindAdapterV2* getInstance();
    void hideIcon();
    void showIcon();
    void installDesktopEventFilter(HWND wallpaper);
    void removeDesktopEventFilter(HWND wallpaper);
    HWND underOnProgmanW(HWND windowHWND);
    HWND topOnProgmanW(HWND windowHWND);
private:
    WindAdapterV2();
    static BOOL CALLBACK  myEnumWindowsProc(_In_ HWND tophandle, _In_ LPARAM topparamhandle);
    HWND getProgmanHWND();
    HWND getWorker();
    HWND findDefviewW();

    static HWND myWorkerW;
    static HWND myProgmanW;
    static HWND myDefviewW;
    static HWND myWorkerWMustHide;



    static WindAdapterV2* instance;
    HookThread *hookthread;
};

#endif // WINDADAPTERV2_H
