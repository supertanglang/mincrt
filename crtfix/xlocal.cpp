#define _WIN32_WINNT _WIN32_WINNT_WINXP
#define WINVER _WIN32_WINNT
#define _CRT_SECURE_NO_WARNINGS
#define _CRTIMP
#define _STATIC_CPPLIB
#define _DISABLE_DEPRECATE_STATIC_CPPLIB

#include <windows.h>
#include <xlocale>
#include <xiosbase>

namespace std 
{
	static std::locale::_Locimp *global_locale = 0;	// pointer to current locale

	__PURE_APPDOMAIN_GLOBAL static locale classic_locale(_Noinit);	// "C" locale object, uninitialized

	__PURE_APPDOMAIN_GLOBAL locale::_Locimp *locale::_Locimp::_Clocptr = 0;	// pointer to classic_locale

	__PURE_APPDOMAIN_GLOBAL int locale::id::_Id_cnt = 0;	// unique id counter for facets

	__PURE_APPDOMAIN_GLOBAL locale::id ctype<char>::id(0);

	__PURE_APPDOMAIN_GLOBAL locale::id ctype<wchar_t>::id(0);

	__PURE_APPDOMAIN_GLOBAL locale::id codecvt<wchar_t, char, mbstate_t>::id(0);

#ifdef _NATIVE_WCHAR_T_DEFINED
	__PURE_APPDOMAIN_GLOBAL locale::id ctype<unsigned short>::id(0);

	__PURE_APPDOMAIN_GLOBAL locale::id codecvt<unsigned short, char, mbstate_t>::id(0);

#endif /* _NATIVE_WCHAR_T_DEFINED */


	std::locale::_Locimp *__cdecl locale::_Getgloballocale()
	{
		return (global_locale);
	}
	void __cdecl locale::_Setgloballocale(void *ptr) {
		global_locale = (std::locale::_Locimp *)ptr;
	}

	std::locale::_Locimp * locale::_Init(bool _Do_incref)
	{
		locale::_Locimp *ptr = 0;

		_BEGIN_LOCK(_LOCK_LOCALE)	// prevent double initialization

		ptr = _Getgloballocale();

		if (ptr == 0)
		{	// create new locales
			_Setgloballocale(ptr = _Locimp::_New_Locimp());
			ptr->_Catmask = all;	// set current locale to "C"
			ptr->_Name = "C";

			_Locimp::_Clocptr = ptr;	// set classic to match
			_Locimp::_Clocptr->_Incref();
			::new (&classic_locale) locale(_Locimp::_Clocptr);
		}

		if (_Do_incref)
			ptr->_Incref();

		_END_LOCK()
		return (ptr);
	}

	std::locale::_Locimp * __cdecl locale::_Locimp::_New_Locimp(bool _Transparent)
	{
		return (new _Locimp(_Transparent));
	}

	void __cdecl locale::_Locimp::_Locimp_dtor(_Locimp* _This)
	{
		_BEGIN_LOCK(_LOCK_LOCALE)
			for (size_t count = _This->_Facetcount; 0 < count; )
				if (_This->_Facetvec[--count] != 0)
					delete _This->_Facetvec[count]->_Decref();
		free(_This->_Facetvec);
		_END_LOCK()
	}

	void  __cdecl std::_Locinfo::_Locinfo_dtor(_Locinfo *pLocinfo)
	{
		if (!pLocinfo->_Oldlocname._Empty())
			setlocale(LC_ALL, pLocinfo->_Oldlocname._C_str());
	}

	void __cdecl std::_Locinfo::_Locinfo_ctor(_Locinfo *pLocinfo, const char *locname)
	{
		const char *oldlocname = setlocale(LC_ALL, 0);
		pLocinfo->_Oldlocname = oldlocname == 0 ? "" : oldlocname;
		if (locname != 0)
			locname = setlocale(LC_ALL, locname);
		pLocinfo->_Newlocname = locname == 0 ? "*" : locname;
	}


	#define NSTDSTR	8	/* cin, wcin, cout, wcout, cerr, wcerr, clog, wclog */

	_PGLOBAL _CRTDATA2 const streamoff _BADOFF = -1;	// initialize constant for bad file offset
	__PURE_APPDOMAIN_GLOBAL int ios_base::_Index = 0;	// initialize source of unique indexes
	__PURE_APPDOMAIN_GLOBAL bool ios_base::_Sync = true;	// initialize synchronization flag
	__PURE_APPDOMAIN_GLOBAL static ios_base *stdstr[NSTDSTR + 2] =
	{ 0 };	// [1, NSTDSTR] hold pointers to standard streams
	__PURE_APPDOMAIN_GLOBAL static char stdopens[NSTDSTR + 2] =
	{ 0 };	// [1, NSTDSTR] hold open counts for standard streams

	void __cdecl std::ios_base::_Ios_base_dtor(std::ios_base *_This)
	{
		if (0 < _This->_Stdstr && 0 < --stdopens[_This->_Stdstr])
			return;
		_This->_Tidy();
		delete _This->_Ploc;
	}

	void __cdecl std::ios_base::_Addstd(std::ios_base *_This)
	{
		_BEGIN_LOCK(_LOCK_STREAM)
			for (_This->_Stdstr = 0; ++_This->_Stdstr < NSTDSTR; )
				if (stdstr[_This->_Stdstr] == 0 || stdstr[_This->_Stdstr] == _This)
					break;	// found a candidate

		stdstr[_This->_Stdstr] = _This;
		++stdopens[_This->_Stdstr];
		_END_LOCK()
	}

	struct _Fac_node{
		_Fac_node(_Fac_node *_Nextarg, _Facet_base *_Facptrarg)
			: _Next(_Nextarg), _Facptr(_Facptrarg){
		}

		~_Fac_node() _NOEXCEPT {
			delete _Facptr->_Decref();
		}

#ifdef _DEBUG
		void * operator new(size_t _Size)
		{	// replace operator new
			void * _Ptr = _malloc_dbg(_Size > 0 ? _Size : 1, _CRT_BLOCK, __FILE__, __LINE__);
			if (!_Ptr)
				_Xbad_alloc();
			return (_Ptr);
		}

		void operator delete(void * _Ptr) _NOEXCEPT
		{	// replace operator delete
			_free_dbg(_Ptr, _CRT_BLOCK);
		}
#endif /* _DEBUG */

		_Fac_node *_Next;
		_Facet_base *_Facptr;
	};

	__PURE_APPDOMAIN_GLOBAL static _Fac_node *_Fac_head = 0;

	void _Facet_Register(_Facet_base * _This)
	{
		_Fac_head = new _Fac_node(_Fac_head, _This);
	}

}