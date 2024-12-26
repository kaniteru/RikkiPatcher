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

#include "ui/ui_text_patcher.hpp"

#include "utils/string_util.hpp"
#include "utils/ui_text_util.hpp"

#include "wv/enums.hpp"
#include "wv/wv_invoker.hpp"

PatcherResult UITextPatcher::patch() {
    PatcherResult result { };
    size_t& total   =  result.m_total;
    size_t& ok       = result.m_ok;
    size_t& failed  = result.m_failed;
    size_t& passed = result.m_passed;

    /*
     * 1. copy game file to temp dir.
     * 2. extract(decrypt) the game file.
     * 3. do patch
     * 4. zip(encrypt) the patched game file.
     * 5. copy patched game file to game dir.
     */
    path_t fPatch { };

    // copy a game file to temp dir
    if (!UITextUtil::copy_startup_from_game_and_decrypt(fPatch)) {
        WvInvoker::log(LOG_LV_ERR, u8"Can't copied the game file from game directory");
        return { };
    }

    // load a game file from temp dir
    UIText ut(fPatch);

    if (!ut.is_valid()) {
        WvInvoker::log(LOG_LV_ERR, u8"Can't read the game file");
        return { };
    }

/*----------------------------------- PATCH START -----------------------------------*/
    {
        auto find_file = [this](auto f) {
            const auto fCustom = path_t(m_db).append(f);
            return std::filesystem::exists(fCustom);
        };

        // in-game text patch
        if (find_file(UITextPatchStream::FILE_IN_GAME)) {
            WvInvoker::log(LOG_LV_ALERT, u8"Start patch the in-game text");

            InGameUITextPatcher patcher(ut, m_dir);
            auto res = patcher.patch();

            WvInvoker::log(LOG_LV_ALERT, u8"In-game text patch finished");
            result += res;
        }
        else {
            // custom patch file not found
        }

        // setting text patch
        if (find_file(UITextPatchStream::FILE_SETTING)) {
            WvInvoker::log(LOG_LV_ALERT, u8"Start patch the setting text");

            SettingUITextPatcher patcher(ut, m_dir);
            result += patcher.patch();

            WvInvoker::log(LOG_LV_ALERT, u8"Setting text patch finished");
        }
        else {
            // custom patch file not found
        }

        // dialog text patch
        if (find_file(UITextPatchStream::FILE_DIALOG)) {
            WvInvoker::log(LOG_LV_ALERT, u8"Start patch the dialog text");

            DialogUITextPatcher patcher(ut, m_dir);
            result += patcher.patch();

            WvInvoker::log(LOG_LV_ALERT, u8"Dialog text patch finished");
        }
        else {
            // custom patch file not found
        }
    }
/*------------------------------------ PATCH END ------------------------------------*/

    // save patched game file into temp dir
    if (!ut.save()) {
        WvInvoker::log(LOG_LV_ERR, u8"Can't save the patched game file");
        return { };
    }

    // copy a patched game file in temp dir to game dir
    if (!UITextUtil::encrypt_startup_and_move_to_game()) {
        WvInvoker::log(LOG_LV_ERR, u8"Can't copied the patched game file to game directory");
        return { };
    }

    std::string log = "Total: " + std::to_string(total) + " | ok: " + std::to_string(ok) + " | passed: " + std::to_string(passed)
                            + " | failed: " + std::to_string(failed);
    WvInvoker::log(LOG_LV_INFO, log);
    return result;
}

PatcherResult UITextPatcher::migration() {
    return { };
}

PatcherResult UITextPatcher::generate_migration_info() {
    return { };
}

UITextPatcher::UITextPatcher(const path_t& src) :
    IPatcher(src) {

    m_db = path_t(src) / UITextPatchStream::FOLDER_BASE;
    std::filesystem::create_directories(m_db);

    m_migrDB = path_t(src).append(FOLDER_MIGRATE) / UITextPatchStream::FOLDER_BASE;
    std::filesystem::create_directories(m_migrDB);

    m_isAvailable = true;
}
