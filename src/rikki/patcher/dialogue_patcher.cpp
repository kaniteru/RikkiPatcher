#include "dialogue_patcher.hpp"
#include "rikki/dir_mgr.hpp"
#include "rikki/stream/dialogue_migr_stream.hpp"
#include "rikki/stream/dialogue_patch_stream.hpp"

#include "utils/hash_util.hpp"
#include "utils/filesystem_util.hpp"
#include "utils/instance_factory.hpp"

#include "wv/enums.hpp"
#include "wv/wv_invoker.hpp"

// ======================== C L A S S ========================
// ===    DialoguePatcher
// ======================== C L A S S ========================

size_t DialoguePatcher::patch() {
    const auto gmdir = InstanceFactory::instance().get<DirMgr>()->get(DIR_GAME_JSON_DIALOGUES);

    size_t total = 0;
    size_t failed = 0;
    size_t passed = 0;
    size_t ok = 0;

    for (const auto files = FilesystemUtil::sort_files(m_database); const auto& f : files) {
        const auto fName = f.filename().generic_u8string();
        const auto fGame = path_t(gmdir).append(fName);
        auto log = fName + u8" => ";

        total++;

        // check game file exists
        if (!std::filesystem::exists(fGame)) {
            log += u8"Pass (no gm data)";
            WvInvoker::log(LOG_LV_PROG, log);

            passed++;
            continue;
        }

        Dialogue dia(fGame);

        if (!dia.is_valid()) {
            log += u8"Read failed";
            WvInvoker::log(LOG_LV_PROG, log);

            failed++;
            continue;
        }

        DialoguePatchStream patchStream(f);

        // get patch file data
        const auto dialogues = patchStream.get_dialogues();
        const auto lenDialogues = std::to_string(dialogues.size());

        // apply patch data into game data
        const auto patched = dia.update_dialogues(dialogues);
        const auto lenPatched = std::to_string(patched.size());

        log += std::u8string(lenPatched.begin(), lenPatched.end())
               + u8" / "
               + std::u8string(lenDialogues.begin(), lenDialogues.end())
               + u8" => ";

        if (dia.save()) {
            log += u8"OK";
            ok++;
        } else {
            log += u8"Write failed";
            failed++;
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
    const auto migrFiles = FilesystemUtil::sort_files(m_migrDB);

    const auto gmFiles = FilesystemUtil::sort_files(gmdir);

    for (const auto& f : gmFiles) {
        const auto fName = f.filename().generic_u8string();

        // path_t
        const auto fPatch = path_t(m_database).append(fName);
        const auto fMigr = path_t(m_migrDB).append(fName);

        // extract pure dialogues from game
        Dialogue pureDia(f);
        auto pureMap = pureDia.extract_dialogues();

        // delete patch data when pure data doesn't exists
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

        for (const auto& [k, v] : pureMap) {
            const auto& idx = k;
            const auto& [pureSpk, pureDia] = v;

            // translation found boolean
            bool tranFound = false;

            // find pure dialogue data exist from migration data
            for (const auto& [migrIdx, migrEntry] : migrMap) {
                const auto& [migrSpk, migrDia] = migrEntry;

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
                if (pureSpk != migrSpk) {
                    tranEntry.m_speaker = pureSpk;
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
    std::filesystem::remove_all(m_migrDB);
    std::filesystem::create_directories(m_migrDB);
    DialogueMigrStream::save_migration_data(m_migrDB);
    return true;
}

DialoguePatcher::DialoguePatcher(const path_t& src) :
    IPatcher(src) {

    m_database = path_t(src).append(FOLDER_BASE);
    std::filesystem::create_directories(m_database);

    m_migrDB = path_t(src).append(FOLDER_MIGRATE).append(FOLDER_BASE);
    std::filesystem::create_directories(m_migrDB);

    m_isAvailable = true;
}

// ======================== C L A S S ========================
// ===    ChoicePatcher
// ======================== C L A S S ========================

size_t ChoicePatcher::patch() {
    const auto gmdir = InstanceFactory::instance().get<DirMgr>()->get(DIR_GAME_JSON_DIALOGUES);

    size_t total = 0;
    size_t failed = 0;
    size_t passed = 0;
    size_t ok = 0;

    for (const auto files = FilesystemUtil::sort_files(m_database); const auto& f : files) {
        const auto fName = f.filename().generic_u8string();
        const auto fGame = path_t(gmdir).append(fName);
        auto log = fName + u8" => ";

        total++;

        // check game file exists
        if (!std::filesystem::exists(fGame)) {
            log += u8"Pass (no gm data)";
            WvInvoker::log(LOG_LV_PROG, log);

            passed++;
            continue;
        }

        Dialogue dia(fGame);

        if (!dia.is_valid()) {
            log += u8"Read failed";
            WvInvoker::log(LOG_LV_PROG, log);

            failed++;
            continue;
        }

        ChoicePatchStream patchStream(f);

        // get patch file data
        const auto choices = patchStream.get_choices();
        const auto lenChoices = std::to_string(choices.size());

        // apply patch data into game data
        const auto patched = dia.update_choices(choices);
        const auto lenPatched = std::to_string(patched.size());

        log += std::u8string(lenPatched.begin(), lenPatched.end())
               + u8" / "
               + std::u8string(lenChoices.begin(), lenChoices.end())
               + u8" => ";

        if (dia.save()) {
            log += u8"OK";
            ok++;
        } else {
            log += u8"Write failed";
            failed++;
        }

        WvInvoker::log(LOG_LV_PROG, log);
    }

    std::string log = "Total: " + std::to_string(total) + " | ok: " + std::to_string(ok) + " | passed: " + std::to_string(passed)
                            + " | failed: " + std::to_string(failed);
    WvInvoker::log(LOG_LV_INFO, log);

    return ok;
}

bool ChoicePatcher::migration() {
    const auto gmdir = InstanceFactory::instance().get<DirMgr>()->get(DIR_GAME_JSON_DIALOGUES);

    const auto migrFiles = FilesystemUtil::sort_files(m_migrDB);
    const auto gmFiles = FilesystemUtil::sort_files(gmdir);

    for (const auto& f : gmFiles) {
        const auto fName = f.filename().generic_u8string();

        // path_t
        const auto fPatch = path_t(m_database).append(fName);
        const auto fMigr = path_t(m_migrDB).append(fName);

        // extract pure dialogues and choices from game
        Dialogue pureDia(f);
        const auto pureMap = pureDia.extract_choices();

        // delete patch data when pure data doesn't exists
        if (pureMap.empty()) {
            std::filesystem::remove(fPatch);
            continue;
        }

        // migration file stream
        ChoiceMigrStream migrStream(fMigr);
        const auto migrMap = migrStream.get_choices();

        // check pure dialogue file is updated using hash
        if (const auto pureHash = HashUtil::file_to_hash(f); pureHash == migrStream.get_file_hash()) {
            // if not, doesn't need working.
            continue;
        }

        // pure dialogue file updated.

        choice_map_t newChoMap { };

        // patch file stream
        ChoicePatchStream patchStream(fPatch);
        const auto patchMap = patchStream.get_choices();

        for (const auto& [pureIdx, pureCho] : pureMap) {
            // translation found boolean
            bool tranFound = false;

            // find pure choice data exist from migration data
            for (const auto& migrCho : migrMap | std::views::values) {
                // choice string doesn't matched
                if (pureCho != migrCho) {
                    continue;
                }

                // choice not found in patch data
                if (!patchStream.is_idx_exists(pureIdx)) {
                    break;
                }

                // found translated dialogue from patch data!
                tranFound = true;

                // load translated dialogue from patch data
                const auto tranCho = patchStream.get_choice(pureIdx);
                newChoMap[pureIdx] = std::move(tranCho);
                break;
            }

            // already migrated, pass it
            if (tranFound) {
                continue;
            }

            newChoMap[pureIdx] = pureCho;
        }

        // clear patch data
        patchStream.clear();
        // overwrite patch data using migrated data
        patchStream.set_choices(newChoMap);
        // save overwrote patch data
        patchStream.save();
    }

    return true;
}

bool ChoicePatcher::generate_migration_info() {
    std::filesystem::remove_all(m_migrDB);
    std::filesystem::create_directories(m_migrDB);
    ChoiceMigrStream::save_migration_data(m_migrDB);
    return true;
}

ChoicePatcher::ChoicePatcher(const path_t& src) :
    IPatcher(src) {

    m_database = path_t(src).append(FOLDER_BASE);
    std::filesystem::create_directories(m_database);

    m_migrDB = path_t(src).append(FOLDER_MIGRATE).append(FOLDER_BASE);
    std::filesystem::create_directories(m_migrDB);

    m_isAvailable = true;
}
