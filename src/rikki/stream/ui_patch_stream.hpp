#ifndef IKKI_PATCHER_RIKKI_STREAM_UI_PATCH_STREAM_HPP
#define IKKI_PATCHER_RIKKI_STREAM_UI_PATCH_STREAM_HPP
#include "precompiled.hpp"

struct InGameUITextKey;
struct SettingUITextKey;
struct DialogUITextKey;
struct SettingUITextEntry;

class UITextPatchStream {
public:
    /**
     * @brief Get loaded ui texts.
     *
     * @tparam T Target
     * @return
     */
    template<class T>
    T get_texts() const;

    template<class T>
    void set_texts(const T& t);

    void clear();

    bool save() const;

public:
    /**
     * @brief Load ui texts from custom patch file.
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
};

template<class T>
T UITextPatchStream::get_texts() const {
    T t { };
    t = m_j.get<T>();
    return t;
}

template<class T>
void UITextPatchStream::set_texts(const T& t) {
    m_j = t;
}


#endif //IKKI_PATCHER_RIKKI_STREAM_UI_PATCH_STREAM_HPP
