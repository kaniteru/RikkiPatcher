#include "dialogue_json.hpp"

namespace j {

bool DialogueSpan::operator==(const DialogueSpan& rhs) const {
    return html == rhs.html && text == rhs.text;
}

bool Choice::operator==(const Choice& rhs) const {
    return text == rhs.text;
}
}
