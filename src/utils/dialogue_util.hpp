#ifndef RIKKI_PATCHER_UTILS_DIALOGUE_UTIL_HPP
#define RIKKI_PATCHER_UTILS_DIALOGUE_UTIL_HPP
#include "precompiled.hpp"

struct DialogueSpan;

class DialogueUtil {
public:
    /**
     * @brief Make span string to DialogueSpan.
     *
     * @param [in] span Target span string.
     * @return Returns extracted items.
     *
     * @code
     * const auto spanStr = "<span ...> abc </span> <span ...> def </span>";
     * auto extracted = DialogueUtil::extract_texts_from_span(spanStr);
     *
     * if (!extracted.empty()) { ... }
     * @endcode
     */
    static std::vector<DialogueSpan> extract_texts_from_span(std::string_view span);

    /**
     * @brief Make DialogueSpan to span string.
     *
     * @param [in] dialogues Target dialogues.
     * @return Returns span string.
     *
     * @code
     * DialogueSpan span { "style=\"color: 'purple'\"",  "I'm a rikki." }
     * auto result = DialogueUtil::insert_dialogue_into_span({ span });
     * // result == <span style="color: 'purple'"> I'm a rikki.</span>
     * @endcode
     */
    static std::string insert_dialogue_into_span(const std::vector<DialogueSpan>& dialogues);
};


#endif //RIKKI_PATCHER_UTILS_DIALOGUE_UTIL_HPP
