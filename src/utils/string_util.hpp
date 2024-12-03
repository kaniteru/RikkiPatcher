#ifndef RIKKI_PATCHER_UTILS_STRING_UTIL_HPP
#define RIKKI_PATCHER_UTILS_STRING_UTIL_HPP
#include "precompiled.hpp"

class StringUtil {
public:
    static void replace(std::string& str, std::string_view oldSub, std::string_view newSub);
    static const char* u8_to_cstr(std::u8string_view str);
};


#endif //RIKKI_PATCHER_UTILS_STRING_UTIL_HPP
