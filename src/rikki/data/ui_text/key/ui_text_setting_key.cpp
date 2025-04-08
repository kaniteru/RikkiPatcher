#include "ui_text_setting_key.hpp"

// ======================= S T R U C T =======================
// ===    SettingUITextKeyMgr
// ======================= S T R U C T =======================

const SettingUITextKey SettingUITextKeyMgr::fullscreen {
    "asset/json/ui/data/ui6.json",
    "77057165895_0.7755981457644934",
    "51693436802_0.14734056462439038",
    "text"
};

const SettingUITextKey SettingUITextKeyMgr::skip_seen_dialogues {
    "asset/json/ui/data/ui6.json",
    "77057165895_0.7755981457644934",
    "51693448886_0.8082126247945838",
    "text"
};

const SettingUITextKey SettingUITextKeyMgr::reverse_mouse_wheel {
    "asset/json/ui/data/ui6.json",
    "77057165895_0.7755981457644934",
    "88208943186_0.07531812759699386",
    "text"
};

const SettingUITextKey SettingUITextKeyMgr::bgm_volume {
    "asset/json/ui/data/ui6.json",
    "77057147563_0.6605757976293434",
    "51693248302_0.4833432092909784",
    "text"
};

const SettingUITextKey SettingUITextKeyMgr::se_volume {
    "asset/json/ui/data/ui6.json",
    "77057147563_0.6605757976293434",
    "77056357431_0.6212357489009417",
    "text"
};

const SettingUITextKey SettingUITextKeyMgr::sfx_volume {
    "asset/json/ui/data/ui6.json",
    "77057147563_0.6605757976293434",
    "77056364584_0.7141317074329632",
    "text"
};

const SettingUITextKey SettingUITextKeyMgr::voice_volume {
    "asset/json/ui/data/ui6.json",
    "77057147563_0.6605757976293434",
    "77056369650_0.48000654850503555",
    "text"
};

const SettingUITextKey SettingUITextKeyMgr::controls {
    "asset/json/ui/data/ui6.json",
    "174126140419_0.35881367396512087",
    "174780833786_0.7244911314922216",
    "label"
};

const SettingUITextKey SettingUITextKeyMgr::dialogue_ui_opacity {
    "asset/json/ui/data/ui6.json",
    "88201534596_0.7776486912477745",
    "88201536361_0.4605433982328708",
    "text"
};

const SettingUITextKey SettingUITextKeyMgr::dialogue_ui_opacity_preview {
    "asset/json/ui/data/ui6.json",
    "88201534596_0.7776486912477745",
    "88201863934_0.8559660352778693",
    "text"
};

const SettingUITextKey SettingUITextKeyMgr::text_speed {
    "asset/json/ui/data/ui6.json",
    "88203784470_0.37947726651767355",
    "88203784472_0.31837593447731405",
    "text"
};

const SettingUITextKey SettingUITextKeyMgr::auto_play_dialogue_speed {
    "asset/json/ui/data/ui6.json",
    "88203784470_0.37947726651767355",
    "88203824570_0.2827155233060785",
    "text"
};

const SettingUITextKey SettingUITextKeyMgr::text_speed_preview {
    "asset/json/ui/data/ui6.json",
    "88203784470_0.37947726651767355",
    "88205831319_0.7978083168023089",
    "text"
};

const SettingUITextKey SettingUITextKeyMgr::controls_usage_title {
    "asset/json/ui/data/ui18.json",
    "174126492725_0.21606692774997383",
    "174131678340_0.5518982213996508",
    "text"
};

const SettingUITextKey SettingUITextKeyMgr::controls_usage_line_1 {
    "asset/json/ui/data/ui18.json",
    "174126492725_0.21606692774997383",
    "174132115884_0.690202079901092",
    "text"
};

const SettingUITextKey SettingUITextKeyMgr::controls_usage_line_2 {
    "asset/json/ui/data/ui18.json",
    "174126492725_0.21606692774997383",
    "174781727267_0.368946395260596",
    "text"
};

const SettingUITextKey SettingUITextKeyMgr::controls_usage_line_3 {
    "asset/json/ui/data/ui18.json",
    "174126492725_0.21606692774997383",
    "174781790431_0.33857905601763716",
    "text"
};

const SettingUITextKey SettingUITextKeyMgr::controls_usage_line_4 {
    "asset/json/ui/data/ui18.json",
    "174126492725_0.21606692774997383",
    "174781854041_0.599565171833589",
    "text"
};

const SettingUITextKey SettingUITextKeyMgr::controls_usage_line_5 {
    "asset/json/ui/data/ui18.json",
    "174126492725_0.21606692774997383",
    "174782567455_0.04516298490071913",
    "text"
};

const SettingUITextKey SettingUITextKeyMgr::controls_usage_line_6 {
    "asset/json/ui/data/ui18.json",
    "174126492725_0.21606692774997383",
    "174783189751_0.2417955823173552",
    "text"
};

const std::map<const char*, const SettingUITextKey&> SettingUITextKeyMgr::g_keys = {
    { KEY_FULLSCREEN, fullscreen },
    { KEY_SKIP_SEEN_DIALOGUES, skip_seen_dialogues },
    { KEY_REVERSE_MOUSE_WHEEL, reverse_mouse_wheel },
    { KEY_BGM_VOLUME, bgm_volume },
    { KEY_SE_VOLUME, se_volume },
    { KEY_SFX_VOLUME, sfx_volume },
    { KEY_VOICE_VOLUME, voice_volume },
    { KEY_CONTROLS, controls },
    { KEY_DIALOGUE_UI_OPACITY, dialogue_ui_opacity },
    { KEY_DIALOGUE_UI_OPACITY_PREVIEW, dialogue_ui_opacity_preview },
    { KEY_TEXT_SPEED, text_speed },
    { KEY_AUTO_PLAY_DIALOGUE_SPEED, auto_play_dialogue_speed },
    { KEY_TEXT_SPEED_PREVIEW, text_speed_preview },
    { KEY_CONTROLS_USAGE_TITLE, controls_usage_title },
    { KEY_CONTROLS_USAGE_LINE_1, controls_usage_line_1 },
    { KEY_CONTROLS_USAGE_LINE_2, controls_usage_line_2 },
    { KEY_CONTROLS_USAGE_LINE_3, controls_usage_line_3 },
    { KEY_CONTROLS_USAGE_LINE_4, controls_usage_line_4 },
    { KEY_CONTROLS_USAGE_LINE_5, controls_usage_line_5 },
    { KEY_CONTROLS_USAGE_LINE_6, controls_usage_line_6 }
};
