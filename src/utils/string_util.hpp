#ifndef RIKKI_PATCHER_UTILS_STRING_UTIL_HPP
#define RIKKI_PATCHER_UTILS_STRING_UTIL_HPP
#include "precompiled.hpp"

class StringUtil {
public:
    static void replace(std::string& str, std::string_view oldSub, std::string_view newSub);
};


#endif //RIKKI_PATCHER_UTILS_STRING_UTIL_HPP
