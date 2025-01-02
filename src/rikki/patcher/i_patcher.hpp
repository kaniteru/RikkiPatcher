#ifndef RIKKI_PATCHER_RIKKI_PATCHER_I_PATCHER_HPP
#define RIKKI_PATCHER_RIKKI_PATCHER_I_PATCHER_HPP
#include "precompiled.hpp"

/* i_patcher.hpp
 *  Included classes:
 *      - IPatcher
 *
 *   Included structs:
 *      - PatcherResult
 */

// ======================== C L A S S ========================
// ===    PatcherResult
// ======================== C L A S S ========================

struct PatcherResult {
    size_t m_total;   /* Total count */
    size_t m_ok;       /* OK count */
    size_t m_failed;  /* Failed count */
    size_t m_passed; /* Passed count */

    PatcherResult& operator+=(const PatcherResult&);
    bool operator==(const PatcherResult&) const;
};

// ======================== C L A S S ========================
// ===    IPatcher
// ======================== C L A S S ========================

class IPatcher {
public:
    /**
     * @brief Check is patcher available.
     *
     * @return Returns true is patcher available.
     */
    bool is_available() const;

    virtual PatcherResult patch() = 0;
    virtual PatcherResult migration() = 0;
    virtual PatcherResult generate_migration_info() = 0;

public:
    /**
     * @brief Initializing patcher.
     * <br>m_dir is point the root path of custom patch data.
     * 
     * @param [in] dir Root path of custom patch data.
     */
    explicit IPatcher(const path_t& dir);
    virtual ~IPatcher() = default;
protected:
    bool m_isAvailable;         /* Is patcher available? */
    const path_t m_dir;        /* Root path of custom patch data. */
    const path_t m_migrDir; /* Root path of custom patch migration data */
};


#endif //RIKKI_PATCHER_RIKKI_PATCHER_I_PATCHER_HPP
