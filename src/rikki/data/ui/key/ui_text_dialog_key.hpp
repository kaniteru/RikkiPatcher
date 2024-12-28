#ifndef RIKKI_PATCHER_RIKKI_DATA_UI_KEY_UI_TEXT_DIALOG_KEY_HPP
#define RIKKI_PATCHER_RIKKI_DATA_UI_KEY_UI_TEXT_DIALOG_KEY_HPP
#include "precompiled.hpp"
#include "ui_key.hpp"

/* ui_text_dialog_key.hpp
 *  Included structs:
 *      - DialogUITextKeyMgr
 */

// ======================= S T R U C T =======================
// ===    DialogUITextKeyMgr
// ======================= S T R U C T =======================

struct DialogUITextKeyMgr {
    static const DialogType1UITextKey delete_save_file;
    static const DialogType2UITextKey save_file_read_error;
    static const DialogType2UITextKey save_file_write_error;
    static const DialogType2UITextKey back_to_title_alert;

    static constexpr auto KEY_DELETE_SAVE_FILE = "delete_save_file";
    static constexpr auto KEY_SAVE_FILE_READ_ERROR = "save_file_read_error";
    static constexpr auto KEY_SAVE_FILE_WRITE_ERROR = "save_file_write_error";
    static constexpr auto KEY_BACK_TO_TITLE_ALERT = "back_to_title_alert";

    static constexpr auto KEY_SYSTEM = "system";
    static constexpr auto KEY_TEXT = "text";


    static const std::map<const char*, const DialogType1UITextKey&> g_type1Keys;
    static const std::map<const char*, const DialogType2UITextKey&> g_type2Keys;
    static constexpr std::array<std::pair<const char*, const DialogType1UITextKey*>, 1> g_type1Arr {
        std::make_pair(KEY_DELETE_SAVE_FILE, &delete_save_file)
    };
    static constexpr std::array<std::pair<const char*, const DialogType2UITextKey*>, 3> g_type2Arr {
        std::make_pair(KEY_SAVE_FILE_READ_ERROR, &save_file_read_error),
        std::make_pair(KEY_SAVE_FILE_WRITE_ERROR, &save_file_write_error),
        std::make_pair(KEY_BACK_TO_TITLE_ALERT, &back_to_title_alert)
    };
};


#endif //RIKKI_PATCHER_RIKKI_DATA_UI_KEY_UI_TEXT_DIALOG_KEY_HPP
