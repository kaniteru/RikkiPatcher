#ifndef RIKKI_PATCHER_RIKKI_DATA_UI_KEY_UI_TEXT_SETTING_KEY_HPP
#define RIKKI_PATCHER_RIKKI_DATA_UI_KEY_UI_TEXT_SETTING_KEY_HPP
#include "precompiled.hpp"
#include "ui_key.hpp"

// ======================= S T R U C T =======================
// ===    SettingUITextKeyMgr
// ======================= S T R U C T =======================

struct SettingUITextKeyMgr {
    static const SettingUITextKey fullscreen;
    static const SettingUITextKey skip_seen_dialogues;
    static const SettingUITextKey reverse_mouse_wheel;
    static const SettingUITextKey bgm_volume;
    static const SettingUITextKey se_volume;
    static const SettingUITextKey sfx_volume;
    static const SettingUITextKey voice_volume;
    static const SettingUITextKey controls;
    static const SettingUITextKey dialogue_ui_opacity;
    static const SettingUITextKey dialogue_ui_opacity_preview;
    static const SettingUITextKey text_speed;
    static const SettingUITextKey auto_play_dialogue_speed;
    static const SettingUITextKey text_speed_preview;
    static const SettingUITextKey controls_usage_title;
    static const SettingUITextKey controls_usage_line_1;
    static const SettingUITextKey controls_usage_line_2;
    static const SettingUITextKey controls_usage_line_3;
    static const SettingUITextKey controls_usage_line_4;
    static const SettingUITextKey controls_usage_line_5;
    static const SettingUITextKey controls_usage_line_6;

    static constexpr auto KEY_FULLSCREEN = "fullscreen";
    static constexpr auto KEY_SKIP_SEEN_DIALOGUES = "skip_seen_dialogues";
    static constexpr auto KEY_REVERSE_MOUSE_WHEEL = "reverse_mouse_wheel";
    static constexpr auto KEY_BGM_VOLUME = "bgm_volume";
    static constexpr auto KEY_SE_VOLUME = "se_volume";
    static constexpr auto KEY_SFX_VOLUME = "sfx_volume";
    static constexpr auto KEY_VOICE_VOLUME = "voice_volume";
    static constexpr auto KEY_CONTROLS = "controls";
    static constexpr auto KEY_DIALOGUE_UI_OPACITY = "dialogue_ui_opacity";
    static constexpr auto KEY_DIALOGUE_UI_OPACITY_PREVIEW = "dialogue_ui_opacity_preview";
    static constexpr auto KEY_TEXT_SPEED = "text_speed";
    static constexpr auto KEY_AUTO_PLAY_DIALOGUE_SPEED = "auto_play_dialogue_speed";
    static constexpr auto KEY_TEXT_SPEED_PREVIEW = "text_speed_preview";

    static constexpr auto KEY_CONTROLS_USAGE_TITLE = "title";
    static constexpr auto KEY_CONTROLS_USAGE_LINE_1 = "line_1";
    static constexpr auto KEY_CONTROLS_USAGE_LINE_2 = "line_2";
    static constexpr auto KEY_CONTROLS_USAGE_LINE_3 = "line_3";
    static constexpr auto KEY_CONTROLS_USAGE_LINE_4 = "line_4";
    static constexpr auto KEY_CONTROLS_USAGE_LINE_5 = "line_5";
    static constexpr auto KEY_CONTROLS_USAGE_LINE_6 = "line_6";

    static constexpr auto KEY_FONT = "font";
    static constexpr auto KEY_COLOR = "color";
    static constexpr auto KEY_SIZE = "size";
    static constexpr auto KEY_TEXT = "text";

    static const std::map<const char*, const SettingUITextKey&> g_keys;
    static constexpr std::array<std::pair<const char*, const SettingUITextKey*>, 20> g_arr {
        std::make_pair(KEY_FULLSCREEN, &fullscreen),
        std::make_pair(KEY_SKIP_SEEN_DIALOGUES, &skip_seen_dialogues),
        std::make_pair(KEY_REVERSE_MOUSE_WHEEL, &reverse_mouse_wheel),
        std::make_pair(KEY_BGM_VOLUME, &bgm_volume),
        std::make_pair(KEY_SE_VOLUME, &se_volume),
        std::make_pair(KEY_SFX_VOLUME, &sfx_volume),
        std::make_pair(KEY_VOICE_VOLUME, &voice_volume),
        std::make_pair(KEY_CONTROLS, &controls),
        std::make_pair(KEY_DIALOGUE_UI_OPACITY, &dialogue_ui_opacity),
        std::make_pair(KEY_DIALOGUE_UI_OPACITY_PREVIEW, &dialogue_ui_opacity_preview),
        std::make_pair(KEY_TEXT_SPEED, &text_speed),
        std::make_pair(KEY_AUTO_PLAY_DIALOGUE_SPEED, &auto_play_dialogue_speed),
        std::make_pair(KEY_TEXT_SPEED_PREVIEW, &text_speed_preview),
        std::make_pair(KEY_CONTROLS_USAGE_TITLE, &controls_usage_title),
        std::make_pair(KEY_CONTROLS_USAGE_LINE_1, &controls_usage_line_1),
        std::make_pair(KEY_CONTROLS_USAGE_LINE_2, &controls_usage_line_2),
        std::make_pair(KEY_CONTROLS_USAGE_LINE_3, &controls_usage_line_3),
        std::make_pair(KEY_CONTROLS_USAGE_LINE_4, &controls_usage_line_4),
        std::make_pair(KEY_CONTROLS_USAGE_LINE_5, &controls_usage_line_5),
        std::make_pair(KEY_CONTROLS_USAGE_LINE_6, &controls_usage_line_6)
    };
};


#endif //RIKKI_PATCHER_RIKKI_DATA_UI_KEY_UI_TEXT_SETTING_KEY_HPP
