#include "crtfix.h"
#include "xmath.h"

//void __cdecl _invoke_watson(wchar_t const* const expression, wchar_t const* const function_name, wchar_t const* const file_name, unsigned int const line_number, uintptr_t const reserved);
void __fastcall _guard_check_icall(void* dummy) { }
void __cdecl __report_rangecheckfailure() { }
void __cdecl __std_terminate(void) { terminate(); }
void __cdecl _invalid_parameter_noinfo_noreturn(void) { _CxxThrowException(NULL, NULL); }

extern "C" double fmod(double _Xx, double _Yx);

namespace std
{
#ifdef __NOTHROW_T_DEFINED
	const nothrow_t nothrow;
#endif

	void __cdecl _Xbad_alloc() { _CxxThrowException(NULL, NULL); }
	void __cdecl _Xinvalid_argument(const char *_Message) { _CxxThrowException(NULL, NULL); }
	void __cdecl _Xlength_error(const char *_Message) { _CxxThrowException(NULL, NULL); }
	void __cdecl _Xout_of_range(const char *_Message) { _CxxThrowException(NULL, NULL); }
	void __cdecl _Xoverflow_error(const char *_Message) { _CxxThrowException(NULL, NULL); }
	void __cdecl _Xruntime_error(const char *_Message) { _CxxThrowException(NULL, NULL); }
	void __cdecl _Xbad_function_call() { _CxxThrowException(NULL, NULL); }
	void __cdecl _Xregex_error(int _Code) { _CxxThrowException(NULL, NULL); }

	int fpclassify(double x)
	{
		union { double d; uint64_t u; }u = { x };

		uint32_t exp = (uint32_t)((u.u & 0x7fffffffffffffffULL) >> 52);

		if (0 == exp) {
			if (u.u & 0x000fffffffffffffULL)
				return FP_SUBNORMAL;

			return FP_ZERO;
		}

		if (0x7ff == exp) {
			if (u.u & 0x000fffffffffffffULL)
				return FP_NAN;

			return FP_INFINITE;
		}

		return FP_NORMAL;
	}

	int fpclassify(float x)
	{
		return fpclassify((double)x);
	}

	float fmod(float _Xx, float _Yx)
	{
		return ::fmod((double)_Xx, (double)_Yx);
	}

	double fmod(double _Xx, double _Yx)
	{
		return ::fmod(_Xx, _Yx);
	}

	double asin(double x)
	{
		return ::asin(x);
	}

	bool isFloatIEEE754Negative(float f)
	{
		float d = f;
		if (sizeof(float) == sizeof(unsigned short int)) {
			return (*(unsigned short int *)(&d) >> (sizeof(unsigned short int)*CHAR_BIT - 1) == 1);
		} else if (sizeof(float) == sizeof(unsigned int)) {
			return (*(unsigned int *)(&d) >> (sizeof(unsigned int)*CHAR_BIT - 1) == 1);
		} else if (sizeof(float) == sizeof(unsigned long)) {
			return (*(unsigned long *)(&d) >> (sizeof(unsigned long)*CHAR_BIT - 1) == 1);
		} else if (sizeof(float) == sizeof(unsigned char)) {
			return (*(unsigned char *)(&d) >> (sizeof(unsigned char)*CHAR_BIT - 1) == 1);
		} else if (sizeof(float) == sizeof(unsigned long long)) {
			return (*(unsigned long long *)(&d) >> (sizeof(unsigned long long)*CHAR_BIT - 1) == 1);
		}
		return false; // Should never get here if you've covered all the potential types!
	}

	bool signbit(float x)
	{
		return isFloatIEEE754Negative(x);
	}

	int _dsign(double x)
	{
		enum { double_per_long = sizeof(double) / sizeof(long) };
		enum { long_msb = sizeof(long) * CHAR_BIT - 1 };
		union { double d; unsigned long i[double_per_long]; } u;
		unsigned long l;

		u.d = x;
#ifdef WORDS_BIGENDIAN
		l = u.i[0];
#else
		l = u.i[double_per_long - 1];
#endif
		return (int)(l >> long_msb);
	}

	bool signbit(double x)
	{
		return _dsign(x) != 0;
	}

	double atan(double x)
	{
		return ::atan(x);
	}

	double atan2(double x, double y)
	{
		return ::atan2(x, y);
	}

	bool isless(double x, double y)
	{
		if (!signbit(x) && signbit(y)) // + -
			return false;
		if (signbit(x) && !signbit(y)) // - +
			return true;
		return x < y;
	}

	double exp(double x)
	{
		return ::exp(x);
	}

	int isinf(double d)
	{
		return fpclassify(d) == FP_INFINITE;
/*
		int expon = 0;
		double val = frexp(d, &expon);
		if (expon == 1025) {
			if (val == 0.5) {
				return 1;
			} else if (val == -0.5) {
				return -1;
			} else {
				return 0;
			}
		} else {
			return 0;
		}
*/
	}

	int isnan(double d)
	{
		return fpclassify(d) == FP_NAN;
/*
		int expon = 0;
		double val = frexp(d, &expon);
		if (expon == 1025) {
			if (val == 0.5) {
				return 0;
			} else if (val == -0.5) {
				return 0;
			} else {
				return 1;
			}
		} else {
			return 0;
		}
*/
	}

	double log(double val)
	{
		return ::log(val);
	}

	float pow(float base, int exp) { return ::pow(base, exp); }
	float pow(float base, float exp) { return ::pow(base, exp); }
	double pow(int base, int exp) { return ::pow(base, exp); }
	double pow(double base, int exp) { return ::pow(base, exp); }
	double pow(double base, double exp) { return ::pow(base, exp); }

	double pow(int base, double exp)
	{
		return ::pow((double)base, exp);
	}

	double __cdecl copysign(double x, double y)
	{
		union { double f; uint64_t u; } ux, uy;

		ux.f = x;
		uy.f = y;

		ux.u &= 0x7fffffffffffffffULL;
		ux.u |= uy.u & 0x8000000000000000ULL;

		return ux.f;
	}

	__int64 abs(__int64 val)
	{
		return (val > 0 ? val : -val);
	}

	double floor(double x)
	{
		return ::floor(x);
	}

	float ceil(float x)
	{
		return ::ceil((double)x);
	}

	double ceil(double x)
	{
		return ::ceil(x);
	}

	double sqrt(double val)
	{
		return ::sqrt(val);
	}

	double acos(double val)
	{
		return ::acos(val);
	}

	double sin(double val)
	{
		return ::sin(val);
	}

	double cos(double val)
	{
		return ::cos(val);
	}

	double tan(double val)
	{
		return ::tan(val);
	}

	double ldexp(double x, int exponent)
	{
		return ::ldexp(x, exponent);
	}
}

FILE* __cdecl __acrt_iob_func(unsigned i) {
	return (&_iob[i]);
}

short __cdecl _dtest(_In_ double* _Px)
{
	_Dval *ps = (_Dval *)(char *)_Px;

	if ((ps->_Sh[_D0] & _DMASK) == _DMAX << _DOFF)
		return ((short)((ps->_Sh[_D0] & _DFRAC) != 0 || ps->_Sh[_D1] != 0
			|| ps->_Sh[_D2] != 0 || ps->_Sh[_D3] != 0 ? _NANCODE : _INFCODE));
	else if ((ps->_Sh[_D0] & ~_DSIGN) != 0 || ps->_Sh[_D1] != 0
		|| ps->_Sh[_D2] != 0 || ps->_Sh[_D3] != 0)
		return ((ps->_Sh[_D0] & _DMASK) == 0 ? _DENORM : _FINITE);
	else
		return (0);
}

short __cdecl _ldtest(_In_ long double* _Px)
{
	return _dtest((double *)_Px);
}

short __cdecl _fdtest(_In_ float* px)
{	/* categorize *px */
	_Fval *ps = (_Fval *)(char *)px;

	if ((ps->_Sh[_F0] & _FMASK) == _FMAX << _FOFF)
		return ((short)((ps->_Sh[_F0] & _FFRAC) != 0 || ps->_Sh[_F1] != 0
			? _NANCODE : _INFCODE));
	else if ((ps->_Sh[_F0] & ~_FSIGN) != 0 || ps->_Sh[_F1] != 0)
		return ((ps->_Sh[_F0] & _FMASK) == 0 ? _DENORM : _FINITE);
	else
		return (0);
}

errno_t __cdecl _controlfp_s(_Out_opt_ unsigned int* _CurrentState, _In_ unsigned int  _NewValue, _In_ unsigned int  _Mask)
{
	int state = _controlfp(_NewValue, _Mask);
	if (_CurrentState) *_CurrentState = state;
	return 0;
}