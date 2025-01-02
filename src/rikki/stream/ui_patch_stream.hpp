#ifndef RIKKI_PATCHER_RIKKI_STREAM_UI_PATCH_STREAM_HPP
#define RIKKI_PATCHER_RIKKI_STREAM_UI_PATCH_STREAM_HPP
#include "precompiled.hpp"

/* ui_patch_stream.hpp
 *  Included classes:
 *      - UITextPatchStream
 */

struct InGameUITextKey;
struct SettingUITextKey;
struct DialogUITextKey;

// ======================== C L A S S ========================
// ===    UITextPatchStream
// ======================== C L A S S ========================

class UITextPatchStream {
public:
    /**
     * @brief Get loaded ui texts.
     *
     * @tparam T Target ui text struct.
     * @return Returns target ui text struct with values.
     */
    template<class T>
    T get_texts() const;

    /**
     * @brief Set ui text contents.
     *
     * @tparam T Target ui text struct.
     * @param [in] t Ui text contents.
     */
    template<class T>
    void set_texts(const T& t);

    /**
     * @brief Clear ui text contents.
     */
    void clear();

    /**
     * @brief Save contents to json file.
     *
     * @return Returns true if save successfully.
     */
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
    nlohmann::ordered_json m_j;
};


#endif //RIKKI_PATCHER_RIKKI_STREAM_UI_PATCH_STREAM_HPP
