#include "ui_text_patcher.hpp"

#include "rikki/data/data_path.hpp"
#include "rikki/data/ui/ui.hpp"
#include "rikki/data/ui_text/ui_text.hpp"
#include "rikki/data/ui_text/ui_text_json.hpp"
#include "rikki/data/ui_text/key/ui_text_in_game_key.hpp"
#include "rikki/data/ui_text/key/ui_text_setting_key.hpp"
#include "rikki/data/ui_text/key/ui_text_dialog_key.hpp"
#include "rikki/data/ui_text/key/ui_text_title_key.hpp"
#include "rikki/stream/ui_patch_stream.hpp"
#include "rikki/stream/ui_migr_stream.hpp"
#include "utils/filesystem_util.hpp"

#include "utils/string_util.hpp"
#include "utils/ui_text_util.hpp"

#include "wv/enums.hpp"
#include "wv/wv_invoker.hpp"

// ======================== C L A S S ========================
// ===    UITextPatcher
// ======================== C L A S S ========================

PatcherResult UITextPatcher::patch() {
    PatcherResult result { };
    size_t& total   =  result.m_total;
    size_t& ok       = result.m_ok;
    size_t& failed  = result.m_failed;
    size_t& passed = result.m_passed;

    auto do_patch = [this](const path_t& f, IUITextPatcher& p, const std::u8string& str) -> PatcherResult {
        if (const path_t file = (path_t(m_dir) / f); !std::filesystem::exists(file)) {
            return { };
        }

        WvInvoker::log(LOG_LV_ALERT, u8"Start patch the " + str + u8" text");
        const auto res = p.patch();
        WvInvoker::log(LOG_LV_ALERT, str + u8" text patch finished");
        return res;
    };

    // in-game text patch
    InGameUITextPatcher ingame(m_dir, m_pUT);
    result += do_patch(UITextPath::PATCH_FILE_IN_GAME, ingame, u8"in-game");

    // setting text patch
    SettingUITextPatcher setting(m_dir, m_pUT);
    result += do_patch(UITextPath::PATCH_FILE_SETTING, setting, u8"setting");

    // dialog text patch
    DialogUITextPatcher dialog(m_dir, m_pUT);
    result += do_patch(UITextPath::PATCH_FILE_DIALOG, dialog, u8"dialog");

    // title text patch
    TitleUITextPatcher title(m_dir, m_pUT);
    result += do_patch(UITextPath::PATCH_FILE_DIALOG, title, u8"title");
    return result;
}

PatcherResult UITextPatcher::migration() {
    return { };
}

PatcherResult UITextPatcher::generate_migration_info() {
    // using migrate dir because currently, it's just wrapper of extractor not pure migr stream.
    //UITextMigrStream::save_migration_data(m_migrDir);
    return { };
}

UITextPatcher::UITextPatcher(const path_t& src, UIText* const pUT) :
    IPatcher(src),
    m_pUT(pUT) {

    m_isAvailable = true;
}

// ======================== C L A S S ========================
// ===    IUITextPatcher
// ======================== C L A S S ========================

IUITextPatcher::IUITextPatcher(const path_t& src, UIText* ut) :
    IPatcher(src),
    m_ut(ut) {

    m_isAvailable = true;
}

// ======================== C L A S S ========================
// ===    InGameUITextPatcher
// ======================== C L A S S ========================

PatcherResult InGameUITextPatcher::patch() {
    PatcherResult result { };
    size_t& total   = result.m_total;
    size_t& ok       = result.m_ok;
    size_t& failed  = result.m_failed;
    size_t& passed = result.m_passed;

    const UITextPatchStream patchStream(m_db);
    auto patchData = patchStream.get_texts<j::InGameUIText>();

    for (const auto& [pKey, val] : patchData.get_map()) {
        total++;
        std::u8string log = StringUtil::cstr_to_u8(pKey) + u8"=>";

        bool patched = false;

        if (const auto it = InGameUITextKeyMgr::g_keys.find(pKey); it != InGameUITextKeyMgr::g_keys.end()) {
            patched = m_ut->set_in_game(it->second, val);
        }

        if (patched) {
            ok++;
            log += u8"OK";
        } else {
            failed++;
            log += u8"Failed";
        }

        WvInvoker::log(LOG_LV_PROG, log);
    }

    const std::string log = "Total: " + std::to_string(total)      + " | ok: " + std::to_string(ok)
                                     + " | failed: " + std::to_string(failed) + " | passed: " + std::to_string(passed);
    WvInvoker::log(LOG_LV_INFO, log);
    return result;
}

PatcherResult InGameUITextPatcher::migration() {
    return { };
}

PatcherResult InGameUITextPatcher::generate_migration_info() {
    return { };
}

InGameUITextPatcher::InGameUITextPatcher(const path_t& src, UIText* ut) :
    IUITextPatcher(src, ut),
    m_db(path_t(src) / UITextPath::PATCH_FILE_IN_GAME),
    m_migrDB(path_t(src) / UITextPath::MIGR_FILE_IN_GAME) { }

// ======================== C L A S S ========================
// ===    SettingUITextPatcher
// ======================== C L A S S ========================

PatcherResult SettingUITextPatcher::patch() {
    PatcherResult result { };
    size_t& total   = result.m_total;
    size_t& ok       = result.m_ok;
    size_t& failed  = result.m_failed;
    size_t& passed = result.m_passed;

    const UITextPatchStream patchStream(m_db);
    auto patchData = patchStream.get_texts<j::SettingUIText>();

    auto loop_map = [this, &total, &ok, &failed](const auto& m) {
        for (const auto& [pKey, val] : m) {
            total++;
            std::u8string log = StringUtil::cstr_to_u8(pKey) + u8"=>";

            bool patched = false;

            if (const auto it = SettingUITextKeyMgr::g_keys.find(pKey); it != SettingUITextKeyMgr::g_keys.end()) {
                const setting_ui_text_t buf(val);
                patched = m_ut->set_setting(it->second, buf);
            }

            if (patched) {
                ok++;
                log += u8"OK";
            } else {
                failed++;
                log += u8"Failed";
            }

            WvInvoker::log(LOG_LV_PROG, log);
        }
    };

    loop_map(patchData.get_map());
    loop_map(patchData.get_controls_usage_map());

    const std::string log = "Total: " + std::to_string(total)      + " | ok: " + std::to_string(ok)
                                     + " | failed: " + std::to_string(failed) + " | passed: " + std::to_string(passed);
    WvInvoker::log(LOG_LV_INFO, log);
    return result;
}

PatcherResult SettingUITextPatcher::migration() {
    return { };
}

PatcherResult SettingUITextPatcher::generate_migration_info() {
    return { };
}

SettingUITextPatcher::SettingUITextPatcher(const path_t& src, UIText* ut) :
    IUITextPatcher(src, ut),
    m_db(path_t(src) / UITextPath::PATCH_FILE_SETTING),
    m_migrDB(path_t(src) / UITextPath::MIGR_FILE_SETTING) { }

// ======================== C L A S S ========================
// ===    DialogUITextPatcher
// ======================== C L A S S ========================

PatcherResult DialogUITextPatcher::patch() {
    PatcherResult result { };
    size_t& total   = result.m_total;
    size_t& ok       = result.m_ok;
    size_t& failed  = result.m_failed;
    size_t& passed = result.m_passed;

    const UITextPatchStream patchStream(m_db);
    auto patchData = patchStream.get_texts<j::DialogUIText>();

    static auto d_to_entry = [](const j::DialogUIText::Dialog& d) {
        dialog_ui_text_t res { };
        res.system = d.system;
        res.text = d.text;
        return res;
    };

    for (const auto& [pKey, val] : patchData.get_type1_map()) {
        total++;
        std::u8string log = StringUtil::cstr_to_u8(pKey) + u8"=>";

        bool patched = false;

        if (const auto it = DialogUITextKeyMgr::g_type1Keys.find(pKey); it != DialogUITextKeyMgr::g_type1Keys.end()) {
            const auto buf = d_to_entry(val);
            patched = m_ut->set_dialog_type1(it->second, buf);
        }

        if (patched) {
            ok++;
            log += u8"OK";
        } else {
            failed++;
            log += u8"Failed";
        }

        WvInvoker::log(LOG_LV_PROG, log);
    }

    for (const auto& [pKey, val] : patchData.get_type2_map()) {
        total++;
        std::u8string log = StringUtil::cstr_to_u8(pKey) + u8"=>";

        bool patched = false;

        if (const auto it = DialogUITextKeyMgr::g_type2Keys.find(pKey); it != DialogUITextKeyMgr::g_type2Keys.end()) {
            const auto buf = d_to_entry(val);
            patched = m_ut->set_dialog_type2(it->second, buf);
        }

        if (patched) {
            ok++;
            log += u8"OK";
        } else {
            failed++;
            log += u8"Failed";
        }

        WvInvoker::log(LOG_LV_PROG, log);
    }

    const std::string log = "Total: " + std::to_string(total)      + " | ok: " + std::to_string(ok)
                                     + " | failed: " + std::to_string(failed) + " | passed: " + std::to_string(passed);
    WvInvoker::log(LOG_LV_INFO, log);
    return result;
}

PatcherResult DialogUITextPatcher::migration() {
    return { };
}

PatcherResult DialogUITextPatcher::generate_migration_info() {
    return { };
}

DialogUITextPatcher::DialogUITextPatcher(const path_t& src, UIText* ut) :
    IUITextPatcher(src, ut),
    m_db(path_t(src) / UITextPath::PATCH_FILE_DIALOG),
    m_migrDB(path_t(src) / UITextPath::MIGR_FILE_DIALOG) { }

// ======================== C L A S S ========================
// ===    TitleUITextPatcher
// ======================== C L A S S ========================

PatcherResult TitleUITextPatcher::patch() {
    PatcherResult result { };
    size_t& total   = result.m_total;
    size_t& ok       = result.m_ok;
    size_t& failed  = result.m_failed;
    size_t& passed = result.m_passed;

    const UITextPatchStream patchStream(m_db);
    auto patchData = patchStream.get_texts<j::TitleUIText>();

    for (const auto& [pKey, val] : patchData.get_map()) {
        total++;
        std::u8string log = StringUtil::cstr_to_u8(pKey) + u8"=>";

        bool patched = false;

        if (const auto it = TitleUITextKeyMgr::g_keys.find(pKey); it != TitleUITextKeyMgr::g_keys.end()) {
            patched = m_ut->set_title(it->second, val);
        }

        if (patched) {
            ok++;
            log += u8"OK";
        } else {
            failed++;
            log += u8"Failed";
        }

        WvInvoker::log(LOG_LV_PROG, log);
    }

    const std::string log = "Total: " + std::to_string(total)      + " | ok: " + std::to_string(ok)
                                     + " | failed: " + std::to_string(failed) + " | passed: " + std::to_string(passed);
    WvInvoker::log(LOG_LV_INFO, log);
    return result;
}

PatcherResult TitleUITextPatcher::migration() {
    return { };
}

PatcherResult TitleUITextPatcher::generate_migration_info() {
    return { };
}

TitleUITextPatcher::TitleUITextPatcher(const path_t& src, UIText* ut) :
    IUITextPatcher(src, ut),
    m_db(path_t(src) / UITextPath::PATCH_FILE_TITLE),
    m_migrDB(path_t(src) / UITextPath::MIGR_FILE_TITLE) { }
