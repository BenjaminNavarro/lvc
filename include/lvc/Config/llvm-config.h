/*===------- llvm/Config/llvm-config.h - llvm configuration -------*- C -*-===*/
/*                                                                            */
/* Part of the LLVM Project, under the Apache License v2.0 with LLVM          */
/* Exceptions.                                                                */
/* See https://llvm.org/LICENSE.txt for license information.                  */
/* SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception                    */
/*                                                                            */
/*===----------------------------------------------------------------------===*/

/* This file enumerates variables from the LLVM configuration so that they
   can be in exported headers and won't override package specific directives.
   This is a C header that can be included in the llvm-c headers. */

#ifndef LVC_CONFIG_H
#define LVC_CONFIG_H

/* Define if LVC_ENABLE_DUMP is enabled */
/* #undef LVC_ENABLE_DUMP */

/* Target triple LLVM will generate code for by default */
#define LVC_DEFAULT_TARGET_TRIPLE "x86_64-unknown-linux-gnu"

/* Define if threads enabled */
#define LVC_ENABLE_THREADS 1

/* Has gcc/MSVC atomic intrinsics */
#define LVC_HAS_ATOMICS 1

/* Host triple LLVM will be executed on */
#define LVC_HOST_TRIPLE "x86_64-unknown-linux-gnu"

/* LLVM architecture name for the native architecture, if available */
#define LVC_NATIVE_ARCH X86

/* LLVM name for the native AsmParser init function, if available */
#define LVC_NATIVE_ASMPARSER LLVMInitializeX86AsmParser

/* LLVM name for the native AsmPrinter init function, if available */
#define LVC_NATIVE_ASMPRINTER LLVMInitializeX86AsmPrinter

/* LLVM name for the native Disassembler init function, if available */
#define LVC_NATIVE_DISASSEMBLER LLVMInitializeX86Disassembler

/* LLVM name for the native Target init function, if available */
#define LVC_NATIVE_TARGET LLVMInitializeX86Target

/* LLVM name for the native TargetInfo init function, if available */
#define LVC_NATIVE_TARGETINFO LLVMInitializeX86TargetInfo

/* LLVM name for the native target MC init function, if available */
#define LVC_NATIVE_TARGETMC LLVMInitializeX86TargetMC

/* Define if this is Unixish platform */
#define LVC_ON_UNIX 1

/* Define if we have the Intel JIT API runtime support library */
#define LVC_USE_INTEL_JITEVENTS 0

/* Define if we have the oprofile JIT-support library */
#define LVC_USE_OPROFILE 0

/* Define if we have the perf JIT-support library */
#define LVC_USE_PERF 0

/* Major version of the LLVM API */
#define LVC_VERSION_MAJOR 13

/* Minor version of the LLVM API */
#define LVC_VERSION_MINOR 0

/* Patch version of the LLVM API */
#define LVC_VERSION_PATCH 0

/* LLVM version string */
#define LVC_VERSION_STRING "13.0.0git"

/* Whether LLVM records statistics for use with GetStatistics(),
 * PrintStatistics() or PrintStatisticsJSON()
 */
#define LVC_FORCE_ENABLE_STATS 0

/* Define if we have z3 and want to build it */
/* #undef LVC_WITH_Z3 */

/* Define if LLVM was built with a dependency to the libtensorflow dynamic library */
/* #undef LVC_HAVE_TF_API */

/* Define if LLVM was built with a dependency to the tensorflow compiler */
/* #undef LVC_HAVE_TF_AOT */

/* Define to 1 if you have the <sysexits.h> header file. */
#define HAVE_SYSEXITS_H 1

/* Define to 1 to enable the experimental new pass manager by default */
#define LVC_ENABLE_NEW_PASS_MANAGER 1

#endif
