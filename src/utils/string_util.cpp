#include "string_util.hpp"
#include "logger.hpp"

// ======================== C L A S S ========================
// ===    StringUtil
// ======================== C L A S S ========================

void StringUtil::replace(std::string& str, const std::string_view oldSub, const std::string_view newSub) {
    if (oldSub.empty()) {
        return;
    }

    size_t pos = 0;

    while ((pos = str.find(oldSub, pos)) != std::string::npos) {
        str.replace(pos, oldSub.length(), newSub);
        pos += newSub.length();
    }
}

std::u8string StringUtil::str_to_u8(const std::string_view str) {
    return { reinterpret_cast<const char8_t*>(str.data()), str.size() };
}

std::string StringUtil::u8_to_str(const std::u8string_view str) {
    return { reinterpret_cast<const char*>(str.data()), str.size() };
}

const char* StringUtil::u8_to_cstr(const std::u8string_view str) {
    return reinterpret_cast<const char*>(str.data());
}

std::u8string StringUtil::wstr_to_u8(const std::wstring_view str) {
    std::u8string res { };
    res.reserve(str.size() * 3); // worst case scenario for UTF-8 encoding

    for (const wchar_t it : str) {
        if (it <= 0x7F) {
            // ASCII range - single byte
            res.push_back(static_cast<char8_t>(it));
        }
        else if (it <= 0x7FF) {
            // 2-byte sequence
            res.push_back(static_cast<char8_t>(0xC0 | (it >> 6)));
            res.push_back(static_cast<char8_t>(0x80 | (it & 0x3F)));
        }
        else if (it <= 0xFFFF) {
            // 3-byte sequence
            res.push_back(static_cast<char8_t>(0xE0 | (it >> 12)));
            res.push_back(static_cast<char8_t>(0x80 | ((it >> 6) & 0x3F)));
            res.push_back(static_cast<char8_t>(0x80 | (it & 0x3F)));
        }
        else if (it <= 0x10FFFF) {
            // 4-byte sequence (for characters outside BMP)
            char32_t c32 = static_cast<char32_t>(it);
            res.push_back(static_cast<char8_t>(0xF0 | (c32 >> 18)));
            res.push_back(static_cast<char8_t>(0x80 | ((c32 >> 12) & 0x3F)));
            res.push_back(static_cast<char8_t>(0x80 | ((c32 >> 6) & 0x3F)));
            res.push_back(static_cast<char8_t>(0x80 | (c32 & 0x3F)));
        }
        else {
            // Invalid Unicode code point
            res.push_back(static_cast<char8_t>('?'));
        }
    }

    return res;
}

std::string StringUtil::wstr_to_str(const std::wstring_view str) {
    const auto u8str = StringUtil::wstr_to_u8(str);
    return StringUtil::u8_to_str(u8str);
}
