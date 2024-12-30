#ifndef RIKKI_PATCHER_RIKKI_DATA_UI_JSON_HPP
#define RIKKI_PATCHER_RIKKI_DATA_UI_JSON_HPP
#include "precompiled.hpp"
#include "utils/json_util.hpp"

/* ui_json.hpp
 *  Included structs:
 *      - InGameUIText
 *      - DialogUIText
 *      - DialogUIText::Dialog
 *      - SettingUIText
 *      - SettingUIText::FontStyle
 *      - SettingUIText::ControlsUsage
 */

// ======================= S T R U C T =======================
// ===    InGameUIText
// ======================= S T R U C T =======================

struct InGameUIText {
    std::string previous_dialogue;
    std::string hide_interface;
    std::string auto_play_dialogue;
    std::string auto_skip_dialogue;
    std::string save_game_progress;
    std::string load_game_progress;
    std::string settings;
    std::string return_to_title;
    std::string enter_save_file_name;
    std::string enter_save_file_name2;

    ORDERED_NLOHMANN_DEFINE_TYPE_INTRUSIVE(InGameUIText,
        previous_dialogue,
        hide_interface,
        auto_play_dialogue,
        auto_skip_dialogue,
        save_game_progress,
        load_game_progress,
        settings,
        return_to_title,
        enter_save_file_name,
        enter_save_file_name2);

    std::map<const char*, std::string&> get_map();
};

// ======================= S T R U C T =======================
// ===    DialogUIText
// ===    DialogUIText::Dialog
// ======================= S T R U C T =======================

struct DialogUIText {
    struct Dialog {
        std::string system;
        std::string text;

        ORDERED_NLOHMANN_DEFINE_TYPE_INTRUSIVE(Dialog,
            system,
            text);

        Dialog& operator=(const struct DialogUITextEntry&);
    };

    DialogUIText::Dialog delete_save_file;
    DialogUIText::Dialog back_to_title_alert;
    DialogUIText::Dialog save_file_read_error;
    DialogUIText::Dialog save_file_write_error;

    ORDERED_NLOHMANN_DEFINE_TYPE_INTRUSIVE(DialogUIText,
        delete_save_file,
        back_to_title_alert,
        save_file_read_error,
        save_file_write_error);

    std::map<const char*, DialogUIText::Dialog&> get_type1_map();
    std::map<const char*, DialogUIText::Dialog&> get_type2_map();
    std::vector<std::pair<uint8_t, std::map<const char*, DialogUIText::Dialog&>>> get_maps(); // type num | map
};

// ======================= S T R U C T =======================
// ===    SettingUIText
// ===    SettingUIText::FontStyle
// ===    SettingUIText::ControlsUsage
// ======================= S T R U C T =======================

struct SettingUIText {
    struct FontStyle {
        std::string font;
        std::string color;
        int32_t size;
        std::string text;

        ORDERED_NLOHMANN_DEFINE_TYPE_INTRUSIVE(FontStyle,
            font,
            color,
            size,
            text);

        FontStyle& operator=(const struct SettingUITextEntry&);
    };

    struct ControlsUsage {
        SettingUIText::FontStyle title;
        SettingUIText::FontStyle line_1;
        SettingUIText::FontStyle line_2;
        SettingUIText::FontStyle line_3;
        SettingUIText::FontStyle line_4;
        SettingUIText::FontStyle line_5;
        SettingUIText::FontStyle line_6; // todo: check using array is available

        ORDERED_NLOHMANN_DEFINE_TYPE_INTRUSIVE(ControlsUsage,
            title,
            line_1,
            line_2,
            line_3,
            line_4,
            line_5,
            line_6);
    };

    SettingUIText::FontStyle fullscreen;
    SettingUIText::FontStyle skip_seen_dialogues;
    SettingUIText::FontStyle reverse_mouse_wheel;
    SettingUIText::FontStyle bgm_volume;
    SettingUIText::FontStyle se_volume;
    SettingUIText::FontStyle sfx_volume;
    SettingUIText::FontStyle voice_volume;
    SettingUIText::FontStyle controls;
    SettingUIText::FontStyle dialogue_ui_opacity;
    SettingUIText::FontStyle dialogue_ui_opacity_preview;
    SettingUIText::FontStyle text_speed;
    SettingUIText::FontStyle auto_play_dialogue_speed;
    SettingUIText::FontStyle text_speed_preview;
    SettingUIText::ControlsUsage controls_usage;

    ORDERED_NLOHMANN_DEFINE_TYPE_INTRUSIVE(SettingUIText,
        fullscreen,
        skip_seen_dialogues,
        reverse_mouse_wheel,
        bgm_volume,
        se_volume,
        sfx_volume,
        voice_volume,
        controls,
        dialogue_ui_opacity,
        dialogue_ui_opacity_preview,
        text_speed,
        auto_play_dialogue_speed,
        text_speed_preview,
        controls_usage);

    std::map<const char*, SettingUIText::FontStyle&> get_map();
    std::map<const char*, SettingUIText::FontStyle&> get_controls_usage_map();
};


#endif //RIKKI_PATCHER_RIKKI_DATA_UI_JSON_HPP
