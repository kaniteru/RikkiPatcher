#ifndef RIKKI_PATCHER_RIKKI_DATA_UI_FONT_UI_FONT_HPP
#define RIKKI_PATCHER_RIKKI_DATA_UI_FONT_UI_FONT_HPP
#include "precompiled.hpp"
#include "rikki/data/i_data.hpp"

/* ui_font.hpp
 *  Included classes:
 *      - UIFont
 */

namespace j {
struct UIFont;
}

class UI;

using font_vector_t = std::vector<j::UIFont>;
using font_iterator_t = std::function<void(nlohmann::basic_json<>& array)>;

// ======================== C L A S S ========================
// ===    UIFont
// ======================== C L A S S ========================

class UIFont final : public IData {
public:
    /**
     * @brief Get all added fonts from json.
     *
     * @return Returns vector of added fonts.
     */
    font_vector_t get_fonts();

    /**
     * @brief Remove existing fonts and add new fonts.
     * <br> Note: This just writes the font info in json. Doesn't copy the font files into game dir.
     *
     * @param [in] fonts Fonts to add.
     */
    void set_fonts(const font_vector_t& fonts);

    bool backup(const path_t& dir) final;
    bool save() final;
    bool save(const path_t& dir) final;
private:
    void iterate_elements(const font_iterator_t& callback);
    nlohmann::json& get_json_font_arr();

public:
    explicit UIFont(UI* ui);
private:
    UI* const m_pUI;
};



#endif //RIKKI_PATCHER_RIKKI_DATA_UI_FONT_UI_FONT_HPP
