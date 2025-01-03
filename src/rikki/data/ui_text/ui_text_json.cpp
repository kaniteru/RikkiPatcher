#include "ui_text_json.hpp"
#include "ui_text.hpp"
#include "key/ui_text_dialog_key.hpp"
#include "key/ui_text_setting_key.hpp"
#include "key/ui_text_in_game_key.hpp"

#define PAIR_AND_ADD_A(MAP, PKEY, VAL) MAP.emplace(PKEY, VAL);
#define PAIR_AND_ADD(PKEY, VAL) PAIR_AND_ADD_A(m_map, PKEY, VAL);

// ======================= S T R U C T =======================
// ===    InGameUIText
// ======================= S T R U C T =======================

std::map<const char*, std::string&> InGameUIText::get_map() {
    std::map<const char*, std::string&> result { };
    PAIR_AND_ADD_A(result, InGameUITextKeyMgr::KEY_PREVIOUS_DIALOGUE, previous_dialogue);
    PAIR_AND_ADD_A(result, InGameUITextKeyMgr::KEY_HIDE_INTERFACE, hide_interface);
    PAIR_AND_ADD_A(result, InGameUITextKeyMgr::KEY_AUTO_PLAY_DIALOGUE, auto_play_dialogue);
    PAIR_AND_ADD_A(result, InGameUITextKeyMgr::KEY_AUTO_SKIP_DIALOGUE, auto_skip_dialogue);
    PAIR_AND_ADD_A(result, InGameUITextKeyMgr::KEY_SAVE_GAME_PROGRESS, save_game_progress);
    PAIR_AND_ADD_A(result, InGameUITextKeyMgr::KEY_LOAD_GAME_PROGRESS, load_game_progress);
    PAIR_AND_ADD_A(result, InGameUITextKeyMgr::KEY_SETTINGS, settings);
    PAIR_AND_ADD_A(result, InGameUITextKeyMgr::KEY_RETURN_TO_TITLE, return_to_title);
    PAIR_AND_ADD_A(result, InGameUITextKeyMgr::KEY_ENTER_SAVE_FILE_NAME, enter_save_file_name);
    PAIR_AND_ADD_A(result, InGameUITextKeyMgr::KEY_ENTER_SAVE_FILE_NAME2, enter_save_file_name2);
    return result;
}

// ======================= S T R U C T =======================
// ===    DialogUIText
// ======================= S T R U C T =======================

DialogUIText::Dialog& DialogUIText::Dialog::operator=(const DialogUITextEntry& other) {
    system = other.m_system;
    text = other.m_text;
    return *this;
}

std::map<const char*, DialogUIText::Dialog&> DialogUIText::get_type1_map() {
    std::map<const char*, DialogUIText::Dialog&> result { };
    PAIR_AND_ADD_A(result, DialogUITextKeyMgr::KEY_DELETE_SAVE_FILE, delete_save_file);
    return result;
}

std::map<const char*, DialogUIText::Dialog&> DialogUIText::get_type2_map() {
    std::map<const char*, DialogUIText::Dialog&> result { };
    PAIR_AND_ADD_A(result, DialogUITextKeyMgr::KEY_BACK_TO_TITLE_ALERT, back_to_title_alert);
    PAIR_AND_ADD_A(result, DialogUITextKeyMgr::KEY_SAVE_FILE_READ_ERROR, save_file_read_error);
    PAIR_AND_ADD_A(result, DialogUITextKeyMgr::KEY_SAVE_FILE_WRITE_ERROR, save_file_write_error);
    return result;
}

std::vector<std::pair<uint8_t, std::map<const char*, DialogUIText::Dialog&>>> DialogUIText::get_maps() {
    std::vector<std::pair<uint8_t, std::map<const char*, DialogUIText::Dialog&>>> result { };
    result.emplace_back(1, this->get_type1_map());
    result.emplace_back(2, this->get_type2_map());
    return result;
}

// ======================= S T R U C T =======================
// ===    SettingUIText
// ======================= S T R U C T =======================

SettingUIText::FontStyle& SettingUIText::FontStyle::operator=(const SettingUITextEntry& rhs) {
    font  = rhs.m_font;
    color = rhs.m_color;
    size   = rhs.m_size;
    text  = rhs.m_text;
    return *this;
}

std::map<const char*, SettingUIText::FontStyle&> SettingUIText::get_map() {
    std::map<const char*, SettingUIText::FontStyle&> result { };
    PAIR_AND_ADD_A(result, SettingUITextKeyMgr::KEY_FULLSCREEN, fullscreen);
    PAIR_AND_ADD_A(result, SettingUITextKeyMgr::KEY_SKIP_SEEN_DIALOGUES, skip_seen_dialogues);
    PAIR_AND_ADD_A(result, SettingUITextKeyMgr::KEY_REVERSE_MOUSE_WHEEL, reverse_mouse_wheel);
    PAIR_AND_ADD_A(result, SettingUITextKeyMgr::KEY_BGM_VOLUME, bgm_volume);
    PAIR_AND_ADD_A(result, SettingUITextKeyMgr::KEY_SE_VOLUME, se_volume);
    PAIR_AND_ADD_A(result, SettingUITextKeyMgr::KEY_SFX_VOLUME, sfx_volume);
    PAIR_AND_ADD_A(result, SettingUITextKeyMgr::KEY_VOICE_VOLUME, voice_volume);
    PAIR_AND_ADD_A(result, SettingUITextKeyMgr::KEY_CONTROLS, controls);
    PAIR_AND_ADD_A(result, SettingUITextKeyMgr::KEY_DIALOGUE_UI_OPACITY, dialogue_ui_opacity);
    PAIR_AND_ADD_A(result, SettingUITextKeyMgr::KEY_DIALOGUE_UI_OPACITY_PREVIEW, dialogue_ui_opacity_preview);
    PAIR_AND_ADD_A(result, SettingUITextKeyMgr::KEY_TEXT_SPEED, text_speed);
    PAIR_AND_ADD_A(result, SettingUITextKeyMgr::KEY_AUTO_PLAY_DIALOGUE_SPEED, auto_play_dialogue_speed);
    PAIR_AND_ADD_A(result, SettingUITextKeyMgr::KEY_TEXT_SPEED_PREVIEW, text_speed_preview);
    return result;
}

std::map<const char*, SettingUIText::FontStyle&> SettingUIText::get_controls_usage_map() {
    std::map<const char*, SettingUIText::FontStyle&> result { };
    PAIR_AND_ADD_A(result, SettingUITextKeyMgr::KEY_CONTROLS_USAGE_TITLE, controls_usage.title);
    PAIR_AND_ADD_A(result, SettingUITextKeyMgr::KEY_CONTROLS_USAGE_LINE_1, controls_usage.line_1);
    PAIR_AND_ADD_A(result, SettingUITextKeyMgr::KEY_CONTROLS_USAGE_LINE_2, controls_usage.line_2);
    PAIR_AND_ADD_A(result, SettingUITextKeyMgr::KEY_CONTROLS_USAGE_LINE_3, controls_usage.line_3);
    PAIR_AND_ADD_A(result, SettingUITextKeyMgr::KEY_CONTROLS_USAGE_LINE_4, controls_usage.line_4);
    PAIR_AND_ADD_A(result, SettingUITextKeyMgr::KEY_CONTROLS_USAGE_LINE_5, controls_usage.line_5);
    PAIR_AND_ADD_A(result, SettingUITextKeyMgr::KEY_CONTROLS_USAGE_LINE_6, controls_usage.line_6);
    return result;
}
