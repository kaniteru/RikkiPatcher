#include "string_util.hpp"

void StringUtil::replace(std::string& str, std::string_view oldSub, std::string_view newSub) {
    size_t pos = 0;

    while ((pos = str.find(oldSub, pos)) != std::string::npos) {
        str.replace(pos, oldSub.length(), newSub);
        pos += newSub.length();
    }
}

const char* StringUtil::u8_to_cstr(std::u8string_view str) {
    return reinterpret_cast<const char*>(str.data());
}
