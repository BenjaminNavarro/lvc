//===- lib/Support/ErrorHandling.cpp - Callbacks for errors ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines an API used to indicate fatal error conditions.  Non-fatal
// errors (most of them) should be handled through LLVMContext.
//
//===----------------------------------------------------------------------===//

#include "lvc/ErrorHandling.h"
#include "lvc/SmallVector.h"
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <mutex>
#include <new>

#if defined(HAVE_UNISTD_H)
#include <unistd.h>
#endif
#if defined(_MSC_VER)
#include <fcntl.h>
#include <io.h>
#endif

using namespace lvc;

static fatal_error_handler_t ErrorHandler = nullptr;
static void *ErrorHandlerUserData = nullptr;

static fatal_error_handler_t BadAllocErrorHandler = nullptr;
static void *BadAllocErrorHandlerUserData = nullptr;

void lvc::report_fatal_error(const std::string &Reason, bool GenCrashDiag) {
  fatal_error_handler_t Handler = nullptr;
  void *HandlerData = nullptr;
  {
    // Only acquire the mutex while reading the handler, so as not to invoke a
    // user-supplied callback under a lock.
#if LVC_ENABLE_THREADS == 1
    std::lock_guard<std::mutex> Lock(BadAllocErrorHandlerMutex);
#endif
    Handler = BadAllocErrorHandler;
    HandlerData = BadAllocErrorHandlerUserData;
  }

  if (Handler) {
    Handler(HandlerData, Reason, GenCrashDiag);
    llvm_unreachable("bad alloc handler should not return");
  }

#ifdef LVC_ENABLE_EXCEPTIONS
  // If exceptions are enabled, make OOM in malloc look like OOM in new.
  throw std::bad_alloc();
#else
  // Don't call the normal error handler. It may allocate memory. Directly write
  // an OOM to stderr and abort.
  const char *OOMMessage = "LLVM ERROR: out of memory\n";
  const char *Newline = "\n";
  (void)!::write(2, OOMMessage, strlen(OOMMessage));
  (void)!::write(2, Reason.c_str(), Reason.size());
  (void)!::write(2, Newline, strlen(Newline));
  abort();
#endif
}

void lvc::report_fatal_error(const char *Reason, bool GenCrashDiag) {
  lvc::fatal_error_handler_t handler = nullptr;
  void *handlerData = nullptr;
  {
    // Only acquire the mutex while reading the handler, so as not to invoke a
    // user-supplied callback under a lock.
#if LVC_ENABLE_THREADS == 1
    std::lock_guard<std::mutex> Lock(ErrorHandlerMutex);
#endif
    handler = ErrorHandler;
    handlerData = ErrorHandlerUserData;
  }

  if (handler) {
    handler(handlerData, Reason, GenCrashDiag);
  } else {
    // Blast the result out to stderr.  We don't try hard to make sure this
    // succeeds (e.g. handling EINTR) and we can't use errs() here because
    // raw ostreams can call report_fatal_error.
    std::string msg = std::string{"LLVM ERROR: "} + Reason + "\n";
    ssize_t written = ::write(2, msg.c_str(), msg.size());
    (void)written; // If something went wrong, we deliberately just give up.
  }

  // If we reached here, we are failing ungracefully. Run the interrupt handlers
  // to make sure any special cleanups get done, in particular that we remove
  // files registered with RemoveFileOnSignal.
  // sys::RunInterruptHandlers(); TODO restore

  abort();
}

void lvc::report_bad_alloc_error(const char *Reason, bool GenCrashDiag) {
  fatal_error_handler_t Handler = nullptr;
  void *HandlerData = nullptr;
  {
    // Only acquire the mutex while reading the handler, so as not to invoke a
    // user-supplied callback under a lock.
#if LVC_ENABLE_THREADS == 1
    std::lock_guard<std::mutex> Lock(BadAllocErrorHandlerMutex);
#endif
    Handler = BadAllocErrorHandler;
    HandlerData = BadAllocErrorHandlerUserData;
  }

  if (Handler) {
    Handler(HandlerData, Reason, GenCrashDiag);
    llvm_unreachable("bad alloc handler should not return");
  }

#ifdef LVC_ENABLE_EXCEPTIONS
  // If exceptions are enabled, make OOM in malloc look like OOM in new.
  throw std::bad_alloc();
#else
  // Don't call the normal error handler. It may allocate memory. Directly write
  // an OOM to stderr and abort.
  const char *OOMMessage = "LLVM ERROR: out of memory\n";
  const char *Newline = "\n";
  (void)!::write(2, OOMMessage, strlen(OOMMessage));
  (void)!::write(2, Reason, strlen(Reason));
  (void)!::write(2, Newline, strlen(Newline));
  abort();
#endif
}

void lvc::llvm_unreachable_internal(const char *msg, const char *file,
                                    unsigned line) {
  // This code intentionally doesn't call the ErrorHandler callback, because
  // llvm_unreachable is intended to be used to indicate "impossible"
  // situations, and not legitimate runtime errors.
  if (msg)
    std::cout << msg << "\n";
  std::cout << "UNREACHABLE executed";
  if (file)
    std::cout << " at " << file << ":" << line;
  std::cout << "!\n";
  abort();
#ifdef LVC_BUILTIN_UNREACHABLE
  // Windows systems and possibly others don't declare abort() to be noreturn,
  // so use the unreachable builtin to avoid a Clang self-host warning.
  LVC_BUILTIN_UNREACHABLE;
#endif
}