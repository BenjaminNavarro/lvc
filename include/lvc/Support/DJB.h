//===-- llvm/Support/DJB.h ---DJB Hash --------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains support for the DJ Bernstein hash function.
//
//===----------------------------------------------------------------------===//

#ifndef LVC_SUPPORT_DJB_H
#define LVC_SUPPORT_DJB_H

#include "lvc/ADT/StringRef.h"

namespace lvc {

/// The Bernstein hash function used by the DWARF accelerator tables.
inline uint32_t djbHash(StringRef Buffer, uint32_t H = 5381) {
  for (unsigned char C : Buffer.bytes())
    H = (H << 5) + H + C;
  return H;
}

/// Computes the Bernstein hash after folding the input according to the Dwarf 5
/// standard case folding rules.
uint32_t caseFoldingDjbHash(StringRef Buffer, uint32_t H = 5381);
} // namespace lvc

#endif // LVC_SUPPORT_DJB_H
