// ======================================================================
// Author : $Author$
// Version: $Revision$
// Date   : $Date$
// Url    : $URL$
// ======================================================================

// ======================================================================
// Copyright: (C) 2009-2013 Gregor Cramer
// ======================================================================

// ======================================================================
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// ======================================================================

#ifndef _SYS_UTF8_H
#define _SYS_UTF8_H

#include "m_types.h"
#include "m_string.h"

namespace sys {
namespace utf8 {

typedef uint16_t uchar;

inline bool isTail(char c) { return (c & 0xc0) == 0x80; }
inline bool isFirst(char c) { return (c & 0xc0) != 0x80; }

inline uchar getChar(char const* str) {
    unsigned char c = *str;
    if (c < 0x80) return c;
    if (c < 0xE0) return ((c & 0x1F) << 6) | (str[1] & 0x3F);
    if (c < 0xF0) return ((c & 0x0F) << 12) | ((str[1] & 0x3F) << 6) | (str[2] & 0x3F);
    return 0;
}

inline char const* nextChar(char const* p) {
    unsigned char c = *p;
    if (c < 0x80) return p + 1;
    if (c < 0xC0) return p + 1;
    if (c < 0xE0) return p + 2;
    if (c < 0xF0) return p + 3;
    if (c < 0xF8) return p + 4;
    return p + 1;
}

inline char const* nextChar(char const* p, uchar& code) {
    code = getChar(p);
    return nextChar(p);
}

inline bool isAlpha(uchar uc) {
    return (uc >= 'A' && uc <= 'Z') || (uc >= 'a' && uc <= 'z');
}

inline bool isSpace(uchar uc) {
    return uc == ' ' || uc == '\t' || uc == '\n' || uc == '\r';
}

inline bool isAscii(uchar uc) {
    return uc < 0x80;
}

inline uchar toLower(uchar uc) {
    return (uc >= 'A' && uc <= 'Z') ? uc + ('a' - 'A') : uc;
}

inline uchar toUpper(uchar uc) {
    return (uc >= 'a' && uc <= 'z') ? uc - ('a' - 'A') : uc;
}

inline bool validate(char const* str) {
    while (*str) {
        unsigned char c = *str;
        if (c < 0x80) { str++; continue; }
        if (c < 0xC0) return false;
        if (c < 0xE0) {
            if ((str[1] & 0xC0) != 0x80) return false;
            str += 2;
        }
        else if (c < 0xF0) {
            if ((str[1] & 0xC0) != 0x80 || (str[2] & 0xC0) != 0x80) return false;
            str += 3;
        }
        else return false;
    }
    return true;
}

inline bool validate(mstl::string const& str) {
    return validate(str.c_str());
}

inline char const* skipSpaces(char const* p, char const* end) {
    while (p < end && isSpace(getChar(p))) p = nextChar(p);
    return p;
}

inline char const* skipNonSpaces(char const* p, char const* end) {
    while (p < end && !isSpace(getChar(p))) p = nextChar(p);
    return p;
}

inline char const* skipAlphas(char const* p, char const* end) {
    while (p < end && isAlpha(getChar(p))) p = nextChar(p);
    return p;
}

inline char const* skipNonAlphas(char const* p, char const* end) {
    while (p < end && !isAlpha(getChar(p))) p = nextChar(p);
    return p;
}

inline char const* prevChar(char const* p, char const* begin) {
    if (p <= begin) return begin;
    --p;
    while (p > begin && (*p & 0xC0) == 0x80) --p;
    return p;
}

inline char const* atIndex(char const* str, unsigned index) {
    while (index-- > 0 && *str) str = nextChar(str);
    return str;
}

inline void append(mstl::string& dst, uchar uc) {
    if (uc < 0x80) {
        dst += char(uc);
    }
    else if (uc < 0x800) {
        dst += char((uc >> 6) | 0xC0);
        dst += char((uc & 0x3F) | 0x80);
    }
    else {
        dst += char((uc >> 12) | 0xE0);
        dst += char(((uc >> 6) & 0x3F) | 0x80);
        dst += char((uc & 0x3F) | 0x80);
    }
}

inline int findFirst(char const* haystack, unsigned haystackLen, char const* needle, unsigned needleLen) {
    if (needleLen > haystackLen) return -1;
    for (unsigned i = 0; i <= haystackLen - needleLen; ++i) {
        if (strncmp(haystack + i, needle, needleLen) == 0) return i;
    }
    return -1;
}

inline int findFirstNoCase(char const* haystack, unsigned haystackLen, char const* needle, unsigned needleLen) {
    if (needleLen > haystackLen) return -1;
    for (unsigned i = 0; i <= haystackLen - needleLen; ++i) {
        if (strncasecmp(haystack + i, needle, needleLen) == 0) return i;
    }
    return -1;
}

inline unsigned countChars(char const* str, unsigned byteLength) {
    unsigned count = 0;
    char const* end = str + byteLength;
    while (str < end) {
        str = nextChar(str);
        ++count;
    }
    return count;
}

} // namespace utf8
} // namespace sys

#endif // _SYS_UTF8_H

// vi:set ts=3 sw=3:
