#ifndef RIKKI_PATCHER_RIKKI_DATA_UI_JSON_HPP
#define RIKKI_PATCHER_RIKKI_DATA_UI_JSON_HPP
#include "precompiled.hpp"

struct IUI { };

struct InGameUIText : IUI {
    std::string previous_dialogue;
    std::string hide_interface;
    std::string auto_play_dialogue;
    std::string auto_skip_dialogue;
    std::string save_game_progress;
    std::string load_game_progress;
    std::string settings;
    std::string return_to_title;
    std::string enter_save_file_name;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(InGameUIText,
        previous_dialogue,
        hide_interface,
        auto_play_dialogue,
        auto_skip_dialogue,
        save_game_progress,
        load_game_progress,
        settings,
        return_to_title,
        enter_save_file_name);
};

struct DialogUIText : IUI {
    std::string system;
    std::string delete_save_file;
    std::string back_to_title_alert;
    std::string save_file_read_error;
    std::string save_file_write_error;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(DialogUIText,
        system,
        delete_save_file,
        back_to_title_alert,
        save_file_read_error,
        save_file_write_error);
};

struct SettingUIText : IUI {
    struct FontStyle {
        std::string font;
        std::string color;
        int32_t size;
        std::string text;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(FontStyle,
            font,
            color,
            size,
            text);
    };

    struct ControlsUsage {
        SettingUIText::FontStyle title;
        SettingUIText::FontStyle line_1;
        SettingUIText::FontStyle line_2;
        SettingUIText::FontStyle line_3;
        SettingUIText::FontStyle line_4;
        SettingUIText::FontStyle line_5;
        SettingUIText::FontStyle line_6; // todo: check using array is available

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(ControlsUsage,
            title,
            line_1,
            line_2,
            line_3,
            line_4,
            line_5,
            line_6);
    };

    std::string fullscreen;
    std::string skip_seen_dialogues;
    std::string reverse_mouse_wheel;
    std::string bgm_volume;
    std::string se_volume;
    std::string sfx_volume;
    std::string voice_volume;
    std::string controls;
    std::string dialogue_ui_opacity;
    std::string dialogue_ui_opacity_preview;
    std::string text_speed;
    std::string auto_play_dialogue_speed;
    std::string text_speed_preview;
    SettingUIText::ControlsUsage controls_usage;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(SettingUIText,
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
};


#endif //RIKKI_PATCHER_RIKKI_DATA_UI_JSON_HPP
