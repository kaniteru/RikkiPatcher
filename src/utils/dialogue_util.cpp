#include "dialogue_util.hpp"
#include "rikki/data/dialogue/dialogue_json.hpp"

std::vector<j::DialogueSpan> DialogueUtil::extract_texts_from_span(std::string_view span) {
    const static auto SPAN_REGEX = std::regex(R"(<span\s+([^>]*)>([^<]*)</span>)");

    std::vector<j::DialogueSpan> result { };
    const std::string target(span);
    std::smatch matched { };
    auto searchStart(target.cbegin());

    while (std::regex_search(searchStart, target.cend(), matched, SPAN_REGEX)) {
        j::DialogueSpan element { };
        element.html = matched[1].str();
        element.text = matched[2].str();

        result.emplace_back(std::move(element));
        searchStart = matched.suffix().first;
    }

    return result;
}

std::string DialogueUtil::insert_dialogue_into_span(const std::vector<j::DialogueSpan>& dialogues) {
    std::string result { };

    for (const auto& [html, text] : dialogues) {
        result += "<span " + html + ">" += text + "</span>";
    }

    return result;
}