#include "dialogue.hpp"

#include "utils/json_util.hpp"
#include "utils/dialogue_util.hpp"
#include "utils/string_util.hpp"

bool Dialogue::is_valid() {
    return m_isValid;
}

dialogue_map_t Dialogue::extract_dialogues() {
    dialogue_map_t result { };

    this->find_dialogues([&](const dialogue_idx_t idx, const std::string& s, const std::string& d) {
        DialogueEntry entry { };
        entry.m_speaker = s;
        entry.m_dialogue = d;

        result[idx] = std::move(entry);
    });

    return result;
}

choice_map_t Dialogue::extract_choices() {
    choice_map_t result { };

    this->find_choices([&](const choice_idx_t idx, const std::string& c) {
        result[idx] = c;
    });

    return result;
}

std::vector<dialogue_idx_t> Dialogue::update_dialogues(const dialogue_map_t& entries) {
    std::vector<dialogue_idx_t> result { };

    this->find_dialogues([&](dialogue_idx_t idx, std::string& s, std::string& d) {
        if (const auto it = entries.find(idx); it != entries.end()) {
            const auto& [spk, dia] = it->second;
            s = spk;
            d = dia;

            result.emplace_back(idx);
        }
    });

    return result;
}

std::vector<choice_idx_t> Dialogue::update_choices(const choice_map_t& entries) {
    std::vector<choice_idx_t> result { };

    this->find_choices([&](const dialogue_idx_t idx, std::string& c) {
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
        std::filesystem::copy(m_file, path_t(dir).append(fName));
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

    dialogue_idx_t nextIdx = 0;

    this->iterate_elements([&](const auto elID, auto& elem) {
        if (elID != ID_DIALOGUE) {
            return;
        }

        const auto idx = nextIdx;
        nextIdx++;

        auto& spk  = elem[IDX_SPEAKER];
        auto& span = elem[IDX_DIALOGUE];

        if (!spk.is_string() || !span.is_string()) {
            return;
        }

        std::string bufSpk(spk);
        std::string bufDia(span);

        if (!DialogueUtil::extract_text_from_span(bufDia, bufDia)) {
            return;
        }

        const std::string orgSpk(bufSpk);
        const std::string orgDia(bufDia);

        callback(idx, bufSpk, bufDia);

        if (orgSpk != bufSpk) {
            spk = bufSpk;
        }

        if (orgDia != bufDia) {
            std::string bufSpan(span);
            StringUtil::replace(bufSpan, orgDia, bufDia);
            span = bufSpan;
        }
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

        const std::string orgCho(cho);
        std::string buf(cho);

        callback(nextIdx, buf);

        if (orgCho != buf) {
            cho = buf;
        }
    });
}

Dialogue::Dialogue(const path_t& file) :
                                       m_isValid(false),
                                       m_file(file) {

    m_isValid = JsonUtil::load_from_file(m_j, m_file);
}
