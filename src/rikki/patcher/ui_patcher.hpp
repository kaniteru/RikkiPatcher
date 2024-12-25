#ifndef RIKKI_PATCHER_RIKKI_PATCHER_UI_PATCHER_HPP
#define RIKKI_PATCHER_RIKKI_PATCHER_UI_PATCHER_HPP
#include "precompiled.hpp"
#include "i_patcher.hpp"

/* ui_patcher.hpp
 *  Included classes:
 *      - UITextPatcher
 */

// ======================== C L A S S ========================
// ===    UITextPatcher
// ======================== C L A S S ========================

class UITextPatcher final : public IPatcher {
public:
    /**
     * @brief Do custom patch into game data.
     *
     * @return Returns patched data count.
     */
    PatcherResult patch() final;

    /**
     * @brief Migrate custom data using data data.
     *              Game data must be unmodified.
     *
     * @return Returns true if migrated successfully.
     */
    PatcherResult migration() final;

    /**
     * @brief Generate migration info data.
     *              This data will be used to migrate custom patch data to match the updated game of features.
     *              Game data must be unmodified.
     *
     * @return Returns true if generated migration info successfully.
     */
    PatcherResult generate_migration_info() final;

public:
    /**
     * @brief Init using custom patch data directory.
     *
     * @param [in] src Root path of custom patch data directory.
     */
    explicit UITextPatcher(const path_t& src);
private:
    path_t m_db;        /* Patch data folder of ui-text data files. */
    path_t m_migrDB; /* Migration folder of ui-text data files */
};


#endif //RIKKI_PATCHER_RIKKI_PATCHER_UI_PATCHER_HPP
