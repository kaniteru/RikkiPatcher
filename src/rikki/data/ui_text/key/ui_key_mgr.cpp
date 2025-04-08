#include "ui_key_mgr.hpp"
#include "ui_text_in_game_key.hpp"
#include "ui_text_setting_key.hpp"
#include "ui_text_dialog_key.hpp"

// ======================== C L A S S ========================
// ===    UIKeyMgr
// ======================== C L A S S ========================

void UIKeyMgr::add_ui_text_in_game() {
    for (const auto& [k, v] : InGameUITextKeyMgr::g_arr) {
        this->add<InGameUITextKey>(k, v);
    }
}

void UIKeyMgr::add_ui_text_setting() {
    for (const auto& [k, v] : SettingUITextKeyMgr::g_arr) {
        this->add<SettingUITextKey>(k, v);
    }
}

void UIKeyMgr::add_ui_text_dialog() {
    for (const auto& [k, v] : DialogUITextKeyMgr::g_type1Arr) {
        this->add<DialogType1UITextKey>(k, v);
    }

    for (const auto& [k, v] : DialogUITextKeyMgr::g_type2Arr) {
        this->add<DialogType2UITextKey>(k, v);
    }
}

UIKeyMgr::UIKeyMgr() {
    this->add_ui_text_in_game();
    this->add_ui_text_setting();
    this->add_ui_text_dialog();
}
