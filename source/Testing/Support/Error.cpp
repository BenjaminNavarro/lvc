//===- llvm/Testing/Support/Error.cpp -------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "lvc/Testing/Support/Error.h"

#include "lvc/ADT/StringRef.h"

using namespace lvc;

lvc::detail::ErrorHolder lvc::detail::TakeError(lvc::Error Err) {
  std::vector<std::shared_ptr<ErrorInfoBase>> Infos;
  handleAllErrors(std::move(Err),
                  [&Infos](std::unique_ptr<ErrorInfoBase> Info) {
                    Infos.emplace_back(std::move(Info));
                  });
  return {std::move(Infos)};
}
