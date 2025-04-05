#include "string_util.hpp"

// ======================== C L A S S ========================
// ===    StringUtil
// ======================== C L A S S ========================

void StringUtil::replace(std::string& str, const std::string_view oldSub, const std::string_view newSub) {
    size_t pos = 0;

    while ((pos = str.find(oldSub, pos)) != std::string::npos) {
        str.replace(pos, oldSub.length(), newSub);
        pos += newSub.length();
    }
}

const char* StringUtil::str_to_u8_then_cstr(const std::string& str) {
    return StringUtil::u8_to_cstr(StringUtil::str_to_u8(str));
}

const char* StringUtil::u8_to_cstr(const std::u8string& str) {
    return reinterpret_cast<const char*>(str.data());
}

std::u8string StringUtil::cstr_to_u8(const char* str) {
    return reinterpret_cast<const char8_t*>(str);
}

std::u8string StringUtil::str_to_u8(const std::string_view str) {
    return { str.begin(), str.end() };
}
