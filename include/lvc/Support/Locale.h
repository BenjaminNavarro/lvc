#ifndef LVC_SUPPORT_LOCALE_H
#define LVC_SUPPORT_LOCALE_H

namespace lvc {
class StringRef;

namespace sys {
namespace locale {

int columnWidth(StringRef s);
bool isPrint(int c);

}
}
}

#endif // LVC_SUPPORT_LOCALE_H
