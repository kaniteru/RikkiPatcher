#ifndef RIKKI_PATCHER_RIKKI_EXTRACTOR_UI_UI_DIALOGUE_EXTRACTOR_HPP
#define RIKKI_PATCHER_RIKKI_EXTRACTOR_UI_UI_DIALOGUE_EXTRACTOR_HPP
#include "precompiled.hpp"
#include "rikki/extractor/i_extractor.hpp"

/* ui_dialogue_extractor.hpp
 *  Included classes:
 *      - UIDialogueExtractor
 */

class UI;

// ======================== C L A S S ========================
// ===    UIDialogueExtractor
// ======================== C L A S S ========================

class UIDialogueExtractor final : public IExtractor {
public:
    size_t extract() final;

public:
    /**
     * @param [in] dst Target root folder of custom patch data
     * @param [in] pUI Loaded UI ptr.
     */
    UIDialogueExtractor(const path_t& dst, UI* pUI);
private:
    const path_t m_dbDia;  /* The folder of ui-dialogue - dialogues data */
    const path_t m_dbCho; /* The folder of ui-dialogue - choices data */
    UI* const m_pUI;         /* Loaded UI ptr */
};


#endif //RIKKI_PATCHER_RIKKI_EXTRACTOR_UI_UI_DIALOGUE_EXTRACTOR_HPP
