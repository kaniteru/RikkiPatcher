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

class UIFontPatcher : public IPatcher {
public:
    PatcherResult patch() final;
    PatcherResult migration() final;
    PatcherResult generate_migration_info() final;

public:
    UIFontPatcher(const path_t& src, UI* pUI);
private:
    UI* const m_pUI;
};


#endif //RIKKI_PATCHER_RIKKI_PATCHER_UI_UI_FONT_PATCHER_HPP
