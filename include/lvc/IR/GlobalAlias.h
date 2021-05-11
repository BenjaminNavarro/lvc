//===-------- llvm/GlobalAlias.h - GlobalAlias class ------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the GlobalAlias class, which
// represents a single function or variable alias in the IR.
//
//===----------------------------------------------------------------------===//

#ifndef LVC_IR_GLOBALALIAS_H
#define LVC_IR_GLOBALALIAS_H

#include "lvc/ADT/ilist_node.h"
#include "lvc/IR/GlobalIndirectSymbol.h"
#include "lvc/IR/Value.h"

namespace lvc {

class Twine;
class Module;
template <typename ValueSubClass> class SymbolTableListTraits;

class GlobalAlias : public GlobalIndirectSymbol,
                    public ilist_node<GlobalAlias> {
  friend class SymbolTableListTraits<GlobalAlias>;

  GlobalAlias(Type *Ty, unsigned AddressSpace, LinkageTypes Linkage,
              const Twine &Name, Constant *Aliasee, Module *Parent);

public:
  GlobalAlias(const GlobalAlias &) = delete;
  GlobalAlias &operator=(const GlobalAlias &) = delete;

  /// If a parent module is specified, the alias is automatically inserted into
  /// the end of the specified module's alias list.
  static GlobalAlias *create(Type *Ty, unsigned AddressSpace,
                             LinkageTypes Linkage, const Twine &Name,
                             Constant *Aliasee, Module *Parent);

  // Without the Aliasee.
  static GlobalAlias *create(Type *Ty, unsigned AddressSpace,
                             LinkageTypes Linkage, const Twine &Name,
                             Module *Parent);

  // The module is taken from the Aliasee.
  static GlobalAlias *create(Type *Ty, unsigned AddressSpace,
                             LinkageTypes Linkage, const Twine &Name,
                             GlobalValue *Aliasee);

  // Type, Parent and AddressSpace taken from the Aliasee.
  static GlobalAlias *create(LinkageTypes Linkage, const Twine &Name,
                             GlobalValue *Aliasee);

  // Linkage, Type, Parent and AddressSpace taken from the Aliasee.
  static GlobalAlias *create(const Twine &Name, GlobalValue *Aliasee);

  /// removeFromParent - This method unlinks 'this' from the containing module,
  /// but does not delete it.
  ///
  void removeFromParent();

  /// eraseFromParent - This method unlinks 'this' from the containing module
  /// and deletes it.
  ///
  void eraseFromParent();

  /// These methods retrieve and set alias target.
  void setAliasee(Constant *Aliasee);
  const Constant *getAliasee() const {
    return getIndirectSymbol();
  }
  Constant *getAliasee() {
    return getIndirectSymbol();
  }

  static bool isValidLinkage(LinkageTypes L) {
    return isExternalLinkage(L) || isLocalLinkage(L) ||
      isWeakLinkage(L) || isLinkOnceLinkage(L);
  }

  // Methods for support type inquiry through isa, cast, and dyn_cast:
  static bool classof(const Value *V) {
    return V->getValueID() == Value::GlobalAliasVal;
  }
};

} // end namespace lvc

#endif // LVC_IR_GLOBALALIAS_H
