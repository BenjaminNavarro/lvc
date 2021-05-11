//===- ReplaceConstant.h - Replacing LLVM constant expressions --*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares the utility function for replacing LLVM constant
// expressions by instructions.
//
//===----------------------------------------------------------------------===//

#ifndef LVC_IR_REPLACECONSTANT_H
#define LVC_IR_REPLACECONSTANT_H

#include "lvc/IR/Constants.h"
#include "lvc/IR/Instruction.h"

namespace lvc {

/// Create a replacement instruction for constant expression \p CE and insert
/// it before \p Instr.
Instruction *createReplacementInstr(ConstantExpr *CE, Instruction *Instr);

} // end namespace lvc

#endif // LVC_IR_REPLACECONSTANT_H
