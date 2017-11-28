//////////////////////////////////////////////////////////////////////////
// 底层安全控制类
//		当前类主要用于:
//		a.权限调整和远程注入
//		b.利用IAT进行API拦截
//		调用示例:
//		a.远程注入
//			HWND hWnd=::FindWindow(NULL,"TargetWnd");
//			DWORD dwProcessId=0;
//			DWORD dwThreadId=GetWindowThreadProcessId(hWnd,&dwProcessId);
//			HANDLE hHandle=LoadLibraryRemote(dwProcessId,"Mission.dll");
//		b.利用IAT进行拦截主程序(EXE)对USER32.DLL中的GetWindowTextA的引用
//			int WINAPI GetWindowTextAForExe(IN HWND hWnd,OUT LPSTR lpString,IN int nMaxCount)
//			{	DisableAPIHook(NULL,"USER32.DLL","GetWindowTextA",(FARPROC)GetWindowTextAForExe);
//				EnableAPIHook(NULL,"USER32.DLL","GetWindowTextA",(FARPROC)GetWindowTextAForExe);
//				return nRet;
//			}
//			EnableAPIHook(NULL,"USER32.DLL","GetWindowTextA",(FARPROC)GetWindowTextAForExe))
//		c.利用IAT进行拦截MFC42.DLL对USER32.DLL中的GetWindowTextA的引用
//			int WINAPI GetWindowTextAForDll(IN HWND hWnd,OUT LPSTR lpString,IN int nMaxCount)
//			{	DisableAPIHook(GetModuleHandle("MFC42.DLL"),"USER32.DLL","GetWindowTextA",(FARPROC)GetWindowTextAForDll);
//				EnableAPIHook(GetModuleHandle("MFC42.DLL"),"USER32.DLL","GetWindowTextA",(FARPROC)GetWindowTextAForDll);
//				return nRet;
//			}
//			EnableAPIHook(GetModuleHandle("MFC42.DLL"),"USER32.DLL","GetWindowTextA",(FARPROC)GetWindowTextAForDll))
#ifndef __ROOTKIT__H__
#define __ROOTKIT__H__
#if defined(PLATFORM_WINDOWS)

// DEBUG权限调整和远程注入
VOID SECURITY_IMP AdjustPrivilege(LONG dwProcessId,BOOL bEnable);
HANDLE SECURITY_IMP LoadLibraryRemote(DWORD dwProcessId,LPCSTR pszDllPath);

// 利用IAT替换接口函数
BOOL SECURITY_IMP SetAPIHook(HMODULE hModule,LPCSTR pszDllName,FARPROC pfnOrg,FARPROC pfnNew);
BOOL SECURITY_IMP EnableAPIHook(HMODULE hModule,LPCSTR pszDllName,LPCSTR pszFuncName,FARPROC pfnNew);
BOOL SECURITY_IMP DisableAPIHook(HMODULE hModule,LPCSTR pszDllName,LPCSTR pszFuncName,FARPROC pfnNew);


#endif // PLATFORM_WINDOWS
#endif // THIS_FILE
