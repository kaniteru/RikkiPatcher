#include "i_patcher.hpp"

bool IRikkiPatcher::is_available() const {
    return m_isAvailable;
}

IRikkiPatcher::IRikkiPatcher(const path_t& dir) :
    m_dir(dir),
    m_isAvailable(false) { }

IPatcher::IPatcher(const path_t& dir) :
    IRikkiPatcher(dir),
    m_migrDir(path_t(dir).append(FOLDER_MIGRATE)) { }
