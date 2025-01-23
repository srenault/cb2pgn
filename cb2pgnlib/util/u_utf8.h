#ifndef _U_UTF8_H
#define _U_UTF8_H

namespace util {
namespace utf8 {

inline char const* nextChar(char const* p) {
    unsigned char c = *p;
    if (c < 0x80) return p + 1;
    if (c < 0xC0) return p + 1;
    if (c < 0xE0) return p + 2;
    if (c < 0xF0) return p + 3;
    if (c < 0xF8) return p + 4;
    return p + 1;
}

} // namespace utf8
} // namespace util

#endif // _U_UTF8_H 