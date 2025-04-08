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

#include "utils/filesystem_util.hpp"

#include "wv/wv_invoker.hpp"

// ======================== C L A S S ========================
// ===    UITextPatcher
// ======================== C L A S S ========================

PatcherResult UITextPatcher::patch() {
    PatcherResult result { };

    auto do_patch = [this](const path_t& f, IUITextPatcher& p) -> PatcherResult {
        if (const path_t file = (path_t(m_dir) / f); !fs::exists(file)) {
            return { };
        }

        const auto res = p.patch();
        return res;
    };

    // in-game text patch
    InGameUITextPatcher ingame(m_dir, m_pUT);
    result += do_patch(UITextPath::PATCH_FILE_IN_GAME, ingame);

    // setting text patch
    SettingUITextPatcher setting(m_dir, m_pUT);
    result += do_patch(UITextPath::PATCH_FILE_SETTING, setting);

    // dialog text patch
    DialogUITextPatcher dialog(m_dir, m_pUT);
    result += do_patch(UITextPath::PATCH_FILE_DIALOG, dialog);

    // title text patch
    TitleUITextPatcher title(m_dir, m_pUT);
    result += do_patch(UITextPath::PATCH_FILE_DIALOG, title);
    return result;
}

PatcherResult UITextPatcher::migration() {
    return { };
}

PatcherResult UITextPatcher::extract() {
    if (!m_pUT->is_valid()) {
        WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::PATCH_UI_TEXT_FAILED_READ);
        return { };
    }

    FilesystemUtil::delete_and_create_directories(path_t(m_dir) / UITextPath::PATCH_BASE);

    PatcherResult result { };

    InGameUITextPatcher inGame(m_dir, m_pUT);
    result += inGame.extract();

    SettingUITextPatcher setting(m_dir, m_pUT);
    result += setting.extract();

    DialogUITextPatcher dialog(m_dir, m_pUT);
    result += dialog.extract();

    TitleUITextPatcher title(m_dir, m_pUT);
    result += title.extract();

    return result;
}

UITextPatcher::UITextPatcher(const path_t& src, std::shared_ptr<UIText> pUT) :
    IPatcher(src),
    m_pUT(pUT) {

    m_isAvailable = true;
}

// ======================== C L A S S ========================
// ===    IUITextPatcher
// ======================== C L A S S ========================

IUITextPatcher::IUITextPatcher(const path_t& src, std::shared_ptr<UIText> pUT) :
    IPatcher(src),
    m_pUT(pUT) {

    m_isAvailable = true;
}

// ======================== C L A S S ========================
// ===    InGameUITextPatcher
// ======================== C L A S S ========================

PatcherResult InGameUITextPatcher::patch() {
    PatcherResult result { };
    auto& ok        = result.m_ok;
    auto& failed  = result.m_failed;
    auto& passed = result.m_passed;

    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::PATCH_UI_TEXT_IN_GAME_START);

    const UITextPatchStream patchStream(m_db);
    auto patchData = patchStream.get_texts<j::InGameUIText>();

    for (const auto& [pKey, val] : patchData.get_map()) {
        bool patched = false;

        if (const auto it = InGameUITextKeyMgr::g_keys.find(pKey); it != InGameUITextKeyMgr::g_keys.end()) {
            patched = m_pUT->set_in_game(it->second, val);
        }

        if (patched) {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::PATCH_UI_TEXT_IN_GAME_OK, pKey);
            ok++;
        } else {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::PATCH_UI_TEXT_IN_GAME_FAILED, pKey);
            failed++;
        }
    }

    WvInvoker::log(WV_LOG_LV_INFO, WvLogFmt::PATCH_UI_TEXT_IN_GAME_RESULT, result.total(), ok, failed, passed);
    return result;
}

PatcherResult InGameUITextPatcher::migration() {
    return { };
}

PatcherResult InGameUITextPatcher::extract() {
    PatcherResult result { };
    auto& ok        = result.m_ok;
    auto& failed  = result.m_failed;
    auto& passed = result.m_passed;

    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::EXTRACT_UI_TEXT_IN_GAME_START);

    j::InGameUIText ig { };

    for (auto& [pKey, val] : ig.get_map()) {
        try {
            const auto key = InGameUITextKeyMgr::g_keys.at(pKey);
            std::string buf { };
            m_pUT->get_in_game(key, buf);
            val = buf;

            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::EXTRACT_UI_TEXT_IN_GAME_OK, pKey);
            ok++;
        }
        catch (const std::exception& ex) {
            WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::EXTRACT_UI_TEXT_IN_GAME_FAILED, pKey, ex.what());
            failed++;
        }
    }

    UITextPatchStream patchStream(m_db);
    patchStream.set_texts<j::InGameUIText>(ig);

    if (!patchStream.save()) {
        WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::EXTRACT_UI_TEXT_IN_GAME_FAILED_WRITE);
        return { 0, result.total(), 0 };
    }

    WvInvoker::log(WV_LOG_LV_INFO, WvLogFmt::EXTRACT_UI_TEXT_IN_GAME_RESULT, result.total(), ok, failed, passed);
    return result;
}

InGameUITextPatcher::InGameUITextPatcher(const path_t& src, std::shared_ptr<UIText> pUT) :
    IUITextPatcher(src, pUT),
    m_db(path_t(src) / UITextPath::PATCH_FILE_IN_GAME),
    m_migrDB(path_t(src) / UITextPath::MIGR_FILE_IN_GAME) { }

// ======================== C L A S S ========================
// ===    SettingUITextPatcher
// ======================== C L A S S ========================

PatcherResult SettingUITextPatcher::patch() {
    PatcherResult result { };
    auto& ok        = result.m_ok;
    auto& failed  = result.m_failed;
    auto& passed = result.m_passed;

    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::PATCH_UI_TEXT_SETTING_START);

    const UITextPatchStream patchStream(m_db);
    auto patchData = patchStream.get_texts<j::SettingUIText>();

    auto loop_map = [this, &ok, &failed](const auto& m) {
        for (const auto& [pKey, val] : m) {
            bool patched = false;

            if (const auto it = SettingUITextKeyMgr::g_keys.find(pKey); it != SettingUITextKeyMgr::g_keys.end()) {
                const setting_ui_text_t buf(val);
                patched = m_pUT->set_setting(it->second, buf);
            }

            if (patched) {
                WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::PATCH_UI_TEXT_SETTING_OK, pKey);
                ok++;
            } else {
                WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::PATCH_UI_TEXT_SETTING_FAILED, pKey);
                failed++;
            }
        }
    };

    loop_map(patchData.get_map());
    loop_map(patchData.get_controls_usage_map());

    WvInvoker::log(WV_LOG_LV_INFO, WvLogFmt::PATCH_UI_TEXT_SETTING_RESULT, result.total(), ok, failed, passed);
    return result;
}

PatcherResult SettingUITextPatcher::migration() {
    return { };
}

PatcherResult SettingUITextPatcher::extract() {
    PatcherResult result { };
    auto& ok        = result.m_ok;
    auto& failed  = result.m_failed;
    auto& passed = result.m_passed;

    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::EXTRACT_UI_TEXT_SETTING_START);

    j::SettingUIText s { };

    for (const auto& [pKey, val] : s.get_map()) {
        try {
            const auto& key = SettingUITextKeyMgr::g_keys.at(pKey);

            setting_ui_text_t buf { };
            m_pUT->get_setting(key, buf);
            val = buf;

            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::EXTRACT_UI_TEXT_SETTING_OK, pKey);
            ok++;
        }
        catch (const std::exception& ex) {
            WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::EXTRACT_UI_TEXT_SETTING_FAILED, pKey, ex.what());
            failed++;
        }
    }

    for (const auto& [pKey, val] : s.get_controls_usage_map()) {
        try {
            const auto& key = SettingUITextKeyMgr::g_keys.at(pKey);

            setting_ui_text_t buf { };
            m_pUT->get_setting(key, buf);
            val = buf;

            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::EXTRACT_UI_TEXT_SETTING_OK, pKey);
            ok++;
        }
        catch (const std::exception& ex) {
            WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::EXTRACT_UI_TEXT_SETTING_FAILED, pKey, ex.what());
            failed++;
        }
    }

    UITextPatchStream patchStream(m_db);
    patchStream.set_texts<j::SettingUIText>(s);

    if (!patchStream.save()) {
        WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::EXTRACT_UI_TEXT_SETTING_FAILED_WRITE);
        return { 0, result.total(), 0 };
    }

    WvInvoker::log(WV_LOG_LV_INFO, WvLogFmt::EXTRACT_UI_TEXT_SETTING_RESULT, result.total(), ok, failed, passed);
    return result;
}

SettingUITextPatcher::SettingUITextPatcher(const path_t& src, std::shared_ptr<UIText> pUT) :
    IUITextPatcher(src, pUT),
    m_db(path_t(src) / UITextPath::PATCH_FILE_SETTING),
    m_migrDB(path_t(src) / UITextPath::MIGR_FILE_SETTING) { }

// ======================== C L A S S ========================
// ===    DialogUITextPatcher
// ======================== C L A S S ========================

PatcherResult DialogUITextPatcher::patch() {
    PatcherResult result { };
    auto& ok        = result.m_ok;
    auto& failed  = result.m_failed;
    auto& passed = result.m_passed;

    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::PATCH_UI_TEXT_DIALOG_START);

    const UITextPatchStream patchStream(m_db);
    auto patchData = patchStream.get_texts<j::DialogUIText>();

    static auto d_to_entry = [](const j::DialogUIText::Dialog& d) {
        dialog_ui_text_t res { };
        res.system = d.system;
        res.text = d.text;
        return res;
    };

    for (const auto& [pKey, val] : patchData.get_type1_map()) {
        bool patched = false;

        if (const auto it = DialogUITextKeyMgr::g_type1Keys.find(pKey); it != DialogUITextKeyMgr::g_type1Keys.end()) {
            const auto buf = d_to_entry(val);
            patched = m_pUT->set_dialog_type1(it->second, buf);
        }

        if (patched) {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::PATCH_UI_TEXT_DIALOG_OK, pKey);
            ok++;
        } else {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::PATCH_UI_TEXT_DIALOG_FAILED, pKey);
            failed++;
        }
    }

    for (const auto& [pKey, val] : patchData.get_type2_map()) {
        bool patched = false;

        if (const auto it = DialogUITextKeyMgr::g_type2Keys.find(pKey); it != DialogUITextKeyMgr::g_type2Keys.end()) {
            const auto buf = d_to_entry(val);
            patched = m_pUT->set_dialog_type2(it->second, buf);
        }

        if (patched) {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::PATCH_UI_TEXT_DIALOG_OK, pKey);
            ok++;
        } else {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::PATCH_UI_TEXT_DIALOG_FAILED, pKey);
            failed++;
        }
    }

    WvInvoker::log(WV_LOG_LV_INFO, WvLogFmt::PATCH_UI_TEXT_DIALOG_RESULT, result.total(), ok, failed, passed);
    return result;
}

PatcherResult DialogUITextPatcher::migration() {
    return { };
}

PatcherResult DialogUITextPatcher::extract() {
    PatcherResult result { };
    auto& ok        = result.m_ok;
    auto& failed  = result.m_failed;
    auto& passed = result.m_passed;

    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::EXTRACT_UI_TEXT_DIALOG_START);

    j::DialogUIText d { };

    for (const auto& [pKey, val] : d.get_type1_map()) {
        try {
            const auto& key = DialogUITextKeyMgr::g_type1Keys.at(pKey);

            dialog_ui_text_t buf { };
            m_pUT->get_dialog_type1(key, buf);
            val = buf;

            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::EXTRACT_UI_TEXT_DIALOG_OK, pKey);
            ok++;
        }
        catch (const std::exception& ex) {
            WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::EXTRACT_UI_TEXT_DIALOG_FAILED, pKey, ex.what());
            failed++;
        }
    }

    for (const auto& [pKey, val] : d.get_type2_map()) {
        try {
            const auto& key = DialogUITextKeyMgr::g_type2Keys.at(pKey);

            dialog_ui_text_t buf { };
            m_pUT->get_dialog_type2(key, buf);
            val = buf;

            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::EXTRACT_UI_TEXT_DIALOG_OK, pKey);
            ok++;
        }
        catch (const std::exception& ex) {
            WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::EXTRACT_UI_TEXT_DIALOG_FAILED, pKey, ex.what());
            failed++;
        }
    }

    UITextPatchStream patchStream(m_db);
    patchStream.set_texts<j::DialogUIText>(d);

    if (!patchStream.save()) {
        WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::EXTRACT_UI_TEXT_DIALOG_FAILED_WRITE);
        return { 0, result.total(), 0 };
    }

    WvInvoker::log(WV_LOG_LV_INFO, WvLogFmt::EXTRACT_UI_TEXT_DIALOG_RESULT, result.total(), ok, failed, passed);
    return result;
}

DialogUITextPatcher::DialogUITextPatcher(const path_t& src, std::shared_ptr<UIText> pUT) :
    IUITextPatcher(src, pUT),
    m_db(path_t(src) / UITextPath::PATCH_FILE_DIALOG),
    m_migrDB(path_t(src) / UITextPath::MIGR_FILE_DIALOG) { }

// ======================== C L A S S ========================
// ===    TitleUITextPatcher
// ======================== C L A S S ========================

PatcherResult TitleUITextPatcher::patch() {
    PatcherResult result { };
    auto& ok        = result.m_ok;
    auto& failed  = result.m_failed;
    auto& passed = result.m_passed;

    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::PATCH_UI_TEXT_TITLE_START);

    const UITextPatchStream patchStream(m_db);
    auto patchData = patchStream.get_texts<j::TitleUIText>();

    for (const auto& [pKey, val] : patchData.get_map()) {
        bool patched = false;

        if (const auto it = TitleUITextKeyMgr::g_keys.find(pKey); it != TitleUITextKeyMgr::g_keys.end()) {
            patched = m_pUT->set_title(it->second, val);
        }

        if (patched) {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::PATCH_UI_TEXT_TITLE_OK, pKey);
            ok++;
        } else {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::PATCH_UI_TEXT_TITLE_FAILED, pKey);
            failed++;
        }
    }

    WvInvoker::log(WV_LOG_LV_INFO, WvLogFmt::PATCH_UI_TEXT_TITLE_RESULT, result.total(), ok, failed, passed);
    return result;
}

PatcherResult TitleUITextPatcher::migration() {
    return { };
}

PatcherResult TitleUITextPatcher::extract() {
    PatcherResult result { };
    auto& ok        = result.m_ok;
    auto& failed  = result.m_failed;
    auto& passed = result.m_passed;

    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::EXTRACT_UI_TEXT_TITLE_START);

    j::TitleUIText t { };

    for (auto& [pKey, val] : t.get_map()) {
        try {
            const auto key = TitleUITextKeyMgr::g_keys.at(pKey);
            title_ui_text_t buf { };
            m_pUT->get_title(key, buf);
            val = buf;

            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::EXTRACT_UI_TEXT_TITLE_OK, pKey);
            ok++;
        }
        catch (const std::exception& ex) {
            WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::EXTRACT_UI_TEXT_TITLE_FAILED, pKey, ex.what());
            failed++;
        }
    }

    UITextPatchStream patchStream(m_db);
    patchStream.set_texts<j::TitleUIText>(t);

    if (!patchStream.save()) {
        WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::EXTRACT_UI_TEXT_TITLE_FAILED_WRITE);
        return { 0, result.total(), 0 };
    }

    WvInvoker::log(WV_LOG_LV_INFO, WvLogFmt::EXTRACT_UI_TEXT_TITLE_RESULT, result.total(), ok, failed, passed);
    return result;
}

TitleUITextPatcher::TitleUITextPatcher(const path_t& src, std::shared_ptr<UIText> pUT) :
    IUITextPatcher(src, pUT),
    m_db(path_t(src) / UITextPath::PATCH_FILE_TITLE),
    m_migrDB(path_t(src) / UITextPath::MIGR_FILE_TITLE) { }
