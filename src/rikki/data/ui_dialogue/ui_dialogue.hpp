#ifndef RIKKI_PATCHER_RIKKI_DATA_UI_DIALOGUE_UI_DIALOGUE_HPP
#define RIKKI_PATCHER_RIKKI_DATA_UI_DIALOGUE_UI_DIALOGUE_HPP
#include "precompiled.hpp"
#include "rikki/data/i_data.hpp"
#include "rikki/data/dialogue/i_dialogue.hpp"

/* ui_dialogue.hpp
 *  Included classes:
 *      - UIDialogue
 */

class UI;

// ======================== C L A S S ========================
// ===    UIDialogue
// ======================== C L A S S ========================

class UIDialogue final : public IData, public IDialogue {
public:
    bool backup(const path_t& dir) final;

    bool save() final;

    bool save(const path_t& path) final;
private:
    void iterate_elements(const dialogue_iterate_t& callback) final;

public:
    /**
     * @param [in] pUI The loaded UI ptr.
     * @param [in] pKey Target UIDialogue key.
     *
     * @code
     * UI ui(...);
     * UIDialogue dia(&ui, UIDialogueKey::...);
     *
     * if (dia.is_valid()) { ... }
     * @endcode
     */
    explicit UIDialogue(UI* pUI, const char* pKey);
private:
    UI* const m_pUI;               /* Loaded UI ptr */
    const char* const m_pKey; /* Target UIDialogue key */
};


#endif //RIKKI_PATCHER_RIKKI_DATA_UI_DIALOGUE_UI_DIALOGUE_HPP
