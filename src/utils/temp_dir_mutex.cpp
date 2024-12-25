#include "temp_dir_mutex.hpp"
#include "rikki/dir_mgr.hpp"
#include "utils/instance_factory.hpp"

bool TempDirMutex::is_locked(const path_t& dir) const {
    return std::ranges::find(m_dirs, dir) != m_dirs.end();
}

bool TempDirMutex::lock(const path_t& dir) {
    if (this->is_locked(dir)) {
        return false;
    }

    std::filesystem::create_directories(path_t(INSTFAC(DirMgr)->get(DIR_PROJ_TEMP)) /= dir);
    m_dirs.emplace_back(dir);
    return true;
}

bool TempDirMutex::unlock(const path_t& dir) {
    if (!this->is_locked(dir)) {
        return false;
    }

    std::filesystem::remove_all(path_t(INSTFAC(DirMgr)->get(DIR_PROJ_TEMP)) /= dir);
    m_dirs.erase(std::ranges::find(m_dirs, dir));
    return true;
}
