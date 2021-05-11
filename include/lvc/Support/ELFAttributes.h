//===-- ELFAttributes.h - ELF Attributes ------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LVC_SUPPORT_ELFATTRIBUTES_H
#define LVC_SUPPORT_ELFATTRIBUTES_H

#include "lvc/ADT/ArrayRef.h"
#include "lvc/ADT/StringRef.h"

namespace lvc {

struct TagNameItem {
  unsigned attr;
  StringRef tagName;
};

using TagNameMap = ArrayRef<TagNameItem>;

namespace ELFAttrs {

enum AttrType : unsigned { File = 1, Section = 2, Symbol = 3 };

StringRef attrTypeAsString(unsigned attr, TagNameMap tagNameMap,
                           bool hasTagPrefix = true);
Optional<unsigned> attrTypeFromString(StringRef tag, TagNameMap tagNameMap);

// Magic numbers for ELF attributes.
enum AttrMagic { Format_Version = 0x41 };

} // namespace ELFAttrs
} // namespace lvc
#endif
