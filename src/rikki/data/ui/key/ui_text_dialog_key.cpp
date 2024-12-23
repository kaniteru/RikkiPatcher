#include "ui_text_dialog_key.hpp"

const DialogType1UITextKey DialogUITextKeyMgr::delete_save_file {
    "asset/json/server/ui/sui1001.json",
    "42588917265_0.8154324523113876"
};

const DialogType2UITextKey DialogUITextKeyMgr::save_file_read_error {
    "asset/json/server/command/data/ws14007.json"
};

const DialogType2UITextKey DialogUITextKeyMgr::save_file_write_error {
    "asset/json/server/command/data/ws14009.json"
};

const DialogType2UITextKey DialogUITextKeyMgr::back_to_title_alert {
    "asset/json/server/command/data/ws15009.json"
};

const std::map<const char*, const DialogType1UITextKey&> DialogUITextKeyMgr::g_type1Keys = {
    { KEY_DELETE_SAVE_FILE, delete_save_file }
};

const std::map<const char*, const DialogType2UITextKey&> DialogUITextKeyMgr::g_type2Keys = {
    { KEY_SAVE_FILE_READ_ERROR, save_file_read_error },
    { KEY_SAVE_FILE_WRITE_ERROR, save_file_write_error },
    { KEY_BACK_TO_TITLE_ALERT, back_to_title_alert }
};
