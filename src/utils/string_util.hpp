#ifndef RIKKI_PATCHER_UTILS_STRING_UTIL_HPP
#define RIKKI_PATCHER_UTILS_STRING_UTIL_HPP
#include "precompiled.hpp"

// ======================== C L A S S ========================
// ===    StringUtil
// ======================== C L A S S ========================

class StringUtil {
public:
    static void replace(std::string& str, std::string_view oldSub, std::string_view newSub);

    static std::u8string str_to_u8(std::string_view str);

    static std::string u8_to_str(std::u8string_view str);

    static const char* u8_to_cstr(std::u8string_view str);

    static std::u8string wstr_to_u8(std::wstring_view str);

    static std::string wstr_to_str(std::wstring_view str);
};

template <>
struct std::formatter<std::u8string> {
    constexpr auto parse(std::format_parse_context& ctx) -> decltype(ctx.begin()) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const std::u8string& u8str, FormatContext& ctx) const -> decltype(ctx.out()) {
        return std::format_to(ctx.out(), "{}", std::string(u8str.begin(), u8str.end()));
    }
};


#endif //RIKKI_PATCHER_UTILS_STRING_UTIL_HPP
