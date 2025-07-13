#include "dialogue_patcher.hpp"
#include "rikki/dir_mgr.hpp"
#include "rikki/dir_mgr_enum.hpp"
#include "rikki/data/data_path.hpp"
#include "rikki/patcher/helper/dialogue_patch_helper.hpp"
#include "rikki/data/dialogue/dialogue.hpp"
#include "rikki/data/dialogue/dialogue_json.hpp"
#include "rikki/stream/dialogue_patch_stream.hpp"

#include "utils/logger.hpp"
#include "utils/filesystem_util.hpp"

#include "wv/wv_invoker.hpp"
#include "wv/wv_log_fmt.hpp"

// ======================== C L A S S ========================
// ===    DialoguePatcher
// ======================== C L A S S ========================

PatcherResult DialoguePatcher::patch() {
    PatcherResult result { };
    auto& ok        = result.m_ok;
    auto& failed  = result.m_failed;
    auto& passed = result.m_passed;

    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::PATCH_DIALOGUE_START);

    const auto gmdir = DirMgr::get(DIR_GAME_JSON_DIALOGUES);

    for (const auto files = FilesystemUtil::sort_files(m_db); const auto& f : files) {
        const auto fName = f.filename().string();
        const auto fGame = path_t(gmdir).append(fName);

        // check is game file exists
        if (!fs::exists(fGame)) {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::PATCH_DIALOGUE_PASS_NO_GM_DATA, fName);

            passed++;
            continue;
        }

        Dialogue dia(fGame);

        // check is game file valid
        if (!dia.is_valid()) {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::PATCH_DIALOGUE_FAILED_READ, fName);

            failed++;
            continue;
        }

        const auto res = DialoguePatchHelper::do_patch(f, &dia);

        // save into game file
        if (dia.save()) {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::PATCH_DIALOGUE_OK, fName, res.total(), res.m_ok);
            ok++;
        } else {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::PATCH_DIALOGUE_FAILED_WRITE, fName);
            failed++;
        }
    }

    WvInvoker::log(WV_LOG_LV_INFO, WvLogFmt::PATCH_DIALOGUE_RESULT, result.total(), ok, failed, passed);
    return result;
}

PatcherResult DialoguePatcher::migration() {
    PatcherResult result { };
    auto& ok        = result.m_ok;
    auto& failed  = result.m_failed;
    auto& passed = result.m_passed;

    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::MIGR_DIALOGUE_START);

    const auto gmdir = DirMgr::get(DIR_GAME_JSON_DIALOGUES);
    const auto gmFiles = FilesystemUtil::sort_files(gmdir);

    for (const auto& f : gmFiles) {
        const auto fName = f.filename().string();

        // pure map
        Dialogue pureDia(f);

        if (!pureDia.is_valid()) {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::MIGR_DIALOGUE_FAILED_READ, fName);

            failed++;
            continue;
        }

        const auto fPatch = path_t(m_db).append(fName);
        const auto fMigr   = path_t(m_migrDB).append(fName);

        const auto res = DialoguePatchHelper::do_migrate(fPatch, fMigr, pureDia.extract_dialogues());

        switch (DialoguePatchHelperResult::to_result(res)) {
        case DialoguePatchHelperResult::OK_NO_DATA :
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::MIGR_DIALOGUE_OK_NO_GM_DATA, fName);
            ok++;
            break;

        case DialoguePatchHelperResult::FAILED_SAVE :
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::MIGR_DIALOGUE_FAILED_WRITE, fName);
            failed++;
            break;

        default:
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::MIGR_DIALOGUE_OK, fName, res.total(), res.m_ok);
            ok++;
            break;
        }
    }

    WvInvoker::log(WV_LOG_LV_INFO, WvLogFmt::MIGR_DIALOGUE_RESULT, result.total(), ok, failed, passed);

    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::MIGR_DIALOGUE_EXTRACT);
    DialoguePatcher::extract(m_migrDB);
    return result;
}

PatcherResult DialoguePatcher::extract() {
    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::EXTRACT_DIALOGUE_START);
    DialoguePatcher::extract(m_db);
    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::MIGR_DIALOGUE_EXTRACT);
    DialoguePatcher::extract(m_migrDB);
    return { }; // todo: handle result
}

PatcherResult DialoguePatcher::extract(const path_t& path) {
    PatcherResult result { };
    auto& ok        = result.m_ok;
    auto& failed  = result.m_failed;
    auto& passed = result.m_passed;

    const auto gmdir = DirMgr::get(DIR_GAME_JSON_DIALOGUES);

    FilesystemUtil::delete_and_create_directories(path);

    for (const auto& files = FilesystemUtil::sort_files(gmdir); const auto& f : files) {
        const auto fName = f.filename().string();

        Dialogue pureDia(f);

        if (!pureDia.is_valid()) {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::EXTRACT_DIALOGUE_FAILED_READ, fName);

            failed++;
            continue;
        }

        auto dialogues = pureDia.extract_dialogues();

        if (dialogues.empty()) {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::EXTRACT_DIALOGUE_PASS_NO_GM_DATA, fName);

            passed++;
            continue;
        }

        DialoguePatchStream patchStream(path_t(path).append(fName));
        patchStream.set_dialogues(dialogues);

        if (patchStream.save()) {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::EXTRACT_DIALOGUE_OK, fName, dialogues.size());
            ok++;
        } else {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::EXTRACT_DIALOGUE_FAILED_WRITE, fName);
            failed++;
        }
    }

    WvInvoker::log(WV_LOG_LV_INFO, WvLogFmt::EXTRACT_DIALOGUE_RESULT, result.total(), ok, failed, passed);
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
    auto& ok        = result.m_ok;
    auto& failed  = result.m_failed;
    auto& passed = result.m_passed;

    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::PATCH_CHOICE_START);

    const auto gmdir = DirMgr::get(DIR_GAME_JSON_DIALOGUES);

    for (const auto files = FilesystemUtil::sort_files(m_db); const auto& f : files) {
        const auto fName = f.filename().string();
        const auto fGame = path_t(gmdir).append(fName);

        // check is game file exists
        if (!fs::exists(fGame)) {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::PATCH_CHOICE_PASS_NO_GM_DATA, fName);

            passed++;
            continue;
        }

        Dialogue dia(fGame);

        // check is game file valid
        if (!dia.is_valid()) {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::PATCH_CHOICE_FAILED_READ, fName);

            failed++;
            continue;
        }

        const auto res = ChoicePatchHelper::do_patch(f, &dia);

        // save into game file
        if (dia.save()) {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::PATCH_CHOICE_OK, fName, res.total(), res.m_ok);
            ok++;
        } else {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::PATCH_CHOICE_FAILED_WRITE, fName);
            failed++;
        }
    }

    WvInvoker::log(WV_LOG_LV_INFO, WvLogFmt::PATCH_CHOICE_RESULT, result.total(), ok, failed, passed);
    return result;
}

PatcherResult ChoicePatcher::migration() {
    PatcherResult result { };
    auto& ok        = result.m_ok;
    auto& failed  = result.m_failed;
    auto& passed = result.m_passed;

    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::MIGR_CHOICE_START);

    const auto gmdir = DirMgr::get(DIR_GAME_JSON_DIALOGUES);
    const auto gmFiles = FilesystemUtil::sort_files(gmdir);

    for (const auto& f : gmFiles) {
        const auto fName = f.filename().string();

        Dialogue pureDia(f);

        if (!pureDia.is_valid()) {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::MIGR_CHOICE_FAILED_READ, fName);

            failed++;
            continue;
        }

        const auto fPatch = path_t(m_db).append(fName);
        const auto fMigr   = path_t(m_migrDB).append(fName);

        const auto res = ChoicePatchHelper::do_migrate(fPatch, fMigr, pureDia.extract_choices());

        switch (DialoguePatchHelperResult::to_result(res)) {
        case DialoguePatchHelperResult::OK_NO_DATA :
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::MIGR_CHOICE_OK_NO_GM_DATA, fName);
            ok++;
            break;

        case DialoguePatchHelperResult::FAILED_SAVE :
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::MIGR_CHOICE_FAILED_WRITE, fName);
            failed++;
            break;

        default:
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::MIGR_CHOICE_OK, fName, res.total(), res.m_ok);
            ok++;
            break;
        }
    }

    WvInvoker::log(WV_LOG_LV_INFO, WvLogFmt::MIGR_CHOICE_RESULT, result.total(), ok, failed, passed);

    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::MIGR_CHOICE_EXTRACT);
    ChoicePatcher::extract(m_migrDB);
    return result;
}

PatcherResult ChoicePatcher::extract() {
    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::EXTRACT_CHOICE_START);
    ChoicePatcher::extract(m_db);
    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::MIGR_CHOICE_EXTRACT);
    ChoicePatcher::extract(m_migrDB);
    return { }; // todo: handle result
}

PatcherResult ChoicePatcher::extract(const path_t& path) {
    PatcherResult result { };
    auto& ok        = result.m_ok;
    auto& failed  = result.m_failed;
    auto& passed = result.m_passed;

    const auto gmdir = DirMgr::get(DIR_GAME_JSON_DIALOGUES);

    FilesystemUtil::delete_and_create_directories(path);

    for (const auto& files = FilesystemUtil::sort_files(gmdir); const auto& f : files) {
        const auto fName = f.filename().string();

        Dialogue pureDia(f);

        if (!pureDia.is_valid()) {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::EXTRACT_CHOICE_FAILED_READ, fName);

            failed++;
            continue;
        }

        auto dialogues = pureDia.extract_choices();

        if (dialogues.empty()) {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::EXTRACT_CHOICE_PASS_NO_GM_DATA, fName);

            passed++;
            continue;
        }

        ChoicePatchStream patchStream(path_t(path).append(fName));
        patchStream.set_choices(dialogues);

        if (patchStream.save()) {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::EXTRACT_CHOICE_OK, fName, dialogues.size());
            ok++;
        } else {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::EXTRACT_CHOICE_FAILED_WRITE, fName);
            failed++;
        }
    }

    WvInvoker::log(WV_LOG_LV_INFO, WvLogFmt::EXTRACT_CHOICE_RESULT, result.total(), ok, failed, passed);
    return result;
}

ChoicePatcher::ChoicePatcher(const path_t& src) :
    IPatcher(src),
    m_db(path_t(src) / DialoguePath::PATCH_FOLDER_CHOICE),
    m_migrDB(path_t(src) / DialoguePath::MIGR_FOLDER_CHOICE) {

    m_isAvailable = true;
}
