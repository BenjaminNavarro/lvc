//===---- Watchdog.cpp - Implement Watchdog ---------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
//  This file implements the Watchdog class.
//
//===----------------------------------------------------------------------===//

#include "lvc/Support/Watchdog.h"
#include "lvc/Config/llvm-config.h"

// Include the platform-specific parts of this class.
#ifdef LVC_ON_UNIX
#include "Unix/Watchdog.inc"
#endif
#ifdef _WIN32
#include "Windows/Watchdog.inc"
#endif
