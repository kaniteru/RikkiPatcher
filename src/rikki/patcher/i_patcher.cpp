#include "i_patcher.hpp"

bool IPatcher::is_available() const {
    return m_isAvailable;
}

IPatcher::IPatcher(const path_t& dir) :
                                      m_dir(dir),
                                      m_migraDir(path_t(dir).append(FOLDER_MIGRATE)),
                                      m_isAvailable(false) { }
