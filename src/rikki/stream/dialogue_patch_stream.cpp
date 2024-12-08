#include "dialogue_patch_stream.hpp"
#include "utils/json_util.hpp"

// ======================== C L A S S ========================
// ===    DialoguePatchStream
// ======================== C L A S S ========================

DialogueEntry DialoguePatchStream::get_dialogue(const dialogue_idx_t idx) const {
    auto& v = m_j[std::to_string(idx)];
    return { v[KEY_SPEAKER], v[KEY_DIALOGUE] };
}

dialogue_map_t DialoguePatchStream::get_dialogues() const {
    dialogue_map_t result { };

    for (auto& it : m_j.items()) {
        auto& k = it.key();
        auto& v = it.value();

        dialogue_idx_t idx = std::stoi(k);
        const std::string spk = v[KEY_SPEAKER];
        const std::string dia = v[KEY_DIALOGUE];
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
        j[KEY_DIALOGUE] = dia;
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

// ======================== C L A S S ========================
// ===    SpeakerPatchStream
// ======================== C L A S S ========================

speaker_map_t SpeakerPatchStream::get_speakers() const {
    speaker_map_t result { };

    for (auto& it : m_j.items()) {
        const std::string& spk = it.key();
        const std::string tran = it.value();
        result[spk] = tran;
    }

    return result;
}

bool SpeakerPatchStream::is_speaker_exists(std::string_view spk) const {
    return m_j.contains(spk.data());
}

void SpeakerPatchStream::set_speakers(const speaker_map_t& map) {
    for (const auto& [spk, tran] : map) {
        m_j[spk] = tran;
    }
}

bool SpeakerPatchStream::remove_speaker(std::string_view spk) {
    if (!this->is_speaker_exists(spk)) {
        return false;
    }

    m_j.erase(spk);
    return true;
}

bool SpeakerPatchStream::save() const {
    return JsonUtil::save_into_file(m_j, m_file);
}

SpeakerPatchStream::SpeakerPatchStream(const path_t& file) :
    m_file(file) {

    JsonUtil::load_from_file(m_j, m_file);
}
