#include "ui_text_patcher.hpp"
#include "rikki/data/ui_text/ui_text.hpp"
#include "rikki/data/ui_text/ui_json.hpp"
#include "rikki/data/ui_text/key/ui_text_dialog_key.hpp"
#include "rikki/data/ui_text/key/ui_text_setting_key.hpp"
#include "rikki/data/ui_text/key/ui_text_in_game_key.hpp"
#include "rikki/stream/ui_patch_stream.hpp"

#include "utils/string_util.hpp"

#include "wv/enums.hpp"
#include "wv/wv_invoker.hpp"

// ======================== C L A S S ========================
// ===    IUITextPatcher
// ======================== C L A S S ========================

IUITextPatcher::IUITextPatcher(UIText* ut, const path_t& src) :
    IPatcher(src),
    m_ut(ut),
    m_base(path_t(src) / UITextPatchStream::FOLDER_BASE),
    m_baseMigr(path_t(m_migrDir) / UITextPatchStream::FOLDER_BASE) { }

// ======================== C L A S S ========================
// ===    InGameUITextPatcher
// ======================== C L A S S ========================

PatcherResult InGameUITextPatcher::patch() {
    PatcherResult result { };
    size_t& total   = result.m_total;
    size_t& ok       = result.m_ok;
    size_t& failed  = result.m_failed;
    size_t& passed = result.m_passed;

    const UITextPatchStream patchStream(path_t(m_base).append(UITextPatchStream::FILE_IN_GAME));
    auto patchData = patchStream.get_texts<InGameUIText>();

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

    const std::string log = "Total: " + std::to_string(total) + " | ok: " + std::to_string(ok) + " | passed: " + std::to_string(passed)
                            + " | failed: " + std::to_string(failed);
    WvInvoker::log(LOG_LV_INFO, log);
    return result;
}

PatcherResult InGameUITextPatcher::migration() {
    return { };
}

PatcherResult InGameUITextPatcher::generate_migration_info() {
    return { };
}

InGameUITextPatcher::InGameUITextPatcher(UIText* ut, const path_t& src) :
    IUITextPatcher(ut, src) { }

// ======================== C L A S S ========================
// ===    SettingUITextPatcher
// ======================== C L A S S ========================

PatcherResult SettingUITextPatcher::patch() {
    PatcherResult result { };
    size_t& total   = result.m_total;
    size_t& ok       = result.m_ok;
    size_t& failed  = result.m_failed;
    size_t& passed = result.m_passed;

    const UITextPatchStream patchStream(path_t(m_base).append(UITextPatchStream::FILE_SETTING));
    auto patchData = patchStream.get_texts<SettingUIText>();

    auto loop_map = [this, &total, &ok, &failed](const auto& m) {
        for (const auto& [pKey, val] : m) {
            total++;
            std::u8string log = StringUtil::cstr_to_u8(pKey) + u8"=>";

            bool patched = false;

            if (const auto it = SettingUITextKeyMgr::g_keys.find(pKey); it != SettingUITextKeyMgr::g_keys.end()) {
                const SettingUITextEntry buf(val);
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

    const std::string log = "Total: " + std::to_string(total) + " | ok: " + std::to_string(ok) + " | passed: " + std::to_string(passed)
                        + " | failed: " + std::to_string(failed);
    WvInvoker::log(LOG_LV_INFO, log);
    return result;
}

PatcherResult SettingUITextPatcher::migration() {
    return { };
}

PatcherResult SettingUITextPatcher::generate_migration_info() {
    return { };
}

SettingUITextPatcher::SettingUITextPatcher(UIText* ut, const path_t& src) :
    IUITextPatcher(ut, src) { }

// ======================== C L A S S ========================
// ===    DialogUITextPatcher
// ======================== C L A S S ========================

PatcherResult DialogUITextPatcher::patch() {
    PatcherResult result { };
    size_t& total   = result.m_total;
    size_t& ok       = result.m_ok;
    size_t& failed  = result.m_failed;
    size_t& passed = result.m_passed;

    const UITextPatchStream patchStream(path_t(m_base).append(UITextPatchStream::FILE_DIALOG));
    auto patchData = patchStream.get_texts<DialogUIText>();

    static auto d_to_entry = [](const DialogUIText::Dialog& d) {
        DialogUITextEntry res { };
        res.m_system = d.system;
        res.m_text = d.text;
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

    const std::string log = "Total: " + std::to_string(total) + " | ok: " + std::to_string(ok) + " | passed: " + std::to_string(passed)
                        + " | failed: " + std::to_string(failed);
    WvInvoker::log(LOG_LV_INFO, log);
    return result;
}

PatcherResult DialogUITextPatcher::migration() {
    return { };
}

PatcherResult DialogUITextPatcher::generate_migration_info() {
    return { };
}

DialogUITextPatcher::DialogUITextPatcher(UIText* ut, const path_t& src) :
    IUITextPatcher(ut, src) { }
