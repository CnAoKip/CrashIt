#include <windows.h>
#include <stdio.h>
#include "../CiHeader.h" 

extern char timerstr[67];

DWORD WINAPI SysBugInvalidHandle(void){
	HWINSTA hWinSta;
	hWinSta = CreateWindowStation("abc123", NULL, 55, NULL);
	if(hWinSta == NULL){
		printf("[%s]: CreateWindowStation failed!", _mktimerstring(timerstr));
		_displaylasterrorstring();
	}
	if(!SetHandleInformation(hWinSta, HANDLE_FLAG_PROTECT_FROM_CLOSE, HANDLE_FLAG_PROTECT_FROM_CLOSE)){
		printf("[%s]: SetHandleInformation failed!", _mktimerstring(timerstr));
		_displaylasterrorstring();
	}
	fflush(stdout);
	if(!CloseWindowStation(hWinSta)){
		printf("[%s]: CloseWindowStation failed!", _mktimerstring(timerstr));
		_displaylasterrorstring();
	}
			
	return GetLastError();
} 

DWORD WINAPI SysBugTerminateCsr(void){
	BOOL bSuccess = SetPrivilege(SE_DEBUG_NAME, TRUE);
	if(!bSuccess) ExitProcess(1);			
	HMODULE hDll = GetModuleHandle("ntdll.dll");
	type_CsrGetProcessId CsrGetProcessId = (type_CsrGetProcessId)GetProcAddress(hDll, "CsrGetProcessId");
		
	if(CsrGetProcessId == NULL){
		printf("[%s]: GetProcAddress failed!", _mktimerstring(timerstr));
		_displaylasterrorstring();
		ExitProcess(1);
	}	
	DWORD Pid = CsrGetProcessId();//拿到csrss.exe的PID 
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Pid);//通过PID拿到句柄 
			
	if(hProcess == NULL) {
		printf("[%s]: OpenProcess failed!", _mktimerstring(timerstr));
		_displaylasterrorstring();
		ExitProcess(1);
	}
	
	if(!TerminateProcess(hProcess, 0)) {
		printf("[%s]: TerminateProcess failed!", _mktimerstring(timerstr));
		_displaylasterrorstring();
	}
	
	return GetLastError();
}

DWORD WINAPI SysBugCriticalExit(void){
	BOOL bSuccess = SetPrivilege(SE_DEBUG_NAME, TRUE);
	if(!bSuccess) ExitProcess(1);			
	
	HMODULE hDll = GetModuleHandle("ntdll.dll");
	type_RtlSetProcessIsCritical RtlSetProcessIsCritical = (type_RtlSetProcessIsCritical)GetProcAddress(hDll, "RtlSetProcessIsCritical");
	if(RtlSetProcessIsCritical == NULL){
		printf("[%s]: GetProcAddress failed!", _mktimerstring(timerstr));
		_displaylasterrorstring();
		ExitProcess(1);
	}	
	
	RtlSetProcessIsCritical(TRUE, NULL, FALSE);

	fflush(stdout);
	Sleep(999); 
	if(!TerminateProcess(GetCurrentProcess(), 0)) {
		printf("[%s]: TerminateProcess failed!", _mktimerstring(timerstr));
		_displaylasterrorstring();
	}
	return GetLastError();
}
