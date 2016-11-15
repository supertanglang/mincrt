#include "crtfix.h"

#ifdef _WIN64
#define DEFAULT_SECURITY_COOKIE 0x00002B992DDFA232
#else  /* _WIN64 */
#define DEFAULT_SECURITY_COOKIE 0xBB40E64E
#endif  /* _WIN64 */

/*
* The global security cookie.  This name is known to the compiler.
* Initialize to a garbage non-zero value just in case we have a buffer overrun
* in any code that gets run before __security_init_cookie() has a chance to
* initialize the cookie to the final value.
*/

DECLSPEC_SELECTANY UINT_PTR __security_cookie = DEFAULT_SECURITY_COOKIE;
DECLSPEC_SELECTANY UINT_PTR __security_cookie_complement = ~(DEFAULT_SECURITY_COOKIE);

void __fastcall __security_check_cookie(UINT_PTR cookie)
{
}

