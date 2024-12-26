#ifndef RIKKI_PATCHER_RIKKI_STREAM_UI_PATCH_STREAM_HPP
#define RIKKI_PATCHER_RIKKI_STREAM_UI_PATCH_STREAM_HPP
#include "precompiled.hpp"

struct InGameUITextKey;
struct SettingUITextKey;
struct DialogUITextKey;

class UITextPatchStream {
public:
    /**
     * @brief Get loaded ui texts.
     *
     * @tparam T Target ui text struct,
     * @return Returns target ui text struct with values.
     */
    template<class T>
    T get_texts() const;

    template<class T>
    void set_texts(const T& t);

    void clear();

    bool save() const;

public:
    /**
     * @brief Create or load the ui texts from custom patch file.
     *
     * @param [in] file Ui text custom patch file path.
     */
    explicit UITextPatchStream(const path_t& file);
private:
    path_t m_file;
    nlohmann::json m_j;

public:
    static constexpr auto FILE_IN_GAME = "in_game.json";
    static constexpr auto FILE_SETTING = "setting.json";
    static constexpr auto FILE_DIALOG = "dialog.json";

    static constexpr auto FOLDER_BASE = "ui/texts";
};


#endif //RIKKI_PATCHER_RIKKI_STREAM_UI_PATCH_STREAM_HPP
