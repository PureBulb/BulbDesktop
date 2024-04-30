#ifndef HOOKTHREAD_H
#define HOOKTHREAD_H

#include <QThread>
#include <QCoreApplication>
#include <windows.h>
#include <tlhelp32.h>
#include <string>
#include "log.h"
class HookThread:public QThread
{
    Q_OBJECT
private:
    static void hookMouseMessage();


    BOOL SetWinHookInject(WCHAR * wzDllPath, WCHAR * wzProcessName);
    UINT32 GetTargetThreadIdFromProcessName(const WCHAR *ProcessName);
    HWND myWorkerW;
    HWND myWallPaperW;
    LONG myWndProc;
public:
    HookThread(HWND workerw);
    void inject();



    // QThread interface
    HWND getMyWorkerW() const;

protected:
    void run();
};

#endif // HOOKTHREAD_H
