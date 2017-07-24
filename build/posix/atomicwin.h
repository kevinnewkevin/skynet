#ifndef atomicwin_h
#define atomicwin_h

#include <Windows.h>
#include <stdbool.h>
#include <stdint.h>
#include <Windows.h>

bool __cdecl ATOM_CAS(volatile int32_t *ptr, int32_t oval, int32_t nval);
bool __cdecl ATOM_CAS_POINTER(volatile void **ptr, void *oval, void *nval);

#define ATOM_INC(ptr)    InterlockedIncrement(ptr)
#define ATOM_INC16(ptr)  InterlockedIncrement16(ptr)
#define ATOM_FINC(ptr)   InterlockedExchangeAdd(ptr, 1)
//#define ATOM_FINC16(ptr) InterlockedExchangeAdd16(ptr, 1)
#define ATOM_DEC(ptr)    InterlockedDecrement(ptr)
#define ATOM_DEC16(ptr)  InterlockedDecrement16(ptr)
//#define ATOM_FDEC(ptr) InterlockedExchangeAdd(ptr, -1)

#define ATOM_ADD(ptr,n)  InterlockedAdd(ptr, n)
#define ATOM_SUB(ptr,n)  InterlockedAdd(ptr, -n)
#define ATOM_AND(ptr,n)  InterlockedAnd(ptr, n)

//#define __sync_add_and_fetch(ptr, value) InterlockedAdd(ptr, n);
//#define __sync_sub_and_fetch(ptr, value) InterlockedAdd(ptr, -n);

#endif // !atomicwin_H
