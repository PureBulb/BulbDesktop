#ifndef INJECTLIB_H
#define INJECTLIB_H

#include "injectLib_global.h"

#include <windows.h>
#include <QDebug>
HHOOK g_hook;
HWND myWallpaperW;
UINT16 buttonMsg;
UINT16 lastMsg;
//安装钩子
extern "C" __declspec(dllexport) BOOL InstallHook();
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     );




//卸载钩子
extern "C" __declspec(dllexport) BOOL UninstallHook();

//钩子处理函数
LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam);
void getHWNDW();


#endif // INJECTLIB_H
