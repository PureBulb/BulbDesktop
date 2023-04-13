#include "hookthread.h"

#include <QtDebug>
void HookThread::hookMouseMessage()
{


}

void HookThread::getProcessId()
{

    enableDebugPrivilege(SE_DEBUG_NAME);
    // 获取窗口所在的PID
    DWORD dwPID = 0;
    GetWindowThreadProcessId(myWorkerW, &dwPID);
    if (dwPID == 0) {
        qDebug()<<"获取PID失败";
        return;
    }

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);
    if (hProcess == NULL) {
        qDebug()<<"进程的句柄获取失败 ";
        return;
    }
    //权限，可添加的权限|可查询的权限
    HANDLE hToken;
    if (FALSE == OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        // 权限修改失败
        qDebug()<<"权限修改失败";
        return;
    }
    LUID luid;
    if (FALSE == LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid)) {
        // 特权信息查询失败
        qDebug()<<"特权信息查询失败";
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
        qDebug()<<"提升特权失败";
        return;
    };

    //在远程进程中申请内存空间
    // 【参数1】程序的句柄对象
    // 【参数2】申请的内存地址，由系统分配，所以为NULL
    // 【参数3】申请的内存长度
    // 【参数4】调用物理存储器
    // 【参数5】这块内存可读可写，可执行
    // 【返回】申请到的地址
//    LPVOID lpAddr = VirtualAllocEx(hProcess, NULL, m_StrDLLPath.GetLength() * 2+2,MEM_COMMIT,PAGE_EXECUTE_READWRITE);
//    if (lpAddr == NULL) {
//        // 在远程进程中申请内存失败
//        MessageBox(L"在远程进程中申请内存失败");
//        return;
//    }

    myWndProc = GetWindowLongPtrW(myWorkerW,GWLP_WNDPROC);
    qDebug()<<myWndProc;
}

int HookThread::enableDebugPrivilege(const wchar_t* name)
{
    HANDLE token;
        TOKEN_PRIVILEGES tp;
        //打开进程令牌环
        if(!OpenProcessToken(GetCurrentProcess(),
            TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY,&token))
        {
            qDebug()<<"open process token error!\n";
            return 0;
        }
        //获得进程本地唯一ID
        LUID luid;
        if(!LookupPrivilegeValue(NULL,name,&luid))
        {
            qDebug()<<"lookup privilege value error!\n";
            return 0;
        }
        tp.PrivilegeCount=1;
        tp.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED;
        tp.Privileges[0].Luid=luid;
        //调整进程权限
        if(!AdjustTokenPrivileges(token,0,&tp,sizeof(TOKEN_PRIVILEGES),NULL,NULL))
        {
            qDebug()<<"adjust token privilege error!\n";
            return 0;
        }
        return 1;
}

HookThread::HookThread(HWND workerw)
{
    this->myWorkerW = workerw;
    getProcessId();

}

void HookThread::run()
{

}
