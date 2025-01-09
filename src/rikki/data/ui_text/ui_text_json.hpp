#ifndef RIKKI_PATCHER_RIKKI_DATA_UI_TEXT_UI_TEXT_JSON_HPP
#define RIKKI_PATCHER_RIKKI_DATA_UI_TEXT_UI_TEXT_JSON_HPP
#include "precompiled.hpp"
#include "utils/json_util.hpp"

/* ui_text_json.hpp
 *  Included structs:
 *      - InGameUIText
 *      - DialogUIText
 *      - DialogUIText::Dialog
 *      - SettingUIText
 *      - MsgBoxText
 *      - SettingUIText::ControlsUsage
 *      - TitleUIText
 *      - TitleUIText::UnlockedSelectChapterMsgbox
 */

namespace j {

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
// ===    MsgBoxText
// ======================= S T R U C T =======================

struct MsgBoxText {
    std::string font;
    std::string color;
    int32_t size;
    int32_t x;
    int32_t y;
    int32_t width;
    bool show;
    std::string text;

    ORDERED_NLOHMANN_DEFINE_TYPE_INTRUSIVE(MsgBoxText,
    font,
    color,
    size,
    x,
    y,
    width,
    show,
    text);

    bool operator==(const MsgBoxText&) const;
    void into_json_array(nlohmann::basic_json<>& j);

    static MsgBoxText from_json_array(const nlohmann::basic_json<>& j);
};

// ======================= S T R U C T =======================
// ===    SettingUIText
// ===    SettingUIText::ControlsUsage
// ======================= S T R U C T =======================

struct SettingUIText {
    struct ControlsUsage {
        MsgBoxText title;
        MsgBoxText line_1;
        MsgBoxText line_2;
        MsgBoxText line_3;
        MsgBoxText line_4;
        MsgBoxText line_5;
        MsgBoxText line_6; // todo: check using array is available

        ORDERED_NLOHMANN_DEFINE_TYPE_INTRUSIVE(ControlsUsage,
            title,
            line_1,
            line_2,
            line_3,
            line_4,
            line_5,
            line_6);
    };

    MsgBoxText fullscreen;
    MsgBoxText skip_seen_dialogues;
    MsgBoxText reverse_mouse_wheel;
    MsgBoxText bgm_volume;
    MsgBoxText se_volume;
    MsgBoxText sfx_volume;
    MsgBoxText voice_volume;
    MsgBoxText controls;
    MsgBoxText dialogue_ui_opacity;
    MsgBoxText dialogue_ui_opacity_preview;
    MsgBoxText text_speed;
    MsgBoxText auto_play_dialogue_speed;
    MsgBoxText text_speed_preview;
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

    std::map<const char*, MsgBoxText&> get_map();
    std::map<const char*, MsgBoxText&> get_controls_usage_map();
};

// ======================= S T R U C T =======================
// ===    TitleUIText
// ===    TitleUIText::UnlockedSelectChapterMsgbox
// ======================= S T R U C T =======================

struct TitleUIText {
    struct UnlockedSelectChapterMsgbox {
        MsgBoxText title;
        MsgBoxText line_1;
        MsgBoxText line_2;

        ORDERED_NLOHMANN_DEFINE_TYPE_INTRUSIVE(UnlockedSelectChapterMsgbox,
            title,
            line_1,
            line_2);
    };

    UnlockedSelectChapterMsgbox unlocked_select_chapter_msgbox;

    ORDERED_NLOHMANN_DEFINE_TYPE_INTRUSIVE(TitleUIText,
        unlocked_select_chapter_msgbox);

    std::map<const char*, MsgBoxText&> get_map();
};
}


#endif //RIKKI_PATCHER_RIKKI_DATA_UI_TEXT_UI_TEXT_JSON_HPP
