#include "ui_dialogue_patcher.hpp"
#include "rikki/data/data_path.hpp"
#include "rikki/stream/dialogue_patch_stream.hpp"
#include "rikki/data/dialogue/i_dialogue.hpp"
#include "rikki/data/dialogue/dialogue.hpp"
#include "rikki/data/dialogue/dialogue_json.hpp"
#include "rikki/data/ui_dialogue/ui_dialogue.hpp"
#include "rikki/data/ui_dialogue/ui_dialogue_key.hpp"
#include "rikki/extractor/ui/ui_dialogue_extractor.hpp"
#include "rikki/patcher/helper/dialogue_patch_helper.hpp"

#include "wv/enums.hpp"
#include "wv/wv_invoker.hpp"

// ======================== C L A S S ========================
// ===    IUIDialoguePatcher
// ======================== C L A S S ========================

IUIDialoguePatcher::IUIDialoguePatcher(UI* pUI) :
    m_pUI(pUI) { }

// ======================== C L A S S ========================
// ===    UIDialoguePatcher
// ======================== C L A S S ========================

PatcherResult UIDialoguePatcher::patch() {
    PatcherResult result { };
    size_t& total   = result.m_total;
    size_t& ok       = result.m_ok;
    size_t& failed  = result.m_failed;
    size_t& passed = result.m_passed;

    for (const auto& [pKey, pFile] : UIDialogueKey::g_arr) {
        const auto fPatch = path_t(m_db).append(pFile);

        if (!std::filesystem::exists(fPatch)) {
            continue;
        }

        auto log = StringUtil::cstr_to_u8(pFile) + u8" => ";

        total++;

        UIDialogue dia(m_pUI, pKey);

        if (!dia.is_valid()) {
            log += u8"Failed (invalid gm data)";
            WvInvoker::log(LOG_LV_PROG, log);

            failed++;
            continue;
        }

        const auto res = DialoguePatchHelper::do_patch(fPatch, &dia);
        const auto lenPatched   = std::to_string(res.m_ok);
        const auto lenDialogues = std::to_string(res.m_total);

        log += std::u8string(lenPatched.begin(), lenPatched.end())
              + u8" / "
              + std::u8string(lenDialogues.begin(), lenDialogues.end())
              + u8"";
        WvInvoker::log(LOG_LV_PROG, log);

        ok++;
    }

    const std::string log = "Total: " + std::to_string(total);
    WvInvoker::log(LOG_LV_INFO, log);
    return result;
}

PatcherResult UIDialoguePatcher::migration() {
    PatcherResult result { };
    size_t& total   = result.m_total;
    size_t& ok       = result.m_ok;
    size_t& failed  = result.m_failed;
    size_t& passed = result.m_passed;

    for (const auto& [pKey, pFile] : UIDialogueKey::g_arr) {
        auto log = StringUtil::cstr_to_u8(pFile) + u8" => ";
        total++;

        UIDialogue dia(m_pUI, pKey);

        if (!dia.is_valid()) {
            log += u8"Failed (invalid gm data)";
            WvInvoker::log(LOG_LV_PROG, log);

            failed++;
            continue;
        }

        const auto fPatch = path_t(m_db).append(pFile);
        const auto fMigr = path_t(m_migrDB).append(pFile);

        const auto res = DialoguePatchHelper::do_migrate(fPatch, fMigr, dia.extract_dialogues());

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

PatcherResult UIDialoguePatcher::generate_migration_info() {
    WvInvoker::log(LOG_LV_WARN, "ui-dialogue dialogues doesn't support generate the migration info");
    return { };
}

UIDialoguePatcher::UIDialoguePatcher(const path_t& src, UI* pUI) :
    IPatcher(src),
    IUIDialoguePatcher(pUI),
    m_db(path_t(src) / UIDialoguePath::PATCH_FOLDER_DIALOGUE),
    m_migrDB(path_t(src) / UIDialoguePath::MIGR_FOLDER_DIALOGUE) { }

// ======================== C L A S S ========================
// ===    UIChoicePatcher
// ======================== C L A S S ========================

PatcherResult UIChoicePatcher::patch() {
    PatcherResult result { };
    size_t& total   = result.m_total;
    size_t& ok       = result.m_ok;
    size_t& failed  = result.m_failed;
    size_t& passed = result.m_passed;

    for (const auto& [pKey, pFile] : UIDialogueKey::g_arr) {
        const auto fPatch = path_t(m_db).append(pFile);

        if (!std::filesystem::exists(fPatch)) {
            continue;
        }

        auto log = StringUtil::cstr_to_u8(pFile) + u8" => ";

        total++;

        UIDialogue dia(m_pUI, pKey);

        if (!dia.is_valid()) {
            log += u8"Failed (invalid gm data)";
            WvInvoker::log(LOG_LV_PROG, log);

            failed++;
            continue;
        }

        const auto res = ChoicePatchHelper::do_patch(fPatch, &dia);
        const auto lenPatched   = std::to_string(res.m_ok);
        const auto lenDialogues = std::to_string(res.m_total);

        log += std::u8string(lenPatched.begin(), lenPatched.end())
              + u8" / "
              + std::u8string(lenDialogues.begin(), lenDialogues.end())
              + u8"";
        WvInvoker::log(LOG_LV_PROG, log);

        ok++;
    }

    const std::string log = "Total: " + std::to_string(total);
    WvInvoker::log(LOG_LV_INFO, log);
    return result;
}

PatcherResult UIChoicePatcher::migration() {
    PatcherResult result { };
    size_t& total   = result.m_total;
    size_t& ok       = result.m_ok;
    size_t& failed  = result.m_failed;
    size_t& passed = result.m_passed;

    for (const auto& [pKey, pFile] : UIDialogueKey::g_arr) {
        auto log = StringUtil::cstr_to_u8(pFile) + u8" => ";
        total++;

        UIDialogue dia(m_pUI, pKey);

        if (!dia.is_valid()) {
            log += u8"Failed (invalid gm data)";
            WvInvoker::log(LOG_LV_PROG, log);

            failed++;
            continue;
        }

        const auto fPatch = path_t(m_db).append(pFile);
        const auto fMigr = path_t(m_migrDB).append(pFile);

        const auto res = ChoicePatchHelper::do_migrate(fPatch, fMigr, dia.extract_choices());

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

PatcherResult UIChoicePatcher::generate_migration_info() {
    WvInvoker::log(LOG_LV_WARN, "ui-dialogue choices doesn't support generate the migration info");
    return { };
}

UIChoicePatcher::UIChoicePatcher(const path_t& src, UI* pUI) :
    IPatcher(src),
    IUIDialoguePatcher(pUI),
    m_db(path_t(src) / UIDialoguePath::PATCH_FOLDER_CHOICE),
    m_migrDB(path_t(src) / UIDialoguePath::MIGR_FOLDER_CHOICE) { }
