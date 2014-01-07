/* atomic.c -- implement atomic routines for Go.

   Copyright 2011 The Go Authors. All rights reserved.
   Use of this source code is governed by a BSD-style
   license that can be found in the LICENSE file.  */

//#include <stdint.h>
#include <u.h>

#include "runtime.h"

_Bool CompareAndSwapInt32 (int32 *, int32, int32)
  __asm__ (GOSYM_PREFIX "sync_atomic.CompareAndSwapInt32");

_Bool
CompareAndSwapInt32 (int32 *val, int32 old, int32 new)
{
  return __sync_bool_compare_and_swap (val, old, new);
}

_Bool CompareAndSwapInt64 (int64 *, int64, int64)
  __asm__ (GOSYM_PREFIX "sync_atomic.CompareAndSwapInt64");

_Bool
CompareAndSwapInt64 (int64 *val, int64 old, int64 new)
{
  return __sync_bool_compare_and_swap (val, old, new);
}

_Bool CompareAndSwapUint32 (uint32 *, uint32, uint32)
  __asm__ (GOSYM_PREFIX "sync_atomic.CompareAndSwapUint32");

_Bool
CompareAndSwapUint32 (uint32 *val, uint32 old, uint32 new)
{
  return __sync_bool_compare_and_swap (val, old, new);
}

_Bool CompareAndSwapUint64 (uint64 *, uint64, uint64)
  __asm__ (GOSYM_PREFIX "sync_atomic.CompareAndSwapUint64");

_Bool
CompareAndSwapUint64 (uint64 *val, uint64 old, uint64 new)
{
  return __sync_bool_compare_and_swap (val, old, new);
}

_Bool CompareAndSwapUintptr (uintptr_t *, uintptr_t, uintptr_t)
  __asm__ (GOSYM_PREFIX "sync_atomic.CompareAndSwapUintptr");

_Bool
CompareAndSwapUintptr (uintptr_t *val, uintptr_t old, uintptr_t new)
{
  return __sync_bool_compare_and_swap (val, old, new);
}

_Bool CompareAndSwapPointer (void **, void *, void *)
  __asm__ (GOSYM_PREFIX "sync_atomic.CompareAndSwapPointer");

_Bool
CompareAndSwapPointer (void **val, void *old, void *new)
{
  return __sync_bool_compare_and_swap (val, old, new);
}

int32 AddInt32 (int32 *, int32)
  __asm__ (GOSYM_PREFIX "sync_atomic.AddInt32");

int32
AddInt32 (int32 *val, int32 delta)
{
  return __sync_add_and_fetch (val, delta);
}

uint32 AddUint32 (uint32 *, uint32)
  __asm__ (GOSYM_PREFIX "sync_atomic.AddUint32");

uint32
AddUint32 (uint32 *val, uint32 delta)
{
  return __sync_add_and_fetch (val, delta);
}

int64 AddInt64 (int64 *, int64)
  __asm__ (GOSYM_PREFIX "sync_atomic.AddInt64");

int64
AddInt64 (int64 *val, int64 delta)
{
  return __sync_add_and_fetch (val, delta);
}

uint64 AddUint64 (uint64 *, uint64)
  __asm__ (GOSYM_PREFIX "sync_atomic.AddUint64");

uint64
AddUint64 (uint64 *val, uint64 delta)
{
  return __sync_add_and_fetch (val, delta);
}

uintptr_t AddUintptr (uintptr_t *, uintptr_t)
  __asm__ (GOSYM_PREFIX "sync_atomic.AddUintptr");

uintptr_t
AddUintptr (uintptr_t *val, uintptr_t delta)
{
  return __sync_add_and_fetch (val, delta);
}

int32 LoadInt32 (int32 *addr)
  __asm__ (GOSYM_PREFIX "sync_atomic.LoadInt32");

int32
LoadInt32 (int32 *addr)
{
  int32 v;

  v = *addr;
  while (! __sync_bool_compare_and_swap (addr, v, v))
    v = *addr;
  return v;
}

int64 LoadInt64 (int64 *addr)
  __asm__ (GOSYM_PREFIX "sync_atomic.LoadInt64");

int64
LoadInt64 (int64 *addr)
{
  int64 v;

  v = *addr;
  while (! __sync_bool_compare_and_swap (addr, v, v))
    v = *addr;
  return v;
}

uint32 LoadUint32 (uint32 *addr)
  __asm__ (GOSYM_PREFIX "sync_atomic.LoadUint32");

uint32
LoadUint32 (uint32 *addr)
{
  uint32 v;

  v = *addr;
  while (! __sync_bool_compare_and_swap (addr, v, v))
    v = *addr;
  return v;
}

uint64 LoadUint64 (uint64 *addr)
  __asm__ (GOSYM_PREFIX "sync_atomic.LoadUint64");

uint64
LoadUint64 (uint64 *addr)
{
  uint64 v;

  v = *addr;
  while (! __sync_bool_compare_and_swap (addr, v, v))
    v = *addr;
  return v;
}

uintptr_t LoadUintptr (uintptr_t *addr)
  __asm__ (GOSYM_PREFIX "sync_atomic.LoadUintptr");

uintptr_t
LoadUintptr (uintptr_t *addr)
{
  uintptr_t v;

  v = *addr;
  while (! __sync_bool_compare_and_swap (addr, v, v))
    v = *addr;
  return v;
}

void *LoadPointer (void **addr)
  __asm__ (GOSYM_PREFIX "sync_atomic.LoadPointer");

void *
LoadPointer (void **addr)
{
  void *v;

  v = *addr;
  while (! __sync_bool_compare_and_swap (addr, v, v))
    v = *addr;
  return v;
}

void StoreInt32 (int32 *addr, int32 val)
  __asm__ (GOSYM_PREFIX "sync_atomic.StoreInt32");

void
StoreInt32 (int32 *addr, int32 val)
{
  int32 v;

  v = *addr;
  while (! __sync_bool_compare_and_swap (addr, v, val))
    v = *addr;
}

void StoreInt64 (int64 *addr, int64 val)
  __asm__ (GOSYM_PREFIX "sync_atomic.StoreInt64");

void
StoreInt64 (int64 *addr, int64 val)
{
  int64 v;

  v = *addr;
  while (! __sync_bool_compare_and_swap (addr, v, val))
    v = *addr;
}

void StoreUint32 (uint32 *addr, uint32 val)
  __asm__ (GOSYM_PREFIX "sync_atomic.StoreUint32");

void
StoreUint32 (uint32 *addr, uint32 val)
{
  uint32 v;

  v = *addr;
  while (! __sync_bool_compare_and_swap (addr, v, val))
    v = *addr;
}

void StoreUint64 (uint64 *addr, uint64 val)
  __asm__ (GOSYM_PREFIX "sync_atomic.StoreUint64");

void
StoreUint64 (uint64 *addr, uint64 val)
{
  uint64 v;

  v = *addr;
  while (! __sync_bool_compare_and_swap (addr, v, val))
    v = *addr;
}

void StoreUintptr (uintptr_t *addr, uintptr_t val)
  __asm__ (GOSYM_PREFIX "sync_atomic.StoreUintptr");

void
StoreUintptr (uintptr_t *addr, uintptr_t val)
{
  uintptr_t v;

  v = *addr;
  while (! __sync_bool_compare_and_swap (addr, v, val))
    v = *addr;
}

void StorePointer (void **addr, void *val)
  __asm__ (GOSYM_PREFIX "sync_atomic.StorePointer");

void
StorePointer (void **addr, void *val)
{
  void *v;

  v = *addr;
  while (! __sync_bool_compare_and_swap (addr, v, val))
    v = *addr;
}
