#ifndef HOOKTHREAD_H
#define HOOKTHREAD_H

#include <QThread>
#include <windows.h>

class HookThread :public QThread
{
private:
    static void hookMouseMessage();
    void getProcessId();
    int enableDebugPrivilege(const wchar_t *name);
    HWND myWorkerW;
    LONG myWndProc;
public:
    HookThread(HWND workerw);
    void run() override;
};

#endif // HOOKTHREAD_H
