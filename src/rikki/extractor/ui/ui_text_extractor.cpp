#include "ui_text_extractor.hpp"
#include "rikki/data/data_path.hpp"
#include "rikki/data/ui_text/ui_text.hpp"
#include "rikki/data/ui_text/ui_json.hpp"
#include "rikki/data/ui_text/key/ui_text_key.hpp"
#include "rikki/data/ui_text/key/ui_text_dialog_key.hpp"
#include "rikki/data/ui_text/key/ui_text_setting_key.hpp"
#include "rikki/data/ui_text/key/ui_text_in_game_key.hpp"
#include "rikki/stream/ui_patch_stream.hpp"

#include "utils/filesystem_util.hpp"

#include "wv/enums.hpp"
#include "wv/wv_invoker.hpp"

// ======================== C L A S S ========================
// ===    UITextExtractor
// ======================== C L A S S ========================

size_t UITextExtractor::extract() {
    UIText ut(m_pUI);

    if (!ut.is_valid()) {
        WvInvoker::log(LOG_LV_ERR, u8"Can't read the game data");
        return 0;
    }

    FilesystemUtil::delete_and_create_directories(path_t(m_dir) / UITextPath::PATCH_BASE);

    size_t result = 0;

    WvInvoker::log(LOG_LV_ALERT, u8"Start extract the in-game text");
    InGameUITextExtractor inGame(ut, m_dir);
    result += inGame.extract();
    WvInvoker::log(LOG_LV_ALERT, u8"In-game text extract finished");

    WvInvoker::log(LOG_LV_ALERT, u8"Start extract the setting text");
    SettingUITextExtractor setting(ut, m_dir);
    result += setting.extract();
    WvInvoker::log(LOG_LV_ALERT, u8"Setting text extract finished");

    WvInvoker::log(LOG_LV_ALERT, u8"Start extract the dialog text");
    DialogUITextExtractor dialog(ut, m_dir);
    result += dialog.extract();
    WvInvoker::log(LOG_LV_ALERT, u8"Dialog text extract finished");

    return result;
}

UITextExtractor::UITextExtractor(const path_t& dst, UI* const pUI) :
    IExtractor(dst),
    m_pUI(pUI) { }

// ======================== C L A S S ========================
// ===    IUITextExtractor
// ======================== C L A S S ========================

IUITextExtractor::IUITextExtractor(UIText& ut) :
    m_ut(ut) { }

// ======================== C L A S S ========================
// ===    InGameUITextExtractor
// ======================== C L A S S ========================

size_t InGameUITextExtractor::extract() {
    size_t total = 0;
    size_t failed = 0;
    size_t ok = 0;

    InGameUIText ig { };

    for (auto& [pKey, val] : ig.get_map()) {
        auto log = StringUtil::cstr_to_u8(pKey) + std::u8string(u8" => ");
        total++;

        try {
            const auto key = InGameUITextKeyMgr::g_keys.at(pKey);
            std::string buf { };
            m_ut.get_in_game(key, buf);
            val = buf;

            log += u8"OK";
            ok++;
        }
        catch (...) {
            log += u8"Failed";
            failed++;
        }

        WvInvoker::log(LOG_LV_PROG, log);
    }

    UITextPatchStream patchStream(m_db);
    patchStream.set_texts<InGameUIText>(ig);

    if (!patchStream.save()) {
        WvInvoker::log(LOG_LV_ERR, "Can't write extracted in-game text data");
        return 0;
    }

    const auto log = "Total: " + std::to_string(total) + " | extracted: " + std::to_string(ok) + " | Failed: " + std::to_string(failed);
    WvInvoker::log(LOG_LV_INFO, log);
    return ok;
}

InGameUITextExtractor::InGameUITextExtractor(UIText& ut, const path_t& dst) :
    IExtractor(dst),
    IUITextExtractor(ut),
    m_db(path_t(dst) / UITextPath::PATCH_FILE_IN_GAME) { }

// ======================== C L A S S ========================
// ===    SettingUITextExtractor
// ======================== C L A S S ========================

size_t SettingUITextExtractor::extract() {
    size_t total = 0;
    size_t failed = 0;
    size_t ok = 0;

    SettingUIText s { };

    for (const auto& [pKey, val] : s.get_map()) {
        auto log = StringUtil::cstr_to_u8(pKey) + std::u8string(u8" => ");
        total++;

        try {
            const auto& key = SettingUITextKeyMgr::g_keys.at(pKey);

            SettingUITextEntry buf { };
            m_ut.get_setting(key, buf);
            val = buf;

            log += u8"OK";
            ok++;
        }
        catch (...) {
            log += u8"Failed";
            failed++;
        }

        WvInvoker::log(LOG_LV_PROG, log);
    }

    for (const auto& [pKey, val] : s.get_controls_usage_map()) {
        auto log = StringUtil::cstr_to_u8(pKey) + std::u8string(u8" => ");
        total++;

        try {
            const auto& key = SettingUITextKeyMgr::g_keys.at(pKey);

            SettingUITextEntry buf { };
            m_ut.get_setting(key, buf);
            val = buf;

            log += u8"OK";
            ok++;
        }
        catch (...) {
            log += u8"Failed";
            failed++;
        }

        WvInvoker::log(LOG_LV_PROG, log);
    }

    UITextPatchStream patchStream(m_db);
    patchStream.set_texts<SettingUIText>(s);

    if (!patchStream.save()) {
        WvInvoker::log(LOG_LV_ERR, "Can't write extracted setting text data");
        return 0;
    }

    const auto log = "Total: " + std::to_string(total) + " | extracted: " + std::to_string(ok) + " | Failed: " + std::to_string(failed);
    WvInvoker::log(LOG_LV_INFO, log);
    return ok;
}

SettingUITextExtractor::SettingUITextExtractor(UIText& ut, const path_t& dst) :
    IExtractor(dst),
    IUITextExtractor(ut),
    m_db(path_t(dst) / UITextPath::PATCH_FILE_SETTING) { }

// ======================== C L A S S ========================
// ===    DialogUITextExtractor
// ======================== C L A S S ========================

size_t DialogUITextExtractor::extract() {
    size_t total = 0;
    size_t failed = 0;
    size_t ok = 0;

    DialogUIText d { };

    for (const auto& [pKey, val] : d.get_type1_map()) {
        auto log = StringUtil::cstr_to_u8(pKey) + std::u8string(u8" => ");
        total++;

        try {
            const auto& key = DialogUITextKeyMgr::g_type1Keys.at(pKey);

            DialogUITextEntry buf { };
            m_ut.get_dialog_type1(key, buf);
            val = buf;

            log += u8"OK";
            ok++;
        }
        catch (...) {
            log += u8"Failed";
            failed++;
        }

        WvInvoker::log(LOG_LV_PROG, log);
    }

    for (const auto& [pKey, val] : d.get_type2_map()) {
        auto log = StringUtil::cstr_to_u8(pKey) + std::u8string(u8" => ");
        total++;

        try {
            const auto& key = DialogUITextKeyMgr::g_type2Keys.at(pKey);

            DialogUITextEntry buf { };
            m_ut.get_dialog_type2(key, buf);
            val = buf;

            log += u8"OK";
            ok++;
        }
        catch (...) {
            log += u8"Failed";
            failed++;
        }

        WvInvoker::log(LOG_LV_PROG, log);
    }

    UITextPatchStream patchStream(m_db);
    patchStream.set_texts<DialogUIText>(d);

    if (!patchStream.save()) {
        WvInvoker::log(LOG_LV_ERR, "Can't write extracted dialog text data");
        return 0;
    }

    const auto log = "Total: " + std::to_string(total) + " | extracted: " + std::to_string(ok) + " | Failed: " + std::to_string(failed);
    WvInvoker::log(LOG_LV_INFO, log);
    return ok;
}

DialogUITextExtractor::DialogUITextExtractor(UIText& ut, const path_t& dst) :
    IExtractor(dst),
    IUITextExtractor(ut),
    m_db(path_t(dst) / UITextPath::PATCH_FILE_DIALOG) { }
