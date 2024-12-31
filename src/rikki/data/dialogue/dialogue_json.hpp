#ifndef RIKKI_PATCHER_RIKKI_DATA_DIALOGUE_DIALOGUE_JSON_HPP
#define RIKKI_PATCHER_RIKKI_DATA_DIALOGUE_DIALOGUE_JSON_HPP
#include "precompiled.hpp"
#include "utils/json_util.hpp"

/* dialogue_json.hpp
 *  Included structs:
 *      - j::DialogueSpan
 *      - j::Dialogue
 *      - j::Choice
 */

namespace j {

// ======================= S T R U C T =======================
// ===    j::DialogueSpan
// ======================= S T R U C T =======================

struct DialogueSpan {
    std::string html; /* example: style="color:#ffffff" */
    std::string text; /* Dialogue text. ex) Good morning, tomori-chan */

    ORDERED_NLOHMANN_DEFINE_TYPE_INTRUSIVE(DialogueSpan,
        html,
        text);

    bool operator==(const DialogueSpan&) const;
};

// ======================= S T R U C T =======================
// ===    j::Dialogue
// ======================= S T R U C T =======================

struct Dialogue {
    std::string speaker; /* Speaker. ex) Rikki Shiina */
    std::vector<DialogueSpan> spans;
    nlohmann::ordered_json atts; /* attributes (using control the font family, font size and etc...) */

    ORDERED_NLOHMANN_DEFINE_TYPE_INTRUSIVE(Dialogue,
    speaker,
    spans,
    atts);

    bool operator==(const Dialogue&) const;
};

// ======================= S T R U C T =======================
// ===    j::Choice
// ======================= S T R U C T =======================

struct Choice {
    std::string text;

    ORDERED_NLOHMANN_DEFINE_TYPE_INTRUSIVE(Choice,
        text);

    bool operator==(const Choice&) const;
};
}


#endif //RIKKI_PATCHER_RIKKI_DATA_DIALOGUE_DIALOGUE_JSON_HPP
