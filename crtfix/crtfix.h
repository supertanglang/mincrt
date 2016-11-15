#pragma once
#define _WIN32_WINNT _WIN32_WINNT_WINXP
#define WINVER _WIN32_WINNT
#define _CRT_SECURE_NO_WARNINGS
#define _CRTIMP
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdint.h>
#include <float.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <vcruntime_new.h>
#include <corecrt_terminate.h>

#ifdef __cplusplus
extern "C" {
#endif

__declspec(dllimport) extern FILE _iob[];
__declspec(dllimport) FILE * __cdecl __iob_func(void);

__declspec(dllimport) int _except_handler3(struct _EXCEPTION_RECORD * pExceptionRecord, struct EXCEPTION_REGISTRATION * pRegistrationFrame, struct _CONTEXT *pContextRecord, void * pDispatcherContext);
__declspec(dllimport) EXCEPTION_DISPOSITION __CxxFrameHandler(void *pExcept, void *pRN, void *pContext, void *pDC);


















#if __cplusplus
}
#endif