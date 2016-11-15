#pragma once
#if defined(NDEBUG) && defined(_DLL)
#define _CRTIMP
#define _STATIC_CPPLIB
#define _DISABLE_DEPRECATE_STATIC_CPPLIB

#define _NO_CRT_STDIO_INLINE
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE

#pragma comment(linker, "/nodefaultlib:msvcrt.lib")
#pragma comment(linker, "/nodefaultlib:msvcprt.lib")

#pragma comment(lib,"msvcrt_xp.lib")
#pragma comment(lib,"msvcrt_fix.lib")

//You must append compile option /d2noftol3 or /arch:IA32
#endif