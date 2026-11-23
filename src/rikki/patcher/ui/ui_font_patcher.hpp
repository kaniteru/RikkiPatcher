#ifndef RIKKI_PATCHER_RIKKI_PATCHER_UI_UI_FONT_PATCHER_HPP
#define RIKKI_PATCHER_RIKKI_PATCHER_UI_UI_FONT_PATCHER_HPP
#include "precompiled.hpp"
#include "rikki/patcher/i_patcher.hpp"

/* ui_font_patcher.hpp
 *  Included classes:
 *      - UIFontPatcher
 */

class UI;

// ======================== C L A S S ========================
// ===    UIFontPatcher
// ======================== C L A S S ========================

class UIFontPatcher final : public IPatcher {
public:
    PatcherResult patch();

    PatcherResult migration();

    PatcherResult extract();

public:
    /**
     * @param [in] src Root path of a custom patch data directory.
     * @param [in] pUI ptr of UI.
     */
    UIFontPatcher(const path_t& src, const std::shared_ptr<UI>& pUI);
private:
    std::shared_ptr<UI> m_pUI;
};


#endif //RIKKI_PATCHER_RIKKI_PATCHER_UI_UI_FONT_PATCHER_HPP
