#include "dialogue.hpp"

#include "utils/json_util.hpp"
#include "utils/dialogue_util.hpp"
#include "utils/string_util.hpp"
#include "utils/hash_util.hpp"

bool Dialogue::is_valid() final {
    return m_isValid;
}

dialogue_map_t Dialogue::extract() {
    dialogue_map_t result { };

    this->find_dialogue([&](dialogue_idx_t idx, const std::string& s, const std::string& d) {
        DialogueEntry entry { };
        entry.m_speaker = s;
        entry.m_dialogue = d;

        result.emplace(idx, std::move(entry));
    });

    return result;
}

std::vector<dialogue_idx_t> Dialogue::update(const dialogue_map_t& entries) {
    std::vector<dialogue_idx_t> result { };

    this->find_dialogue([&](dialogue_idx_t idx, std::string& s, std::string& d) {
        if (const auto it = entries.find(idx); it != entries.end()) {
            const auto& [spk, dia] = it->second;
            s = spk;
            d = dia;

            result.emplace_back(idx);
        }
    });

    return result;
}

bool Dialogue::backup(const path_t& dir) final {
    try {
        const auto fName = m_file.filename().u8string();
        std::filesystem::copy(m_file, path_t(dir).append(fName));
    }
    catch (const std::exception& e) {
        return false;
    }

    return true;
}

bool Dialogue::save() final {
    return this->save(m_file);
}

bool Dialogue::save(const path_t& path) final {
    return JsonUtil::save_into_file(m_j, path);
}

void Dialogue::find_dialogue(const dialogue_callback_t& callback) {
    constexpr static auto KEY                      = "customCommands";
    constexpr static auto ID_DIALOGUE   = 11;
    constexpr static auto IDX_ID               = 0;
    constexpr static auto IDX_SPEAKER    = 3;
    constexpr static auto IDX_DIALOGUE = 6;

    for (auto& cmd : m_j[KEY]) {
        for (auto& elem : cmd) {
            if (elem.empty() || !elem.is_array()) {
                continue;
            }

            dialogue_idx_t idx = 0;

            if (auto& id = elem[IDX_ID]; !id.is_number_integer() || id != ID_DIALOGUE) {
                continue;
            } else {
                idx = id;
            }

            auto& spk  = elem[IDX_SPEAKER];
            auto& span = elem[IDX_DIALOGUE];

            if (!spk.is_string() || !span.is_string()) {
                continue;
            }

            std::string bufSpk(spk);
            std::string bufDia(span);

            if (!DialogueUtil::extract_text_from_span(bufDia, bufDia)) {
                continue;
            }

            std::string orgSpk(bufSpk);
            std::string orgDia(bufDia);

            callback(idx, bufSpk, bufDia);

            if (orgSpk != bufSpk) {
                spk = bufSpk;
            }

            if (orgDia != bufDia) {
                std::string bufSpan(span);
                StringUtil::replace(bufSpan, orgDia, bufDia);
                span = bufSpan;
            }
        }
    }
}

Dialogue::Dialogue(const path_t& file) :
    m_isValid(true),
    m_file(file) {

    if (!JsonUtil::load_from_file(m_j, m_file)) {
        m_isValid = false;
    }
}

bool DialogueMigr::save(const path_t& file) const {
    nlohmann::json j { };
    auto& hash = j[KEY_MIGR_HASH];
    auto& list = j[KEY_MIGR_DIA_LIST];

    for (const auto& [k, v] : m_entries) {
        const auto& idx = k;
        const auto& [spk, dia] = v;

        auto& entry = list[idx];
        entry[KEY_MIGR_SPEAKER] = spk;
        entry[KEY_MIGR_DIALOGUE] = dia;
    }

    return JsonUtil::save_into_file(j, file);
}

DialogueMigr DialogueMigr::from_file(const path_t& file) {
    DialogueMigr result { };
    nlohmann::json j { };
    JsonUtil::load_from_file(j, file);

    const auto& hash = j[KEY_MIGR_HASH];
    result.m_hash = hash;

    for (auto& list = j[KEY_MIGR_DIA_LIST]; auto& it : list.items()) {
        auto& key = it.key();
        auto& entry = it.value();

        const dialogue_idx_t idx = std::stoi(key);
        const std::string spk = entry[KEY_MIGR_SPEAKER];
        const std::string dia = entry[KEY_MIGR_DIALOGUE];
        result.m_entries[idx] = DialogueEntry{ spk, dia };
    }

    return result;
}
