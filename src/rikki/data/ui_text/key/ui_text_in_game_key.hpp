#ifndef RIKKI_PATCHER_RIKKI_DATA_UI_KEY_UI_TEXT_IN_GAME_KEY_HPP
#define RIKKI_PATCHER_RIKKI_DATA_UI_KEY_UI_TEXT_IN_GAME_KEY_HPP
#include "precompiled.hpp"
#include "ui_text_key.hpp"

/* ui_text_in_game_key.hpp
 *  Included structs:
 *      - InGameUITextKeyMgr
 */

// ======================= S T R U C T =======================
// ===    InGameUITextKeyMgr
// ======================= S T R U C T =======================

struct InGameUITextKeyMgr {
    static const InGameUITextKey previous_dialogue;
    static const InGameUITextKey hide_interface;
    static const InGameUITextKey auto_play_dialogue;
    static const InGameUITextKey auto_skip_dialogue;
    static const InGameUITextKey save_game_progress;
    static const InGameUITextKey load_game_progress;
    static const InGameUITextKey settings;
    static const InGameUITextKey return_to_title;
    static const InGameUITextKey enter_save_file_name;
    static const InGameUITextKey enter_save_file_name2;

    static constexpr auto KEY_PREVIOUS_DIALOGUE = "previous_dialogue";
    static constexpr auto KEY_HIDE_INTERFACE = "hide_interface";
    static constexpr auto KEY_AUTO_PLAY_DIALOGUE = "auto_play_dialogue";
    static constexpr auto KEY_AUTO_SKIP_DIALOGUE = "auto_skip_dialogue";
    static constexpr auto KEY_SAVE_GAME_PROGRESS = "save_game_progress";
    static constexpr auto KEY_LOAD_GAME_PROGRESS = "load_game_progress";
    static constexpr auto KEY_SETTINGS = "settings";
    static constexpr auto KEY_RETURN_TO_TITLE = "return_to_title";
    static constexpr auto KEY_ENTER_SAVE_FILE_NAME = "enter_save_file_name";
    static constexpr auto KEY_ENTER_SAVE_FILE_NAME2 = "enter_save_file_name2";

    static const std::map<const char*, const InGameUITextKey&> g_keys;
    static constexpr std::array<std::pair<const char*, const InGameUITextKey*>, 10> g_arr {
        std::make_pair(KEY_PREVIOUS_DIALOGUE, &previous_dialogue),
        std::make_pair(KEY_HIDE_INTERFACE, &hide_interface),
        std::make_pair(KEY_AUTO_PLAY_DIALOGUE, &auto_play_dialogue),
        std::make_pair(KEY_AUTO_SKIP_DIALOGUE, &auto_skip_dialogue),
        std::make_pair(KEY_SAVE_GAME_PROGRESS, &save_game_progress),
        std::make_pair(KEY_LOAD_GAME_PROGRESS, &load_game_progress),
        std::make_pair(KEY_SETTINGS, &settings),
        std::make_pair(KEY_RETURN_TO_TITLE, &return_to_title),
        std::make_pair(KEY_ENTER_SAVE_FILE_NAME, &enter_save_file_name),
        std::make_pair(KEY_ENTER_SAVE_FILE_NAME2, &enter_save_file_name2)
    };
};


#endif //RIKKI_PATCHER_RIKKI_DATA_UI_KEY_UI_TEXT_IN_GAME_KEY_HPP
