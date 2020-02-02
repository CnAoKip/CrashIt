#include <stdio.h>
#include "../CiHeader.h"

extern char timerstr[67];

/* CrashItUtil.cpp:
   Functions:
		char *_mktimerstring(void);
		
		long __stdcall CeUnhandledExceptionFilter(_EXCEPTION_POINTERS *excp);
 */





/* Function: _mktimerstring
 
 * Make a NON_WIDE string for the current time.
  
 * Arguments: None
  
 * Return Value: A pointer to the new string.
 
 */
 

void _displaylasterrorstring(){
	LPVOID lpMsgBuf;

    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                  FORMAT_MESSAGE_FROM_SYSTEM | 
                  FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL, GetLastError(),
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
            (LPTSTR) &lpMsgBuf, 0, NULL
    );
    int len = lstrlen((LPCSTR)lpMsgBuf);
    
    /*FIXME: The string formed by FormatMessage is ended with \r\n.*/
    *((LPSTR)lpMsgBuf + len - 2) = 0;
    *((LPSTR)lpMsgBuf + len - 1) = 0;
    
    printf("(\"%s\")\n\n", (LPSTR)lpMsgBuf);
    LocalFree(lpMsgBuf);
    return ;
}

char *_mktimerstring(char *timerstr){
	SYSTEMTIME systime;
	GetLocalTime(&systime);
	sprintf(timerstr,
			"%02d:%02d:%02d.%02d",
			systime.wHour,
			systime.wMinute,
			systime.wSecond,
			systime.wMilliseconds);
			
	return timerstr;
} 

/* Function: SetPrivilege
 
 * Sets the specified privilege.
  
 * Arguments:
 ****************************************************************
 *	LPCSTR lpPrivilegeName: specifies the desired privilege.
 
 *	WINBOOL fEnable: If this is FALSE, we disable all privileges.
 **************************************************************** 
 
 * Return Value: If succeed, the return value is nonzero.
 
 * To handle the error, use GetLastError();
 
 */
 
BOOL SetPrivilege(LPCSTR lpPrivilegeName, WINBOOL fEnable)
{
	printf("[%s]: Try to set privilege...\n", _mktimerstring(timerstr));
	
	HANDLE hToken; 
	TOKEN_PRIVILEGES NewState; 
	LUID luidPrivilegeLUID; 
 
	
	if(!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
	{ 
		
		/*If opening token failed...*/
		printf("[%s]: OpenProcessToken failed!", _mktimerstring(timerstr));
		_displaylasterrorstring();
		ExitProcess(1);
		
		return FALSE; 
	} 
	
	
	if(fEnable == FALSE) /*We disable all the privileges... */
	{
		if(!AdjustTokenPrivileges(hToken, TRUE, NULL, NULL, NULL, NULL))
		{
			printf("[%s]: AdjustTokenPrivileges failed!", _mktimerstring(timerstr));
			_displaylasterrorstring();
			ExitProcess(1);
			
			return FALSE;
		}
		else return TRUE;
	}
	/*Look up the LUID value of the privilege... */
	LookupPrivilegeValue(NULL, lpPrivilegeName, &luidPrivilegeLUID);
	
	NewState.PrivilegeCount = 1; 
	NewState.Privileges[0].Luid = luidPrivilegeLUID; 
	NewState.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
	/*Improve this process's privilege, so we can shut down the system next. */
	if(!AdjustTokenPrivileges(hToken, FALSE, &NewState, NULL, NULL, NULL))
	{
		printf("[%s]: AdjustTokenPrivileges failed!", _mktimerstring(timerstr));
		_displaylasterrorstring();
		ExitProcess(1);
		
		return FALSE;
	}
	
	/*We should not only check if the improving was successed... */
	if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
	{
		printf("[%s]: Failed to adjust the privilege!", _mktimerstring(timerstr));
		_displaylasterrorstring();
		ExitProcess(1);
		return FALSE;
	} 
	
	printf("[%s]: Succeeded to set privilege!\n", _mktimerstring(timerstr));
	return TRUE;
}


long __stdcall UtilBugCheckEx(ULONG StopCode, PVOID Argument1, PVOID Argument2, PVOID Argument3, PVOID Argument4){
	
	ULONG args[4] = {
		(ULONG)Argument1,
		(ULONG)Argument2,
		(ULONG)Argument3,
		(ULONG)Argument4
	};
	HMODULE hDll = GetModuleHandle(TEXT("ntdll.dll"));
    type_NtRaiseHardError NtRaiseHardError = (type_NtRaiseHardError)GetProcAddress(hDll, "NtRaiseHardError");
	
	if(NtRaiseHardError == NULL){
		printf("[%s]: GetProcAddress failed!", _mktimerstring(timerstr));
		_displaylasterrorstring();
		ExitProcess(1);
	}
	
	HARDERROR_RESPONSE Response;
	NTSTATUS ret = 0;
	bool bSuccess = SetPrivilege(SE_SHUTDOWN_NAME, TRUE);
	if(bSuccess) ret = NtRaiseHardError(StopCode, 4, NULL, args, OptionShutdownSystem, &Response);
	
	if(ret < 0){
		printf("[%s]: NtRaiseHardError failed with a status of %d.\n", _mktimerstring(timerstr), ret);
	}
	
	bSuccess = SetPrivilege(SE_SHUTDOWN_NAME, FALSE);
	return 0;   
}


/* EOF */
