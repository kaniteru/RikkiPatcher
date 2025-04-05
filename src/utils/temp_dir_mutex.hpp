#ifndef TEMP_DIR_MUTEX_HPP
#define TEMP_DIR_MUTEX_HPP
#include "precompiled.hpp"

// ======================== C L A S S ========================
// ===    TempDirMutex
// ======================== C L A S S ========================

class TempDirMutex {
public:
    bool is_locked(const path_t& dir) const;

    bool lock(const path_t& dir);
    bool unlock(const path_t& dir);

private:
    std::vector<path_t> m_dirs;
};



#endif //TEMP_DIR_MUTEX_HPP
