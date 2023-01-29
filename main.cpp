#define UNICODE
#pragma comment(linker, "/opt:nowin98")
#include <windows.h>

typedef UINT (WINAPI* GETSYSTEMWOW64DIRECTORY)(LPTSTR, UINT);

EXTERN_C void __cdecl WinMainCRTStartup()
{
	
	TCHAR szTemp[1024];
	GETSYSTEMWOW64DIRECTORY getSystemWow64Directory;
	HMODULE hKernel32;
	TCHAR Wow64Directory[MAX_PATH];
	hKernel32 = GetModuleHandle(TEXT("kernel32.dll"));
	if (hKernel32 == NULL)
	{
		lstrcpy(szTemp,TEXT("32"));
	}
	else
	{
		getSystemWow64Directory = (GETSYSTEMWOW64DIRECTORY)GetProcAddress( hKernel32, "GetSystemWow64DirectoryW" );
		if (getSystemWow64Directory == NULL)
		{
			lstrcpy(szTemp,TEXT("32"));
		}
		else
		{
			if ((getSystemWow64Directory(Wow64Directory, sizeof(Wow64Directory)/sizeof(TCHAR)) == 0) && (GetLastError() == ERROR_CALL_NOT_IMPLEMENTED))
			{
				lstrcpy(szTemp,TEXT("32"));
			}
			else
			{
				lstrcpy(szTemp,TEXT("64"));
			}
		}
	}
	lstrcat(szTemp,TEXT(" ビット オペレーティング システム"));
	MessageBox(GetDesktopWindow(),szTemp,TEXT("システムの種類"),0);
	ExitProcess(0);
}

#if _DEBUG
void main(){}
#endif