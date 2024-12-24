#ifndef RIKKI_PATCHER_UTILS_STRING_UTIL_HPP
#define RIKKI_PATCHER_UTILS_STRING_UTIL_HPP
#include "precompiled.hpp"

class StringUtil {
public:
    static void replace(std::string& str, std::string_view oldSub, std::string_view newSub);
    static const char* u8_to_cstr(std::u8string_view str);
    static std::u8string cstr_to_u8(const char* str);
    static std::u8string str_to_u8(std::string_view str);
};


#endif //RIKKI_PATCHER_UTILS_STRING_UTIL_HPP
