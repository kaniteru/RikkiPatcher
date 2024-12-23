#include "dir_mgr.hpp"

const path_t& DirMgr::get(eDir type) {
    return m_dirs[type];
}

DirMgr::DirMgr(const path_t gmDir) {
    auto add = [this](eDir e, const std::filesystem::path& d) {
        m_dirs[e] = d;
    };

    auto add_dir = [this](eDir e, eDir parent, const char* s) {
        const auto dir = path_t(m_dirs[parent]).append(s);
        std::filesystem::create_directories(dir);
        m_dirs[e] = dir;
    };

    add(DIR_PROJ_BASE, std::filesystem::current_path());
    add(DIR_PROJ_TEMP, std::filesystem::current_path().append("temp"));
    add_dir(DIR_PROJ_DATA_EXTRACED, DIR_PROJ_BASE, "extracted");
    add(DIR_PROJ_EXE_7ZIP, std::filesystem::current_path().append("7zip").append("7za.exe"));

    add(DIR_GAME_BASE, gmDir);

    // todo: improve
    const auto json = path_t(gmDir).append("asset").append("json");
    add(DIR_GAME_JSON_DIALOGUES, path_t(json).append("server").append("scene"));
    add(DIR_GAME_JSON_STARTUP, path_t(json).append("startup.json"));
}
