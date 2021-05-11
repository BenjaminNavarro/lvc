//===- TargetSelect.h - Target Selection & Registration ---------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides utilities to make sure that certain classes of targets are
// linked into the main application executable, and initialize them as
// appropriate.
//
//===----------------------------------------------------------------------===//

#ifndef LVC_SUPPORT_TARGETSELECT_H
#define LVC_SUPPORT_TARGETSELECT_H

#include "lvc/Config/llvm-config.h"

extern "C" {
  // Declare all of the target-initialization functions that are available.
#define LVC_TARGET(TargetName) void LLVMInitialize##TargetName##TargetInfo();
#include "lvc/Config/Targets.def"

#define LVC_TARGET(TargetName) void LLVMInitialize##TargetName##Target();
#include "lvc/Config/Targets.def"

  // Declare all of the target-MC-initialization functions that are available.
#define LVC_TARGET(TargetName) void LLVMInitialize##TargetName##TargetMC();
#include "lvc/Config/Targets.def"

  // Declare all of the available assembly printer initialization functions.
#define LVC_ASM_PRINTER(TargetName) void LLVMInitialize##TargetName##AsmPrinter();
#include "lvc/Config/AsmPrinters.def"

  // Declare all of the available assembly parser initialization functions.
#define LVC_ASM_PARSER(TargetName) void LLVMInitialize##TargetName##AsmParser();
#include "lvc/Config/AsmParsers.def"

  // Declare all of the available disassembler initialization functions.
#define LVC_DISASSEMBLER(TargetName) \
  void LLVMInitialize##TargetName##Disassembler();
#include "lvc/Config/Disassemblers.def"
}

namespace lvc {
  /// InitializeAllTargetInfos - The main program should call this function if
  /// it wants access to all available targets that LLVM is configured to
  /// support, to make them available via the TargetRegistry.
  ///
  /// It is legal for a client to make multiple calls to this function.
  inline void InitializeAllTargetInfos() {
#define LVC_TARGET(TargetName) LLVMInitialize##TargetName##TargetInfo();
#include "lvc/Config/Targets.def"
  }

  /// InitializeAllTargets - The main program should call this function if it
  /// wants access to all available target machines that LLVM is configured to
  /// support, to make them available via the TargetRegistry.
  ///
  /// It is legal for a client to make multiple calls to this function.
  inline void InitializeAllTargets() {
    // FIXME: Remove this, clients should do it.
    InitializeAllTargetInfos();

#define LVC_TARGET(TargetName) LLVMInitialize##TargetName##Target();
#include "lvc/Config/Targets.def"
  }

  /// InitializeAllTargetMCs - The main program should call this function if it
  /// wants access to all available target MC that LLVM is configured to
  /// support, to make them available via the TargetRegistry.
  ///
  /// It is legal for a client to make multiple calls to this function.
  inline void InitializeAllTargetMCs() {
#define LVC_TARGET(TargetName) LLVMInitialize##TargetName##TargetMC();
#include "lvc/Config/Targets.def"
  }

  /// InitializeAllAsmPrinters - The main program should call this function if
  /// it wants all asm printers that LLVM is configured to support, to make them
  /// available via the TargetRegistry.
  ///
  /// It is legal for a client to make multiple calls to this function.
  inline void InitializeAllAsmPrinters() {
#define LVC_ASM_PRINTER(TargetName) LLVMInitialize##TargetName##AsmPrinter();
#include "lvc/Config/AsmPrinters.def"
  }

  /// InitializeAllAsmParsers - The main program should call this function if it
  /// wants all asm parsers that LLVM is configured to support, to make them
  /// available via the TargetRegistry.
  ///
  /// It is legal for a client to make multiple calls to this function.
  inline void InitializeAllAsmParsers() {
#define LVC_ASM_PARSER(TargetName) LLVMInitialize##TargetName##AsmParser();
#include "lvc/Config/AsmParsers.def"
  }

  /// InitializeAllDisassemblers - The main program should call this function if
  /// it wants all disassemblers that LLVM is configured to support, to make
  /// them available via the TargetRegistry.
  ///
  /// It is legal for a client to make multiple calls to this function.
  inline void InitializeAllDisassemblers() {
#define LVC_DISASSEMBLER(TargetName) LLVMInitialize##TargetName##Disassembler();
#include "lvc/Config/Disassemblers.def"
  }

  /// InitializeNativeTarget - The main program should call this function to
  /// initialize the native target corresponding to the host.  This is useful
  /// for JIT applications to ensure that the target gets linked in correctly.
  ///
  /// It is legal for a client to make multiple calls to this function.
  inline bool InitializeNativeTarget() {
  // If we have a native target, initialize it to ensure it is linked in.
#ifdef LVC_NATIVE_TARGET
    LVC_NATIVE_TARGETINFO();
    LVC_NATIVE_TARGET();
    LVC_NATIVE_TARGETMC();
    return false;
#else
    return true;
#endif
  }

  /// InitializeNativeTargetAsmPrinter - The main program should call
  /// this function to initialize the native target asm printer.
  inline bool InitializeNativeTargetAsmPrinter() {
  // If we have a native target, initialize the corresponding asm printer.
#ifdef LVC_NATIVE_ASMPRINTER
    LVC_NATIVE_ASMPRINTER();
    return false;
#else
    return true;
#endif
  }

  /// InitializeNativeTargetAsmParser - The main program should call
  /// this function to initialize the native target asm parser.
  inline bool InitializeNativeTargetAsmParser() {
  // If we have a native target, initialize the corresponding asm parser.
#ifdef LVC_NATIVE_ASMPARSER
    LVC_NATIVE_ASMPARSER();
    return false;
#else
    return true;
#endif
  }

  /// InitializeNativeTargetDisassembler - The main program should call
  /// this function to initialize the native target disassembler.
  inline bool InitializeNativeTargetDisassembler() {
  // If we have a native target, initialize the corresponding disassembler.
#ifdef LVC_NATIVE_DISASSEMBLER
    LVC_NATIVE_DISASSEMBLER();
    return false;
#else
    return true;
#endif
  }
}

#endif
