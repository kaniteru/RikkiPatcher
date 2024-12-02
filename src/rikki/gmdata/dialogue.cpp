#include "dialogue.hpp"
#include "utils/json_util.hpp"
#include "utils/dialogue_util.hpp"
#include "utils/string_util.hpp"

bool Dialogue::is_valid() const {
    return m_isValid;
}

DialogueEntry Dialogue::extract() {
    DialogueEntry result { };
    auto& spk = result.m_speakers;
    auto& dia = result.m_dialogues;

    this->find_dialogue([&](const std::string& s, const std::string& d) {
        spk[s] = "";
        dia.emplace_back(d);
    });

    return result;
}

void Dialogue::update(DialogueEntry& de) {
    auto& spk = de.m_speakers;
    auto& dia = de.m_dialogues;

    this->find_dialogue([&](std::string& s, std::string& d) {
        if (const auto it = spk.find(s); it != spk.end()) {
            s = it->second;
        }

        d = dia.front();
        dia.erase(dia.begin());
    });
}

bool Dialogue::save() {
    return this->save(m_file);
}

bool Dialogue::save(const path_t& path) {
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

            if (auto& id = elem[IDX_ID]; !id.is_number_integer() || id != ID_DIALOGUE) {
                continue;
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

            callback(bufSpk, bufDia);

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
