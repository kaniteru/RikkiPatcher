#include "dialogue_patch_stream.hpp"
#include "rikki/data/dialogue/dialogue.hpp"
#include "rikki/data/dialogue/dialogue_json.hpp"

#include "utils/json_util.hpp"
#include "utils/string_util.hpp"

// ======================== C L A S S ========================
// ===    DialoguePatchStream
// ======================== C L A S S ========================

bool DialoguePatchStream::get_dialogue(const dialogue_idx_t idx, j::Dialogue& e) const {
    const auto strIdx = std::to_string(idx);

    if (!m_j.contains(strIdx)) {
        return false;
    }

    auto& j = m_j[strIdx];
    e = j;
    return true;
}

dialogue_map_t DialoguePatchStream::get_dialogues() const {
    dialogue_map_t result { };

    for (auto& [k, v] : m_j.items()) {
        const auto idx = std::stoi(k);
        result[idx] = v;
    }

    return result;
}

bool DialoguePatchStream::is_idx_exists(const dialogue_idx_t idx) const {
    return m_j.contains(std::to_string(idx));
}

void DialoguePatchStream::set_dialogues(const dialogue_map_t& map) {
    for (const auto& [idx, v] : map) {
        auto& j = m_j[std::to_string(idx)];
        j = v;
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

    for (auto& [k, v] : m_j.items()) {
        const choice_idx_t idx = std::stoi(k);
        result[idx] = v;
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
