#include "ui_text_patcher.hpp"
#include "rikki/dir_mgr.hpp"
#include "rikki/data/ui/ui.hpp"
#include "rikki/data/ui/ui_json.hpp"
#include "rikki/data/ui/key/ui_key.hpp"
#include "rikki/data/ui/key/ui_key_mgr.hpp"
#include "rikki/data/ui/key/ui_text_dialog_key.hpp"
#include "rikki/data/ui/key/ui_text_setting_key.hpp"
#include "rikki/data/ui/key/ui_text_in_game_key.hpp"
#include "rikki/stream/ui_patch_stream.hpp"

#include "utils/string_util.hpp"
#include "utils/ui_text_util.hpp"

#include "wv/enums.hpp"
#include "wv/wv_invoker.hpp"

// ======================== C L A S S ========================
// ===    IUITextPatcher
// ======================== C L A S S ========================

IUITextPatcher::IUITextPatcher(class UIText& ut, const path_t& src) :
    IPatcher(src),
    m_ut(ut),
    m_base(path_t(src).append(UITextPatchStream::FOLDER_BASE)),
    m_baseMigr(path_t(m_migrDir).append(UITextPatchStream::FOLDER_BASE)) { }

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
    const auto patchData = patchStream.get_texts<InGameUIText>();

    for (const auto& [pKey, val] : patchData.m_map) {
        total++;
        std::u8string log = StringUtil::cstr_to_u8(pKey) + u8"=>";

        if (const auto it = InGameUITextKeyMgr::g_keys.find(pKey); it != InGameUITextKeyMgr::g_keys.end()) {
            m_ut.set_in_game(it->second, val);
            ok++;
            log += u8"OK";
        }
        else {
            failed++;
            log += u8"Failed";
        }

        WvInvoker::log(LOG_LV_PROG, log);
    }
}

PatcherResult InGameUITextPatcher::migration() {
    return { };
}

PatcherResult InGameUITextPatcher::generate_migration_info() {
    return { };
}

InGameUITextPatcher::InGameUITextPatcher(class UIText& ut, const path_t& src) :
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
    const auto patchData = patchStream.get_texts<SettingUIText>();

    auto loop_map = [this, &total, &ok, &failed](auto& m) {
        for (const auto& [pKey, val] : m) {
            total++;
            std::u8string log = StringUtil::cstr_to_u8(pKey) + u8"=>";

            if (const auto it = SettingUITextKeyMgr::g_keys.find(pKey); it != SettingUITextKeyMgr::g_keys.end()) {
                const SettingUITextEntry buf = val;
                m_ut.set_setting(it->second, buf);
                ok++;
                log += u8"OK";
            }
            else {
                failed++;
                log += u8"Failed";
            }

            WvInvoker::log(LOG_LV_PROG, log);
        }
    };

    loop_map(patchData.m_map);
    loop_map(patchData.m_ControlsUsageMap);
    return result;
}

PatcherResult SettingUITextPatcher::migration() {
    return { };
}

PatcherResult SettingUITextPatcher::generate_migration_info() {
    return { };
}

SettingUITextPatcher::SettingUITextPatcher(class UIText& ut, const path_t& src) :
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
    const auto patchData = patchStream.get_texts<DialogUIText>();

    static auto d_to_entry = [](const DialogUIText::Dialog& d) {
        DialogUITextEntry res { };
        res.m_system = d.system;
        res.m_text = d.text;
        return res;
    };

    auto loop_map = [this, &total, &ok, &failed]<typename T2>(auto& m1, auto m2, auto typeNum) {
        for (const auto& [pKey, val] : m1) {
            total++;
            std::u8string log = StringUtil::cstr_to_u8(pKey) + u8"=>";

            const std::map<const char*, const T2&>* map = m2;

            if (const auto it = map->find(pKey); it != map->end()) {
                const auto buf = d_to_entry(val);

                switch (typeNum) { // todo: fix here
                case 1 : {
                    m_ut.set_dialog_type1(it->second, buf);
                    break;
                }
                case 2 : {
                    m_ut.set_dialog_type2(it->second, buf);
                    break;
                }
                default:
                    throw std::runtime_error("Unknown type numeric");
                }

                ok++;
                log += u8"OK";
            }
            else {
                failed++;
                log += u8"Failed";
            }

            WvInvoker::log(LOG_LV_PROG, log);
        }
    };

    loop_map.template operator()<DialogType1UITextKey>(patchData.m_type1Map, &DialogUITextKeyMgr::g_type1Keys, 1);
    loop_map.template operator()<DialogType2UITextKey>(patchData.m_type2Map, &DialogUITextKeyMgr::g_type2Keys, 2);
    return result;
}

PatcherResult DialogUITextPatcher::migration() {
    return { };
}

PatcherResult DialogUITextPatcher::generate_migration_info() {
    return { };
}

DialogUITextPatcher::DialogUITextPatcher(class UIText& ut, const path_t& src) :
    IUITextPatcher(ut, src) { }
