#ifndef RIKKI_PATCHER_RIKKI_PATCHER_UI_UI_DIALOGUE_PATCHER_HPP
#define RIKKI_PATCHER_RIKKI_PATCHER_UI_UI_DIALOGUE_PATCHER_HPP
#include "precompiled.hpp"
#include "rikki/data/dialogue/dialogue_json.hpp"
#include "rikki/data/dialogue/i_dialogue.hpp"
#include "rikki/patcher/i_patcher.hpp"

class UI;

/* ui_dialogue_patcher.hpp
 *  Included classes:
 *      - UIDialoguePatcher
 *      - UIChoicePatcher
 */

// ======================== C L A S S ========================
// ===    IUIDialoguePatcher
// ======================== C L A S S ========================

class IUIDialoguePatcher {
public:
    explicit IUIDialoguePatcher(UI* pUI);
protected:
    UI* const m_pUI;
};

// ======================== C L A S S ========================
// ===    UIDialoguePatcher
// ======================== C L A S S ========================

class UIDialoguePatcher final : public IPatcher, IUIDialoguePatcher {
public:
    virtual PatcherResult patch() override;

    virtual PatcherResult migration() override;

    virtual PatcherResult generate_migration_info() override;

public:
    UIDialoguePatcher(const path_t& src, UI* pUI);
private:
    const path_t m_db;         /* Path of ui dialogue-dialogues patch folder */
    const path_t m_migrDB; /* Patch of ui dialogue-dialogues migration folder */
};

// ======================== C L A S S ========================
// ===    UIChoicePatcher
// ======================== C L A S S ========================

class UIChoicePatcher final : public IPatcher, IUIDialoguePatcher {
public:
    virtual PatcherResult patch() override;

    virtual PatcherResult migration() override;

    virtual PatcherResult generate_migration_info() override;

public:
    UIChoicePatcher(const path_t& src, UI* pUI);
private:
    const path_t m_db;         /* Path of ui dialogue-choices patch folder */
    const path_t m_migrDB; /* Patch of ui dialogue-choices migration folder */
};


#endif //RIKKI_PATCHER_RIKKI_PATCHER_UI_UI_DIALOGUE_PATCHER_HPP
