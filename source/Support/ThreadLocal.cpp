//===- ThreadLocal.cpp - Thread Local Data ----------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements the lvc::sys::ThreadLocal class.
//
//===----------------------------------------------------------------------===//

#include "lvc/Support/ThreadLocal.h"
#include "lvc/Config/llvm-config.h"
#include "lvc/Support/Compiler.h"

//===----------------------------------------------------------------------===//
//=== WARNING: Implementation here must contain only TRULY operating system
//===          independent code.
//===----------------------------------------------------------------------===//

#if !defined(LVC_ENABLE_THREADS) || LVC_ENABLE_THREADS == 0
// Define all methods as no-ops if threading is explicitly disabled
namespace lvc {
using namespace sys;
ThreadLocalImpl::ThreadLocalImpl() : data() { }
ThreadLocalImpl::~ThreadLocalImpl() { }
void ThreadLocalImpl::setInstance(const void* d) {
  static_assert(sizeof(d) <= sizeof(data), "size too big");
  void **pd = reinterpret_cast<void**>(&data);
  *pd = const_cast<void*>(d);
}
void *ThreadLocalImpl::getInstance() {
  void **pd = reinterpret_cast<void**>(&data);
  return *pd;
}
void ThreadLocalImpl::removeInstance() {
  setInstance(nullptr);
}
}
#elif defined(LVC_ON_UNIX)
#include "Unix/ThreadLocal.inc"
#elif defined( _WIN32)
#include "Windows/ThreadLocal.inc"
#else
#warning Neither LVC_ON_UNIX nor _WIN32 set in Support/ThreadLocal.cpp
#endif
