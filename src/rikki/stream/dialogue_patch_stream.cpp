#include "dialogue_patch_stream.hpp"
#include "utils/json_util.hpp"

// ======================== C L A S S ========================
// ===    DialoguePatchStream
// ======================== C L A S S ========================

bool DialoguePatchStream::get_dialogue(const dialogue_idx_t idx, DialogueEntry& e) const {
    if (const auto strIdx = std::to_string(idx); !m_j.contains(strIdx)) {
        return false;
    }

    auto& j = m_j[std::to_string(idx)];
    e.m_speaker = j[KEY_SPEAKER];

    for (const auto& d : j[KEY_DIALOGUE]) {
        DialogueSpan span { };
        span.m_html = d[KEY_DIA_HTML];
        span.m_text = d[KEY_DIA_TEXT];

        e.m_dialogues.emplace_back(std::move(span));
    }

    return true;
}

dialogue_map_t DialoguePatchStream::get_dialogues() const {
    dialogue_map_t result { };

    for (auto& it : m_j.items()) {
        auto& k = it.key();
        auto& v = it.value();

        dialogue_idx_t idx = std::stoi(k);
        const std::string spk = v[KEY_SPEAKER];
        const auto& diaJ = v[KEY_DIALOGUE];

        std::vector<DialogueSpan> dia { };

        for (const auto& d : diaJ) {
            DialogueSpan span { };
            span.m_html = d[KEY_DIA_HTML];
            span.m_text = d[KEY_DIA_TEXT];

            dia.emplace_back(std::move(span));
        }

        result[idx] = { spk, dia };
    }

    return result;
}

bool DialoguePatchStream::is_idx_exists(const dialogue_idx_t idx) const {
    return m_j.contains(std::to_string(idx));
}

void DialoguePatchStream::set_dialogues(const dialogue_map_t& map) {
    for (const auto& [k, v] : map) {
        const auto& idx = k;
        const auto& [spk, dia] = v;

        auto& j = m_j[std::to_string(idx)];
        j[KEY_SPEAKER] = spk;

        for (const auto& [html, text] : dia) {
            j[KEY_DIALOGUE] += { { KEY_DIA_HTML, html }, { KEY_DIA_TEXT, text } };
        }
    }
}

void DialoguePatchStream::remove_dialogue(const dialogue_idx_t idx) {
    m_j.erase(idx);
}

void DialoguePatchStream::clear() {
    m_j.clear();
}

bool DialoguePatchStream::save() const {
    return JsonUtil::save_into_file(m_j, m_file);
}

DialoguePatchStream::DialoguePatchStream(const path_t& file) :
    m_file(file) {

    JsonUtil::load_from_file(m_j, m_file);
}

// ======================== C L A S S ========================
// ===    ChoicePatchStream
// ======================== C L A S S ========================

std::string ChoicePatchStream::get_choice(const choice_idx_t idx) const {
    return m_j[std::to_string(idx)];
}

choice_map_t ChoicePatchStream::get_choices() const {
    choice_map_t result { };

    for (auto& it : m_j.items()) {
        const auto& k = it.key();
        const auto& v = it.value();

        const choice_idx_t idx = std::stoi(k);
        const std::string cho = v;
        result[idx] = cho;
    }

    return result;
}

bool ChoicePatchStream::is_idx_exists(const choice_idx_t idx) const {
    return m_j.contains(std::to_string(idx));
}

void ChoicePatchStream::set_choices(const choice_map_t& map) {
    for (const auto& [idx, cho] : map) {
        auto& j = m_j[std::to_string(idx)];
        j = cho;
    }
}

void ChoicePatchStream::remove_choice(const choice_idx_t idx) {
    m_j.erase(idx);
}

void ChoicePatchStream::clear() {
    m_j.clear();
}

bool ChoicePatchStream::save() const {
    return JsonUtil::save_into_file(m_j, m_file);
}

ChoicePatchStream::ChoicePatchStream(const path_t& file) :
    m_file(file) {

    JsonUtil::load_from_file(m_j, m_file);
}
