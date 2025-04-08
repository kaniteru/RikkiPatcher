#ifndef RIKKI_PATCHER_RIKKI_DATA_UI_UI_HPP
#define RIKKI_PATCHER_RIKKI_DATA_UI_UI_HPP
#include "precompiled.hpp"
#include "rikki/data/i_data.hpp"

/* ui.hpp
 *  Included classes:
 *      - UI
 */

class UI;

// ======================== C L A S S ========================
// ===    UI
// ======================== C L A S S ========================

class UI final : public IData {
public:
    bool save() final;

    bool save(const path_t& dir) final;

    /**
     * @brief Get json ref.
     *
     * @return Returns ref of startup json.
     *
     * @code
     * UI ui(...);
     *
     * if (ui.is_valid()) {
     *      auto& j = ui.get_json();
     *      ...
     * }
     * @endcode
     */
    nlohmann::json& get_json();

public:
    /**
     * @param [in] file The path of decrypted startup.json.
     */
    explicit UI(const path_t& file);
private:
    const path_t m_file; /* Path of decrypted startup.json */
    nlohmann::json m_j;  /* Loaded json data */
};


#endif //RIKKI_PATCHER_RIKKI_DATA_UI_UI_HPP
