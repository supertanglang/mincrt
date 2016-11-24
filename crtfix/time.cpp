#include "crtfix.h"
#include <time.h>

_Check_return_wat_
_ACRTIMP errno_t __cdecl _localtime64_s(_Out_ struct tm* _Tm, _In_  __time64_t const* _Time)
{
	struct tm*t = _localtime64(_Time);
	if (t && _Tm) *_Tm = *t; 
	return 0;
}

_Check_return_wat_
_ACRTIMP struct tm* __cdecl _localtime32(_In_ __time32_t const* _Time)
{
	return localtime((const time_t*)_Time);
}

_Check_return_wat_ 
_ACRTIMP errno_t __cdecl _localtime32_s(_Out_ struct tm* _Tm, _In_  __time32_t const* _Time)
{
	struct tm*t = _localtime32(_Time);
	if (t && _Tm) *_Tm = *t;
	return 0;
}

_Check_return_wat_
_ACRTIMP errno_t __cdecl _gmtime64_s(_Out_ struct tm* _Tm, _In_  __time64_t const* _Time)
{

	struct tm*t = _gmtime64(_Time);
	if (t && _Tm) *_Tm = *t;
	return 0;
}
