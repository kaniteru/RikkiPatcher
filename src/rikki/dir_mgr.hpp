#ifndef RIKKI_PATCHER_RIKKI_DIR_MGR_HPP
#define RIKKI_PATCHER_RIKKI_DIR_MGR_HPP
#include "precompiled.hpp"

enum eDir {
    DIR_PROJ_BASE,
    DIR_PROJ_DATA,
    DIR_PROJ_DATA_BACKUP,
    DIR_PROJ_DATA_LANGUAGES,
    DIR_PROJ_DATA_EXTRACED,

    DIR_GAME_BASE,
    DIR_GAME_JSON_DIALOGUES
};

/**
 * @brief Using get directory path.
 */
class DirMgr {
public:
    /**
     * @brief Get target path.
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
    explicit DirMgr(const path_t gmDir);
private:
    std::unordered_map<eDir, path_t> m_dirs;
};


#endif //RIKKI_PATCHER_RIKKI_DIR_MGR_HPP
