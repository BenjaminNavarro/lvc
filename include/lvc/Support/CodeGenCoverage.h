//== llvm/Support/CodeGenCoverage.h ------------------------------*- C++ -*-==//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
/// \file This file provides rule coverage tracking for tablegen-erated CodeGen.
//===----------------------------------------------------------------------===//

#ifndef LVC_SUPPORT_CODEGENCOVERAGE_H
#define LVC_SUPPORT_CODEGENCOVERAGE_H

#include "lvc/ADT/BitVector.h"

namespace lvc {
class LLVMContext;
class MemoryBuffer;

class CodeGenCoverage {
protected:
  BitVector RuleCoverage;

public:
  using const_covered_iterator = BitVector::const_set_bits_iterator;

  CodeGenCoverage();

  void setCovered(uint64_t RuleID);
  bool isCovered(uint64_t RuleID) const;
  iterator_range<const_covered_iterator> covered() const;

  bool parse(MemoryBuffer &Buffer, StringRef BackendName);
  bool emit(StringRef FilePrefix, StringRef BackendName) const;
  void reset();
};
} // namespace lvc

#endif // LVC_SUPPORT_CODEGENCOVERAGE_H
