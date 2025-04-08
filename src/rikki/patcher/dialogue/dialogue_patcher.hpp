#ifndef RIKKI_PATCHER_RIKKI_PATCHER_DIALOGUE_PATCHER_HPP
#define RIKKI_PATCHER_RIKKI_PATCHER_DIALOGUE_PATCHER_HPP
#include "precompiled.hpp"
#include "rikki/patcher/i_patcher.hpp"

/* dialogue_patcher.hpp
 *  Included classes:
 *      - DialoguePatcher
 *      - ChoicePatcher
 */

// ======================== C L A S S ========================
// ===    DialoguePatcher
// ======================== C L A S S ========================

class DialoguePatcher final : public IPatcher {
public:
    /**
     * @brief Do custom patch into game data.
     *
     * @return Returns patched files count.
     */
    PatcherResult patch() final;

    /**
     * @brief Migrate custom data using game data. <br>
     * Game data must be unmodified.
     *
     * @return Returns true if migrated successfully.
     */
    PatcherResult migration() final;

    /**
     * @brief
     * @return
     */
    PatcherResult extract() final;
private:
    /**
     * @param [in] path Directory of dialogue data files.
     * @return Returns patch result.
     */
    static PatcherResult extract(const path_t& path);

public:
    /**
     * @brief Initialize using custom patch data directory.
     *
     * @param [in] src Root path of custom patch data directory.
     */
    explicit DialoguePatcher(const path_t& src);
private:
    const path_t m_db;        /* Patch data folder of dialogue data files. */
    const path_t m_migrDB; /* Migration folder of dialogue data files */
};

// ======================== C L A S S ========================
// ===    ChoicePatcher
// ======================== C L A S S ========================

class ChoicePatcher final : public IPatcher {
public:
    /**
     * @brief Do custom patch into game data.
     *
     * @return Returns patched files count.
     */
    PatcherResult patch() final;

    /**
     * @brief Migrate custom data using game data. <br>
     * Game data must be unmodified.
     *
     * @return Returns true if migrated successfully.
     */
    PatcherResult migration() final;

    PatcherResult extract() final;

    static PatcherResult extract(const path_t& path);

public:
    /**
     * @brief Initialize using custom data directory.
     *
     * @param [in] src Custom data directory root path.
     */
    explicit ChoicePatcher(const path_t& src);
private:
    const path_t m_db;        /* Patch data folder of Choice data files */
    const path_t m_migrDB; /* Migration folder of choice data files */
};


#endif //RIKKI_PATCHER_RIKKI_PATCHER_DIALOGUE_PATCHER_HPP
