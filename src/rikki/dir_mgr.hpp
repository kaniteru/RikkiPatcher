#ifndef RIKKI_PATCHER_RIKKI_DIR_MGR_HPP
#define RIKKI_PATCHER_RIKKI_DIR_MGR_HPP
#include "precompiled.hpp"

enum eDir {
    DIR_PROJ_BASE,
    DIR_PROJ_DATA,
    DIR_PROJ_DATA_BACKUP,
    DIR_PROJ_DATA_EXTRACED,

    DIR_GAME_BASE,
    DIR_GAME_JSON_DIALOGUES
};

class DirMgr {
public:
    const path_t& get(eDir type);

public:
    explicit DirMgr(const path_t gmDir);
private:
    std::unordered_map<eDir, path_t> m_dirs;
};


#endif //RIKKI_PATCHER_RIKKI_DIR_MGR_HPP
