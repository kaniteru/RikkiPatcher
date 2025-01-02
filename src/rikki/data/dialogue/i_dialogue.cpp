#include "i_dialogue.hpp"
#include "dialogue_json.hpp"
#include "dialogue_key.hpp"

#include "utils/dialogue_util.hpp"

// ======================== C L A S S ========================
// ===    IDialogue
// ======================== C L A S S ========================

dialogue_map_t IDialogue::extract_dialogues() {
    dialogue_map_t result { };

    this->find_dialogues([&](const dialogue_idx_t idx, const j::Dialogue& dia) {
        result[idx] = dia;
    });

    return result;
}

choice_map_t IDialogue::extract_choices() {
    choice_map_t result { };

    this->find_choices([&](const choice_idx_t idx, const j::Choice& c) {
        result[idx] = c;
    });

    return result;
}

std::vector<dialogue_idx_t> IDialogue::update_dialogues(const dialogue_map_t& entries) {
    std::vector<dialogue_idx_t> result { };

    this->find_dialogues([&](const dialogue_idx_t idx, j::Dialogue& e) {
        if (const auto it = entries.find(idx); it != entries.end()) {
            e = it->second;

            result.emplace_back(idx);
        }
    });

    return result;
}

std::vector<choice_idx_t> IDialogue::update_choices(const choice_map_t& entries) {
    std::vector<choice_idx_t> result { };

    this->find_choices([&](const dialogue_idx_t idx, j::Choice& c) {
       if (const auto it = entries.find(idx); it != entries.end()) {
           c = it->second;

           result.emplace_back(idx);
       }
    });

    return result;
}

void IDialogue::find_dialogues(const dialogue_callback_t& callback) {
    dialogue_idx_t nextIdx = 0;

    this->iterate_elements([&](const auto elID, auto& elem) {
        if (elID != DialogueKey::ID_DIALOGUE) {
            return;
        }

        const auto idx = nextIdx;
        nextIdx++;

        auto& spk  = elem[DialogueKey::IDX_SPEAKER];
        auto& span = elem[DialogueKey::IDX_DIALOGUE_SPAN];
        auto& atts = elem[DialogueKey::IDX_ATTS][DialogueKey::KEY_ATTS];

        if (!spk.is_string() || !span.is_string()) {
            return;
        }

        j::Dialogue buf { spk, DialogueUtil::extract_texts_from_span(span), atts };

        callback(idx, buf);

        spk   = buf.speaker;
        span = DialogueUtil::insert_dialogue_into_span(buf.spans);
        atts = buf.atts;
    });
}

void IDialogue::find_choices(const choices_callback_t& callback) {
    dialogue_idx_t nextIdx = 0;

    this->iterate_elements([&](const auto elID, auto& elem) {
        if (elID != ChoiceKey::ID_CHOICE) {
            return;
        }

        nextIdx++;

        auto& cho = elem[ChoiceKey::IDX_CHOICE];

        if (!cho.is_string()) {
            return;
        }

        const j::Choice org { cho };
        j::Choice buf = org;

        callback(nextIdx, buf);

        if (org != buf) {
            cho = buf.text;
        }
    });
}
