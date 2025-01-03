#include "dialogue_patcher.hpp"
#include "rikki/dir_mgr.hpp"
#include "rikki/data/data_path.hpp"
#include "rikki/patcher/helper/dialogue_patch_helper.hpp"
#include "rikki/data/dialogue/dialogue.hpp"
#include "rikki/data/dialogue/dialogue_json.hpp"
#include "rikki/extractor/dialogue/dialogue_extractor.hpp"

#include "utils/filesystem_util.hpp"
#include "utils/instance_factory.hpp"

#include "wv/enums.hpp"
#include "wv/wv_invoker.hpp"

// ======================== C L A S S ========================
// ===    DialoguePatcher
// ======================== C L A S S ========================

PatcherResult DialoguePatcher::patch() { // todo: make using dialogue_patch_helper
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

        const auto res = DialoguePatchHelper::do_patch(f, &dia);
        const auto lenPatched   = std::to_string(res.m_ok);
        const auto lenDialogues = std::to_string(res.m_total);

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

    const std::string log = "Total: " + std::to_string(total)      + " | ok: " + std::to_string(ok)
                                     + " | failed: " + std::to_string(failed) + " | passed: " + std::to_string(passed);
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

        const auto fPatch = path_t(m_db).append(fName);
        const auto fMigr = path_t(m_migrDB).append(fName);

        const auto res = DialoguePatchHelper::do_migrate(fPatch, fMigr, pureDia.extract_dialogues());

        switch (DialoguePatchHelperResult::to_result(res)) {
        case DialoguePatchHelperResult::OK_NO_DATA :
            ok++;
            log += u8"OK (no data)";
            break;

        case DialoguePatchHelperResult::FAILED_SAVE :
            failed++;
            log += u8"Write failed";
            break;

        default:
            ok++;
            log += u8"OK";
            break;
        }

        WvInvoker::log(LOG_LV_PROG, log);
    }

    const std::string log = "Total: " + std::to_string(total)      + " | ok: " + std::to_string(ok)
                                     + " | failed: " + std::to_string(failed) + " | passed: " + std::to_string(passed);
    WvInvoker::log(LOG_LV_INFO, log);
    return result;
}

PatcherResult DialoguePatcher::generate_migration_info() {
    DialogueExtractor extractor(m_migrDir);
    const auto ok = extractor.extract();

    PatcherResult result { };
    result.m_total = ok;
    result.m_ok = ok;
    return result;
}

DialoguePatcher::DialoguePatcher(const path_t& src) :
    IPatcher(src),
    m_db(path_t(src) / DialoguePath::PATCH_FOLDER_DIALOGUE),
    m_migrDB(path_t(src) / DialoguePath::MIGR_FOLDER_DIALOGUE) {

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

        const auto res = ChoicePatchHelper::do_patch(f, &dia);
        const auto lenPatched   = std::to_string(res.m_ok);
        const auto lenChoices = std::to_string(res.m_total);

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

    const std::string log = "Total: " + std::to_string(total)      + " | ok: " + std::to_string(ok)
                                     + " | failed: " + std::to_string(failed) + " | passed: " + std::to_string(passed);
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
        const auto fMigr = path_t(m_migrDB).append(fName);

        auto log = fName + u8" => ";
        total++;

        Dialogue pureDia(f);

        if (!pureDia.is_valid()) {
            log += u8"Read failed (invalid gm data)";
            WvInvoker::log(LOG_LV_PROG, log);

            failed++;
            continue;
        }

        const auto res = ChoicePatchHelper::do_migrate(fPatch, fMigr, pureDia.extract_choices());

        switch (DialoguePatchHelperResult::to_result(res)) {
        case DialoguePatchHelperResult::OK_NO_DATA :
            ok++;
            log += u8"OK (no data)";
            break;

        case DialoguePatchHelperResult::FAILED_SAVE :
            failed++;
            log += u8"Write failed";
            break;

        default:
            ok++;
            log += u8"OK";
            break;
        }

        WvInvoker::log(LOG_LV_PROG, log);
    }

    const std::string log = "Total: " + std::to_string(total)      + " | ok: " + std::to_string(ok)
                                     + " | failed: " + std::to_string(failed) + " | passed: " + std::to_string(passed);
    WvInvoker::log(LOG_LV_INFO, log);
    return result;
}

PatcherResult ChoicePatcher::generate_migration_info() {
    ChoiceExtractor extractor(m_migrDir);
    const auto ok = extractor.extract();

    PatcherResult result { };
    result.m_total = ok;
    result.m_ok = ok;
    return result;
}

ChoicePatcher::ChoicePatcher(const path_t& src) :
    IPatcher(src),
    m_db(path_t(src) / DialoguePath::PATCH_FOLDER_CHOICE),
    m_migrDB(path_t(src) / DialoguePath::MIGR_FOLDER_CHOICE) {

    m_isAvailable = true;
}
