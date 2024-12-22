#ifndef RIKKI_PATCHER_RIKKI_DATA_UI_HPP
#define RIKKI_PATCHER_RIKKI_DATA_UI_HPP
#include "precompiled.hpp"
#include "i_data.hpp"

struct InGameUITextKey;
struct SettingUITextKey;
struct DialogUITextKey;
struct SettingUITextEntry;

using in_game_ui_text_callback_t = std::function<void(std::string&)>;
using setting_ui_text_callback_t = std::function<void(SettingUITextEntry&)>;
using dialog_ui_text_callback_t = std::function<void(std::string&)>;

struct SettingUITextEntry {
    std::string m_font;
    std::string m_color;
    int32_t m_size;
    std::string m_text;
};

class UIText : public IData {
public:
    bool get_in_game(const InGameUITextKey& key, std::string& result);
    bool set_in_game(const InGameUITextKey& key, std::string& value);

    bool get_setting(const SettingUITextKey& key, SettingUITextEntry& result);
    bool set_setting(const SettingUITextKey& key, SettingUITextEntry& value);

    bool get_dialog(const DialogUITextKey& key, std::string& result);
    bool set_dialog(const DialogUITextKey& key, std::string& value);

    bool backup(const path_t& dir) final;

    bool save() final;

    bool save(const path_t& dir) final;
private:
    void find_in_game(const InGameUITextKey& key, const in_game_ui_text_callback_t& callback);
    void find_setting(const SettingUITextKey& key, const setting_ui_text_callback_t& callback);
    void find_dialog(const DialogUITextKey& key, const dialog_ui_text_callback_t& callback);

public:
    explicit UIText(const path_t& file);
private:
    path_t m_file;
    nlohmann::json m_j;
};


#endif //RIKKI_PATCHER_RIKKI_DATA_UI_HPP
