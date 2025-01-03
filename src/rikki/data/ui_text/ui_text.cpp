#include "ui_text.hpp"
#include "rikki/data/ui/ui.hpp"
#include "key/ui_text_key.hpp"

#include "utils/json_util.hpp"

// ======================= S T R U C T =======================
// ===    SettingUITextEntry
// ======================= S T R U C T =======================

SettingUITextEntry::SettingUITextEntry(const SettingUIText::FontStyle& fs) {
    m_font  = fs.font;
    m_color = fs.color;
    m_size   = fs.size;
    m_text  = fs.text;
}

SettingUITextEntry& SettingUITextEntry::operator=(const SettingUIText::FontStyle& rhs) {
    m_font  = rhs.font;
    m_color = rhs.color;
    m_size   = rhs.size;
    m_text  = rhs.text;
    return *this;
}

// ======================== C L A S S ========================
// ===    UIText
// ======================== C L A S S ========================

bool UIText::get_in_game(const InGameUITextKey& key, std::string& result) {
    bool found = false;

    this->find_in_game(key, [&found, &result](const std::string& s) {
        found = true;
        result.assign(s);
    });

    return found;
}

bool UIText::set_in_game(const InGameUITextKey& key, const std::string& value) {
    bool found = false;

    this->find_in_game(key, [&found, value](std::string& s) {
        found = true;
        s = value;
    });

    return found;
}

bool UIText::get_setting(const SettingUITextKey& key, SettingUITextEntry& result) {
    bool found = false;

    this->find_setting(key, [&found, &result](const SettingUITextEntry& e) {
        found = true;
        result = e;
    });

    return found;
}

bool UIText::set_setting(const SettingUITextKey& key, const SettingUITextEntry& value) {
    bool found = false;

    this->find_setting(key, [&found, value](SettingUITextEntry& e) {
        found = true;
        e = value;
    });

    return found;
}

bool UIText::get_dialog_type1(const DialogType1UITextKey& key, DialogUITextEntry& result) {
    bool found = false;

    this->find_dialog_type1(key, [&found, &result](const DialogUITextEntry& s) {
        found = true;
        result = s;
    });

    return found;
}

bool UIText::set_dialog_type1(const DialogType1UITextKey& key, const DialogUITextEntry& value) {
    bool found = false;

    this->find_dialog_type1(key, [&found, value](DialogUITextEntry& s) {
        found = true;
        s = value;
    });

    return found;
}

bool UIText::get_dialog_type2(const DialogType2UITextKey& key, DialogUITextEntry& result) {
    bool found = false;

    this->find_dialog_type2(key, [&found, &result](const DialogUITextEntry& s) {
        found = true;
        result = s;
    });

    return found;
}

bool UIText::set_dialog_type2(const DialogType2UITextKey& key, const DialogUITextEntry& value) {
    bool found = false;

    this->find_dialog_type2(key, [&found, value](DialogUITextEntry& s) {
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

void UIText::find_in_game(const InGameUITextKey& key, const in_game_ui_text_callback_t& callback) {
    try {
        auto& jText = m_pUI->get_json()
        [key.m_iKey][key.m_iiKey]["commands"][key.m_iIdx][key.m_iiIdx][1][key.m_iiiKey][1][2]["atts"][key.m_iiiiKey][1]["text"];

        std::string buf = jText;
        callback(buf);
        jText = buf;
    }
    catch (const nlohmann::json::exception& e) { }
}

void UIText::find_setting(const SettingUITextKey& key, const setting_ui_text_callback_t& callback) {
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

            auto& jFont = arr2It["font"];
            auto& jColor = arr2It["color"];
            auto& jSize = arr2It["fontSize"];
            auto& jText = arr2It[key.m_textKey];

            SettingUITextEntry e { };
            e.m_font = jFont;
            e.m_color = jColor;
            e.m_size = jSize;
            e.m_text = jText;

            callback(e);

            jFont = e.m_font;
            jColor = e.m_color;
            jSize = e.m_size;
            jText = e.m_text;
        }
    }
}

void UIText::find_dialog_type1(const DialogType1UITextKey& key, const dialog_ui_text_callback_t& callback) {
    auto& arr = m_pUI->get_json()[key.m_ikey][key.m_iiKey]["commands"][0];
    auto& jSys = arr[3][5];
    auto& jText = arr[4][5];

    DialogUITextEntry buf { jSys, jText };
    callback(buf);

    jSys = buf.m_system;
    jText = buf.m_text;
}

void UIText::find_dialog_type2(const DialogType2UITextKey& key, const dialog_ui_text_callback_t& callback) {
    auto& arr = m_pUI->get_json()[key.m_ikey]["commands"];

    if (key.m_iIdx > -1) {
        arr[key.m_iIdx];
    }

    auto& jSys = arr[key.m_iiIdx][5];
    auto& jText = arr[key.m_iiiIdx][5];

    DialogUITextEntry buf { jSys, jText };
    callback(buf);

    jSys = buf.m_system;
    jText = buf.m_text;
}

UIText::UIText(UI* const pUI) :
    m_pUI(pUI) {

    m_isValid = m_pUI->is_valid();
}
