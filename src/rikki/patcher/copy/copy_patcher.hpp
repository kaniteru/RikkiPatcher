#ifndef RIKKI_PATCHER_RIKKI_PATCHER_COPY_PATCHER_HPP
#define RIKKI_PATCHER_RIKKI_PATCHER_COPY_PATCHER_HPP
#include "precompiled.hpp"
#include "rikki/patcher/i_patcher.hpp"

/* copy_patcher.hpp
 *  Included classes:
 *      - CopyPatcher
 */

// ======================== C L A S S ========================
// ===    CopyPatcher
// ======================== C L A S S ========================

class CopyPatcher final : public IPatcher {
public:
    PatcherResult patch() final;

    PatcherResult migration() final;

    PatcherResult generate_migration_info() final;

public:
    explicit CopyPatcher(const path_t& dir);
private:
    const path_t m_db;

public:
    static constexpr auto FOLDER_BASE = "copy";
    static constexpr auto FILE_NAME = "copy.json";
};


#endif //RIKKI_PATCHER_RIKKI_PATCHER_COPY_PATCHER_HPP
