#pragma once
#ifndef atomic_lock_h
#define atomic_lock_h

#include <stdbool.h>

int __sync_fetch_and_sub(int *ptr, int value);
int __sync_fetch_and_add(int *ptr, int value);

int __sync_add_and_fetch(int *ptr, int value);
int __sync_sub_and_fetch(int *ptr, int value);
int __sync_and_and_fetch(int *ptr, int value);

bool __sync_bool_compare_and_swap(int *ptr, int oldval, int newval);
int  __sync_val_compare_and_swap(int *ptr, int oldval, int newval);

int __sync_lock_test_and_set(int *ptr, int value);
void __sync_lock_release(int *ptr);
void __sync_synchronize();

#endif // !atomic_lock_h
