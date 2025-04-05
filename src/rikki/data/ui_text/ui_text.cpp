#include "ui_text.hpp"
#include "rikki/data/ui/ui.hpp"
#include "key/ui_text_msg_box_text.hpp"

// ======================== C L A S S ========================
// ===    UIText
// ======================== C L A S S ========================

bool UIText::get_in_game(const InGameUITextKey& key, in_game_ui_text_t& result) {
    bool found = false;

    this->find_in_game(key, [&found, &result](const in_game_ui_text_t& s) {
        found = true;
        result.assign(s);
    });

    return found;
}

bool UIText::set_in_game(const InGameUITextKey& key, const in_game_ui_text_t& value) {
    bool found = false;

    this->find_in_game(key, [&found, value](in_game_ui_text_t& s) {
        found = true;
        s = value;
    });

    return found;
}

bool UIText::get_setting(const SettingUITextKey& key, setting_ui_text_t& result) {
    bool found = false;

    this->find_setting(key, [&found, &result](const setting_ui_text_t& e) {
        found = true;
        result = e;
    });

    return found;
}

bool UIText::set_setting(const SettingUITextKey& key, const setting_ui_text_t& value) {
    bool found = false;

    this->find_setting(key, [&found, value](setting_ui_text_t& e) {
        found = true;
        e = value;
    });

    return found;
}

bool UIText::get_dialog_type1(const DialogType1UITextKey& key, dialog_ui_text_t& result) {
    bool found = false;

    this->find_dialog_type1(key, [&found, &result](const dialog_ui_text_t& s) {
        found = true;
        result = s;
    });

    return found;
}

bool UIText::set_dialog_type1(const DialogType1UITextKey& key, const dialog_ui_text_t& value) {
    bool found = false;

    this->find_dialog_type1(key, [&found, value](dialog_ui_text_t& s) {
        found = true;
        s = value;
    });

    return found;
}

bool UIText::get_dialog_type2(const DialogType2UITextKey& key, dialog_ui_text_t& result) {
    bool found = false;

    this->find_dialog_type2(key, [&found, &result](const dialog_ui_text_t& s) {
        found = true;
        result = s;
    });

    return found;
}

bool UIText::set_dialog_type2(const DialogType2UITextKey& key, const dialog_ui_text_t& value) {
    bool found = false;

    this->find_dialog_type2(key, [&found, value](dialog_ui_text_t& s) {
        found = true;
        s = value;
    });

    return found;
}

bool UIText::get_title(const TitleUITextKey& key, title_ui_text_t& result) {
    bool found = false;

    this->find_title(key, [&found, &result](const title_ui_text_t& s) {
        found = true;
        result = s;
    });

    return found;
}

bool UIText::set_title(const TitleUITextKey& key, const title_ui_text_t& value) {
    bool found = false;

    this->find_title(key, [&found, value](title_ui_text_t& s) {
        found = true;
        s = value;
    });

    return found;
}

bool UIText::backup(const path_t& dir) {
    throw std::exception("Not Implemented. Use UI::backup().");
}

bool UIText::save() {
    throw std::exception("Not Implemented. Use UI::save().");
}

bool UIText::save(const path_t& dir) {
    throw std::exception("Not Implemented. Use UI::save().");
}

void UIText::find_in_game(const InGameUITextKey& key, const in_game_ui_text_callback_t& callback) const {
    try {
        auto& jText = m_pUI->get_json()
        [key.m_iKey][key.m_iiKey]["commands"][key.m_iIdx][key.m_iiIdx][1][key.m_iiiKey][1][2]["atts"][key.m_iiiiKey][1]["text"];

        in_game_ui_text_t buf = jText;
        callback(buf);
        jText = buf;
    }
    catch (const nlohmann::json::exception& e) { }
}

void UIText::find_setting(const SettingUITextKey& key, const setting_ui_text_callback_t& callback) const {
    for (auto& arr1 = m_pUI->get_json()[key.m_iKey]["root"]["children"]; auto& arr1It : arr1) {
        if (arr1It.contains("id") && arr1It["id"] != key.m_iiKey) {
            continue;
        }

        if (!arr1It.contains("children")) {
            continue;
        }

        for (auto& arr2 = arr1It["children"]; auto& arr2It : arr2) {
            if (arr2It.contains("id") && arr2It["id"] != key.m_iiiKey) {
                continue;
            }

            auto& jFont = arr2It[MsgBoxUITextKey::KEY_FONT];
            auto& jColor = arr2It[MsgBoxUITextKey::KEY_COLOR];
            auto& jSize = arr2It[MsgBoxUITextKey::KEY_FONT_SIZE];
            auto& jX = arr2It[MsgBoxUITextKey::KEY_X];
            auto& jY = arr2It[MsgBoxUITextKey::KEY_Y];
            auto& jWidth = arr2It[MsgBoxUITextKey::KEY_WIDTH];
            auto& jShow = arr2It[MsgBoxUITextKey::KEY_SHOW];
            auto& jText = arr2It[key.m_textKey]; //

            setting_ui_text_t buf { };
            buf.font = jFont;
            buf.color = jColor;
            buf.size = jSize;
            buf.x = jX;
            buf.y = jY;
            buf.width = jWidth;
            buf.show = jShow;
            buf.text = jText;

            callback(buf);

            jFont = buf.font;
            jColor = buf.color;
            jSize = buf.size;
            jX = buf.x;
            jY = buf.y;
            jWidth = buf.width;
            jShow = buf.show;
            jText = buf.text;
        }
    }
}

void UIText::find_dialog_type1(const DialogType1UITextKey& key, const dialog_ui_text_callback_t& callback) const {
    auto& arr = m_pUI->get_json()[key.m_ikey][key.m_iiKey]["commands"][0];
    auto& jSys = arr[3][5];
    auto& jText = arr[4][5];

    dialog_ui_text_t buf { jSys, jText };
    callback(buf);

    jSys = buf.system;
    jText = buf.text;
}

void UIText::find_dialog_type2(const DialogType2UITextKey& key, const dialog_ui_text_callback_t& callback) const {
    auto& arr = m_pUI->get_json()[key.m_ikey]["commands"];

    if (key.m_iIdx > -1) {
        arr[key.m_iIdx];
    }

    auto& jSys = arr[key.m_iiIdx][5];
    auto& jText = arr[key.m_iiiIdx][5];

    dialog_ui_text_t buf { jSys, jText };
    callback(buf);

    jSys = buf.system;
    jText = buf.text;
}

void UIText::find_title(const TitleUITextKey& key, const setting_ui_text_callback_t& callback) const {
    auto& arr = m_pUI->get_json()[key.m_iKey][key.m_iiKey][key.m_iiiKey][key.m_iIdx][key.m_iiiiKey][key.m_iiIdx];
    auto& jText = arr["text"];

    auto buf = j::MsgBoxText::from_json_array(arr);
    callback(buf);
    buf.into_json_array(arr);
}

UIText::UIText(std::shared_ptr<UI> pUI) :
    m_pUI(pUI) {

    m_isValid = m_pUI->is_valid();
}
