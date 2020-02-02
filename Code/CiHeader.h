/* CiHeader.h - Copyrights (C) 2017-2018 Handick Software Co.,Ltd. All rights reserved.
 *
 * This is a part of Cak-Elib - CrashIt.
 *
 * 
 * Abstract:
 * Declartions of marcos and some functions.
 *
 *
 *  
 */


#ifndef _CIHEADER_
#define _CIHEADER_

#include <windows.h>


#define MD_CALLFUNCTIONS 0x00000001
#define MD_RAISEDIRECTLY 0x00000002
#define MD_SYSTEMBUG 0x00000003

#define OPTION_SMALLEST 0x00000001

#define OPTION_STACK_OVERFLOW 0x00000001
#define OPTION_ACCESS_VIOLATION 0x00000002
#define OPTION_BUFFER_OVERFLOW 0x00000003
#define OPTION_ACCESS_DENIED 0x00000004
#define OPTION_INVALID_HANDLE 0x00000005
#define OPTION_INTEGER_DEVIDED_BY_ZERO 0x00000006

#define OPTION_GREATEST OPTION_INTEGER_DEVIDED_BY_ZERO



#define SYSBUG_SMALLEST 0x00000001

#define SYSBUG_INVALID_KERNEL_HANDLE 0x00000001
#define SYSBUG_CRITICAL_TERMINATION 0x00000002
#define SYSBUG_CRITICAL_AND_EXIT 0x00000003

#define SYSBUG_GREATEST SYSBUG_CRITICAL_AND_EXIT


typedef enum _HARDERROR_RESPONSE_OPTION {
    OptionAbortRetryIgnore,
    OptionOk,
    OptionOkCancel,
    OptionRetryCancel,
    OptionYesNo,
    OptionYesNoCancel,
    OptionShutdownSystem,
    OptionOkNoWait,
    OptionCancelTryContinue
} HARDERROR_RESPONSE_OPTION, *PHARDERROR_RESPONSE_OPTION;

typedef enum _HARDERROR_RESPONSE {
    ResponseReturnToCaller,
    ResponseNotHandled,
    ResponseAbort,
    ResponseCancel,
    ResponseIgnore,
    ResponseNo,
    ResponseOk,
    ResponseRetry,
    ResponseYes
} HARDERROR_RESPONSE, *PHARDERROR_RESPONSE;


typedef struct _UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
    PWCH   Buffer;
} UNICODE_STRING, *PUNICODE_STRING;


typedef LONG (WINAPI *type_NtRaiseHardError)
(NTSTATUS ErrorStatus,
 ULONG NumberOfParameters,
 PUNICODE_STRING UnicodeStringParameterMask,
 PULONG_PTR Parameters,
 HARDERROR_RESPONSE_OPTION ValidResponseOptions,
 PHARDERROR_RESPONSE Response);
 
typedef DWORD (*type_CsrGetProcessId)();
typedef VOID (WINAPI * type_RtlSetProcessIsCritical)(BOOLEAN, PBOOLEAN, BOOLEAN);




void _displaylasterrorstring(); 
char *_mktimerstring(char *timerstr);
		
long __stdcall UtilBugCheckEx(ULONG StopCode, PVOID Argument1, PVOID Argument2, PVOID Argument3, PVOID Argument4);

#define UtilBugCheck(ErrorStatus) UtilBugCheckEx(ErrorStatus, 0, 0, 0, 0)
BOOL SetPrivilege(LPCSTR lpPrivilegeName, WINBOOL fEnable);

DWORD WINAPI SysBugInvalidHandle(void);
DWORD WINAPI SysBugTerminateCsr(void);
DWORD WINAPI SysBugCriticalExit(void);

#endif /*CiHeader.h*/

