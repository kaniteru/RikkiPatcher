#include "dialogue_patcher.hpp"
#include "rikki/dir_mgr.hpp"
#include "rikki/data/dialogue/dialogue.hpp"
#include "rikki/data/dialogue/dialogue_json.hpp"
#include "rikki/extractor/dialogue_extractor.hpp"
#include "rikki/stream/dialogue_patch_stream.hpp"

#include "utils/filesystem_util.hpp"
#include "utils/instance_factory.hpp"

#include "wv/enums.hpp"
#include "wv/wv_invoker.hpp"

// ======================== C L A S S ========================
// ===    DialoguePatcher
// ======================== C L A S S ========================

PatcherResult DialoguePatcher::patch() {
    const auto gmdir = INSTFAC(DirMgr)->get(DIR_GAME_JSON_DIALOGUES);
    PatcherResult result { };

    size_t& total =  result.m_total;
    size_t& ok = result.m_ok;
    size_t& failed = result.m_failed;
    size_t& passed = result.m_passed;

    for (const auto files = FilesystemUtil::sort_files(m_db); const auto& f : files) {
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

    const std::string log = "Total: " + std::to_string(total) + " | ok: " + std::to_string(ok) + " | passed: " + std::to_string(passed)
                            + " | failed: " + std::to_string(failed);
    WvInvoker::log(LOG_LV_INFO, log);
    return result;
}

PatcherResult DialoguePatcher::migration() {
    PatcherResult result { };
    size_t& total   =  result.m_total;
    size_t& ok       = result.m_ok;
    size_t& failed  = result.m_failed;
    size_t& passed = result.m_passed;

    const auto gmdir = INSTFAC(DirMgr)->get(DIR_GAME_JSON_DIALOGUES);
    const auto gmFiles = FilesystemUtil::sort_files(gmdir);

    for (const auto& f : gmFiles) {
        const auto fName = f.filename().generic_u8string();
        const auto fPatch = path_t(m_db).append(fName);

        auto log = fName + u8" => ";
        total++;

        // pure map
        Dialogue pureDia(f);

        if (!pureDia.is_valid()) {
            log += u8"Read failed (invalid gm data)";
            WvInvoker::log(LOG_LV_PROG, log);

            failed++;
            continue;
        }

        const auto pureMap = pureDia.extract_dialogues();

        // delete patch data when pure data doesn't exists
        if (pureMap.empty()) {
            if (std::filesystem::exists(fPatch)) {
                std::filesystem::remove(fPatch);
            }

            log += u8"OK";
            WvInvoker::log(LOG_LV_PROG, log);

            ok++;
            continue;
        }

        // patcher stream
        DialoguePatchStream patchStream(fPatch);

        // create a pure patch file when doesn't exist
        if (!std::filesystem::exists(fPatch)) {
            patchStream.clear();
            patchStream.set_dialogues(pureMap);

            if (patchStream.save()) {
                log += u8"OK";
                ok++;
            } else {
                log += u8"Write failed";
                failed++;
            }

            WvInvoker::log(LOG_LV_PROG, log);
            continue;
        }

        const auto fMigr = path_t(m_migrDB).append(fName);

        // delete and create a pure patch file when migr file doesn't exist.
        if (!std::filesystem::exists(fMigr)) {
            patchStream.clear();
            patchStream.set_dialogues(pureMap);

            if (patchStream.save()) {
                log += u8"OK";
                ok++;
            } else {
                log += u8"Write failed";
                failed++;
            }

            WvInvoker::log(LOG_LV_PROG, log);
            continue;
        }

        DialoguePatchStream migrStream(fMigr);

        // migr map
        const auto migrMap = migrStream.get_dialogues();
        // patch map
        const auto patchMap = patchStream.get_dialogues();

        // new map
        dialogue_map_t newMap { };

        for (const auto& [idx, pureEntry] : pureMap) {
            if (const auto migrIt = migrMap.find(idx); migrIt != migrMap.end()) {
                const auto& migrEntry = migrIt->second;

                // check is equals the pure-entry same as migr-entry
                if (pureEntry == migrEntry) {
                    // found translated entry
                    if (const auto patchIt = patchMap.find(idx); patchIt != patchMap.end()) {
                        newMap[idx] = patchIt->second;
                        continue;
                    }
                }
            }

            // dialogue was updated
            j::Dialogue newEntry = pureEntry;
            bool foundSpk = false;
            const auto lenPureSpans = pureEntry.spans.size();
            std::vector<size_t> foundTexts { };
            foundTexts.reserve(lenPureSpans);

            // check is atts updated
            if (migrMap.at(idx).atts == pureEntry.atts) {
                newEntry.atts = patchMap.at(idx).atts;
            }

            for (const auto& [migrIdx, migrEntry] : migrMap) {
                // check is equals the migr-entry same as pure-entry
                if (migrEntry == pureEntry) {
                    // translated entry found
                    newEntry = patchMap.at(migrIdx);
                    break;
                }

                // found a translated speaker when not found
                if (!foundSpk && migrEntry.speaker == pureEntry.speaker) {
                    newEntry.speaker = patchMap.at(migrIdx).speaker;
                    foundSpk = true;
                }

                // found translated texts when not found
                if (!foundTexts.size() != lenPureSpans) {
                    for (uint32_t i = 0; i < pureEntry.spans.size(); i++) {
                        if (std::ranges::find(foundTexts, i) != foundTexts.end()) {
                            continue;
                        }

                        const auto& pureText = pureEntry.spans[i].html;
                        const auto& migrSpans = migrEntry.spans;

                        for (uint32_t j = 0; j < migrSpans.size(); j++) {
                            if (migrSpans[j].text == pureText) {
                                foundTexts.push_back(i);
                                newEntry.spans[i].text = patchMap.at(migrIdx).spans[j].text;
                                break;
                            }
                        }
                    }
                }

                // escape the loop when found translated entry perfectly
                if (foundSpk && foundTexts.size() == lenPureSpans) {
                    break;
                }
            }

            newMap[idx] = newEntry;
        }

        patchStream.clear();
        patchStream.set_dialogues(newMap);

        if (!patchStream.save()) {
            log += u8"Write failed";
            WvInvoker::log(LOG_LV_PROG, log);

            failed++;
        } else {
            log += u8"OK";
            WvInvoker::log(LOG_LV_PROG, log);

            ok++;
        }
    }

    std::string log = "Total: " + std::to_string(total) + " | ok: " + std::to_string(ok)
                            + " | failed: " + std::to_string(failed) + " | passed: " + std::to_string(passed);
    WvInvoker::log(LOG_LV_INFO, log);
    return result;
}

PatcherResult DialoguePatcher::generate_migration_info() {
    std::filesystem::remove_all(m_migrDB);
    //std::filesystem::create_directories(m_migrDB); // will do it in the extractor

    DialogueExtractor extractor(m_migrDir); // using m_migrDir because extractor automatically appends folder name into arg
    const auto ok = extractor.extract();

    PatcherResult result { };
    result.m_total = ok;
    result.m_ok = ok;
    return result;
}

DialoguePatcher::DialoguePatcher(const path_t& src) :
    IPatcher(src) {

    m_db = path_t(src).append(FOLDER_BASE);
    std::filesystem::create_directories(m_db);

    m_migrDB = path_t(src).append(FOLDER_MIGRATE).append(FOLDER_BASE);
    std::filesystem::create_directories(m_migrDB);

    m_isAvailable = true;
}

// ======================== C L A S S ========================
// ===    ChoicePatcher
// ======================== C L A S S ========================

PatcherResult ChoicePatcher::patch() {
    PatcherResult result { };
    size_t& total   =  result.m_total;
    size_t& ok       = result.m_ok;
    size_t& failed  = result.m_failed;
    size_t& passed = result.m_passed;

    const auto gmdir = INSTFAC(DirMgr)->get(DIR_GAME_JSON_DIALOGUES);

    for (const auto files = FilesystemUtil::sort_files(m_db); const auto& f : files) {
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

    return result;
}

PatcherResult ChoicePatcher::migration() {
    PatcherResult result { };
    size_t& total   =  result.m_total;
    size_t& ok       = result.m_ok;
    size_t& failed  = result.m_failed;
    size_t& passed = result.m_passed;

    const auto gmdir = INSTFAC(DirMgr)->get(DIR_GAME_JSON_DIALOGUES);
    const auto gmFiles = FilesystemUtil::sort_files(gmdir);

    for (const auto& f : gmFiles) {
        const auto fName = f.filename().generic_u8string();
        const auto fPatch = path_t(m_db).append(fName);

        auto log = fName + u8" => ";
        total++;

        // pure map
        Dialogue pureDia(f);

        if (!pureDia.is_valid()) {
            log += u8"Read failed (invalid gm data)";
            WvInvoker::log(LOG_LV_PROG, log);

            failed++;
            continue;
        }

        const auto pureMap = pureDia.extract_choices();

        // delete patch data when pure data doesn't exists
        if (pureMap.empty()) {
            if (std::filesystem::exists(fPatch)) {
                std::filesystem::remove(fPatch);
            }

            log += u8"OK";
            WvInvoker::log(LOG_LV_PROG, log);

            ok++;
            continue;
        }

        // patcher stream
        ChoicePatchStream patchStream(fPatch);

        // create a pure patch file when doesn't exist
        if (!std::filesystem::exists(fPatch)) {
            patchStream.clear();
            patchStream.set_choices(pureMap);

            if (patchStream.save()) {
                log += u8"OK";
                ok++;
            } else {
                log += u8"Write failed";
                failed++;
            }

            WvInvoker::log(LOG_LV_PROG, log);
            continue;
        }

        const auto fMigr = path_t(m_migrDB).append(fName);

        // delete and create a pure patch file when migr file doesn't exist.
        if (!std::filesystem::exists(fMigr)) {
            patchStream.clear();
            patchStream.set_choices(pureMap);

            if (patchStream.save()) {
                log += u8"OK";
                ok++;
            } else {
                log += u8"Write failed";
                failed++;
            }

            WvInvoker::log(LOG_LV_PROG, log);
            continue;
        }

        ChoicePatchStream migrPatcher(fMigr);

        // migr map
        const auto migrMap = migrPatcher.get_choices();

        // patch map
        const auto patchMap = patchStream.get_choices();

        // new map
        choice_map_t newMap { };

        for (const auto& [idx, pureEntry] : pureMap) {
            if (const auto migrIt = migrMap.find(idx); migrIt != migrMap.end()) {
                const auto& migrEntry = migrIt->second;

                // check is equals the pure-entry same as migr-entry
                if (pureEntry == migrEntry) {
                    // found translated entry
                    if (const auto patchIt = patchMap.find(idx); patchIt != patchMap.end()) {
                        newMap[idx] = patchIt->second;
                        continue;
                    }
                }
            }

            // choice was updated
            j::Choice newEntry = pureEntry;

            for (const auto& [migrIdx, migrEntry] : migrMap) {
                // check is equals the migr-entry same as pure-entry
                if (migrEntry == pureEntry) {
                    // translated entry found
                    newEntry = patchMap.at(migrIdx);
                    break;
                }
            }

            newMap[idx] = newEntry;
        }

        patchStream.clear();
        patchStream.set_choices(newMap);

        if (!patchStream.save()) {
            log += u8"Write failed";
            WvInvoker::log(LOG_LV_PROG, log);

            failed++;
        } else {
            log += u8"OK";
            WvInvoker::log(LOG_LV_PROG, log);

            ok++;
        }
    }

    std::string log = "Total: " + std::to_string(total) + " | ok: " + std::to_string(ok)
                        + " | failed: " + std::to_string(failed) + " | passed: " + std::to_string(passed);
    WvInvoker::log(LOG_LV_INFO, log);
    return result;
}

PatcherResult ChoicePatcher::generate_migration_info() {
    std::filesystem::remove_all(m_migrDB);
    //std::filesystem::create_directories(m_migrDB); // will do it in the extractor

    ChoiceExtractor extractor(m_migrDir); // using m_migrDir because extractor automatically appends folder name into arg
    const auto ok = extractor.extract();

    PatcherResult result { };
    result.m_total = ok;
    result.m_ok = ok;
    return result;
}

ChoicePatcher::ChoicePatcher(const path_t& src) :
    IPatcher(src) {

    m_db = path_t(src).append(FOLDER_BASE);
    std::filesystem::create_directories(m_db);

    m_migrDB = path_t(src).append(FOLDER_MIGRATE).append(FOLDER_BASE);
    std::filesystem::create_directories(m_migrDB);

    m_isAvailable = true;
}
