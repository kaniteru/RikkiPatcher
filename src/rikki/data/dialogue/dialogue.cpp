#include "dialogue.hpp"
#include "dialogue_json.hpp"

#include "utils/json_util.hpp"
#include "utils/dialogue_util.hpp"

// ======================== C L A S S ========================
// ===    Dialogue
// ======================== C L A S S ========================

dialogue_map_t Dialogue::extract_dialogues() {
    dialogue_map_t result { };

    this->find_dialogues([&](const dialogue_idx_t idx, const j::Dialogue& dia) {
        j::Dialogue buf = dia;
        result[idx] = std::move(buf);
    });

    return result;
}

choice_map_t Dialogue::extract_choices() {
    choice_map_t result { };

    this->find_choices([&](const choice_idx_t idx, const j::Choice& c) {
        result[idx] = c;
    });

    return result;
}

std::vector<dialogue_idx_t> Dialogue::update_dialogues(const dialogue_map_t& entries) {
    std::vector<dialogue_idx_t> result { };

    this->find_dialogues([&](dialogue_idx_t idx, j::Dialogue& e) {
        if (const auto it = entries.find(idx); it != entries.end()) {
            e = it->second;

            result.emplace_back(idx);
        }
    });

    return result;
}

std::vector<choice_idx_t> Dialogue::update_choices(const choice_map_t& entries) {
    std::vector<choice_idx_t> result { };

    this->find_choices([&](const dialogue_idx_t idx, j::Choice& c) {
       if (const auto it = entries.find(idx); it != entries.end()) {
           c = it->second;

           result.emplace_back(idx);
       }
    });

    return result;
}

bool Dialogue::backup(const path_t& dir) {
    try {
        const auto fName = m_file.filename().u8string();
        std::filesystem::copy(m_file, path_t(dir).append(fName), std::filesystem::copy_options::overwrite_existing);
    }
    catch (const std::exception& e) {
        return false;
    }

    return true;
}

bool Dialogue::save() {
    return this->save(m_file);
}

bool Dialogue::save(const path_t& path) {
    return JsonUtil::save_into_file(m_j, path);
}

void Dialogue::iterate_elements(const dialogue_iterate_t& callback) {
    constexpr static auto KEY_ELEMETNS = "customCommands";
    constexpr static auto IDX_ID                = 0;

    for (auto& elements : m_j[KEY_ELEMETNS]) {
        for (auto& elem : elements) {
            if (elem.empty() || !elem.is_array()) {
                continue;
            }

            if (auto& id = elem[IDX_ID]; id.is_number_integer()) {
                callback(id, elem);
            }
        }
    }
}

void Dialogue::find_dialogues(const dialogue_callback_t& callback) {
    constexpr static auto ID_DIALOGUE   = 11;
    constexpr static auto IDX_SPEAKER    = 3;
    constexpr static auto IDX_DIALOGUE = 6;
    constexpr static auto IDX_ATTS          = 11;
    constexpr static auto KEY_ATTS          = "atts";

    dialogue_idx_t nextIdx = 0;

    this->iterate_elements([&](const auto elID, auto& elem) {
        if (elID != ID_DIALOGUE) {
            return;
        }

        const auto idx = nextIdx;
        nextIdx++;

        auto& spk  = elem[IDX_SPEAKER];
        auto& span = elem[IDX_DIALOGUE];
        auto& atts = elem[IDX_ATTS][KEY_ATTS];

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

void Dialogue::find_choices(const choices_callback_t& callback) {
    constexpr static auto ID_CHOICE   = 4;
    constexpr static auto IDX_CHOICE = 1;

    dialogue_idx_t nextIdx = 0;

    this->iterate_elements([&](const auto elID, auto& elem) {
        if (elID != ID_CHOICE) {
            return;
        }

        nextIdx++;

        auto& cho = elem[IDX_CHOICE];

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

Dialogue::Dialogue(const path_t& file) :
    m_file(file) {

    m_isValid = JsonUtil::load_from_file(m_j, m_file);
}
