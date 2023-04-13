#ifndef WINDADAPTER_H
#define WINDADAPTER_H

#include <windows.h>
#include <dwmapi.h>
#include <QMessageBox>
#include "log.h"

#include "hookthread.h"
class WindAdapter
{
public:

    HWND getProgmanHWND();
    HWND getWorker();
    HWND findDefviewW();
    HWND underOnProgmanW(HWND windowHWND);
    HWND topOnProgmanW(HWND windowHWND);
    static WindAdapter* getInstance(HWND wallpaperW);
    bool removeHook();
    bool installHook();
    void hideIcon();
    void showIcon();
    static void setMyWallpaperW(const HWND &value);
    void reFindWallpaperW();

protected:
    WindAdapter();
    ~WindAdapter();
private:


    static BOOL CALLBACK  myEnumWindowsProc(_In_ HWND tophandle, _In_ LPARAM topparamhandle);
    static HWND myWorkerWMustHide;
    static HWND myWorkerW;
    static HWND myWallpaperW;
    static HWND myProgmanW;
    static HWND myDefviewW;
    static HHOOK mouseHook;

    static UINT16 buttonMsg;
    static UINT16 lastMsg;

    static WindAdapter* instance;
    HookThread *Hookthread;

};

#endif // WINDADAPTER_H
