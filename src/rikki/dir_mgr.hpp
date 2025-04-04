#ifndef RIKKI_PATCHER_RIKKI_DIR_MGR_HPP
#define RIKKI_PATCHER_RIKKI_DIR_MGR_HPP
#include "precompiled.hpp"

/* dir_mgr.hpp
 *  Included classes:
 *      - DirMgr
 */

// ======================== C L A S S ========================
// ===    DirMgr
// ======================== C L A S S ========================

enum eDir {
    DIR_PROJ_BASE,
    DIR_PROJ_TEMP,

    DIR_PROJ_DATA_EXTRACED,

    DIR_PROJ_EXE_7ZIP,

    DIR_GAME_BASE,
    DIR_GAME_FONTS,
    DIR_GAME_JSON_STARTUP,
    DIR_GAME_JSON_DIALOGUES
};

/**
 * @brief Used get a dir path.
 */
class DirMgr {
public:
    /**
     * @brief Get a target path.
     *
     * @param [in] type Target type.
     * @return Returns target path.
     *
     * @code
     * DirMgr dirMgr(...);
     * eDir dirType = ...;
     * auto path = dirMgr.get(dirType);
     * @endcode
     */
    const path_t& get(eDir type);

public:
    /**
     * @brief Initialize using game directory.
     *
     * @param [in] gmDir Game directory path.
     */
    explicit DirMgr(const path_t& gmDir);
private:
    std::unordered_map<eDir, path_t> m_dirs;
};


#endif //RIKKI_PATCHER_RIKKI_DIR_MGR_HPP
