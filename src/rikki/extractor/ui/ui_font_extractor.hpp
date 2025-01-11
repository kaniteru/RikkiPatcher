#ifndef RIKKI_PATCHER_RIKKI_EXTRACTOR_UI_UI_FONT_EXTRACTOR_HPP
#define RIKKI_PATCHER_RIKKI_EXTRACTOR_UI_UI_FONT_EXTRACTOR_HPP
#include "precompiled.hpp"
#include "rikki/extractor/i_extractor.hpp"

/* ui_font_extractor.hpp
 *  Included classes:
 *      - UIFontExtractor
 */

class UI;

// ======================== C L A S S ========================
// ===    UIFontExtractor
// ======================== C L A S S ========================

class UIFontExtractor final : public IExtractor {
public:
    size_t extract() final;

public:
    /**
     * @param [in] dst Root path of custom patch data.
     * @param [in] pUI Ptr of loaded UI.
     */
    UIFontExtractor(const path_t& dst, UI* pUI);
private:
    UI* const m_pUI; /* Ptr of UI */
};


#endif //RIKKI_PATCHER_RIKKI_EXTRACTOR_UI_UI_FONT_EXTRACTOR_HPP
