#ifndef RIKKI_PATCHER_RIKKI_PATCHER_DIALOGUE_PATCHER_HPP
#define RIKKI_PATCHER_RIKKI_PATCHER_DIALOGUE_PATCHER_HPP
#include "precompiled.hpp"
#include "i_patcher.hpp"

/* dialogue_patcher.hpp
 *  Included classes:
 *      - DialoguePatcher
 *      - ChoicePatcher
 */

// ======================== C L A S S ========================
// ===    DialoguePatcher
// ======================== C L A S S ========================

class DialoguePatcher : public IPatcher {
public:
    /**
     * @brief Do custom patch into game data.
     *
     * @return Returns patched files count.
     */
    size_t patch() final;

    /**
     * @brief Migrate custom data using game data.
     *             Game data must be unmodified.
     *
     * @return Returns true if migrated successfully.
     */
    bool migration() final;

    /**
     * @brief Generate migration info data.
     *             This data will be used to migrate custom patch data to match the updated game in the future.
     *             Game data must be unmodified.
     *
     * @return
     */
    bool generate_migration_info() final;

public:
    /**
     * @brief Initialize using custom data directory.
     *
     * @param [in] src Custom data directory root path.
     */
    explicit DialoguePatcher(const path_t& src);
private:
    path_t m_database; /* Patch data folder of dialogue data files. */
    path_t m_migrDB;    /* Migration folder of dialogue data files */

    constexpr static auto FOLDER_BASE = "dialogues";
};

// ======================== C L A S S ========================
// ===    ChoicePatcher
// ======================== C L A S S ========================

class ChoicePatcher : public IPatcher {
public:
    /**
     * @brief Do custom patch into game data.
     *
     * @return Returns patched files count.
     */
    size_t patch() final;

    /**
     * @brief Migrate custom data using game data.
     *             Game data must be unmodified.
     *
     * @return Returns true if migrated successfully.
     */
    bool migration() final;

    /**
     * @brief Generate migration info data.
     *             This data will be used to migrate custom patch data to match the updated game in the future.
     *             Game data must be unmodified.
     *
     * @return
     */
    bool generate_migration_info() final;

public:
    /**
     * @brief Initialize using custom data directory.
     *
     * @param [in] src Custom data directory root path.
     */
    explicit ChoicePatcher(const path_t& src);
private:
    path_t m_database; /* Patch data folder of Choice data files */
    path_t m_migrDB;    /* Migration folder of choice data files */

    constexpr static auto FOLDER_BASE = "choices";
};


#endif //RIKKI_PATCHER_RIKKI_PATCHER_DIALOGUE_PATCHER_HPP
