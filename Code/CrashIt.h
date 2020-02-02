#ifndef _CRASHIT_H
#define _CRASHIT_H
#include "CiHeader.h"



#endif
#pragma once
char timerstr[67];
char *_mktimerstring(void);
		
long __stdcall CeUnhandledExceptionFilter(_EXCEPTION_POINTERS *excp);

BOOL SetPrivilege(LPCSTR lpPrivilegeName, WINBOOL fEnable);
