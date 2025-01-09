#include "ui_text_json.hpp"
#include "ui_text.hpp"
#include "key/ui_text_dialog_key.hpp"
#include "key/ui_text_setting_key.hpp"
#include "key/ui_text_msg_box_text.hpp"
#include "key/ui_text_in_game_key.hpp"
#include "key/ui_text_title_key.hpp"

#define PAIR_AND_ADD_A(MAP, PKEY, VAL) MAP.emplace(PKEY, VAL);
#define PAIR_AND_ADD(PKEY, VAL) PAIR_AND_ADD_A(m_map, PKEY, VAL);

namespace j {

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
// ===    MsgBoxText
// ======================= S T R U C T =======================

bool MsgBoxText::operator==(const MsgBoxText& rhs) const {
    return font == rhs.font && color == rhs.color && size == rhs.size && x == rhs.x && y == rhs.y && width == rhs.width
        && show == rhs.show && text == rhs.text;
}

void MsgBoxText::into_json_array(nlohmann::basic_json<>& j) {
    j[MsgBoxUITextKey::KEY_FONT] = font;
    j[MsgBoxUITextKey::KEY_COLOR] = color;
    j[MsgBoxUITextKey::KEY_FONT_SIZE] = size;
    j[MsgBoxUITextKey::KEY_X] = x;
    j[MsgBoxUITextKey::KEY_Y] = y;
    j[MsgBoxUITextKey::KEY_WIDTH] = width;
    j[MsgBoxUITextKey::KEY_SHOW] = show;
    j[MsgBoxUITextKey::KEY_TEXT] = text;
}

MsgBoxText MsgBoxText::from_json_array(const nlohmann::basic_json<>& j) {
    MsgBoxText result { };
    result.font = j[MsgBoxUITextKey::KEY_FONT];
    result.color = j[MsgBoxUITextKey::KEY_COLOR];
    result.size = j[MsgBoxUITextKey::KEY_FONT_SIZE];
    result.x = j[MsgBoxUITextKey::KEY_X];
    result.y = j[MsgBoxUITextKey::KEY_Y];
    result.width = j[MsgBoxUITextKey::KEY_WIDTH];
    result.show = j[MsgBoxUITextKey::KEY_SHOW];
    result.text = j[MsgBoxUITextKey::KEY_TEXT];
    return result;
}

// ======================= S T R U C T =======================
// ===    SettingUIText
// ======================= S T R U C T =======================

std::map<const char*, MsgBoxText&> SettingUIText::get_map() {
    std::map<const char*, MsgBoxText&> result { };
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

std::map<const char*, MsgBoxText&> SettingUIText::get_controls_usage_map() {
    std::map<const char*, MsgBoxText&> result { };
    PAIR_AND_ADD_A(result, SettingUITextKeyMgr::KEY_CONTROLS_USAGE_TITLE, controls_usage.title);
    PAIR_AND_ADD_A(result, SettingUITextKeyMgr::KEY_CONTROLS_USAGE_LINE_1, controls_usage.line_1);
    PAIR_AND_ADD_A(result, SettingUITextKeyMgr::KEY_CONTROLS_USAGE_LINE_2, controls_usage.line_2);
    PAIR_AND_ADD_A(result, SettingUITextKeyMgr::KEY_CONTROLS_USAGE_LINE_3, controls_usage.line_3);
    PAIR_AND_ADD_A(result, SettingUITextKeyMgr::KEY_CONTROLS_USAGE_LINE_4, controls_usage.line_4);
    PAIR_AND_ADD_A(result, SettingUITextKeyMgr::KEY_CONTROLS_USAGE_LINE_5, controls_usage.line_5);
    PAIR_AND_ADD_A(result, SettingUITextKeyMgr::KEY_CONTROLS_USAGE_LINE_6, controls_usage.line_6);
    return result;
}

// ======================= S T R U C T =======================
// ===    TitleUIText
// ======================= S T R U C T =======================

std::map<const char*, MsgBoxText&> TitleUIText::get_map() {
    std::map<const char*, MsgBoxText&> result { };
    PAIR_AND_ADD_A(result, TitleUITextKeyMgr::KEY_UNLOCKED_SELECT_CHAPTER_MSGBOX_TITLE, unlocked_select_chapter_msgbox.title);
    PAIR_AND_ADD_A(result, TitleUITextKeyMgr::KEY_UNLOCKED_SELECT_CHAPTER_MSGBOX_LINE1, unlocked_select_chapter_msgbox.line_1);
    PAIR_AND_ADD_A(result, TitleUITextKeyMgr::KEY_UNLOCKED_SELECT_CHAPTER_MSGBOX_LINE2, unlocked_select_chapter_msgbox.line_2);
    return result;
}
}
