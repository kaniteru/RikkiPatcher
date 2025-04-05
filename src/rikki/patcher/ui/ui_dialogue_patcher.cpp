#include "ui_dialogue_patcher.hpp"
#include "rikki/data/data_path.hpp"
#include "rikki/stream/dialogue_patch_stream.hpp"
#include "rikki/data/dialogue/i_dialogue.hpp"
#include "rikki/data/dialogue/dialogue.hpp"
#include "rikki/data/dialogue/dialogue_json.hpp"
#include "rikki/data/ui_dialogue/ui_dialogue.hpp"
#include "rikki/data/ui_dialogue/ui_dialogue_key.hpp"
#include "rikki/patcher/helper/dialogue_patch_helper.hpp"

#include "utils/filesystem_util.hpp"

#include "wv/wv_invoker.hpp"

// ======================== C L A S S ========================
// ===    IUIDialoguePatcher
// ======================== C L A S S ========================

IUIDialoguePatcher::IUIDialoguePatcher(std::shared_ptr<UI> pUI) :
    m_pUI(pUI) { }

// ======================== C L A S S ========================
// ===    UIDialoguePatcher
// ======================== C L A S S ========================

PatcherResult UIDialoguePatcher::patch() {
    PatcherResult result { };
    auto& ok        = result.m_ok;
    auto& failed  = result.m_failed;
    auto& passed = result.m_passed;

    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::PATCH_UI_DIALOGUE_START);

    for (const auto& [pKey, pFile] : UIDialogueKey::g_arr) {
        const auto fPatch = path_t(m_db).append(pFile);

        if (!std::filesystem::exists(fPatch)) {
            continue;
        }

        UIDialogue dia(m_pUI, pKey);

        if (!dia.is_valid()) {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::PATCH_UI_DIALOGUE_FAILED_READ, pFile);

            failed++;
            continue;
        }

        const auto res = DialoguePatchHelper::do_patch(fPatch, &dia);

        WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::PATCH_UI_DIALOGUE_OK, pFile, res.total(), res.m_ok);

        ok++;
    }

    WvInvoker::log(WV_LOG_LV_INFO, WvLogFmt::PATCH_UI_DIALOGUE_RESULT, result.total(), ok, failed, passed);
    return result;
}

PatcherResult UIDialoguePatcher::migration() {
    PatcherResult result { };
    auto& ok        = result.m_ok;
    auto& failed  = result.m_failed;
    auto& passed = result.m_passed;

    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::MIGR_UI_DIALOGUE_START);

    for (const auto& [pKey, pFile] : UIDialogueKey::g_arr) {
        UIDialogue dia(m_pUI, pKey);

        if (!dia.is_valid()) {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::MIGR_UI_DIALOGUE_FAILED_READ, pFile);

            failed++;
            continue;
        }

        const auto fPatch = path_t(m_db).append(pFile);
        const auto fMigr = path_t(m_migrDB).append(pFile);

        const auto res = DialoguePatchHelper::do_migrate(fPatch, fMigr, dia.extract_dialogues());

        switch (DialoguePatchHelperResult::to_result(res)) {
        case DialoguePatchHelperResult::OK_NO_DATA :
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::MIGR_UI_DIALOGUE_OK_NO_GM_DATA, pFile);
            ok++;
            break;

        case DialoguePatchHelperResult::FAILED_SAVE :
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::MIGR_UI_DIALOGUE_FAILED_WRITE, pFile);
            failed++;
            break;

        default:
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::MIGR_UI_DIALOGUE_OK, pFile, res.total(), res.m_ok);
            ok++;
            break;
        }
    }

    WvInvoker::log(WV_LOG_LV_INFO, WvLogFmt::MIGR_UI_DIALOGUE_RESULT, result.total(), ok, failed, passed);

    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::MIGR_UI_DIALOGUE_EXTRACT);
    UIDialoguePatcher::extract(m_migrDB, m_pUI);
    return result;
}

PatcherResult UIDialoguePatcher::extract() {
    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::EXTRACT_UI_DIALOGUE_START);
    UIDialoguePatcher::extract(m_db, m_pUI);
    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::MIGR_UI_DIALOGUE_EXTRACT);
    UIDialoguePatcher::extract(m_migrDB, m_pUI);
    return { }; // todo: handle result
}

PatcherResult UIDialoguePatcher::extract(const path_t& dir, std::shared_ptr<UI> pUI) {
    PatcherResult result { };
    auto& ok        = result.m_ok;
    auto& failed  = result.m_failed;
    auto& passed = result.m_passed;

    FilesystemUtil::delete_and_create_directories(dir);

    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::EXTRACT_UI_DIALOGUE_START);

    for (const auto& [pKey, pFile] : UIDialogueKey::g_arr) {
        UIDialogue dia(pUI, pKey);

        if (!dia.is_valid()) {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::EXTRACT_UI_DIALOGUE_FAILED_READ, pFile);

            failed++;
            continue;
        }

        const auto dialogues = dia.extract_dialogues();

        if (dialogues.empty()) {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::EXTRACT_UI_DIALOGUE_PASS_NO_GM_DATA, pFile);

            passed++;
            continue;
        }

        DialoguePatchStream patchStream(path_t(dir).append(pFile));
        patchStream.set_dialogues(dialogues);

        if (patchStream.save()) {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::EXTRACT_UI_DIALOGUE_OK, pFile, dialogues.size());
            ok++;
        } else {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::EXTRACT_UI_DIALOGUE_FAILED_WRITE, pFile);
            failed++;
        }
    }

    WvInvoker::log(WV_LOG_LV_INFO, WvLogFmt::EXTRACT_UI_DIALOGUE_RESULT, result.total(), ok, failed, passed);
    return result;
}

UIDialoguePatcher::UIDialoguePatcher(const path_t& src, std::shared_ptr<UI> pUI) :
    IPatcher(src),
    IUIDialoguePatcher(pUI),
    m_db(path_t(src) / UIDialoguePath::PATCH_FOLDER_DIALOGUE),
    m_migrDB(path_t(src) / UIDialoguePath::MIGR_FOLDER_DIALOGUE) { }

// ======================== C L A S S ========================
// ===    UIChoicePatcher
// ======================== C L A S S ========================

PatcherResult UIChoicePatcher::patch() {
    PatcherResult result { };
    auto& ok        = result.m_ok;
    auto& failed  = result.m_failed;
    auto& passed = result.m_passed;

    for (const auto& [pKey, pFile] : UIDialogueKey::g_arr) {
        const auto fPatch = path_t(m_db).append(pFile);

        if (!std::filesystem::exists(fPatch)) {
            continue;
        }

        UIDialogue dia(m_pUI, pKey);

        if (!dia.is_valid()) {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::PATCH_UI_CHOICE_FAILED_READ, pFile);

            failed++;
            continue;
        }

        const auto res = ChoicePatchHelper::do_patch(fPatch, &dia);

        WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::PATCH_UI_CHOICE_OK, pFile, res.total(), res.m_ok);

        ok++;
    }

    WvInvoker::log(WV_LOG_LV_INFO, WvLogFmt::PATCH_UI_CHOICE_RESULT, result.total(), ok, failed, passed);
    return result;
}

PatcherResult UIChoicePatcher::migration() {
    PatcherResult result { };
    auto& ok        = result.m_ok;
    auto& failed  = result.m_failed;
    auto& passed = result.m_passed;

    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::MIGR_UI_CHOICE_START);

    for (const auto& [pKey, pFile] : UIDialogueKey::g_arr) {
        UIDialogue dia(m_pUI, pKey);

        if (!dia.is_valid()) {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::MIGR_UI_CHOICE_FAILED_READ, pFile);

            failed++;
            continue;
        }

        const auto fPatch = path_t(m_db).append(pFile);
        const auto fMigr = path_t(m_migrDB).append(pFile);

        const auto res = ChoicePatchHelper::do_migrate(fPatch, fMigr, dia.extract_choices());

        switch (DialoguePatchHelperResult::to_result(res)) {
        case DialoguePatchHelperResult::OK_NO_DATA :
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::MIGR_UI_CHOICE_OK_NO_GM_DATA, pFile);
            ok++;
            break;

        case DialoguePatchHelperResult::FAILED_SAVE :
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::MIGR_UI_CHOICE_FAILED_WRITE, pFile);
            failed++;
            break;

        default:
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::MIGR_UI_CHOICE_OK, pFile, res.total(), res.m_ok);
            ok++;
            break;
        }
    }

    WvInvoker::log(WV_LOG_LV_INFO, WvLogFmt::MIGR_UI_CHOICE_RESULT, result.total(), ok, failed, passed);

    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::MIGR_UI_CHOICE_EXTRACT);
    UIChoicePatcher::extract(m_migrDB, m_pUI);
    return result;
}

PatcherResult UIChoicePatcher::extract() {
    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::EXTRACT_UI_CHOICE_START);
    UIChoicePatcher::extract(m_db, m_pUI);
    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::MIGR_UI_CHOICE_EXTRACT);
    UIChoicePatcher::extract(m_migrDB, m_pUI);
    return { }; // todo: handle result
}

PatcherResult UIChoicePatcher::extract(const path_t& src, std::shared_ptr<UI> pUI) {
    PatcherResult result { };
    auto& ok        = result.m_ok;
    auto& failed  = result.m_failed;
    auto& passed = result.m_passed;

    FilesystemUtil::delete_and_create_directories(src);

    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::EXTRACT_UI_CHOICE_START);

    for (const auto& [pKey, pFile] : UIDialogueKey::g_arr) {
        UIDialogue dia(pUI,  pKey);

        if (!dia.is_valid()) {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::EXTRACT_UI_CHOICE_FAILED_READ, pFile);

            failed++;
            continue;
        }

        const auto choices = dia.extract_choices();

        if (choices.empty()) {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::EXTRACT_UI_CHOICE_PASS_NO_GM_DATA, pFile);

            passed++;
            continue;
        }

        ChoicePatchStream patchStream(path_t(src).append(pFile));
        patchStream.set_choices(choices);

        if (patchStream.save()) {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::EXTRACT_UI_CHOICE_OK, pFile, choices.size());
            ok++;
        } else {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::EXTRACT_UI_CHOICE_FAILED_WRITE, pFile);
            failed++;
        }
    }

    WvInvoker::log(WV_LOG_LV_INFO, WvLogFmt::EXTRACT_UI_CHOICE_RESULT, result.total(), ok, failed, passed);
    return result;
}

UIChoicePatcher::UIChoicePatcher(const path_t& src, std::shared_ptr<UI> pUI) :
    IPatcher(src),
    IUIDialoguePatcher(pUI),
    m_db(path_t(src) / UIDialoguePath::PATCH_FOLDER_CHOICE),
    m_migrDB(path_t(src) / UIDialoguePath::MIGR_FOLDER_CHOICE) { }
