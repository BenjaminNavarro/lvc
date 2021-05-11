//===--- Annotations.cpp - Annotated source code for unit tests --*- C++-*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "lvc/Testing/Support/Annotations.h"

#include "lvc/ADT/StringExtras.h"
#include "lvc/Support/FormatVariadic.h"
#include "lvc/Support/raw_ostream.h"

using namespace lvc;

// Crash if the assertion fails, printing the message and testcase.
// More elegant error handling isn't needed for unit tests.
static void require(bool Assertion, const char *Msg, lvc::StringRef Code) {
  if (!Assertion) {
    lvc::errs() << "Annotated testcase: " << Msg << "\n" << Code << "\n";
    lvc_unreachable("Annotated testcase assertion failed!");
  }
}

Annotations::Annotations(lvc::StringRef Text) {
  auto Require = [Text](bool Assertion, const char *Msg) {
    require(Assertion, Msg, Text);
  };
  lvc::Optional<lvc::StringRef> Name;
  lvc::SmallVector<std::pair<lvc::StringRef, size_t>, 8> OpenRanges;

  Code.reserve(Text.size());
  while (!Text.empty()) {
    if (Text.consume_front("^")) {
      Points[Name.getValueOr("")].push_back(Code.size());
      Name = lvc::None;
      continue;
    }
    if (Text.consume_front("[[")) {
      OpenRanges.emplace_back(Name.getValueOr(""), Code.size());
      Name = lvc::None;
      continue;
    }
    Require(!Name, "$name should be followed by ^ or [[");
    if (Text.consume_front("]]")) {
      Require(!OpenRanges.empty(), "unmatched ]]");
      Range R;
      R.Begin = OpenRanges.back().second;
      R.End = Code.size();
      Ranges[OpenRanges.back().first].push_back(R);
      OpenRanges.pop_back();
      continue;
    }
    if (Text.consume_front("$")) {
      Name =
          Text.take_while([](char C) { return lvc::isAlnum(C) || C == '_'; });
      Text = Text.drop_front(Name->size());
      continue;
    }
    Code.push_back(Text.front());
    Text = Text.drop_front();
  }
  Require(!Name, "unterminated $name");
  Require(OpenRanges.empty(), "unmatched [[");
}

size_t Annotations::point(lvc::StringRef Name) const {
  auto I = Points.find(Name);
  require(I != Points.end() && I->getValue().size() == 1,
          "expected exactly one point", Code);
  return I->getValue()[0];
}

std::vector<size_t> Annotations::points(lvc::StringRef Name) const {
  auto I = Points.find(Name);
  if (I == Points.end())
    return {};
  return {I->getValue().begin(), I->getValue().end()};
}

Annotations::Range Annotations::range(lvc::StringRef Name) const {
  auto I = Ranges.find(Name);
  require(I != Ranges.end() && I->getValue().size() == 1,
          "expected exactly one range", Code);
  return I->getValue()[0];
}

std::vector<Annotations::Range>
Annotations::ranges(lvc::StringRef Name) const {
  auto I = Ranges.find(Name);
  if (I == Ranges.end())
    return {};
  return {I->getValue().begin(), I->getValue().end()};
}

lvc::raw_ostream &lvc::operator<<(lvc::raw_ostream &O,
                                    const lvc::Annotations::Range &R) {
  return O << lvc::formatv("[{0}, {1})", R.Begin, R.End);
}
