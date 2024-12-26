#ifndef RIKKI_PATCHER_RIKKI_STREAM_UI_MIGR_STREAM_HPP
#define RIKKI_PATCHER_RIKKI_STREAM_UI_MIGR_STREAM_HPP
#include "precompiled.hpp"
#include "i_stream.hpp"

/* ui_migr_stream.hpp
 *  Included classes:
 *      - UITextMigrStream
 */

// ======================== C L A S S ========================
// ===    UITextMigrStream
// ======================== C L A S S ========================

class UITextMigrStream : public IMigrStream {
public:
    /**
     * @brief Get pure ui-texts from data.
     *
     * @tparam T Target ui-text data structure.
     * @return Returns target ui-text data structure.
     *
     * @code
     * UITextMigrStream stream("setting.json");
     * SettingUIText buf = stream.get_texts<SettingUIText>();
     * @endcode
     */
    template <class T>
    T get_texts() const;

    /**
     * @brief Save migration data files.
     * <br>Game data must be unmodified,
     *
     * @param [in] dir Path to save the migration data files.
     */
    static void save_migration_data(const path_t& dir);

public:
    /**
     * @brief Load migration data form file.
     *
     * @param [in] file Migration data file path.
     *
     * @code
     * UITextMigrStream settingStream("setting.json");
     * UITextMigrStream dialogStream("dialog.json");
     * @endcode
     */
    explicit UITextMigrStream(const path_t& file);
private:
    nlohmann::json m_j;
    const path_t m_file; /* path of json file. */
};


#endif //RIKKI_PATCHER_RIKKI_STREAM_UI_MIGR_STREAM_HPP
