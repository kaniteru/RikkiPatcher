#include "dialogue_patcher.hpp"

#include "rikki/dir_mgr.hpp"
#include "utils/filesystem_util.hpp"
#include "utils/instance_factory.hpp"
#include "utils/json_util.hpp"
#include "utils/hash_util.hpp"
#include "wv/enums.hpp"
#include "wv/wv_invoker.hpp"

size_t DialoguePatcher::patch() {
    const auto gmdir = InstanceFactory::instance().get<DirMgr>()->get(DIR_GAME_JSON_DIALOGUES);
    const auto spkdir = path_t(m_dataBase).append(FILE_SPEAKERS);

    /*SpeakerPatchStream sps(spkdir);
    const auto speakers = sps.get_speakers();*/

    size_t total = 0;
    size_t failed = 0;
    size_t passed = 0;
    size_t ok = 0;

    for (const auto& files = FilesystemUtil::sort_files(gmdir); const auto& f : files) {
        const auto fName = f.filename().generic_u8string();
        const auto fCustom = path_t(m_dataBase).append(fName);
        auto log = fName + u8" => ";

        total++;

        // check patch file exists
        if (!std::filesystem::exists(fCustom)) {
            log += u8"Pass (no data)";
            WvInvoker::log(LOG_LV_PROG, log);

            passed++;
            continue;
        }

        DialoguePatchStream patchStream(fCustom);
        Dialogue dia(f);

        if (!dia.is_valid()) {
            log += u8"Read failed";
            WvInvoker::log(LOG_LV_PROG, log);

            failed++;
            continue;
        }

        // get patch file data
        const auto entries = patchStream.get_dialogues();
        const auto lenEntries = std::to_string(entries.size());

        /*for (auto& e : entries) {
            auto& s = e.second.m_speaker;

            if (const auto it = speakers.find(s); it != speakers.end()) {
                s = it->second;
            }
        }*/

        // apply patch data into game data
        const auto patched = dia.update(entries);
        const auto lenPatched = std::to_string(patched.size());

        log += std::u8string(lenPatched.begin(), lenPatched.end())
              + u8" / "
              + std::u8string(lenEntries.begin(), lenEntries.end())
              += u8" => ";

        if (dia.save()) {
            log += u8"OK";

            ok++;
        } else {
            log += u8"Write failed";
        }

        WvInvoker::log(LOG_LV_PROG, log);
    }

    std::string log = "Total: " + std::to_string(total) + " | ok: " + std::to_string(ok) + " | passed: " + std::to_string(passed)
                            + " | failed: " + std::to_string(failed);
    WvInvoker::log(LOG_LV_INFO, log);

    return ok;
}

bool DialoguePatcher::migration() {
    const auto gmdir = InstanceFactory::instance().get<DirMgr>()->get(DIR_GAME_JSON_DIALOGUES);
    auto migrFiles = FilesystemUtil::sort_files(m_migrBase);

    /*SpeakerPatchStream sps { };

    // find spekaer file
    for (auto& f : migrFiles) {
        if (f.filename().generic_string() != FILE_SPEAKERS) {
            continue;
        }

        sps = SpeakerPatchStream(f);
        std::erase(migrFiles, f);
        break;
    }*/

    auto gmFiles = FilesystemUtil::sort_files(gmdir);

    for (const auto& f : gmFiles) {
        const auto fName = f.filename().generic_u8string();

        // path_t
        const auto fPatch = path_t(m_dataBase).append(fName);
        const auto fMigr = path_t(m_migrBase).append(fName);

        // extract pure dialogues from game
        Dialogue pureDia(f);
        auto pureMap = pureDia.extract();

        // delete patch data when pure dialogues doesn't exists
        if (pureMap.empty()) {
            std::filesystem::remove(fPatch);
            continue;
        }

        // migration file stream
        DialogueMigrStream migrStream(fMigr);
        const auto migrMap = migrStream.get_dialogues();

        // check pure dialogue file is updated using hash
        if (const auto pureHash = HashUtil::file_to_hash(f); pureHash == migrStream.get_file_hash()) {
            // if not, doesn't need working.
            continue;
        }

        // pure dialogue file updated.

        dialogue_map_t newDiaMap { };

        // patch file stream
        DialoguePatchStream patchStream(fPatch);
        const auto patchMap = patchStream.get_dialogues();

        for (const auto pureDiaMap = pureDia.extract(); const auto& [k, v] : pureDiaMap) {
            const auto& idx = k;
            const auto& [pureSkp, pureDia] = v;

            /*if (!sps.is_spekaer_exists(pureSpk)) {
                sps.set_speakers({ pureSpk, pureSpk });
            }*/

            // translation found boolean
            bool tranFound = false;

            // find pure dialogue data exist from migration data
            for (const auto& [migrIdx, value] : migrMap) {
                const auto& [migrSpk, migrDia] = value;

                // dialogue doesn't matched
                if (pureDia != migrDia) {
                    continue;
                }

                // dialogue not found in patch data
                if (!patchStream.is_idx_exists(migrIdx)) {
                    break;
                }

                // found translated dialogue from patch data!
                tranFound = true;

                // load translated dialogue from patch data
                auto tranEntry = patchStream.get_dialogue(idx);

                // if speaker updated, change it to pure speaker str
                if (pureSkp != migrSpk) {
                    tranEntry.m_speaker = pureSkp;
                }

                newDiaMap[idx] = std::move(tranEntry);
                break;
            }

            // already migrated, pass it
            if (tranFound) {
                continue;
            }

            newDiaMap[idx] = v;
        }

        // clear patch data
        patchStream.clear();
        // overwrite patch data using migrated data
        patchStream.set_dialogues(newDiaMap);
        // save overwrote patch data
        patchStream.save();
    }

    return true;
}

bool DialoguePatcher::generate_migration_info() {
    std::filesystem::remove_all(m_migrBase);
    std::filesystem::create_directories(m_migrBase);
    DialogueMigrStream::save_migration_data(m_migrBase);
    return true;
}

DialoguePatcher::DialoguePatcher(const path_t& src) :
    IPatcher(src) {

    m_dataBase = path_t(src).append(FOLDER_BASE);
    std::filesystem::create_directories(m_dataBase);

    m_migrBase = path_t(src).append("migration").append(FOLDER_BASE);
    std::filesystem::create_directories(m_migrBase);

    m_isAvailable = true;
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

    return result;
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
    const auto gmdir = InstanceFactory::instance().get<DirMgr>()->get(DIR_GAME_JSON_DIALOGUES);
    //std::set<std::string> speakers { };

    size_t total = 0;
    size_t failed = 0;
    size_t ok = 0;

    for (const auto files = FilesystemUtil::sort_files(gmdir); const auto& f : files) {
        const auto fName = f.filename().generic_u8string();
        auto log = fName + std::u8string(u8" => ");

        total++;

        Dialogue dia(f);

        if (!dia.is_valid()) {
            log += u8"Read failed";
            failed++;
            continue;
        }

        const auto hash = HashUtil::file_to_hash(f);
        const auto entries = dia.extract();

        nlohmann::ordered_json j { };
        j[KEY_HASH] = hash;

        auto& list = j[KEY_LIST];

        for (const auto& [k, v] : dia.extract()) {
            const auto& idx = k;
            const auto& [spk, dia] = v;

            auto& entry = list[std::to_string(idx)];
            entry[KEY_SPEAKER] = spk;
            entry[KEY_DIALOGUE] = dia;
            //speakers.emplace(spk);
        }

        if (JsonUtil::save_into_file(j, path_t(dir).append(fName))) {
            log += u8"OK";
            ok++;
        }
        else {
            log += u8"Write failed";
            failed++;
        }

        WvInvoker::log(LOG_LV_PROG, log);
    }

    const auto log = "Total: " + std::to_string(total) + " | migrated: " + std::to_string(ok) + " | Failed: " + std::to_string(failed);
    WvInvoker::log(LOG_LV_INFO, log);

    /*nlohmann::json j { };
    j.parse(speakers);
    JsonUtil::save_into_file(j, path_t(dir).append(FILE_SPEAKERS));*/
}

DialogueMigrStream::DialogueMigrStream(const path_t& file) :
    m_isValid(false) {

    m_isValid = JsonUtil::load_from_file(m_j, file);
}
