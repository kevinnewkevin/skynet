#include "atomicwin.h"

#include <Windows.h>
#include "pthread.h"

bool __cdecl ATOM_CAS8(volatile int8_t *ptr, int8_t oval, int8_t nval) {
	pthread_mutex_t mtx;
	pthread_mutex_init(&mtx, NULL);
	pthread_mutex_lock(&mtx);
	if (ptr != NULL && *ptr == oval) {
		*ptr = nval;
		pthread_mutex_unlock(&mtx);
		pthread_mutex_destroy(&mtx);
		return true;
	}
	pthread_mutex_unlock(&mtx);
	pthread_mutex_destroy(&mtx);
	return false;
}

//bool ATOM_CAS16(volatile int16_t *ptr, int16_t oval, int16_t nval) {
//	InterlockedCompareExchange16(ptr, nval, oval);
//	return (*ptr == nval);
//}
//
//bool ATOM_CAS(volatile int32_t *ptr, int32_t oval, int32_t nval) {
//	InterlockedCompareExchange(ptr, nval, oval);
//	return (*ptr == nval);
//}

bool __cdecl ATOM_CAS_POINTER(volatile void **ptr, void *oval, void *nval) {
	InterlockedCompareExchangePointer(ptr, nval, oval);
	return (*ptr == nval);
}