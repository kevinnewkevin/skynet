#include "atomicwin.h"

#include <Windows.h>

bool ATOM_CAS(volatile int32_t *ptr, int32_t oval, int32_t nval) {
	InterlockedCompareExchange(ptr, nval, oval);
	return (*ptr == nval);
}

bool __cdecl ATOM_CAS_POINTER(volatile void **ptr, void *oval, void *nval) {
	InterlockedCompareExchangePointer(ptr, nval, oval);
	return (*ptr == nval);
}