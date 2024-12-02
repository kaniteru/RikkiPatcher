#include "dialogue_patcher.hpp"

#include "rikki/dir_mgr.hpp"
#include "utils/filesystem_util.hpp"
#include "utils/instance_factory.hpp"
#include "utils/json_util.hpp"
#include "utils/hash_util.hpp"
#include "utils/string_util.hpp"

size_t DialoguePatcher::patch() {
    size_t result = 0;
    constexpr auto gmdir = InstanceFactory::instance().get<DirMgr>()->get(DIR_GAME_JSON_DIALOGUES);
    const auto spkdir = path_t(m_dataBase).append(FILE_SPEAKERS);

    SpeakerPatchStream sps(spkdir);
    const auto speakers = sps.get_speakers();

    for (const auto files = FilesystemUtil::sort_files(gmdir); const auto& f : files) {
        auto fName = f.filename().generic_u8string();
        auto fCustom = path_t(m_dataBase).append(fName);

        if (!std::filesystem::exists(fCustom)) {
            continue;
        }

        DialoguePatchStream dps(fCustom);
        Dialogue dia(f);

        if (!dia.is_valid()) {
            continue;
        }

        auto entries = dps.get_dialogues();

        for (auto& e : entries) {
            auto& s = e.second.m_speaker;

            if (const auto it = speakers.find(s); it != speakers.end()) {
                s = it->second;
            }
        }

        const auto patched = dia.update(entries);

        if (dia.save()) {
            result++;
        }
    }

    return result;
}

bool DialoguePatcher::migration() {
    constexpr auto gmdir = InstanceFactory::instance().get<DirMgr>()->get(DIR_GAME_JSON_DIALOGUES);
    const auto files = FilesystemUtil::sort_files(m_migrBase);

    for (const auto& f : files) {
        auto fName = f.filename().generic_u8string();

        // Handle speakers
        if (StringUtil::u8_to_cstr(fName) == DialogueMigrStream::FILE_SPEAKERS) {
            auto speakers = DialogueMigrStream::get_spekaers(f);
            SpeakerPatchStream sps(path_t(m_migrBase).append(FILE_SPEAKERS));

            for (const auto& it : speakers) {
                if (sps.is_spekaer_exists(it)) {
                    speakers.erase(std::remove(speakers.begin(), speakers.end(), it), speakers.end());
                    continue;
                }

                sps.remove_spekaer(it);
            }

            speaker_map_t map { };

            for (const auto& it : speakers) {
                map[it] = it;
            }

            if (!map.empty()) {
                sps.set_speakers(map);
            }

            continue;
        }

        // todo: Handle dialogues
    }
}

bool DialoguePatcher::generate_migration_info() {
    DialogueMigrStream::save_migration_data(m_migrBase);
    return true;
}

DialoguePatcher::DialoguePatcher(const path_t& src) :
    IPatcher(src) {

    m_dataBase = path_t(src).append(FOLDER_BASE);
    m_migrBase = path_t(src).append(FOLDER_BASE);
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

bool SpeakerPatchStream::is_spekaer_exists(std::string_view spk) const {
    return m_j.contains(spk.data());
}

void SpeakerPatchStream::set_speakers(const speaker_map_t& map) {
    for (const auto& [spk, tran] : map) {
        m_j[spk] = tran;
    }
}

bool SpeakerPatchStream::remove_spekaer(std::string_view spk) {
    if (!this->is_spekaer_exists(spk)) {
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

// ======================== C L A S S ========================
// ===    DialoguePatchStream
// ======================== C L A S S ========================

DialogueEntry DialoguePatchStream::get_dialogue(const dialogue_idx_t idx) const {
    auto& v = m_j[idx];
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
    for (const auto& it : map) {
        const auto& idx = it.first;
        const auto& [spk, dia] = it.second;

        auto& j = m_j[idx];
        j[KEY_SPEAKER] = spk;
        j[KEY_DIALOGUE] = dia;
    }
}

void DialoguePatchStream::remove_dialogue(const dialogue_idx_t idx) {
    m_j.erase(idx);
}

bool DialoguePatchStream::save() const {
    return JsonUtil::save_into_file(m_j, m_file);
}

DialoguePatchStream::DialoguePatchStream(const path_t& file) {
    JsonUtil::load_from_file(m_j, file);
}

// ======================== C L A S S ========================
// ===    DialogueMigrStream
// ======================== C L A S S ========================

bool DialogueMigrStream::is_valid() const {
    return m_isValid;
}

std::string DialogueMigrStream::get_file_hash() const {
    return m_j[KEY_HASH];
}

dialogue_map_t DialogueMigrStream::get_dialogues() const {
    dialogue_map_t result { };
    auto& entires = m_j[KEY_LIST];

    for (auto& it : entires.items()) {
        dialogue_idx_t idx = std::stoi(it.key());

        const auto& e = it.value();
        const std::string spk = e[KEY_SPEAKER];
        const std::string dia = e[KEY_DIALOGUE];
        result[idx] = { spk, dia };
    }
}

std::vector<std::string> DialogueMigrStream::get_spekaers(const path_t& file) {
    std::vector<std::string> result { };
    nlohmann::json j { };

    JsonUtil::load_from_file(j, file);

    for (auto& it : j) {
        result.emplace_back(j);
    }

    return result;
}

void DialogueMigrStream::save_migration_data(const path_t& dir) {
    constexpr auto gmdir = InstanceFactory::instance().get<DirMgr>()->get(DIR_GAME_JSON_DIALOGUES);
    std::set<std::string> speakers { };

    for (const auto files = FilesystemUtil::sort_files(gmdir); const auto& f : files) {
        const auto fName = f.filename().generic_u8string();
        Dialogue dia(f);

        if (!dia.is_valid()) {
            continue;
        }

        const auto hash = HashUtil::file_to_hash(f);
        const auto entries = dia.extract();

        nlohmann::json j { };
        j[KEY_HASH] = hash;

        auto& list = j[KEY_LIST];

        for (const auto& [k, v] : dia.extract()) {
            const auto& idx = k;
            const auto& [spk, dia] = v;

            auto& entry = list[idx];
            entry[KEY_SPEAKER] = spk;
            entry[KEY_DIALOGUE] = dia;
            speakers.emplace(spk);
        }

        JsonUtil::save_into_file(j, path_t(dir).append(fName));
    }

    nlohmann::json j { };
    j.parse(speakers);
    JsonUtil::save_into_file(j, path_t(dir).append(FILE_SPEAKERS));
}

DialogueMigrStream::DialogueMigrStream(const path_t& file) :
    m_isValid(false) {

    m_isValid = JsonUtil::load_from_file(m_j, file);
}
