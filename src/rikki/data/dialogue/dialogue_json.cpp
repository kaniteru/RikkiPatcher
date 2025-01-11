#include "dialogue_json.hpp"

namespace j {

// ======================= S T R U C T =======================
// ===    j::DialogueSpan
// ======================= S T R U C T =======================

bool DialogueSpan::operator==(const DialogueSpan& rhs) const {
    return html == rhs.html && text == rhs.text;
}

// ======================= S T R U C T =======================
// ===    j::Dialogue
// ======================= S T R U C T =======================

bool Dialogue::operator==(const Dialogue& rhs) const {
    return speaker == rhs.speaker && spans == rhs.spans && atts == rhs.atts;
}

// ======================= S T R U C T =======================
// ===    j::Choice
// ======================= S T R U C T =======================

bool Choice::operator==(const Choice& rhs) const {
    return text == rhs.text;
}
}
