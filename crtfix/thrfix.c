#include "crtfix.h"

int _Init_global_epoch = INT_MIN;
int _Init_thread_epoch = INT_MIN;
const int Uninitialized = 0;
const int BeingInitialized = -1;
const int EpochStart = INT_MIN;

void __cdecl _Init_thread_lock(void)
{

}

void __cdecl _Init_thread_unlock(void)
{

}


bool __cdecl _Init_thread_wait(DWORD const timeout)
{
	return true;
}

void __cdecl _Init_thread_notify(void)
{

}

void __cdecl _Init_thread_header(int* const pOnce)
{
	*pOnce = BeingInitialized;
}


void __cdecl _Init_thread_abort(int* const pOnce)
{

}

void __cdecl _Init_thread_footer(int* const pOnce)
{
	++_Init_global_epoch;
	*pOnce = _Init_global_epoch;
}

