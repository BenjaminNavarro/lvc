//===----- lib/Support/ExtensibleRTTI.cpp - ExtensibleRTTI utilities ------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "lvc/Support/ExtensibleRTTI.h"

void lvc::RTTIRoot::anchor() {}
char lvc::RTTIRoot::ID = 0;
