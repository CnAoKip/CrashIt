#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include "CiHeader.h"

char timerstr[67];

long WINAPI CeLeadSystemBug(DWORD dwFlags){
	switch(dwFlags){
		case SYSBUG_INVALID_KERNEL_HANDLE:{
			SysBugInvalidHandle();
			break;
		}
		
		case SYSBUG_CRITICAL_TERMINATION:{
			SysBugTerminateCsr();
			break;
		}
		
		case SYSBUG_CRITICAL_AND_EXIT:{
			SysBugCriticalExit();
			break;
		}
	}
	
	return 0;
}



long WINAPI CeBugCheckProc(ULONG ulFlags, ULONG ErrorMode, ULONG CheckCode){
	if(ulFlags == MD_SYSTEMBUG) return 0 & CeLeadSystemBug(ErrorMode);
	if(ulFlags == MD_RAISEDIRECTLY){
		UtilBugCheck(CheckCode);
		return -1;
	}
	else if(ulFlags == MD_CALLFUNCTIONS){
		switch(ErrorMode){
			case OPTION_STACK_OVERFLOW:{
				UtilBugCheck(STATUS_STACK_OVERFLOW);
				break;
			}
			
			case OPTION_ACCESS_VIOLATION:{
				UtilBugCheck(STATUS_ACCESS_VIOLATION);
				break;
			}
			
			
			
			case OPTION_BUFFER_OVERFLOW:{
				UtilBugCheck(STATUS_STACK_BUFFER_OVERRUN);
				break;
			}
			
			case OPTION_ACCESS_DENIED:{
				UtilBugCheck(0xC0000022);
				break;
			}
			
			case OPTION_INVALID_HANDLE:{
				UtilBugCheck(0xC0000008);
				break;
			}
			
			case OPTION_INTEGER_DEVIDED_BY_ZERO:{
				UtilBugCheck(STATUS_INTEGER_DIVIDE_BY_ZERO);
				break;
			}
			
			default: return -1;
		}
	}
	return 0;
}


int main(int argc, char *argv[]) {
	SetConsoleTitle("CrashIt v1.4.0");
		
	ULONG CallFlag = 0, CallCode = 0, CallMode = 0;
	BOOL ArgsRight = FALSE;
	
	if(argc > 1){
		/*if(!strcmp(argv[1], "/?")) print_help_();
		else*/ if(!strcmp(argv[1], "checkcode")){
			if(argc > 1) {
				CallFlag = MD_RAISEDIRECTLY;
				CallCode = strtoul(argv[2], NULL, 0);
				//printf("Argsright01\n");
				if(CallCode >= 0xC0000000 && CallCode <= 0xCFFFFFFF)ArgsRight = TRUE;
			}
		}
		else if(!strcmp(argv[1], "crash")){
			if(argc > 1){
				CallFlag = MD_CALLFUNCTIONS;
				CallMode = strtoul(argv[2], NULL, 0);
				//printf("Argsright02\n");
				if(CallMode >= OPTION_SMALLEST && CallMode <= OPTION_GREATEST)ArgsRight = TRUE; 
			}
		}
		
		else if(!strcmp(argv[1], "sysbug")){
			CallFlag = MD_SYSTEMBUG;
			CallMode = strtoul(argv[2], NULL, 0);
			//printf("Argsright02\n");
			if(CallMode >= SYSBUG_SMALLEST && CallMode <= SYSBUG_GREATEST)ArgsRight = TRUE; 
		}
	}
	
	if(argc <= 3) printf("\nCrashIt v1.4.0 - A loophole and Bug test program\nCopyright (C) 2017-2019 Handick Software Co.,Ltd.\n\n");
	else if(!strcmp(argv[3], "-q")) printf("\nCrashIt v1.4.0 - A loophole test program\nCopyright (C) 2017-2019 Handick Software Co.,Ltd.\n\n");
	 
	if(!ArgsRight) return 0 & printf(" ^Error - Illegal Input.\n\n");
	else CeBugCheckProc(CallFlag, CallMode, CallCode);
	
	return 0;
}
