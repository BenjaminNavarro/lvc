/*===------- llvm/Config/abi-breaking.h - llvm configuration -------*- C -*-===*/
/*                                                                            */
/* Part of the LLVM Project, under the Apache License v2.0 with LLVM          */
/* Exceptions.                                                                */
/* See https://llvm.org/LICENSE.txt for license information.                  */
/* SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception                    */
/*                                                                            */
/*===----------------------------------------------------------------------===*/

/* This file controls the C++ ABI break introduced in LLVM public header. */

#ifndef LVC_ABI_BREAKING_CHECKS_H
#define LVC_ABI_BREAKING_CHECKS_H

/* Define to enable checks that alter the LLVM C++ ABI */
#define LVC_ENABLE_ABI_BREAKING_CHECKS 1

/* Define to enable reverse iteration of unordered llvm containers */
#define LVC_ENABLE_REVERSE_ITERATION 0

/* Allow selectively disabling link-time mismatch checking so that header-only
   ADT content from LLVM can be used without linking libSupport. */
#if !defined(LVC_DISABLE_ABI_BREAKING_CHECKS_ENFORCING) || !LVC_DISABLE_ABI_BREAKING_CHECKS_ENFORCING

// ABI_BREAKING_CHECKS protection: provides link-time failure when clients build
// mismatch with LLVM
#if defined(_MSC_VER)
// Use pragma with MSVC
#define LVC_XSTR(s) LVC_STR(s)
#define LVC_STR(s) #s
#pragma detect_mismatch("LVC_ENABLE_ABI_BREAKING_CHECKS", LVC_XSTR(LVC_ENABLE_ABI_BREAKING_CHECKS))
#undef LVC_XSTR
#undef LVC_STR
#elif defined(_WIN32) || defined(__CYGWIN__) // Win32 w/o #pragma detect_mismatch
// FIXME: Implement checks without weak.
#elif defined(__cplusplus)
#if !(defined(_AIX) && defined(__GNUC__) && !defined(__clang__))
#define LVC_HIDDEN_VISIBILITY __attribute__ ((visibility("hidden")))
#else
// GCC on AIX does not support visibility attributes. Symbols are not
// exported by default on AIX.
#define LVC_HIDDEN_VISIBILITY
#endif
namespace lvc {
#if LVC_ENABLE_ABI_BREAKING_CHECKS
extern int EnableABIBreakingChecks;
LVC_HIDDEN_VISIBILITY
__attribute__((weak)) int *VerifyEnableABIBreakingChecks =
    &EnableABIBreakingChecks;
#else
extern int DisableABIBreakingChecks;
LVC_HIDDEN_VISIBILITY
__attribute__((weak)) int *VerifyDisableABIBreakingChecks =
    &DisableABIBreakingChecks;
#endif
}
#undef LVC_HIDDEN_VISIBILITY
#endif // _MSC_VER

#endif // LVC_DISABLE_ABI_BREAKING_CHECKS_ENFORCING

#endif
