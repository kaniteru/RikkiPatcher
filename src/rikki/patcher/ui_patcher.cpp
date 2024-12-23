#include "ui_patcher.hpp"
#include "rikki/dir_mgr.hpp"
#include "rikki/data/ui/ui.hpp"
#include "rikki/data/ui/ui_json.hpp"
#include "rikki/data/ui/key/ui_key.hpp"
#include "rikki/data/ui/key/ui_key_mgr.hpp"
#include "rikki/data/ui/key/ui_text_dialog_key.hpp"
#include "rikki/data/ui/key/ui_text_setting_key.hpp"
#include "rikki/data/ui/key/ui_text_in_game_key.hpp"
#include "rikki/stream/ui_patch_stream.hpp"

#include "utils/sevenzip_util.hpp"
#include "utils/instance_factory.hpp"

#include "wv/enums.hpp"
#include "wv/wv_invoker.hpp"

size_t UITextPatcher::patch() {
    const auto pDirMgr = InstanceFactory::instance().get<DirMgr>();
    const auto& fGm = pDirMgr->get(DIR_GAME_JSON_STARTUP);
    const auto& fSvzip = pDirMgr->get(DIR_PROJ_EXE_7ZIP);

    const auto& fTemp = pDirMgr->get(DIR_PROJ_TEMP);
    const auto fPatch = path_t(fTemp).append("startup.json");
    const auto fPatchZip = path_t(fTemp).append("startup.zip");

    size_t total = 0;
    size_t failed = 0;
    size_t passed = 0;
    size_t ok = 0;

    SevenzipUtil svzip(fSvzip);
    static constexpr auto PW = u8"gc_zip";

    std::filesystem::remove_all(fTemp);
    std::filesystem::create_directories(fTemp);

    // copy the game file to temp dir
    if (!std::filesystem::copy_file(fGm, fPatchZip, std::filesystem::copy_options::overwrite_existing)) {
        return ok;
    }

    // decrypt the game file
    if (!svzip.unzip(fPatchZip, fTemp, true, PW)) {
        return ok;
    }

    // do patch

    auto find_file = [this](auto f) {
        auto fCustom = m_db.append(f);
        return std::filesystem::exists(fCustom);
    };

    UIText ut(fPatch);

    // in-game text patch
    if (find_file(UITextPatchStream::FILE_IN_GAME)) {
        const UITextPatchStream patchStream(UITextPatchStream::FILE_IN_GAME);
        const auto patchData = patchStream.get_texts<InGameUIText>();

        for (const auto& [pKey, val] : patchData.m_map) {
            total++;

            if (const auto it = InGameUITextKeyMgr::g_keys.find(pKey); it != InGameUITextKeyMgr::g_keys.end()) {
                ut.set_in_game(it->second, val);
                ok++;
            }
            else {
                failed++;
            }
        }
    }
    else {
        // logging pass
    }

    {
        static auto fs_to_entry = [](const SettingUIText::FontStyle& fs) {
            SettingUITextEntry result { };
            result.m_font = fs.font;
            result.m_color = fs.color;
            result.m_size = fs.size;
            result.m_text = fs.text;
            return result;
        };

        uint8_t patchPassed = 0;
        const UITextPatchStream patchStream(UITextPatchStream::FILE_SETTING);
        const auto patchData = patchStream.get_texts<SettingUIText>();

        // setting text patch
        if (find_file(UITextPatchStream::FILE_SETTING)) {
            for (const auto& [pKey, val] : patchData.m_map) {
                total++;

                if (const auto it = SettingUITextKeyMgr::g_keys.find(pKey); it != SettingUITextKeyMgr::g_keys.end()) {
                    const auto buf = fs_to_entry(val);
                    ut.set_setting(it->second, buf);
                    ok++;
                }
                else {
                    failed++;
                }
            }
        }
        else {
            patchPassed++;
        }

        // setting controls-usage text patch
        if (find_file(UITextPatchStream::FILE_SETTING)) {
            for (const auto& [pKey, val] : patchData.m_ControlsUsageMap) {
                total++;

                if (const auto it = SettingUITextKeyMgr::g_keys.find(pKey); it != SettingUITextKeyMgr::g_keys.end()) {
                    const auto buf = fs_to_entry(val);
                    ut.set_setting(it->second, buf);
                    ok++;
                }
                else {
                    failed++;
                }
            }
        }
        else {
            patchPassed++;
        }

        if (patchPassed > 1) {
            passed++;
            // todo: logging pass
        }
    }

    {
        static auto d_to_entry = [](const DialogUIText::Dialog& d) {
            DialogUITextEntry result { };
            result.m_system = d.system;
            result.m_text = d.text;
            return result;
        };

        uint8_t patchPassed = 0;
        const UITextPatchStream patchStream(UITextPatchStream::FILE_DIALOG);
        const auto data = patchStream.get_texts<DialogUIText>();

        // dialog type1 text patch
        if (find_file(UITextPatchStream::FILE_DIALOG)) {
            for (const auto& [pKey, val] : data.m_type1Map) {
                total++;

                if (const auto it = DialogUITextKeyMgr::g_type1Keys.find(pKey); it != DialogUITextKeyMgr::g_type1Keys.end()) {
                    const auto buf = d_to_entry(val);
                    ut.set_dialog_type1(it->second, buf);
                    ok++;
                }
                else {
                    failed++;
                }
            }
        }
        else {
            patchPassed++;
        }

        // dialog type2 text patch
        if (find_file(UITextPatchStream::FILE_DIALOG)) {
            for (const auto& [pKey, val] : data.m_type2Map) {
                total++;

                if (const auto it = DialogUITextKeyMgr::g_type2Keys.find(pKey); it != DialogUITextKeyMgr::g_type2Keys.end()) {
                    const auto buf = d_to_entry(val);
                    ut.set_dialog_type2(it->second, buf);
                    ok++;
                }
                else {
                    failed++;
                }
            }
        }
        else {
            patchPassed++;
        }

        if (patchPassed > 1) {
            passed++;
            // todo: logging pass
        }
    }


    // end patch

    if (!svzip.zip({ fPatch }, fPatchZip, true, PW)) {
        return 0;
    }

    // can't copy patch file into gmdir
    if (!std::filesystem::copy_file(fPatchZip, fGm, std::filesystem::copy_options::overwrite_existing)) {
        return 0;
    }

    std::filesystem::remove_all(fTemp);
    return ok;
}

bool UITextPatcher::migration() {
    return true;
}

bool UITextPatcher::generate_migration_info() {
    return true;
}

UITextPatcher::UITextPatcher(const path_t& src) :
    IPatcher(src) {

    m_db = path_t(src).append(FOLDER_BASE);
    std::filesystem::create_directories(m_db);

    m_migrDB = path_t(src).append(FOLDER_MIGRATE).append(FOLDER_BASE);
    std::filesystem::create_directories(m_migrDB);

    m_isAvailable = true;
}
