#ifndef RIKKI_PATCHER_UTILS_STRING_UTIL_HPP
#define RIKKI_PATCHER_UTILS_STRING_UTIL_HPP
#include "precompiled.hpp"

/* string_util.hpp
 *  Included classes:
 *      - StringUtil
 */

// ======================== C L A S S ========================
// ===    StringUtil
// ======================== C L A S S ========================

class StringUtil {
public:
    /**
     * @brief Replace all occurrences of @p oldSub with @p newSub in @p str.
     *
     * @param str String to modify.
     * @param oldSub Substring to replace.
     * @param newSub Replacement substring.
     */
    static void replace(std::string& str, std::string_view oldSub, std::string_view newSub);

    /**
     * @brief Convert a UTF-8 byte string (std::string) to std::u8string without re-encoding.
     * This is a byte reinterpretation/copy, it does not validate UTF-8.
     *
     * @param[in] str Source string.
     * @return Equivalent byte sequence as std::u8string.
     */
    static std::u8string str_to_u8(std::string_view str);

    /**
     * @brief Convert a std::u8string to std::string without re-encoding.
     * This is a byte reinterpretation/copy; it does not validate UTF-8.
     *
     * @param[in] str Source UTF-8 byte sequence.
     * @return Equivalent byte sequence as std::string.
     */
    static std::string u8_to_str(std::u8string_view str);

    /**
     * @brief Return a const char* view of a std::u8string_view buffer (no allocation).
     * The returned pointer is only valid as long as the underlying storage referenced by @p str
     * remains alive and unchanged, and it is not guaranteed to be null-terminated.
     *
     * @param[in] str Source UTF-8 byte sequence view.
     * @return Pointer to the underlying bytes, reinterpreted as const char*.
     */
    static const char* u8_to_cstr(std::u8string_view str);

    /**
     * @brief Convert a wide string to UTF-8 bytes (std::u8string).
     * Note: this performs a simple per-code-unit conversion and does not handle surrogate pairs.
     *
     * @param[in] str Source wide string.
     * @return UTF-8 encoded bytes (best-effort).
     */
    static std::u8string wstr_to_u8(std::wstring_view str);

    /**
     * @brief Convert a wide string to a UTF-8 byte string (std::string).
     * Note: this performs a simple per-code-unit conversion and does not handle surrogate pairs.
     *
     * @param[in] str Source wide string.
     * @return UTF-8 encoded bytes (best-effort) as std::string.
     */
    static std::string wstr_to_str(std::wstring_view str);
};

/**
 * @brief std::formatter specialization for std::u8string (formats as UTF-8 bytes via std::string).
 */
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
