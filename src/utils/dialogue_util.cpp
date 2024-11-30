#include "dialogue_util.hpp"
#include "string_util.hpp"

bool DialogueUtil::extract_text_from_span(std::string_view span, std::string& result) {
    static const auto SPAN_REGEX = std::regex("<span.*?>(.*?)</span>");
    std::match_results<std::string_view::const_iterator> matches { };

    if (!std::regex_search(span.begin(), span.end(), matches, SPAN_REGEX)) {
        return false;
    }

    result = matches[1].str();
    return true;
}

bool DialogueUtil::replace_text_in_span(std::string& span, std::string_view text) {
    std::string extracted { };

    if (!DialogueUtil::extract_text_from_span(span, extracted)) {
        return false;
    }

    StringUtil::replace(span, extracted, text);
    return true;
}
