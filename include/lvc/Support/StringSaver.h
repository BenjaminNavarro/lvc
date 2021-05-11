//===- llvm/Support/StringSaver.h -------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LVC_SUPPORT_STRINGSAVER_H
#define LVC_SUPPORT_STRINGSAVER_H

#include "lvc/ADT/DenseSet.h"
#include "lvc/ADT/StringRef.h"
#include "lvc/ADT/Twine.h"
#include "lvc/Support/Allocator.h"

namespace lvc {

/// Saves strings in the provided stable storage and returns a
/// StringRef with a stable character pointer.
class StringSaver final {
  BumpPtrAllocator &Alloc;

public:
  StringSaver(BumpPtrAllocator &Alloc) : Alloc(Alloc) {}

  // All returned strings are null-terminated: *save(S).end() == 0.
  StringRef save(const char *S) { return save(StringRef(S)); }
  StringRef save(StringRef S);
  StringRef save(const Twine &S) { return save(StringRef(S.str())); }
  StringRef save(const std::string &S) { return save(StringRef(S)); }
};

/// Saves strings in the provided stable storage and returns a StringRef with a
/// stable character pointer. Saving the same string yields the same StringRef.
///
/// Compared to StringSaver, it does more work but avoids saving the same string
/// multiple times.
///
/// Compared to StringPool, it performs fewer allocations but doesn't support
/// refcounting/deletion.
class UniqueStringSaver final {
  StringSaver Strings;
  lvc::DenseSet<lvc::StringRef> Unique;

public:
  UniqueStringSaver(BumpPtrAllocator &Alloc) : Strings(Alloc) {}

  // All returned strings are null-terminated: *save(S).end() == 0.
  StringRef save(const char *S) { return save(StringRef(S)); }
  StringRef save(StringRef S);
  StringRef save(const Twine &S) { return save(StringRef(S.str())); }
  StringRef save(const std::string &S) { return save(StringRef(S)); }
};

} // namespace lvc
#endif
