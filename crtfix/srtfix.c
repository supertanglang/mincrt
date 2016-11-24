#include "crtfix.h"
#include "internal_shared.h"

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

_Check_return_wat_
_ACRTIMP errno_t __cdecl strcpy_s(_Out_writes_z_(_SizeInBytes) char* _Destination, _In_ rsize_t _SizeInBytes, _In_z_ char const* _Source)
{
	strcpy(_Destination, _Source);
	return 0;
}

_Check_return_wat_
_ACRTIMP errno_t __cdecl strcat_s(_Inout_updates_z_(_SizeInBytes) char* _Destination, _In_ rsize_t _SizeInBytes, _In_z_ char const* _Source)
{
	strcat(_Destination, _Source);
	return 0;
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

int __CRTDECL vsprintf_s(_Out_writes_z_(_BufferCount) char* const _Buffer, _In_ size_t const _BufferCount, _In_z_ _Printf_format_string_ char const* const _Format, va_list _ArgList)
{
	return _vsnprintf(_Buffer, _BufferCount, _Format, _ArgList);
}

int __CRTDECL sprintf_s(_Out_writes_z_(_BufferCount)  char* const _Buffer, _In_ size_t const _BufferCount, _In_z_ _Printf_format_string_ char const* const _Format, ...)
{
	int len;
	va_list args;
	__crt_va_start(args, _Format);
	len = vsnprintf(_Buffer, _BufferCount,_Format, args);
	__crt_va_end(args);
	return len;
}

int __CRTDECL snprintf(_Out_writes_z_(_BufferCount)  char* const _Buffer, _In_ size_t const _BufferCount, _In_z_ _Printf_format_string_ char const* const _Format, ...)
{
	int len;
	va_list args;
	__crt_va_start(args, _Format);
	len = vsnprintf(_Buffer, _BufferCount, _Format, args);
	__crt_va_end(args);
	return len;
}
int __CRTDECL swprintf_s(_Out_writes_z_(_BufferCount) wchar_t* const _Buffer, _In_ size_t const _BufferCount, _In_z_ _Printf_format_string_ wchar_t const* const _Format, ...)
{
	int len;
	va_list args;
	__crt_va_start(args, _Format);
	len = _vsnwprintf(_Buffer, _BufferCount, _Format, args);
	__crt_va_end(args);
	return len;
}

int __CRTDECL vswprintf_s(_Out_writes_z_(_BufferCount) wchar_t* const _Buffer, _In_ size_t const _BufferCount, _In_z_ _Printf_format_string_ wchar_t const* const _Format, va_list _ArgList)
{
	return _vsnwprintf(_Buffer, _BufferCount, _Format, _ArgList);
}

int __CRTDECL _vswprintf(_Pre_notnull_ _Post_z_ wchar_t* const _Buffer, _In_z_ _Printf_format_string_ wchar_t const* const _Format, va_list _ArgList)
{
	return vswprintf(_Buffer, _Format, _ArgList);
}

//
int __CRTDECL _Tolower(int c, const _Ctypevec *ploc)
{
	int size;
	unsigned char inbuffer[3];
	unsigned char outbuffer[3];

	LCID handle;
	UINT codepage;

	if (ploc == 0)
	{
		handle = ___lc_handle_func()[LC_CTYPE];
		codepage = ___lc_codepage_func();
	} else
	{
		handle = ploc->_Hand;
		codepage = ploc->_Page;
	}

	if (handle == _CLOCALEHANDLE)
	{
		if ((c >= 'A') && (c <= 'Z'))
			c = c + ('a' - 'A');
		return c;
	}

	/* if checking case of c does not require API call, do it */
	if ((unsigned)c < 256)
	{
		if (ploc == 0)
		{
			if (!isupper(c))
			{
				return c;
			}
		} else
		{
			if (!(ploc->_Table[c] & _UPPER))
			{
				return c;
			}
		}
	}

	/* convert int c to multibyte string */
	if (ploc == 0 ? _cpp_isleadbyte((c >> 8) & 0xff)
		: (ploc->_Table[(c >> 8) & 0xff] & _LEADBYTE) != 0)
	{
		inbuffer[0] = (c >> 8 & 0xff);
		inbuffer[1] = (unsigned char)c;
		inbuffer[2] = 0;
		size = 2;
	} else {
		inbuffer[0] = (unsigned char)c;
		inbuffer[1] = 0;
		size = 1;
	}

	/* convert wide char to lowercase */
	if (0 == (size = __crtLCMapStringA(NULL, handle, LCMAP_LOWERCASE,
		(const char *)inbuffer, size, (char *)outbuffer, 3, codepage, TRUE)))
	{
		return c;
	}

	/* construct integer return value */
	if (size == 1)
		return ((int)outbuffer[0]);
	else
		return ((int)outbuffer[1] | ((int)outbuffer[0] << 8));

}


int __CRTDECL _Toupper(int c, const _Ctypevec *ploc)
{
	int size;
	unsigned char inbuffer[3];
	unsigned char outbuffer[3];

	LCID handle;
	UINT codepage;

	if (ploc == 0)
	{
		handle = ___lc_handle_func()[LC_CTYPE];
		codepage = ___lc_codepage_func();
	} else
	{
		handle = ploc->_Hand;
		codepage = ploc->_Page;
	}

	if (handle == _CLOCALEHANDLE)
	{
		if ((c >= 'a') && (c <= 'z'))
			c = c - ('a' - 'A');
		return c;
	}

	/* if checking case of c does not require API call, do it */
	if ((unsigned)c < 256)
	{
		if (ploc == 0)
		{
			if (!islower(c))
			{
				return c;
			}
		} else
		{
			if (!(ploc->_Table[c] & _LOWER))
			{
				return c;
			}
		}
	}

	/* convert int c to multibyte string */
	if (ploc == 0 ? _cpp_isleadbyte((c >> 8) & 0xff)
		: (ploc->_Table[(c >> 8) & 0xff] & _LEADBYTE) != 0)
	{
		inbuffer[0] = (c >> 8 & 0xff);
		inbuffer[1] = (unsigned char)c;
		inbuffer[2] = 0;
		size = 2;
	} else {
		inbuffer[0] = (unsigned char)c;
		inbuffer[1] = 0;
		size = 1;
	}

	/* convert wide char to uppercase */
	if (0 == (size = __crtLCMapStringA(NULL, handle, LCMAP_UPPERCASE,
		(const char *)inbuffer, size, (char *)outbuffer, 3, codepage, TRUE)))
	{
		return c;
	}

	/* construct integer return value */
	if (size == 1)
		return ((int)outbuffer[0]);
	else
		return ((int)outbuffer[1] | ((int)outbuffer[0] << 8));

}

_Ctypevec __CRTDECL _Getctype()
{
	/* get ctype info for current locale */
	_Ctypevec ctype = {0};

	ctype._Hand = ___lc_handle_func()[LC_COLLATE];
	ctype._Page = ___lc_codepage_func();
	ctype._Table = (const short *)_calloc_crt(256, sizeof(*__pctype_func()));
	if (ctype._Table != 0)
	{
		memcpy((void *)ctype._Table, __pctype_func(), 256 * sizeof(*__pctype_func()));
		ctype._Delfl = 1;
	} else
	{
		ctype._Table = (const short *)__pctype_func();
		ctype._Delfl = 0;
	}

	return (ctype);
}

_Cvtvec __CRTDECL _Getcvt()
{
	_Cvtvec cvt = {0};
	cvt._Hand = ___lc_handle_func()[LC_CTYPE];
	cvt._Page = ___lc_codepage_func();
	return (cvt);
}
