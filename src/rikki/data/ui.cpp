#include "ui.hpp"
#include "ui_key.hpp"

#include "utils/json_util.hpp"

bool UIText::get_in_game(const InGameUITextKey& key, std::string& result) {
    bool found = false;

    this->find_in_game(key, [&found, result](const std::string& s) {
        found = true;
        result = s;
    });

    return found;
}

bool UIText::set_in_game(const InGameUITextKey& key, std::string& value) {
    bool found = false;

    this->find_in_game(key, [&found, value](std::string& s) {
        found = true;
        s = value;
    });

    return found;
}

bool UIText::get_setting(const SettingUITextKey& key, SettingUITextEntry& result) {
    bool found = false;

    this->find_setting(key, [&found, result](const SettingUITextEntry& e) {
        found = true;
        result = e;
    });

    return found;
}

bool UIText::set_setting(const SettingUITextKey& key, SettingUITextEntry& value) {
    bool found = false;

    this->find_setting(key, [&found, value](SettingUITextEntry& e) {
        found = true;
        e = value;
    });

    return found;
}

bool UIText::get_dialog(const DialogUITextKey& key, std::string& result) {
    bool found = false;

    this->find_dialog(key, [&found, result](const std::string& s) {
        found = true;
        result = s;
    });

    return found;
}

bool UIText::set_dialog(const DialogUITextKey& key, std::string& value) {
    bool found = false;

    this->find_dialog(key, [&found, value](std::string& s) {
        found = true;
        s = value;
    });

    return found;
}

bool UIText::backup(const path_t& dir) {
    try {
        const auto fName = m_file.filename().u8string();
        std::filesystem::copy(m_file, path_t(dir).append(fName), std::filesystem::copy_options::overwrite_existing);
    }
    catch (const std::exception& e) {
        return false;
    }

    return true;
}

bool UIText::save() {
    return this->save(m_file);
}

bool UIText::save(const path_t& dir) {
    return JsonUtil::save_into_file(m_j, dir);
}

void UIText::find_in_game(const InGameUITextKey& key, const in_game_ui_text_callback_t& callback) {
    try {
        auto& jText = m_j[key.m_iKey][key.m_iiKey]["commands"][1][0][1][key.m_iiiKey][1][2]["atts"][key.m_iiiiKey][1]["text"];
        std::string buf = jText;
        callback(buf);
        jText = buf;
    }
    catch (const nlohmann::json::exception& e) { }
}

void UIText::find_setting(const SettingUITextKey& key, const setting_ui_text_callback_t& callback) {
    for (auto arr1 = m_j[key.m_iKey]["root"]["children"]; auto& arr1It : arr1) {
        if (arr1It.contains("id") && arr1It["id"] != key.m_iiKey) {
            continue;
        }

        if (!arr1It.contains("children")) {
            continue;
        }

        for (auto arr2 = arr1It["children"]; auto& arr2It : arr2) {
            if (arr2It.contains("id") && arr2It["id"] != key.m_iiiKey) {
                continue;
            }

            auto& jFont = arr2It["font"];
            auto& jColor = arr2It["color"];
            auto& jSize = arr2It["fontSize"];
            auto& jText = arr2It["text"];

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

void UIText::find_dialog(const DialogUITextKey& key, const dialog_ui_text_callback_t& callback) {
    auto& arr = m_j[key.m_ikey][key.m_iiKey]["commands"][0];

    for (auto& it : arr) {
        if (auto& idx = it[0]; !idx.is_number_integer() || idx != 13) {
            continue;
        }

        std::string cmdID { };

        if (auto& cmdIdx = it[15]; cmdIdx.is_array()) {
            cmdID = cmdIdx["___cmdID"];
        } else {
            continue;
        }

        auto& jText = it[5];

        if (!jText.is_string()) {
            continue;
        }

        std::string buf = jText;
        callback(buf);
        jText = buf;
    }
}

UIText::UIText(const path_t& file) :
                                   m_file(file) {

    m_isValid = JsonUtil::load_from_file(m_j, file);
}
