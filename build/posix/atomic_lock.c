#include "atomic_lock.h"

#if defined(_WIN32) && defined(ASM)
__declspec(naked) int __sync_fetch_and_sub(int *p, int n) {
	__asm {
		push	ebp
		mov		ebp,esp
		mov		edx,[n]
		mov		eax,[p]
		neg		edx
		lock	xadd [eax],edx
		mov		edx,eax
		pop		ebp
		ret
	}
}

__declspec(naked) int __sync_fetch_and_add(int *p, int n) {
	__asm {
		push	ebp
		mov		ebp,esp
		mov		edx,[n]
		mov		eax,[p]
		lock	xadd [eax],edx
		mov		eax,edx
		pop		ebp
		ret
	}
}

__declspec(naked) int __sync_add_and_fetch(int *p, int n) {
	__asm {
		push	ebp
		mov		ebp,esp
		mov     ecx,[n]
		mov     edx,[p]
		mov		eax,ecx
		lock	xadd [edx],eax
		add		eax,ecx
		pop		ebp
		ret
	}
}

__declspec(naked) int __sync_sub_and_fetch(int *p, int n) {
	__asm {
		push	ebp
		mov		ebp,esp
		mov		eax,[n]
		mov		edx,[p]
		neg		eax
		mov		ecx,eax
		mov		eax,ecx
		lock	xadd [edx],eax
		add		eax,ecx
		pop		ebp
		ret
	}
}

__declspec(naked) int __sync_lock_test_and_set(int *p, int n) {
	__asm {
		push	ebp
		mov		ebp,esp
		mov		edx,[n]
		mov		eax,[p]
		xchg	[eax],edx
		mov		eax,edx
		pop		ebp
		ret
	}
}

__declspec(naked) void __sync_lock_release(int *p) {
	__asm {
		push	ebp
		mov		ebp,esp
		mov		eax,[p]
		mov		edx,0
		mov		[eax],edx
		nop
		pop		ebp
		ret
	}
}

__declspec(naked) void __sync_synchronize() {
	__asm {
		push	ebp
		mov		ebp,esp
		lock	or [esp],0
		pop		ebp
		ret
	}
}

__declspec(naked) char __sync_bool_compare_and_swap(int *p, int value, int compare) {
	__asm {
		push	ebp
		mov		ebp,esp
		mov		ecx,[compare]
		mov		eax,[value]
		mov		edx,[p]
		lock	cmpxchg [edx],ecx
		sete	al
		movzx	eax,al
		pop		ebp
		ret
	}
}

__declspec(naked) int __sync_and_and_fetch(int *p, int n) {
	__asm {
		push	ebp
		mov		ebp,esp
		push	esi
		push	ebx
		mov		esi,[n]
		mov		edx,[p]
		mov		eax,[edx]
retry:
		mov		ecx,eax
		and		ecx,esi
		mov		ebx,ecx
		lock	cmpxchg [edx],ecx
		sete	cl
		test	cl,cl
		je		retry
		mov		eax,ebx
		pop		ebx
		pop		esi
		pop		ebp
		ret
	}
}
#else
#include <Windows.h>
#include <pthread.h>
int __sync_fetch_and_sub(int *ptr, int value) {
	return InterlockedExchangeAdd(ptr, -value);
}

int __sync_fetch_and_add(int *ptr, int value) {
	return InterlockedExchangeAdd(ptr, value);
}

int __sync_add_and_fetch(int *ptr, int value) {
	return InterlockedAdd(ptr, value);
}

int __sync_sub_and_fetch(int *ptr, int value) {
	return InterlockedAdd(ptr, -value);
}

int __sync_and_and_fetch(int *ptr, int value) {
	return InterlockedAnd(ptr, value);
}

bool __sync_bool_compare_and_swap(int *ptr, int oldval, int newval) {
#if 1
	pthread_mutex_t mtx;
	pthread_mutex_init(&mtx, NULL);
	pthread_mutex_lock(&mtx);
	if (*ptr == oldval) {
		*ptr = newval;
		pthread_mutex_unlock(&mtx);
		pthread_mutex_destroy(&mtx);
		return true;
	}
	pthread_mutex_unlock(&mtx);
	pthread_mutex_destroy(&mtx);
	return false;
#else
	if (InterlockedCompareExchangeAcquire(ptr, newval, oldval) == oldval) {
		return false;
	} else {
		return true;
	}
#endif
}

int  __sync_val_compare_and_swap(int *ptr, int oldval, int newval) {
	return InterlockedCompareExchange(ptr, newval, oldval);
}

int __sync_lock_test_and_set(int *ptr, int value) {
	return InterlockedExchange(ptr, value);
}

void __sync_lock_release(int *ptr) {
	InterlockedExchange(ptr, 0);
}

void __sync_synchronize() {
	MemoryBarrier();
}

#endif