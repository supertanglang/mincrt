#include "crtfix.h"

//wchar
_Check_return_wat_
_ACRTIMP errno_t __cdecl wcscpy_s(_Out_writes_z_(_SizeInWords) wchar_t* _Destination, _In_ rsize_t _SizeInWords, _In_z_ wchar_t const* _Source)
{
	wcscpy(_Destination, _Source);
	return 0;
}

_Check_return_wat_
_ACRTIMP errno_t __cdecl wcscat_s(_Inout_updates_z_(_SizeInWords) wchar_t* _Destination, _In_ rsize_t _SizeInWords, _In_z_ wchar_t const* _Source)
{
	wcscat(_Destination, _Source);
	return 0;
}

_Check_return_wat_
_ACRTIMP errno_t __cdecl wcsncat_s(_Inout_updates_z_(_SizeInWords) wchar_t* _Destination, _In_ rsize_t _SizeInWords, _In_reads_or_z_(_MaxCount) wchar_t const* _Source, _In_ rsize_t _MaxCount)
{
	wcsncat(_Destination, _Source, _MaxCount);
	return 0;
}

_Check_return_wat_
_ACRTIMP errno_t __cdecl wcsncpy_s(_Out_writes_z_(_SizeInWords) wchar_t* _Destination, _In_ rsize_t _SizeInWords, _In_reads_or_z_(_MaxCount) wchar_t const* _Source, _In_ rsize_t _MaxCount)
{
	wcsncpy(_Destination, _Source, _MaxCount);
	return 0;
}

_Check_return_
_ACRTIMP wchar_t* __cdecl wcstok_s(_Inout_opt_z_ wchar_t* _String, _In_z_ wchar_t const* _Delimiter, _Inout_ _Deref_prepost_opt_z_ wchar_t** _Context)
{
	return wcstok(_String, _Delimiter, _Context);
}

//char
_Check_return_
_ACRTIMP int __cdecl _tolower_l(int c, _locale_t plocinfo)
{
	return _tolower(c);
}

//format
int __CRTDECL _vsprintf_l(_Pre_notnull_ _Post_z_ char* const _Buffer, _In_z_ char const* const _Format, _In_opt_ _locale_t const _Locale, va_list _ArgList)
{
	return vsprintf(_Buffer, _Format, _ArgList);
}

int __CRTDECL _vsprintf_s_l(_Out_writes_z_(_BufferCount) char* const _Buffer, _In_ size_t const _BufferCount, _In_z_ _Printf_format_string_params_(2) char const* const _Format, _In_opt_ _locale_t const _Locale, va_list _ArgList)
{
	return _vsprintf_l(_Buffer, _Format, _Locale, _ArgList);
}

int __CRTDECL vsnprintf(_Out_writes_(_BufferCount) char* const _Buffer, _In_ size_t const _BufferCount, _In_z_ _Printf_format_string_ char const* const _Format, va_list _ArgList)
{
	return _vsnprintf(_Buffer, _BufferCount, _Format, _ArgList);
}

int __CRTDECL _vsnprintf_s(_Out_writes_z_(_BufferCount) char* const _Buffer, _In_ size_t const _BufferCount, _In_ size_t const _MaxCount, _In_z_ _Printf_format_string_ char const* const _Format, va_list _ArgList)
{
	return _vsnprintf(_Buffer, _BufferCount, _Format, _ArgList);
}