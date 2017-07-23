#include "atomicwin.h"

#include <Windows.h>

//bool ATOM_CAS16(volatile int16_t *ptr, int16_t oval, int16_t nval) {
//	InterlockedCompareExchange16(ptr, nval, oval);
//	return (*ptr == nval);
//}
//
bool ATOM_CAS(volatile int32_t *ptr, int32_t oval, int32_t nval) {
	InterlockedCompareExchange(ptr, nval, oval);
	return (*ptr == nval);
}

bool __cdecl ATOM_CAS_POINTER(volatile void **ptr, void *oval, void *nval) {
	InterlockedCompareExchangePointer(ptr, nval, oval);
	return (*ptr == nval);
}