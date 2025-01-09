#ifndef RIKKI_PATCHER_RIKKI_DATA_UI_HPP
#define RIKKI_PATCHER_RIKKI_DATA_UI_HPP
#include "precompiled.hpp"
#include "rikki/data/i_data.hpp"
#include "ui_text_json.hpp"
#include "key/ui_text_key.hpp"

/* ui_text.hpp
 *  Included classes:
 *      - UIText
 */

class UI;

using in_game_ui_text_t = std::string;
using setting_ui_text_t = j::MsgBoxText;
using dialog_ui_text_t = j::DialogUIText::Dialog;
using title_ui_text_t = j::MsgBoxText;

using in_game_ui_text_callback_t = std::function<void(in_game_ui_text_t&)>;
using setting_ui_text_callback_t = std::function<void(setting_ui_text_t&)>;
using dialog_ui_text_callback_t = std::function<void(dialog_ui_text_t&)>;
using title_ui_text_callback_t = std::function<void(title_ui_text_t&)>;

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
    bool get_in_game(const InGameUITextKey& key, in_game_ui_text_t& result);

    /**
     * @brief Set in-game data using key.
     *
     * @param [in] key Target in-game data key.
     * @param [in] value Target value.
     * @return Returns true if found target.
     */
    bool set_in_game(const InGameUITextKey& key, const in_game_ui_text_t& value);

    /**
     * @brief Get setting data using key.
     *
     * @param [in] key Target setting data key.
     * @param [out] result Target value.
     * @return Return true if found target.
     */
    bool get_setting(const SettingUITextKey& key, setting_ui_text_t& result);

    /**
     * @brief Set setting data using key.
     *
     * @param [in] key Target setting data key.
     * @param [in] value Target value.
     * @return Returns true if found target.
     */
    bool set_setting(const SettingUITextKey& key, const setting_ui_text_t& value);

    /**
     * @brief Get dialog data using key.
     *
     * @param [in] key Target dialog data key.
     * @param [out] result Target value.
     * @return Returns true if found target.
     */
    bool get_dialog_type1(const DialogType1UITextKey& key, dialog_ui_text_t& result);

    /**
     * @brief Set dialog data using key.
     *
     * @param [in] key Target dialog data key.
     * @param [in] value Target value.
     * @return Returns true if found target.
     */
    bool set_dialog_type1(const DialogType1UITextKey& key, const dialog_ui_text_t& value);

    /**
     * @brief Get dialog data using key.
     *
     * @param [in] key Target dialog data key.
     * @param [out] result Target value.
     * @return Returns true if found target.
     */
    bool get_dialog_type2(const DialogType2UITextKey& key, dialog_ui_text_t& result);

    /**
     * @brief Set dialog data using key.
     *
     * @param [in] key Target dialog data key.
     * @param [in] value Target value.
     * @return Returns true if found target.
     */
    bool set_dialog_type2(const DialogType2UITextKey& key, const dialog_ui_text_t& value);

    /**
     * @brief Get title data using key.
     *
     * @param [in] key Target title data key.
     * @param [out] result Target value.
     * @return Returns true if found target.
     */
    bool get_title(const TitleUITextKey& key, title_ui_text_t& result);

    /**
     * @brief Set title data using key.
     *
     * @param [in] key Target title data key.
     * @param [in] value Target value.
     * @return Returns true if found target.
     */
    bool set_title(const TitleUITextKey& key, const title_ui_text_t& value);

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
    void find_in_game(const InGameUITextKey& key, const in_game_ui_text_callback_t& callback) const;

    /**
     * @brief Find setting data in the loaded data using key.
     *
     * @param [in] key Target setting data key.
     * @param [in, out] callback Get/set the setting ui entry value.
     */
    void find_setting(const SettingUITextKey& key, const setting_ui_text_callback_t& callback) const;

    /**
     * @brief Find dialog data in the loaded data using key.
     *
     * @param [in] key Target dialog data key.
     * @param [in, out] callback Get/set the value string.
     */
    void find_dialog_type1(const DialogType1UITextKey& key, const dialog_ui_text_callback_t& callback) const;

    /**
     * @brief Find dialog data in the loaded data using key.
     *
     * @param [in] key Target dialog data key.
     * @param [in, out] callback Get/set the value string.
     */
    void find_dialog_type2(const DialogType2UITextKey& key, const dialog_ui_text_callback_t& callback) const;

    /**
     * @brief Find title data in the loaded data using key.
     *
     * @param [in] key Target title data key.
     * @param [in, out] callback Get/set the value.
     */
    void find_title(const TitleUITextKey& key, const setting_ui_text_callback_t& callback) const;

public:
    /**
     * @brief Load ui-text from game data file.
     *
     * @param [in, out] pUI Ptr of UI.
     */
    explicit UIText(UI* pUI);
private:
    UI* const m_pUI;
};


#endif //RIKKI_PATCHER_RIKKI_DATA_UI_HPP
