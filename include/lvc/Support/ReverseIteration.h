#ifndef LVC_SUPPORT_REVERSEITERATION_H
#define LVC_SUPPORT_REVERSEITERATION_H

#include "lvc/Config/abi-breaking.h"
#include "lvc/Support/PointerLikeTypeTraits.h"

namespace lvc {

template<class T = void *>
bool shouldReverseIterate() {
#if LVC_ENABLE_REVERSE_ITERATION
  return detail::IsPointerLike<T>::value;
#else
  return false;
#endif
}

}
#endif
