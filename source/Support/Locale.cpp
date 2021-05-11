#include "lvc/Support/Locale.h"
#include "lvc/ADT/StringRef.h"
#include "lvc/Support/Unicode.h"

namespace lvc {
namespace sys {
namespace locale {

int columnWidth(StringRef Text) {
  return lvc::sys::unicode::columnWidthUTF8(Text);
}

bool isPrint(int UCS) {
  return lvc::sys::unicode::isPrintable(UCS);
}

} // namespace locale
} // namespace sys
} // namespace lvc
