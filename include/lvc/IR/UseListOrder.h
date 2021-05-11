//===- llvm/IR/UseListOrder.h - LLVM Use List Order -------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file has structures and command-line options for preserving use-list
// order.
//
//===----------------------------------------------------------------------===//

#ifndef LVC_IR_USELISTORDER_H
#define LVC_IR_USELISTORDER_H

#include <cstddef>
#include <vector>

namespace lvc {

class Function;
class Value;

/// Structure to hold a use-list order.
struct UseListOrder {
  const Value *V = nullptr;
  const Function *F = nullptr;
  std::vector<unsigned> Shuffle;

  UseListOrder(const Value *V, const Function *F, size_t ShuffleSize)
      : V(V), F(F), Shuffle(ShuffleSize) {}

  UseListOrder() = default;
  UseListOrder(UseListOrder &&) = default;
  UseListOrder &operator=(UseListOrder &&) = default;
};

using UseListOrderStack = std::vector<UseListOrder>;

} // end namespace lvc

#endif // LVC_IR_USELISTORDER_H
