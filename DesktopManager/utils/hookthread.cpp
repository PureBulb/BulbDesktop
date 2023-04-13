#include "hookthread.h"

#include <QtDebug>




void HookThread::inject()
{

    char  dllPath[] = "E:/project/c#/test/MinHookDllDemo/x64/Debug/MinHookDllDemo.dll";
    int buffSize = (strlen(dllPath) + 1) * sizeof(char) ;
    // 获取窗口所在的PID
    DWORD dwPID = 0;
    qDebug()<<"inject into hwnd:"<<myWorkerW;
    GetWindowThreadProcessId(myWorkerW, &dwPID);
    if (dwPID == 0) {
        loge("inject","获取PID失败\n");

        return;
    }

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);
    if (hProcess == NULL) {
        loge("inject","进程的句柄获取失败\n");
        return;
    }
    //权限，可添加的权限|可查询的权限
    HANDLE hToken;
    if (FALSE == OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        // 权限修改失败
        loge("inject","权限修改失败\n");
        return;
    }
    LUID luid;
    if (FALSE == LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid)) {
        // 特权信息查询失败
        loge("inject","特权信息查询失败\n");
        return;
    };
    //3.调节进程的访问令牌的特权属性
    // 这几行代码固定不变
    TOKEN_PRIVILEGES tkp;
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Luid = luid;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; // 打开特权
    // 【参数1】访问令牌
    // 【参数2】是否禁用特权
    // 【参数3】新特权所占的字节数
    // 【参数4】原来的特权是否需要保存
    // 【参数5】原特权的长度
    if (FALSE == AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(tkp), NULL, NULL)) {
        // 提升特权失败
        loge("inject","提升特权失败\n");
        return;
    };

    //在远程进程中申请内存空间
    // 【参数1】程序的句柄对象
    // 【参数2】申请的内存地址，由系统分配，所以为NULL
    // 【参数3】申请的内存长度
    // 【参数4】调用物理存储器
    // 【参数5】这块内存可读可写，可执行
    // 【返回】申请到的地址

    LPVOID lpAddr = VirtualAllocEx(hProcess, NULL,buffSize,MEM_COMMIT,PAGE_EXECUTE_READWRITE);
    if (lpAddr == NULL) {
        // 在远程进程中申请内存失败

        loge("inject","在远程进程中申请内存失败\n");
        return;
    }
    // 把DLL路径写入到远程进程中
        // 强行修改程序的内存
        // 【参数1】程序的句柄
        // 【参数2】申请到的内存首地址
        // 【参数3】写入的内容
        // 【参数4】要写入的字节数
        // 【参数5】
        if (FALSE == WriteProcessMemory(hProcess, lpAddr, dllPath,
            buffSize, NULL)) {
            // 在远程进程中写入数据失败
            loge("inject","在远程进程中写入数据失败\n");
            return ;
        };


        // 调用Kernel32.dll中的LoadLibraryW方法用以加载DLL文件
        PTHREAD_START_ROUTINE pfnStartAssr =
            (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(L"Kernel32.dll"),
    "LoadLibraryA");

        // 在远程进程中开辟线程
        // 【参数1】远程线程的句柄
        // 【参数2】线程属性。NULL表示使用默认属性
        // 【参数3】堆栈大小。0代表默认
        // 【参数4】加载DLL文件的对象
        // 【参数5】加载文件的路径
        // 【参数6】延迟时间。0代表立即启动
        // 【参数7】线程ID。为NULL就行了
        HANDLE hRemoteThread = CreateRemoteThread(hProcess, NULL, 0, pfnStartAssr, lpAddr, 0,
            NULL);
        if (hRemoteThread == NULL) {
            // 创建远程线程失败
            loge("inject","创建远程线程失败\n");
            // 释放内存
            VirtualFreeEx(hProcess, lpAddr, 0, MEM_FREE);
            return ;
        }

        logi("inject","注入成功\n");
        WaitForSingleObject(hRemoteThread, INFINITE);
//         关闭线程
        CloseHandle(hRemoteThread);
//         释放内存
        VirtualFreeEx(hProcess, lpAddr, 0, MEM_FREE);

}

void HookThread::run()
{
    inject();
}





HWND HookThread::getMyWorkerW() const
{
    return myWorkerW;
}

HookThread::HookThread(HWND workerw)
{
    myWorkerW = workerw;


}



