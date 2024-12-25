#ifndef RIKKI_PATCHER_RIKKI_DATA_UI_HPP
#define RIKKI_PATCHER_RIKKI_DATA_UI_HPP
#include "precompiled.hpp"
#include "rikki/data/i_data.hpp"
#include "ui_json.hpp"
#include "key/ui_key.hpp"

/* ui.hpp
 *  Included classes:
 *      - UIText
 *
 *  Included structs:
 *      - SettingUITextEntry
 *      - DialogUITextEntry
 */

struct InGameUITextKey;
struct SettingUITextKey;
struct DialogType1UITextKey;
struct DialogType2UITextKey;

struct SettingUITextEntry;
struct DialogUITextEntry;

using in_game_ui_text_callback_t = std::function<void(std::string&)>;
using setting_ui_text_callback_t = std::function<void(SettingUITextEntry&)>;
using dialog_ui_text_callback_t = std::function<void(DialogUITextEntry&)>;

// todo: hmmm
// using ui_text_text_t = std::string;

// ======================= S T R U C T =======================
// ===    SettingUITextEntry
// ======================= S T R U C T =======================

struct SettingUITextEntry {
    std::string m_font;
    std::string m_color;
    int32_t m_size;
    std::string m_text;

    SettingUITextEntry() = default;
    SettingUITextEntry(const SettingUIText::FontStyle& fs);

    SettingUITextEntry& operator=(const SettingUIText::FontStyle&);
};

// ======================= S T R U C T =======================
// ===    DialogUITextEntry
// ======================= S T R U C T =======================

enum eDialogUITextType {
    DIALOG_UI_TEXT_TYPE_1,
    DIALOG_UI_TEXT_TYPE_2
};

struct DialogUITextEntry {
    std::string m_system;
    std::string m_text;
};

// ======================== C L A S S ========================
// ===    UIText
// ======================== C L A S S ========================

class UIText final : public IData {
public:
    /**
     * @brief Get in-game data using key.
     *
     * @param [in] key Target in-game data key.
     * @param [out] result Target value.
     * @return Returns true if found target.
     */
    bool get_in_game(const InGameUITextKey& key, std::string& result);

    /**
     * @brief Set in-game data using key.
     *
     * @param [in] key Target in-game data key.
     * @param [in] value Target value.
     * @return Returns true if found target.
     */
    bool set_in_game(const InGameUITextKey& key, const std::string& value);

    /**
     * @brief Get setting data using key.
     *
     * @param [in] key Target setting data key.
     * @param [out] result Target value.
     * @return Return true if found target.
     */
    bool get_setting(const SettingUITextKey& key, SettingUITextEntry& result);

    /**
     * @brief Set setting data using key.
     *
     * @param [in] key Target setting data key.
     * @param [in] value Target value.
     * @return Returns true if found target.
     */
    bool set_setting(const SettingUITextKey& key, const SettingUITextEntry& value);

    /**
     * @brief Get dialog data using key.
     *
     * @param [in] key Target dialog data key.
     * @param [out] result Target value.
     * @return Returns true if found target.
     */
    bool get_dialog_type1(const DialogType1UITextKey& key, DialogUITextEntry& result);

    /**
     * @brief Set dialog data using key.
     *
     * @param [in] key Target dialog data key.
     * @param [in] value Target value.
     * @return Returns true if found target.
     */
    bool set_dialog_type1(const DialogType1UITextKey& key, const DialogUITextEntry& value);

    /**
     * @brief Get dialog data using key.
     *
     * @param [in] key Target dialog data key.
     * @param [out] result Target value.
     * @return Returns true if found target.
     */
    bool get_dialog_type2(const DialogType2UITextKey& key, DialogUITextEntry& result);

    /**
     * @brief Set dialog data using key.
     *
     * @param [in] key Target dialog data key.
     * @param [in] value Target value.
     * @return Returns true if found target.
     */
    bool set_dialog_type2(const DialogType2UITextKey& key, const DialogUITextEntry& value);

    bool backup(const path_t& dir) final;

    bool save() final;

    bool save(const path_t& dir) final;
private:
    /**
     * @brief Find in-game data in the loaded data using key.
     *
     * @param [in] key Target in-game data key.
     * @param [in, out] callback Get/set the value string.
     */
    void find_in_game(const InGameUITextKey& key, const in_game_ui_text_callback_t& callback);

    /**
     * @brief Find setting data in the loaded data using key.
     *
     * @param [in] key Target setting data key.
     * @param [in, out] callback Get/set the setting ui entry value.
     */
    void find_setting(const SettingUITextKey& key, const setting_ui_text_callback_t& callback);

    /**
     * @brief Find dialog data in the loaded data using key.
     *
     * @param [in] key Target dialog data key.
     * @param [in, out] callback Get/set the value string.
     */
    void find_dialog_type1(const DialogType1UITextKey& key, const dialog_ui_text_callback_t& callback);

    /**
     * @brief Find dialog data in the loaded data using key.
     *
     * @param [in] key Target dialog data key.
     * @param [in, out] callback Get/set the value string.
     */
    void find_dialog_type2(const DialogType2UITextKey& key, const dialog_ui_text_callback_t& callback);

public:
    /**
     * @brief Load ui-text from game data file.
     *
     * @param [in] file decrypted 'asset/json/startup.json' file path.
     */
    explicit UIText(const path_t& file);
private:
    path_t m_file;         /* Target decrypted startup.json file path */
    nlohmann::json m_j; /* Loaded startup.json data */
};


#endif //RIKKI_PATCHER_RIKKI_DATA_UI_HPP
