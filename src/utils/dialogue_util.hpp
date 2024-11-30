#ifndef RIKKI_PATCHER_UTILS_DIALOGUE_UTIL_HPP
#define RIKKI_PATCHER_UTILS_DIALOGUE_UTIL_HPP
#include "precompiled.hpp"

class DialogueUtil {
public:
    static bool extract_text_from_span(std::string_view span, std::string& result);
    static bool replace_text_in_span(std::string& span, std::string_view text);
};


#endif //RIKKI_PATCHER_UTILS_DIALOGUE_UTIL_HPP
