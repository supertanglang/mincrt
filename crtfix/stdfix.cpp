#include "crtfix.h"
#include "xmath.h"
#include "undname.h"
#include "internal_shared.h"


struct __type_info_node {
	_SLIST_HEADER _Header;
};
__type_info_node __type_info_root_node{};


//void __cdecl _invoke_watson(wchar_t const* const expression, wchar_t const* const function_name, wchar_t const* const file_name, unsigned int const line_number, uintptr_t const reserved);
void __fastcall _guard_check_icall(void* dummy) { }
void __cdecl __report_rangecheckfailure() { }
void __cdecl __std_terminate(void) { terminate(); }
void __cdecl _invalid_parameter_noinfo_noreturn(void) { _CxxThrowException(NULL, NULL); }



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


	const char *_Syserror_map(int _Errcode)
	{
		return ("unknown error");
	}
	
	//lockit
	#define MAX_LOCK	8	/* must be power of two */
	static CRITICAL_SECTION mtx[MAX_LOCK];
	static long init = -1;


#if !_MULTI_THREAD
	#define _Mtxinit(mtx)
	#define _Mtxdst(mtx)
	#define _Mtxlock(mtx)
	#define _Mtxunlock(mtx)
#else
	#define _Mtxinit(mtx)	InitializeCriticalSection(mtx)
	#define _Mtxdst(mtx)	DeleteCriticalSection(mtx)
	#define _Mtxlock(mtx)	EnterCriticalSection(mtx)
	#define _Mtxunlock(mtx) LeaveCriticalSection(mtx)
#endif /* !_MULTI_THREAD */

	__thiscall _Init_locks::_Init_locks()
	{
		if (InterlockedIncrement(&init) == 0)
			for (int count = 0; count < MAX_LOCK; ++count)
				_Mtxinit(&mtx[count]);
	}

	__thiscall _Init_locks::~_Init_locks() _NOEXCEPT
	{
		if (InterlockedDecrement(&init) < 0)
			for (int count = 0; count < MAX_LOCK; ++count)
				_Mtxdst(&mtx[count]);
	}

	static _Init_locks initlocks;

	__thiscall _Lockit::_Lockit()
		: _Locktype(0)

	{
		_Mtxlock(&mtx[0]);
	}

	__thiscall _Lockit::_Lockit(int kind)
		: _Locktype(kind & (MAX_LOCK - 1))
	{
		if (_Locktype < MAX_LOCK)
			_Mtxlock(&mtx[_Locktype]);
	}

	__thiscall _Lockit::~_Lockit()
	{
		if (_Locktype < MAX_LOCK)
			_Mtxlock(&mtx[_Locktype]);
	}

	bool __cdecl uncaught_exception()
	{	
		return false;
	}

}

//export
FILE* __cdecl __acrt_iob_func(unsigned i) {
	return (&_iob[i]);
}

_CRT_BEGIN_C_HEADER
int __cdecl __std_type_info_compare(__std_type_info_data const* const lhs, __std_type_info_data const* const rhs)
{
	if (lhs == rhs){
		return 0;
	}
	return strcmp(lhs->_DecoratedName + 1, rhs->_DecoratedName + 1);
}

size_t __cdecl __std_type_info_hash(__std_type_info_data const* const data)
{
	// FNV-1a hash function for the undecorated name

#ifdef _WIN64
	static_assert(sizeof(size_t) == 8, "This code is for 64-bit size_t.");
	size_t const fnv_offset_basis = 14695981039346656037ULL;
	size_t const fnv_prime = 1099511628211ULL;
#else
	static_assert(sizeof(size_t) == 4, "This code is for 32-bit size_t.");
	size_t const fnv_offset_basis = 2166136261U;
	size_t const fnv_prime = 16777619U;
#endif

	size_t value = fnv_offset_basis;
	for (char const* it = data->_DecoratedName + 1; *it != '\0'; ++it)
	{
		value ^= static_cast<size_t>(static_cast<unsigned char>(*it));
		value *= fnv_prime;
	}

#ifdef _WIN64
	static_assert(sizeof(size_t) == 8, "This code is for 64-bit size_t.");
	value ^= value >> 32;
#else
	static_assert(sizeof(size_t) == 4, "This code is for 32-bit size_t.");
#endif

	return value;
}

char const* __cdecl __std_type_info_name(__std_type_info_data* const data, __type_info_node* const root_node)
{
	// First check to see if we've already cached the undecorated name; if we
	// have, we can just return it:
	{
		char const* const cached_undecorated_name = __crt_interlocked_read_pointer(&data->_UndecoratedName);
		if (cached_undecorated_name)
		{
			return cached_undecorated_name;
		}
	}

	__crt_unique_heap_ptr<char> undecorated_name(__unDName(
		nullptr,
		data->_DecoratedName + 1,
		0,
		[](size_t const n) { return _malloc_crt(n); },
		[](void*  const p) { return _free_crt(p);   },
		UNDNAME_32_BIT_DECODE | UNDNAME_TYPE_ONLY));

	if (!undecorated_name)
	{
		return nullptr; // CRT_REFACTOR TODO This is nonconforming
	}

	size_t undecorated_name_length = strlen(undecorated_name.get());
	while (undecorated_name_length != 0 && undecorated_name.get()[undecorated_name_length - 1] == ' ')
	{
		undecorated_name.get()[undecorated_name_length - 1] = '\0';
		--undecorated_name_length;
	}

	size_t const undecorated_name_count = undecorated_name_length + 1;
	size_t const node_size = sizeof(SLIST_ENTRY) + undecorated_name_count;

	__crt_unique_heap_ptr<void> node_block(_malloc_crt(node_size));
	if (!node_block)
	{
		return nullptr; // CRT_REFACTOR TODO This is nonconforming
	}

	PSLIST_ENTRY const node_header = static_cast<PSLIST_ENTRY>(node_block.get());
	char*        const node_string = reinterpret_cast<char*>(node_header + 1);

	*node_header = SLIST_ENTRY{};
	strcpy_s(node_string, undecorated_name_count, undecorated_name.get());

	char const* const cached_undecorated_name = __crt_interlocked_compare_exchange_pointer(
		&data->_UndecoratedName,
		node_string,
		nullptr);

	// If the cache already contained an undecorated name pointer, another
	// thread must have cached it while we were computing the undecorated
	// name.  Discard the string we created and return the cached string:
	if (cached_undecorated_name)
	{
		return cached_undecorated_name;
	}

	// Otherwise, we've successfully cached our string; link it into the list
	// and return it:
	node_block.detach();
	InterlockedPushEntrySList(&root_node->_Header, node_header);
	return node_string;
}


void __cdecl __std_exception_copy(
	__std_exception_data const* const from,
	__std_exception_data*       const to
)
{
	_ASSERTE(to->_What == nullptr && to->_DoFree == false);

	if (!from->_DoFree || !from->_What)
	{
		to->_What = from->_What;
		to->_DoFree = false;
	} else {
		to->_What = "unknown exception";
		to->_DoFree = false;
	}
}

void __cdecl __std_exception_destroy(
	__std_exception_data* const data
)
{
	if (data->_DoFree){
		free(const_cast<char*>(data->_What));
	}

	data->_DoFree = false;
	data->_What = nullptr;
}
_CRT_END_C_HEADER

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