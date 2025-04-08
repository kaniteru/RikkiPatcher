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
    explicit IUIDialoguePatcher(std::shared_ptr<UI> pUI);
protected:
    std::shared_ptr<UI> m_pUI;
};

// ======================== C L A S S ========================
// ===    UIDialoguePatcher
// ======================== C L A S S ========================

class UIDialoguePatcher final : public IPatcher, IUIDialoguePatcher {
public:
    PatcherResult patch() final;

    PatcherResult migration() final;

    PatcherResult extract() final;
private:
    static PatcherResult extract(const path_t& dir, std::shared_ptr<UI> pUI);

public:
    /**
     * @param [in] src Root path of custom patch data directory.
     * @param [in] pUI ptr of UI.
     */
    UIDialoguePatcher(const path_t& src, std::shared_ptr<UI> pUI);
private:
    const path_t m_db;         /* Path of ui dialogue-dialogues patch folder */
    const path_t m_migrDB; /* Patch of ui dialogue-dialogues migration folder */
};

// ======================== C L A S S ========================
// ===    UIChoicePatcher
// ======================== C L A S S ========================

class UIChoicePatcher final : public IPatcher, IUIDialoguePatcher {
public:
    PatcherResult patch() final;

    PatcherResult migration() final;

    PatcherResult extract() final;
private:
    static PatcherResult extract(const path_t& src, std::shared_ptr<UI> pUI);

public:
    /**
     * @param [in] src Root path of custom patch data directory.
     * @param [in] pUI ptr of UI.
     */
    UIChoicePatcher(const path_t& src, std::shared_ptr<UI> pUI);
private:
    const path_t m_db;         /* Path of ui dialogue-choices patch folder */
    const path_t m_migrDB; /* Patch of ui dialogue-choices migration folder */
};


#endif //RIKKI_PATCHER_RIKKI_PATCHER_UI_UI_DIALOGUE_PATCHER_HPP
