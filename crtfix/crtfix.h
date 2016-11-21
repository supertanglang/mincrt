#pragma once
#define _WIN32_WINNT _WIN32_WINNT_WINXP
#define WINVER _WIN32_WINNT
#define _CRT_SECURE_NO_WARNINGS
#define _CRTIMP
#define _STATIC_CPPLIB
#define _DISABLE_DEPRECATE_STATIC_CPPLIB

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdint.h>
#include <locale.h>
#include <float.h>
#include <yvals.h>
#include <malloc.h>
#include <crtdbg.h>
#include <stdbool.h>
#include <intrin.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <vcruntime_new.h>
#include <corecrt_terminate.h>
#include <corecrt_wctype.h>

#pragma warning(disable:4273)
#pragma warning(disable:4996)

#ifdef __cplusplus
_CRT_BEGIN_C_HEADER
#endif

__declspec(dllimport) extern FILE _iob[];
__declspec(dllimport) FILE * __cdecl __iob_func(void);

__declspec(dllimport) int _except_handler3(struct _EXCEPTION_RECORD * pExceptionRecord, struct EXCEPTION_REGISTRATION * pRegistrationFrame, struct _CONTEXT *pContextRecord, void * pDispatcherContext);
__declspec(dllimport) EXCEPTION_DISPOSITION __CxxFrameHandler(void *pExcept, void *pRN, void *pContext, void *pDC);


#define _malloc_crt(s)          _malloc_dbg(s, _CRT_BLOCK, _THISFILE, __LINE__)
#define _calloc_crt(c, s)       _calloc_dbg(c, s, _CRT_BLOCK, _THISFILE, __LINE__)
#define _realloc_crt(p, s)      _realloc_dbg(p, s, _CRT_BLOCK, _THISFILE, __LINE__)
#define _recalloc_crt(p, c, s)  _recalloc_dbg(p, c, s, _CRT_BLOCK, _THISFILE, __LINE__)
#define _expand_crt(p, s)       _expand_dbg(p, s, _CRT_BLOCK)
#define _free_crt(p)            _free_dbg(p, _CRT_BLOCK)
#define _msize_crt(p)           _msize_dbg(p, _CRT_BLOCK)
#define _dupenv_s_crt(ps1, size, s2)    _dupenv_s_dbg(ps1, size, s2, _CRT_BLOCK, _THISFILE, __LINE__)
#define _wdupenv_s_crt(ps1, size, s2)   _wdupenv_s_dbg(ps1, size, s2, _CRT_BLOCK, _THISFILE, __LINE__)

#pragma warning(push)
#pragma warning(disable: 4510 4512 4610) // This type can never be instantiated
struct __std_type_info_data
{
	char const* _UndecoratedName;
	char const  _DecoratedName[1];
};
#pragma warning(pop)

struct __std_exception_data
{
	char const* _What;
	bool        _DoFree;
};

typedef struct _Ctypevec
{	/* stuff needed by _Tolower, etc. */
	unsigned long _Hand;	// LCID
	unsigned int _Page;		// UINT
	const short *_Table;
	int _Delfl;
} _Ctypevec;

typedef struct _Cvtvec
{	/* stuff needed by _Mbrtowc, etc. */
	unsigned long _Hand;	// LCID
	unsigned int _Page;		// UINT
	int _Isclocale;	// LCID == _CLOCALEHANDLE
	unsigned char _Isleadbyte[32];	// 256 bits
} _Cvtvec;

#define _CLOCALEHANDLE  0       /* "C" locale handle */

#define _cpp_isleadbyte(c) (__pctype_func()[(unsigned char)(c)] & _LEADBYTE)

__declspec(dllimport) int __cdecl __crtLCMapStringA(
	_locale_t _Plocinfo,
	LCID _Locale,
	DWORD _DwMapFlag,
	LPCSTR _LpSrcStr,
	int _CchSrc,
	LPSTR _LpDestStr,
	int _CchDest,
	int _Code_page,
	BOOL _BError
);

__declspec(dllimport) BOOL __cdecl __crtGetStringTypeW(
	_locale_t _Plocinfo,
	DWORD _DWInfoType,
	LPCWSTR _LpSrcStr,
	int _CchSrc,
	LPWORD _LpCharType,
	int _Code_page,
	int _Lcid
);

__declspec(dllimport) LCID* __cdecl ___lc_handle_func(void);






#if __cplusplus
_CRT_END_C_HEADER
#endif